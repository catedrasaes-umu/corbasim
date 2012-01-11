// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective_fwd.hpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * CORBASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORBASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORBASIM_CORE_REFLECTIVE_FWD_HPP
#define CORBASIM_CORE_REFLECTIVE_FWD_HPP

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <corbasim/adapted.hpp>
#include <corbasim/event.hpp>
#include <corbasim/core/inserter.hpp>

namespace corbasim 
{
namespace core 
{

struct holder;

struct holder_impl_base {};

typedef boost::shared_ptr< holder_impl_base > holder_impl_ptr;

template< typename T >
struct holder_ref_impl;

struct holder
{
    holder()
    {
    }

    /**
     * @brief Assumes its shared ownership.
     *
     * @param impl
     */
    holder(holder_impl_base * impl) :
        m_impl(holder_impl_ptr(impl))
    {
    }

    holder(const holder& o) :
        m_impl(o.m_impl)
    {
    }

    holder& operator=(const holder& o)
    {
        m_impl = o.m_impl;

        return *this;
    }

    template< typename Value >
    Value to_value() const
    {
        typedef holder_ref_impl< Value > value_impl;

        value_impl const * p = reinterpret_cast< value_impl const * >(
                m_impl.get());

        return p->t_;
    }
    
    holder_impl_ptr m_impl;
};

template< typename T >
struct holder_ref_impl : public holder_impl_base
{
    typedef T value_type;

    T * aux;
    T& t_;

    holder_ref_impl(T& t) : 
        aux(NULL), t_(t)
    {
    }

    // String sequence case
    holder_ref_impl(const T& t) : 
        aux(new T(t)), t_(*aux)
    {
    }

    ~holder_ref_impl()
    {
        delete aux;
    }
};

template < typename T >
holder_impl_base * create_holder(T& t)
{
    return new holder_ref_impl< T >(t);
}

template < typename T >
holder_impl_base * create_holder(const T& t)
{
    return new holder_ref_impl< T >(t);
}

// And some other special cases for holders...

enum reflective_type
{
    TYPE_INVALID,
    TYPE_CHAR,
    TYPE_OCTET,
    TYPE_BOOL,
    TYPE_ENUM,
    TYPE_SHORT,
    TYPE_USHORT,
    TYPE_LONG,
    TYPE_ULONG,
    TYPE_LONGLONG,
    TYPE_ULONGLONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_WSTRING,
    TYPE_OBJREF,
    TYPE_STRUCT,
    TYPE_ARRAY,
    TYPE_UNION,
    TYPE_SEQUENCE
};

struct reflective_base
{
    virtual ~reflective_base();

    // static information
    // virtual tag_t get_tag() const = 0;

    reflective_base const * get_parent() const;

    virtual unsigned int get_children_count() const;
    virtual const char * get_child_name(unsigned int idx) const;
    virtual reflective_base const * get_child(unsigned int idx) const;

    virtual bool is_repeated() const;
    virtual bool is_variable_length() const;
    virtual bool is_primitive() const;

    virtual reflective_type get_type() const;

    // Requires is_repeated
    virtual reflective_base const * get_slice() const;

    // dynamic information
    /*
    virtual unsigned int get_length(holder const& value) const;
    virtual void set_length(holder& value) const;
     */

    virtual holder get_child_value(holder& value, 
        unsigned int idx) const;

    /*
    virtual holder get_child_value(holder_base const& value, 
        unsigned int idx) const;

    virtual std::string to_string() const;
     */

protected:
    reflective_base(reflective_base const * parent = NULL);

    reflective_base const * m_parent;
};

typedef boost::shared_ptr< reflective_base > reflective_ptr;

template< typename T >
struct reflective;

// Implementation

namespace detail 
{

template< typename T >
struct bool_reflective : public reflective_base
{
    bool_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }
    
    bool is_primitive() const { return true; }

    reflective_type get_type() const
    {
        return TYPE_BOOL;
    }
};

template< typename T >
struct primitive_reflective : public reflective_base
{
    primitive_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }

    bool is_primitive() const { return true; }
};

template< typename T >
struct array_reflective : public reflective_base
{
    typedef typename boost::remove_bounds < T >::type slice_t;
    typedef reflective < slice_t > slice_reflective_t;

    static const size_t size = sizeof(T) / sizeof(slice_t);

    array_reflective(reflective_base const * parent) :
        reflective_base(parent), m_slice(this)
    {
    }

    bool is_repeated() const { return true; }

    reflective_base const * get_slice() const
    {
        return &m_slice;
    }

    reflective_type get_type() const
    {
        return TYPE_ARRAY;
    }

    // Dynamic information
    holder get_child_value(holder& value, 
        unsigned int idx) const
    {
        typedef holder_ref_impl< T > parent_impl;

        parent_impl * p = reinterpret_cast< parent_impl * >(
                value.m_impl.get());

        return holder(create_holder(p->t_[idx]));
    }

    slice_reflective_t m_slice;
};

template< typename T >
struct string_reflective : public reflective_base
{
    string_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }

    bool is_variable_length() const { return true; }
    bool is_primitive() const       { return true; }

    reflective_type get_type() const
    {
        return TYPE_STRING;
    }
};

template< typename T >
struct sequence_reflective : public reflective_base
{
    typedef typename adapted::is_corbaseq < T >::slice_type slice_t;
    typedef reflective < slice_t > slice_reflective_t;

    sequence_reflective(reflective_base const * parent) :
        reflective_base(parent), m_slice(this)
    {
    }

    bool is_repeated() const        { return true; }
    bool is_variable_length() const { return true; }
    
    reflective_type get_type() const
    {
        return TYPE_SEQUENCE;
    }

    reflective_base const * get_slice() const
    {
        return &m_slice;
    }

    // Dynamic information
    holder get_child_value(holder& value, 
        unsigned int idx) const
    {
        typedef holder_ref_impl< T > parent_impl;

        parent_impl * p = reinterpret_cast< parent_impl * >(
                value.m_impl.get());

        return holder(create_holder(p->t_[idx]));
    }

    slice_reflective_t m_slice;
};

typedef std::vector< reflective_ptr > reflective_children;

struct accessor_base
{
    virtual holder get(holder& parent) const = 0;
    virtual ~accessor_base() {}
};

typedef boost::shared_ptr< accessor_base > accessor_ptr;

template< typename S, typename N >
struct accessor : public accessor_base
{
    holder get(holder& parent) const
    {
        typedef typename cs_mpl::type_of_member< S, N >::type current_t;
        typedef holder_ref_impl< S > parent_impl;

        parent_impl * p = reinterpret_cast< parent_impl * >(
                parent.m_impl.get());

        return holder(create_holder(boost::fusion::at < N >(p->t_)));
    }
};

template < typename S, typename Reflective >
struct create_iterator
{
    Reflective * m_this;

    create_iterator(Reflective * _this) : m_this(_this)
    {}

    template < typename N >
    void operator()(N const& nn)
    {
        // Tipo del campo actual
        typedef typename cs_mpl::type_of_member< S, N >::type current_t;

        // Tipo que contiene el nombre del campo actual
        typedef cs_mpl::name_of_member< S, N > name_t;

        typedef reflective< current_t > reflective_t;

        reflective_ptr ptr_(new reflective_t(m_this));
        accessor_ptr ac_(new accessor< S, N >());

        m_this->m_children.push_back(ptr_);
        m_this->m_child_names.push_back(name_t::call());
        m_this->m_accessors.push_back(ac_);
    }
};

template< typename T >
struct struct_reflective : public reflective_base
{
    static const std::size_t members_count = 
        boost::fusion::result_of::size< T >::value;
    typedef boost::mpl::range_c< size_t, 0, members_count > 
        members_range_t;

    struct_reflective(reflective_base const * parent = NULL) :
        reflective_base(parent)
    {
        // Reserve
        m_children.reserve(members_count);
        m_child_names.reserve(members_count);
        m_accessors.reserve(members_count);

        // Iterate
        create_iterator< T, struct_reflective > it(this);
        boost::mpl::for_each< members_range_t >(it);
    }

    unsigned int get_children_count() const 
    { 
        return members_count;
    }

    const char * get_child_name(unsigned int idx) const 
    { 
        return m_child_names[idx];
    }
    
    reflective_base const * get_child(unsigned int idx) const
    {
        return m_children[idx].get();
    }

    reflective_type get_type() const
    {
        return TYPE_STRUCT;
    }

    // Dynamic information
    holder get_child_value(holder& value, 
        unsigned int idx) const
    {
        return m_accessors[idx]->get(value);
    }

    static inline struct_reflective const * get_instance()
    {
        static boost::shared_ptr< struct_reflective > _instance(
                new struct_reflective);
        return _instance.get();
    }

    // Data
    reflective_children m_children;
    std::vector< const char * > m_child_names;
    std::vector< accessor_ptr > m_accessors;
};

template< typename T >
struct union_reflective : public reflective_base
{
    union_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }

    reflective_type get_type() const
    {
        return TYPE_UNION;
    }
};

template< typename T >
struct enum_reflective : public reflective_base
{
    enum_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }

    reflective_type get_type() const
    {
        return TYPE_ENUM;
    }
};

template< typename T >
struct objrefvar_reflective : public reflective_base
{
    objrefvar_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }

    reflective_type get_type() const
    {
        return TYPE_OBJREF;
    }
};

template< typename T >
struct unsupported_type : public reflective_base
{
    unsupported_type(reflective_base const * parent) :
        reflective_base(parent)
    {
    }
};

template< typename T >
struct calculate_reflective
{
    typedef typename 
        // if
        cs_mpl::eval_if_identity< cs_mpl::is_bool< T >, 
            bool_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< boost::is_arithmetic< T >, 
            primitive_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< boost::is_array< T >, 
            array_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< boost::is_enum< T >, 
            enum_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_string< T >, 
            string_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_corbaseq< T >, 
            sequence_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_union< T >, 
            union_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_struct< T >, 
            struct_reflective< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_objrefvar< T >, 
            objrefvar_reflective< T >,
        // else
            boost::mpl::identity< unsupported_type< T > >
        > > > > > > > > >::type type;
};

} // namespace detail

template < typename T >
struct reflective : public detail::calculate_reflective< T >::type
{
    typedef typename detail::calculate_reflective< T >::type base_t;

    reflective(reflective_base const * parent = NULL) : base_t(parent) {}
};

struct operation_reflective_base : 
    public virtual reflective_base
{
    virtual const char * get_name() const = 0;
    virtual tag_t get_tag() const = 0;

    virtual holder get_holder(event::request_ptr req) const = 0;

    virtual ~operation_reflective_base() {}
};

struct interface_reflective_base
{
    unsigned int operation_count() const;
    operation_reflective_base const * get_reflective_by_index(
            unsigned int idx) const;
    operation_reflective_base const * get_reflective_by_name(
            const std::string& name) const;
    operation_reflective_base const * get_reflective_by_tag(tag_t tag) const;

    virtual ~interface_reflective_base();

    // virtual const char * get_name() const = 0;
    // virtual const char * get_fqn() const = 0;

protected:

    void insert_reflective(const std::string& name,
        tag_t tag, operation_reflective_base const * reflective);

    // Data
    typedef std::vector< operation_reflective_base const * > 
        reflectives_t;
    reflectives_t m_reflectives;

    typedef std::map< std::string, operation_reflective_base const * > 
        reflectives_by_name_t;
    reflectives_by_name_t m_reflectives_by_name;

    typedef std::map< tag_t, operation_reflective_base const * > 
        reflectives_by_tag_t;
    reflectives_by_tag_t m_reflectives_by_tag;
};

template< typename Value >
struct operation_reflective : 
    public virtual operation_reflective_base,
    public detail::struct_reflective< Value >
{
    typedef event::request_impl< Value > request_t;
    typedef detail::struct_reflective< Value > base_t;

    operation_reflective()
    {
    }
    
    unsigned int get_children_count() const 
    { 
        return base_t::get_children_count();
    }

    const char * get_child_name(unsigned int idx) const 
    { 
        return base_t::get_child_name(idx);
    }
    
    reflective_base const * get_child(unsigned int idx) const
    {
        return base_t::get_child(idx);
    }

    reflective_type get_type() const
    {
        return base_t::get_type();
    }

    // Dynamic information
    holder get_child_value(holder& value, 
        unsigned int idx) const
    {
        return base_t::get_child_value(value, idx);
    }

    const char * get_name() const
    {
        return adapted::name< Value >::call();
    }

    tag_t get_tag() const
    {
        return tag< Value >::value();
    }
    
    holder get_holder(event::request_ptr req) const
    {
        request_t * r = reinterpret_cast< request_t* >(req.get());
        return create_holder(r->m_values);
    }

    static inline operation_reflective const * get_instance()
    {
        static boost::shared_ptr< operation_reflective > _instance(
                new operation_reflective);
        return _instance.get();
    }
};

template< typename Interface >
struct interface_reflective : public interface_reflective_base
{
    interface_reflective()
    {
        typedef typename  adapted::interface< Interface >::_op_list 
            operations_t;

        typedef core::impl::inserter< interface_reflective > inserter_t;
        cs_mpl::for_each_list< operations_t >(inserter_t(this));
    }

    template< typename Value >
    inline void append()
    {
        typedef operation_reflective< Value > reflective_t;
        operation_reflective_base const * f = 
            reflective_t::get_instance();

        insert_reflective(f->get_name(), f->get_tag(), f);
    }

    static inline interface_reflective const * get_instance()
    {
        static boost::shared_ptr< interface_reflective > _instance(
                new interface_reflective);
        return _instance.get();
    }
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_REFLECTIVE_FWD_HPP */


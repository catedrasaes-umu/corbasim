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

#include <boost/shared_ptr.hpp>
// #include <boost/any.hpp>
#include <corbasim/adapted.hpp>

namespace corbasim 
{
namespace core 
{

/*
struct holder_base {};

template< typename T >
struct holder : public holder_base
{
    typedef T value_type;

    T& t_;

    holder(T& t) : t_(t) {}
};
 */

struct reflective_base
{
    virtual ~reflective_base() {}

    // static information
    // virtual tag_t get_tag() const = 0;

    reflective_base const * get_parent() const { return m_parent; }

    virtual unsigned int get_children_count() const 
    { 
        return 0; 
    }

    virtual const char * get_child_name(unsigned int idx) const 
    { 
        return 0;
    }
    
    virtual reflective_base const * get_child(unsigned int idx) const
    {
        return 0;
    }

    virtual bool is_repeated() const        { return false; }
    virtual bool is_variable_length() const { return false; }
    virtual bool is_primitive() const       { return false; }

    // dynamic information
    /*
    virtual unsigned int get_length(holder_base * const value) const;
    virtual void set_length(holder_base * value) const;

    virtual holder_base * get_child_value(holder_base * value, unsigned int idx) const;
    virtual holder_base const * get_child_value(holder_base const * value, unsigned int idx) const;

    virtual void to_any(holder_base const * value, boost::any& any) const;
    virtual void from_any(const boost::any& any, holder_base * value) const;
     */

protected:
    reflective_base(reflective_base const * parent = NULL) : 
        m_parent(parent)
    {
    }

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
};

template< typename T >
struct primitive_reflective : public reflective_base
{
    primitive_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }
};

template< typename T >
struct array_reflective : public reflective_base
{
    array_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }
};

template< typename T >
struct string_reflective : public reflective_base
{
    string_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }
};

template< typename T >
struct sequence_reflective : public reflective_base
{
    sequence_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }
};

typedef std::vector< reflective_ptr > reflective_children;

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

        m_this->m_children.push_back(ptr_);
        m_this->m_child_names.push_back(name_t::call());
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

        // Iterate
        create_iterator< T, struct_reflective > it(this);
        boost::mpl::for_each< members_range_t >(it);
    }

    reflective_children m_children;
    std::vector< const char * > m_child_names;

    static inline struct_reflective const * get_instance()
    {
        static boost::shared_ptr< struct_reflective > _instance(
                new struct_reflective);
        return _instance.get();
    }
};

template< typename T >
struct union_reflective : public reflective_base
{
    union_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
    }
};

template< typename T >
struct objrefvar_reflective : public reflective_base
{
    objrefvar_reflective(reflective_base const * parent) :
        reflective_base(parent)
    {
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
        cs_mpl::eval_if< cs_mpl::is_bool< T >, bool_reflective< T >,
        // else if
        cs_mpl::eval_if< boost::is_arithmetic< T >, 
            primitive_reflective< T >,
        // else if
        cs_mpl::eval_if< boost::is_array< T >, array_reflective< T >,
        // else if
        cs_mpl::eval_if< boost::is_enum< T >, enum_reflective< T >,
        // else if
        cs_mpl::eval_if< cs_mpl::is_string< T >, 
            string_reflective< T >,
        // else if
        cs_mpl::eval_if< adapted::is_corbaseq< T >, 
            sequence_reflective< T >,
        // else if
        cs_mpl::eval_if< adapted::is_union< T >, 
            union_reflective< T >,
        // else if
        cs_mpl::eval_if< cs_mpl::is_struct< T >, 
            struct_reflective< T >,
        // else if
        cs_mpl::eval_if< adapted::is_objrefvar< T >, 
            objrefvar_reflective< T >,
        // else
        unsupported_type< T >
        > > > > > > > > >::type type;
};

} // namespace detail

template < typename T >
struct reflective : public detail::calculate_reflective< T >::type
{
    typedef typename detail::calculate_reflective< T >::type base_t;

    reflective(reflective_base const * parent = NULL) : base_t(parent) {}
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_REFLECTIVE_FWD_HPP */


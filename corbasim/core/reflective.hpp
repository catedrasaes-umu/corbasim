// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.hpp
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

#ifndef CORBASIM_CORE_REFLECTIVE_HPP
#define CORBASIM_CORE_REFLECTIVE_HPP

#include <corbasim/core/reflective_fwd.hpp>

namespace corbasim 
{
namespace core 
{
namespace detail
{

template< typename T >
struct bool_reflective : public reflective_base
{
    bool_reflective(reflective_base const * parent, unsigned int idx);
    
    bool is_primitive() const;
    
    holder create_holder() const;

    reflective_type get_type() const;
    
    void copy(holder const& src, holder& dst) const;
};

template< typename T >
struct primitive_reflective : public reflective_base
{
    primitive_reflective(reflective_base const * parent, 
            unsigned int idx);

    bool is_primitive() const;

    reflective_type get_type() const;
    
    holder create_holder() const;

    double to_double(holder const& value) const;
    
    void copy(holder const& src, holder& dst) const;
};

template< typename T >
struct array_reflective : public reflective_base
{
    typedef typename boost::remove_bounds < T >::type slice_t;
    typedef reflective < slice_t > slice_reflective_t;

    static const size_t size = sizeof(T) / sizeof(slice_t);

    array_reflective(reflective_base const * parent, unsigned int idx);

    unsigned int get_children_count() const;

    reflective_base const * get_child(unsigned int idx) const;

    bool is_repeated() const;

    reflective_base const * get_slice() const;

    reflective_type get_type() const;

    // Dynamic information

    holder create_holder() const;

    unsigned int get_length(holder const& value) const;

    holder get_child_value(holder& value, unsigned int idx) const;

    void copy(holder const& src, holder& dst) const;

    slice_reflective_t m_slice;
};

template< typename T >
struct string_reflective : public reflective_base
{
    string_reflective(reflective_base const * parent = NULL,
            unsigned int idx = 0);

    bool is_variable_length() const;

    bool is_primitive() const;

    reflective_type get_type() const;

    holder create_holder() const;

    std::string to_string(holder const& h) const;

    void from_string(holder& h, const std::string& str) const;
    
    void copy(holder const& src, holder& dst) const;
};

template< typename T >
struct sequence_reflective : public reflective_base
{
    typedef typename adapted::is_corbaseq < T >::slice_type slice_t;
    // typedef reflective < slice_t > slice_reflective_t;

    sequence_reflective(reflective_base const * parent = NULL,
            unsigned int idx = 0);
    
    ~sequence_reflective();

    reflective_base const * get_child(unsigned int idx) const;

    bool is_repeated() const;
    bool is_variable_length() const;
    
    reflective_type get_type() const;

    reflective_base const * get_slice() const;

    // Dynamic information
    holder create_holder() const;

    unsigned int get_length(holder const& value) const;

    void set_length(holder& value, unsigned int length) const;

    holder get_child_value(holder& value, 
        unsigned int idx) const;

    void copy(holder const& src, holder& dst) const;

    reflective_base const * m_slice;
};

typedef std::vector< reflective_ptr > reflective_children;

struct accessor_base
{
    virtual holder get(holder& parent) const = 0;
    virtual void set(holder& parent, holder& value) const = 0;
    virtual ~accessor_base() {}
};

typedef boost::shared_ptr< accessor_base > accessor_ptr;

template< typename T >
struct struct_reflective : public reflective_base
{
    static const std::size_t members_count = 
        boost::fusion::result_of::size< T >::value;
    typedef boost::mpl::range_c< size_t, 0, members_count > 
        members_range_t;

    struct_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);

    unsigned int get_children_count() const;

    const char * get_child_name(unsigned int idx) const;
    
    reflective_base const * get_child(unsigned int idx) const;

    reflective_type get_type() const;

    // Dynamic information
    holder create_holder() const;

    holder get_child_value(holder& value, 
        unsigned int idx) const;

    void copy(holder const& src, holder& dst) const;

    static struct_reflective const * get_instance();

    // Data
    reflective_children m_children;
    std::vector< const char * > m_child_names;
    std::vector< accessor_ptr > m_accessors;
};

template< typename T >
struct union_reflective : public reflective_base
{
    typedef adapted::is_union< T > adapted_t;
    typedef typename adapted_t::discriminator_t discriminator_t;

    static const std::size_t members_count = 
        boost::fusion::result_of::size< T >::value;
    typedef boost::mpl::range_c< size_t, 0, members_count > 
        members_range_t;

    union_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);

    reflective_type get_type() const;

    unsigned int get_children_count() const;

    const char * get_child_name(unsigned int idx) const;
    
    reflective_base const * get_child(unsigned int idx) const;

    holder create_holder() const;

    reflective_base const * get_slice() const;

    // Devuelve el indice del hijo con valor valido.
    // 0 si no hay hijo valido.
    unsigned int get_length(holder const& value) const;

    holder get_child_value(holder& value, unsigned int idx) const;

    void set_child_value(holder& value, 
        unsigned int idx, holder& child_value) const;

    void copy(holder const& src, holder& dst) const;
  
    static union_reflective const * get_instance();
    
    reflective_children m_children;
    std::vector< const char * > m_child_names;
    std::vector< accessor_ptr > m_accessors;
};

template< typename T >
struct enum_reflective : public reflective_base
{
    typedef adapted::enumeration< T > adapted_t;

    enum_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);

    bool is_enum() const;

    reflective_type get_type() const;

    unsigned int get_children_count() const;

    const char * get_child_name(unsigned int idx) const;

    holder create_holder() const;

    void copy(holder const& src, holder& dst) const;
};

template< typename T, typename Y = T >
struct objrefvar_reflective : public objrefvar_reflective_base
{
    objrefvar_reflective(reflective_base const * parent = NULL,
            unsigned int idx = 0);

    reflective_type get_type() const;

    /**
     * @brief You can't use this method when in a sequence slice. 
     *
     * Y must be the same type than T.
     *
     * @return A new holder o a null holder.
     */
    holder create_holder() const;
    
    void copy(holder const& src, holder& dst) const;
    
    // objrefvar_reflective_base
    CORBA::Object_ptr to_object(holder const& h) const;

    void from_object(holder& h, CORBA::Object_ptr obj) const;

    // interface_reflective_base const * get_interface() const;

    reference_validator_base * create_validator() const;
};

template< typename T >
struct unsupported_type : public reflective_base
{
    unsupported_type(reflective_base const * parent = NULL, 
            unsigned int idx = 0);
};


/**
 * @brief Calculates the reflective type for a type Y based on a type T.
 *
 * @tparam T A basic CORBA type.
 * @tparam Y Must have the same basic usage than T.
 */
template< typename T, typename Y = T >
struct calculate_reflective
{
    typedef typename 
        // if
        cs_mpl::eval_if_identity< cs_mpl::is_bool< T >, 
            bool_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< boost::is_arithmetic< T >, 
            primitive_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< boost::is_array< T >, 
            array_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< boost::is_enum< T >, 
            enum_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_string< T >, 
            string_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_corbaseq< T >, 
            sequence_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_union< T >, 
            union_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_struct< T >, 
            struct_reflective< Y >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_objrefvar< T >, 
            objrefvar_reflective< T, Y >,
        // else
            boost::mpl::identity< unsupported_type< Y > >
        > > > > > > > > >::type type;
};

} // namespace detail


template < typename T, typename Y >
reflective_base * create_reflective(const T& t_, const Y& y_, 
        reflective_base const * parent, unsigned int idx)
{
    return new typename detail::calculate_reflective< T, Y >::type (parent, idx);
}

template < typename T >
struct reflective : public detail::calculate_reflective< T >::type
{
    typedef typename detail::calculate_reflective< T >::type base_t;

    reflective(reflective_base const * parent = NULL,
            unsigned int idx = 0) : base_t(parent, idx) 
    {}
};

template< typename Value >
struct operation_reflective : 
    public virtual operation_reflective_base,
    public detail::struct_reflective< Value >
{
    typedef event::request_impl< Value > request_t;
    typedef event::response_impl< Value > response_t;
    typedef detail::struct_reflective< Value > base_t;

    std::vector< direction_type > m_param_direction;

    operation_reflective();
    
    unsigned int get_children_count() const;

    const char * get_child_name(unsigned int idx) const;
    
    reflective_base const * get_child(unsigned int idx) const;

    reflective_type get_type() const;

    // Dynamic information
    holder get_child_value(holder& value, 
        unsigned int idx) const;

    void copy(holder const& src, holder& dst) const;

    const char * get_name() const;

    tag_t get_tag() const;
    
    event::request_ptr create_request() const;

    direction_type get_parameter_direction(
            unsigned int idx) const;

    holder get_holder(event::request_ptr req) const;
    holder get_holder(event::response_ptr req) const;

    static operation_reflective const * get_instance();
};

template< typename Interface >
struct interface_reflective : public interface_reflective_base
{
    interface_reflective();

    interface_caller_base * create_caller() const;

    reference_validator_base * create_validator() const;

    // Servant
    PortableServer::ServantBase * create_servant(
            request_processor * proc) const;
   
    const char * get_name() const;

    const char * get_fqn() const;

    template< typename Value >
    inline void append();

    static interface_reflective const * get_instance();
};

} // namespace core
} // namespace corbasim

#ifndef CORBASIM_NO_IMPL
#include <corbasim/core/reflective.ipp>
#endif

#endif /* CORBASIM_CORE_REFLECTIVE_HPP */


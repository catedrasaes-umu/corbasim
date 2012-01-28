// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective_primitive.ipp
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

#include "reflective.hpp"

namespace corbasim 
{
namespace core 
{

template< typename Value >
Value& holder::to_value()
{
    typedef holder_ref_impl< Value > value_impl;

    value_impl * p = reinterpret_cast< value_impl * >(
            m_impl.get());

    return p->t_;
}

template< typename T >
struct holder_ref_impl : public holder_impl_base
{
    typedef T value_type;

    T aux;
    T& t_;

    holder_ref_impl() : 
        t_(aux)
    {
    }

    holder_ref_impl(T& t) : 
        t_(t)
    {
    }

    // String sequence case
    holder_ref_impl(const T& t) : 
        aux(t), t_(aux)
    {
    }

    ~holder_ref_impl()
    {
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

namespace detail 
{

// Array reflective

template< typename T >
array_reflective< T >::array_reflective(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx), m_slice(this, 0)
{
}

template< typename T >
bool array_reflective< T >::is_repeated() const { return true; }

template< typename T >
reflective_base const * array_reflective< T >::get_slice() const
{
    return &m_slice;
}

template< typename T >
reflective_type array_reflective< T >::get_type() const
{
    return TYPE_ARRAY;
}

// Dynamic information

template< typename T >
holder array_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
unsigned int array_reflective< T >::get_length(holder const& value) const
{
    return size;
}

template< typename T >
holder array_reflective< T >::get_child_value(holder& value, 
    unsigned int idx) const
{
    typedef holder_ref_impl< T > parent_impl;

    parent_impl * p = reinterpret_cast< parent_impl * >(
            value.m_impl.get());

    return holder( ::corbasim::core::create_holder(p->t_[idx]));
}

// String reflective
template< typename T >
string_reflective< T >::string_reflective(reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool string_reflective< T >::is_variable_length() const { return true; }

template< typename T >
bool string_reflective< T >::is_primitive() const       { return true; }

template< typename T >
reflective_type string_reflective< T >::get_type() const
{
    return TYPE_STRING;
}

template< typename T >
holder string_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
std::string string_reflective< T >::to_string(holder const& value) const
{
    return std::string(const_cast< holder& >(value).to_value< T >());
}

template< typename T >
void string_reflective< T >::from_string(holder& value, const std::string& str) const
{
    value.to_value< T >() = str.c_str();
}

// Sequence reflective
template< typename T >
sequence_reflective< T >::sequence_reflective(reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx), m_slice(this, 0)
{
}

template< typename T >
bool sequence_reflective< T >::is_repeated() const        { return true; }

template< typename T >
bool sequence_reflective< T >::is_variable_length() const { return true; }

template< typename T >
reflective_type sequence_reflective< T >::get_type() const
{
    return TYPE_SEQUENCE;
}

template< typename T >
reflective_base const * sequence_reflective< T >::get_slice() const
{
    return &m_slice;
}

// Dynamic information
template< typename T >
holder sequence_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
unsigned int sequence_reflective< T >::get_length(holder const& value) const
{
    typedef holder_ref_impl< T > parent_impl;

    parent_impl const * p = reinterpret_cast< parent_impl const * >(
            value.m_impl.get());

    return p->t_.length();
}

template< typename T >
void sequence_reflective< T >::set_length(holder& value, unsigned int length)
{
    typedef holder_ref_impl< T > parent_impl;

    parent_impl const * p = reinterpret_cast< parent_impl const * >(
            value.m_impl.get());

    p->t_.length(length);
}

template< typename T >
holder sequence_reflective< T >::get_child_value(holder& value, 
    unsigned int idx) const
{
    typedef holder_ref_impl< T > parent_impl;

    parent_impl * p = reinterpret_cast< parent_impl * >(
            value.m_impl.get());

    return holder( ::corbasim::core::create_holder(p->t_[idx]));
}

// Struct reflective
template< typename S, typename N >
struct accessor : public accessor_base
{
    holder get(holder& parent) const
    {
        typedef typename cs_mpl::type_of_member< S, N >::type current_t;
        typedef holder_ref_impl< S > parent_impl;

        parent_impl * p = reinterpret_cast< parent_impl * >(
                parent.m_impl.get());

        return holder( ::corbasim::core::create_holder(
                    boost::fusion::at < N >(p->t_)));
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

        reflective_ptr ptr_(new reflective_t(m_this, N::value));
        accessor_ptr ac_(new accessor< S, N >());

        m_this->m_children.push_back(ptr_);
        m_this->m_child_names.push_back(name_t::call());
        m_this->m_accessors.push_back(ac_);
    }
};

template< typename T >
struct_reflective< T >::struct_reflective(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
    // Reserve
    m_children.reserve(members_count);
    m_child_names.reserve(members_count);
    m_accessors.reserve(members_count);

    // Iterate
    create_iterator< T, struct_reflective > it(this);
    boost::mpl::for_each< members_range_t >(it);
}

template< typename T >
unsigned int struct_reflective< T >::get_children_count() const 
{ 
    return members_count;
}

template< typename T >
const char * struct_reflective< T >::get_child_name(unsigned int idx) const 
{
    return m_child_names[idx];
}

template< typename T >
reflective_base const * struct_reflective< T >::get_child(
        unsigned int idx) const
{
    return m_children[idx].get();
}

template< typename T >
reflective_type struct_reflective< T >::get_type() const
{
    return TYPE_STRUCT;
}

// Dynamic information
template< typename T >
holder struct_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
holder struct_reflective< T >::get_child_value(holder& value, 
    unsigned int idx) const
{
    return m_accessors[idx]->get(value);
}

template< typename T >
struct_reflective< T > const * struct_reflective< T >::get_instance()
{
    static boost::shared_ptr< struct_reflective > _instance(
            new struct_reflective);
    return _instance.get();
}

// Union reflective

template< typename T >
union_reflective< T >::union_reflective(reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
reflective_type union_reflective< T >::get_type() const
{
    return TYPE_UNION;
}

template< typename T >
holder union_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

// Enum reflective
template< typename T >
enum_reflective< T >::enum_reflective(reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool enum_reflective< T >::is_enum() const
{
    return true;
}

template< typename T >
reflective_type enum_reflective< T >::get_type() const
{
    return TYPE_ENUM;
}

template< typename T >
unsigned int enum_reflective< T >::get_children_count() const
{
    return adapted_t::size;
}

template< typename T >
const char * enum_reflective< T >::get_child_name(unsigned int idx) const
{
    return adapted_t::values()[idx];
}

template< typename T >
holder enum_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

// Object reflective
template< typename T >
objrefvar_reflective< T >::objrefvar_reflective(
        reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
reflective_type objrefvar_reflective< T >::get_type() const
{
    return TYPE_OBJREF;
}

template< typename T >
holder objrefvar_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

// Unsupported type
template< typename T >
unsupported_type< T >::unsupported_type(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

// Operations
struct direction_inserter
{
    std::vector< direction_type >& m_param_direction;

    direction_inserter(std::vector< direction_type >& p) :
        m_param_direction(p)
    {
    }

    template < typename T >
    void operator()(const Arg_IN< T >& /* unused */)
    {
        m_param_direction.push_back(DIRECTION_IN);
    }

    template < typename T >
    void operator()(const Arg_OUT< T >& /* unused */)
    {
        m_param_direction.push_back(DIRECTION_OUT);
    }

    template < typename T >
    void operator()(const Arg_INOUT< T >& /* unused */)
    {
        m_param_direction.push_back(DIRECTION_INOUT);
    }
};

} // namespace detail

template < typename Value >
operation_reflective< Value >::operation_reflective()
{
    m_param_direction.reserve(get_children_count());
    detail::direction_inserter insert(m_param_direction);

    boost::mpl::for_each< typename Value::_arg_list >(insert);
}

template < typename Value >
unsigned int operation_reflective< Value >::get_children_count() const 
{ 
    return base_t::get_children_count();
}

template < typename Value >
const char * operation_reflective< Value >::get_child_name(
        unsigned int idx) const 
{ 
    return base_t::get_child_name(idx);
}

template < typename Value >
reflective_base const * operation_reflective< Value >::get_child(
        unsigned int idx) const
{
    return base_t::get_child(idx);
}

template < typename Value >
reflective_type operation_reflective< Value >::get_type() const
{
    return base_t::get_type();
}

// Dynamic information
template < typename Value >
holder operation_reflective< Value >::get_child_value(holder& value, 
    unsigned int idx) const
{
    return base_t::get_child_value(value, idx);
}

template < typename Value >
const char * operation_reflective< Value >::get_name() const
{
    return adapted::name< Value >::call();
}

template < typename Value >
tag_t operation_reflective< Value >::get_tag() const
{
    return tag< Value >::value();
}

template < typename Value >
event::request_ptr operation_reflective< Value >::create_request() const
{
    return event::request_ptr(new request_t);
}

template < typename Value >
direction_type operation_reflective< Value >::get_parameter_direction(
        unsigned int idx) const
{
    return m_param_direction[idx];
}

template < typename Value >
holder operation_reflective< Value >::get_holder(event::request_ptr req) const
{
    request_t * r = reinterpret_cast< request_t* >(req.get());
    return ::corbasim::core::create_holder(r->m_values);
}

template < typename Value >
operation_reflective< Value > const * 
operation_reflective< Value >::get_instance()
{
    static boost::shared_ptr< operation_reflective > _instance(
            new operation_reflective);
    return _instance.get();
}

// Interface

template < typename Interface >
interface_reflective< Interface >::interface_reflective()
{
    typedef typename  adapted::interface< Interface >::_op_list 
        operations_t;

    typedef core::impl::inserter< interface_reflective > inserter_t;
    cs_mpl::for_each_list< operations_t >(inserter_t(this));
}

template < typename Interface >
interface_caller_base* interface_reflective< Interface >::create_caller() const
{
    return new core::interface_caller< Interface >();
}

template < typename Interface >
reference_validator_base * interface_reflective< Interface >::create_validator() const
{
    return new reference_validator_impl< Interface >();
}

// Servant
template < typename Interface >
PortableServer::ServantBase * interface_reflective< Interface >::create_servant(
        request_processor * proc) const
{
    return new typename adapted::servant< Interface >::template 
        _type< callable >(callable(proc));
}

template < typename Interface >
const char * interface_reflective< Interface >::get_name() const
{
    return adapted::name< Interface >::call();
}

template < typename Interface >
const char * interface_reflective< Interface >::get_fqn() const
{
    return adapted::full_qualified_name< Interface >::call();
}

template< typename Interface >
template< typename Value >
inline void interface_reflective< Interface >::append()
{
    typedef operation_reflective< Value > reflective_t;
    operation_reflective_base const * f = 
        reflective_t::get_instance();

    insert_reflective(f->get_name(), f->get_tag(), f);
}

template < typename Interface >
interface_reflective< Interface > const * 
interface_reflective< Interface >::get_instance()
{
    static boost::shared_ptr< interface_reflective > _instance(
            new interface_reflective);
    return _instance.get();
}

} // namespace core
} // namespace corbasim


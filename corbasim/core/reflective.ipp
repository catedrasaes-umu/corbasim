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
#ifndef CORBASIM_CORE_REFLECTIVE_IPP
#define CORBASIM_CORE_REFLECTIVE_IPP

#include <corbasim/core/copy.hpp>

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

template< typename T >
void array_reflective< T >::copy(holder const& src, holder& dst) const
{
    for (unsigned i = 0; i < size; i++) 
    {
        holder child_src = get_child_value(const_cast< holder& >(src), i);
        holder child_dst = get_child_value(dst, i);
        m_slice.copy(child_src, child_dst);
    }
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
    // Note: you can not use this method for slice member 
    // of a sequence.
    return new holder_ref_impl< orbimpl::String_Manager >();
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

template< typename T >
void string_reflective< T >::copy(holder const& src, holder& dst) const
{
    dst.to_value< T >() = const_cast< holder& >(src).to_value< T >();
}

template< typename T, typename Y >
reflective_base const * create_slice_reflective(
    T t, Y y, // dummy parameters
    reflective_base const * parent, unsigned int idx)
{
    return new typename calculate_reflective< T, Y >::type(parent, idx);
}

// Sequence reflective
template< typename T >
sequence_reflective< T >::sequence_reflective(
        reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx)
{
    // Type used to calculate
    slice_t t;

    // Real one
    T y;
    y.length(1);

    m_slice = create_slice_reflective(t, y[0], this, 0);
}

template< typename T >
sequence_reflective< T >::~sequence_reflective()
{
    delete m_slice;
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
    return m_slice;
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
void sequence_reflective< T >::set_length(holder& value, 
        unsigned int length) const
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

template< typename T >
void sequence_reflective< T >::copy(holder const& src, holder& dst) const
{
    unsigned int length = get_length(src);
    set_length(dst, length);

    for (unsigned i = 0; i < length; i++) 
    {
        holder child_src = get_child_value(const_cast< holder& >(src), i);
        holder child_dst = get_child_value(dst, i);
        m_slice->copy(child_src, child_dst);
    }
}

// Struct reflective
template< typename S, typename N >
struct accessor : public accessor_base
{
    typedef typename cs_mpl::type_of_member< S, N >::type current_t;

    holder get(holder& parent) const
    {
        S& t_ = parent.to_value< S >();

        return holder( ::corbasim::core::create_holder(
                    boost::fusion::at < N >(t_)));
    }

    void set(holder& parent, holder& value) const
    {
        S& t_ = parent.to_value< S >();

        do_copy(boost::fusion::at < N >(t_),
                value.to_value<  current_t >());

        // boost::fusion::at < N >(t_) = value.to_value<  current_t >();
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

template< typename S, typename N >
struct union_accessor : public accessor_base
{
    typedef typename cs_mpl::type_of_member< S, N >::type current_t;

    holder get(holder& parent) const
    {
        S& t_ = parent.to_value< S >();

        const current_t current(boost::fusion::at < N >(t_));

        return holder( ::corbasim::core::create_holder(current));
    }

    void set(holder& parent, holder& value) const
    {
        S& t_ = parent.to_value< S >();

        boost::fusion::at < N >(t_) = value.to_value<  current_t >();
    }
};

template < typename S, typename Reflective >
struct union_create_iterator
{
    Reflective * m_this;

    union_create_iterator(Reflective * _this) : m_this(_this)
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
        accessor_ptr ac_(new union_accessor< S, N >());

        m_this->m_children.push_back(ptr_);
        m_this->m_child_names.push_back(name_t::call());
        m_this->m_accessors.push_back(ac_);
    }
};

template< typename T >
struct_reflective< T >::struct_reflective(
        reflective_base const * parent, 
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
const char * struct_reflective< T >::get_child_name(
        unsigned int idx) const 
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

template< typename T >
void struct_reflective< T >::copy(holder const& src, holder& dst) const
{
    for (unsigned i = 0; i < members_count; i++) 
    {
        holder child_src = get_child_value(
                const_cast< holder& >(src), i);

        holder child_dst = get_child_value(dst, i);

        get_child(i)->copy(child_src, child_dst);
    }
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
    // Reserve
    m_children.reserve(members_count);
    m_child_names.reserve(members_count);
    m_accessors.reserve(members_count);

    // Iterate
    union_create_iterator< T, union_reflective > it(this);
    boost::mpl::for_each< members_range_t >(it);
}

template< typename T >
unsigned int union_reflective< T >::get_children_count() const 
{ 
    return m_children.size();
}

template< typename T >
const char * union_reflective< T >::get_child_name(
        unsigned int idx) const 
{
    return m_child_names[idx];
}

template< typename T >
reflective_base const * union_reflective< T >::get_child(
        unsigned int idx) const
{
    return m_children[idx].get();
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

template< typename T >
reflective_base const * union_reflective< T >::get_slice() const
{
    return m_children[0].get();
}

template< typename T >
union_reflective< T > const * union_reflective< T >::get_instance()
{
    static boost::shared_ptr< union_reflective > _instance(
            new union_reflective);
    return _instance.get();
}

template< typename T >
holder union_reflective< T >::get_child_value(holder& value, 
    unsigned int idx) const
{
    return m_accessors[idx]->get(value);
}

template< typename T >
void union_reflective< T >::set_child_value(holder& value, 
    unsigned int idx, holder& child_value) const
{
    m_accessors[idx]->set(value, child_value);
}

template< typename T >
void union_reflective< T >::copy(holder const& src, holder& dst) const
{
    dst.to_value< T >() = const_cast< holder& >(src).to_value< T >();
}

template< typename T >
unsigned int union_reflective< T >::get_length(
        holder const& value) const
{
    T& t = const_cast< holder& >(value).to_value< T >();
    discriminator_t _d = t._d();

    for (unsigned int i = 0; i < adapted_t::size; i++) 
    {
        if (_d == adapted_t::discriminators()[i])
        {
            return adapted_t::member()[i];
        }
    }

    // TODO default

    return 0; // invalid
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

template< typename T >
void enum_reflective< T >::copy(holder const& src, holder& dst) const
{
    dst.to_value< T >() = const_cast< holder& >(src).to_value< T >();
}

template< typename Var >
struct calculate_iface
{
    typedef typename Var::_obj_type type;
};

template< >
struct calculate_iface< CORBA::Object_var >
{
    typedef CORBA::Object type;
};

// Object reflective
template< typename T, typename Y >
objrefvar_reflective< T, Y >::objrefvar_reflective(
        reflective_base const * parent,
        unsigned int idx) :
    objrefvar_reflective_base(parent, idx)
{
}

template< typename T, typename Y >
reflective_type objrefvar_reflective< T, Y >::get_type() const
{
    return TYPE_OBJREF;
}

template< typename T, typename Y >
holder objrefvar_reflective< T, Y >::create_holder() const
{
    // Just when Y == T
    return new holder_ref_impl< T >();
}

template< typename T, typename Y >
void objrefvar_reflective< T, Y >::copy(holder const& src, holder& dst) const
{
    dst.to_value< Y >() = const_cast< holder& >(src).to_value< Y >();
}

template< typename T, typename Y >
CORBA::Object_ptr objrefvar_reflective< T, Y >::to_object(holder const& h) const
{
    typedef typename calculate_iface< T >::type iface_t;

    return iface_t::_duplicate(const_cast< holder& >(h).to_value< Y >());
}

template< typename T, typename Y >
void objrefvar_reflective< T, Y >::from_object(holder& h, 
        CORBA::Object_ptr obj) const
{
    typedef typename calculate_iface< T >::type iface_t;
    
    h.to_value< Y >() = iface_t::_narrow(obj);;
}

template< typename T, typename Y>
reference_validator_base * 
objrefvar_reflective< T, Y >::create_validator() const
{
    typedef typename calculate_iface< T >::type iface_t;
    
    return new reference_validator_impl< iface_t >();
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
    if (idx >= m_param_direction.size())
        return DIRECTION_RETURN;

    return m_param_direction[idx];
}

template < typename Value >
holder operation_reflective< Value >::get_holder(event::request_ptr req) const
{
    request_t * r = reinterpret_cast< request_t* >(req.get());
    return ::corbasim::core::create_holder(r->m_values);
}

template < typename Value >
holder operation_reflective< Value >::get_holder(event::response_ptr req) const
{
    response_t * r = reinterpret_cast< response_t* >(req.get());
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
#endif /* CORBASIM_CORE_REFLECTIVE_IPP */

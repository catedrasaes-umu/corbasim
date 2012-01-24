// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.ipp
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

// Boolean
namespace corbasim 
{
namespace core 
{
namespace detail 
{

template< typename T >
bool_reflective< T >::bool_reflective(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool bool_reflective< T >::is_primitive() const { return true; }

template< typename T >
reflective_type bool_reflective< T >::get_type() const
{
    return TYPE_BOOL;
}

// Primitive

template< typename T >
primitive_reflective< T >::primitive_reflective(
        reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool primitive_reflective< T >::is_primitive() const 
{ 
    return true; 
}

template< typename T >
double primitive_reflective< T >::to_double(holder const& value) const
{
    typedef holder_ref_impl< T > impl_t;

    impl_t const * p = reinterpret_cast< impl_t const * >(
            value.m_impl.get());

    return (double) p->t_;
}

template< >
reflective_type primitive_reflective< double >::get_type() const
{
    return TYPE_DOUBLE;
}

template< >
reflective_type primitive_reflective< float >::get_type() const
{
    return TYPE_FLOAT;
}

template< >
reflective_type primitive_reflective< char >::get_type() const
{
    return TYPE_CHAR;
}

template< >
reflective_type primitive_reflective< unsigned char >::get_type() const
{
    return TYPE_OCTET;
}

template< >
reflective_type primitive_reflective< short >::get_type() const
{
    return TYPE_SHORT;
}

template< >
reflective_type primitive_reflective< unsigned short >::get_type() const
{
    return TYPE_USHORT;
}

template< >
reflective_type primitive_reflective< CORBA::ULong >::get_type() const
{
    return TYPE_ULONG;
}

template< >
reflective_type primitive_reflective< CORBA::Long >::get_type() const
{
    return TYPE_LONG;
}

template< >
reflective_type primitive_reflective< CORBA::ULongLong >::get_type() const
{
    return TYPE_ULONGLONG;
}

template< >
reflective_type primitive_reflective< CORBA::LongLong >::get_type() const
{
    return TYPE_LONGLONG;
}


} // namespace detail
} // namespace core
} // namespace corbasim


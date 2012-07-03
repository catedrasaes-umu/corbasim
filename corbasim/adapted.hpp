// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * adapted.hpp
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

#ifndef CORBASIM_ADAPTED_HPP
#define CORBASIM_ADAPTED_HPP

#include <corbasim/mpl.hpp>

namespace CORBA 
{
class TypeCode;
} // namespace CORBA

namespace corbasim 
{

/**
 * @brief Espacio de nombres con el código necesario para adaptar el código
 * generado para el uso de las distintas metafunciones.
 */
namespace adapted 
{

template< typename T >
struct is_objrefvar : public cs_mpl::false_
{
};

template< typename T >
struct is_corbaseq : public cs_mpl::false_
{
};

template< typename T >
struct is_union : public cs_mpl::false_
{
};

template< typename T >
struct is_oneway : public cs_mpl::false_
{
};

template< typename T >
struct enumeration;
/*
{
    // Error!
};
*/

template< typename T >
struct interface;
/*
{
    // Error!
};
*/

template< typename Value >
struct call;
/*
{
    // template < typename Interface >
    // static inline void invoke(Interface * ref, Value& value)
    // {
           // Error! Must be redefined.
    // }
};
*/

template< typename Value >
struct name
{
    static const char * call();
};

template< typename TypeDef >
struct full_qualified_name
{
    static const char * call();
};

template< typename TypeDef >
struct typecode
{
    static CORBA::TypeCode const * call();
};

template< typename Inteface >
struct servant;

template< typename T, unsigned int N >
struct member
{
    typedef T type;
    static const unsigned int index = N;
    typedef boost::mpl::int_< N > index_type;
}; 

template< typename M >
struct member_type
{
    typedef typename cs_mpl::type_of_member< typename M::type, 
        typename M::index_type >::type type;
};

namespace detail 
{
template< typename T >
struct is_string_slice_impl
{
    typedef typename 
        cs_mpl::eval_if< cs_mpl::is_string< 
                    typename is_corbaseq< T >::slice_type >,
                boost::mpl::identity< cs_mpl::true_ >,
                boost::mpl::identity< cs_mpl::false_ >
            >::type type;
};

template< typename T >
struct is_string_slice
{
    typedef typename cs_mpl::eval_if< is_corbaseq< T >,
                is_string_slice_impl< T >,
                boost::mpl::identity< cs_mpl::false_ >
            >::type type;
};
} // namespace detail

template< typename T >
struct is_corbaseq_string : public detail::is_string_slice< T >::type
{
};

template< class Interface, typename F >
inline typename servant< Interface >::template _type< F& >* create_servant(F& f)
{
    return new typename servant< Interface >::template _type< F& >(f);
}

} // namespace adapted
} // namespace corbasim

#endif /* CORBASIM_ADAPTED_HPP */


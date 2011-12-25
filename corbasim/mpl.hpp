// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mpl.hpp
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

#ifndef CORBASIM_MPL_HPP
#define CORBASIM_MPL_HPP

#include <boost/type_traits.hpp> // is_array, is_class, remove_bounds
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/for_each.hpp> // run-time foreach

#include <boost/fusion/mpl.hpp>
#include <boost/fusion/adapted.hpp> // BOOST_FUSION_ADAPT_STRUCT

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>

//#include <corbasim/mpl/vector.hpp>
#include <corbasim/mpl/list.hpp>
//#include <corbasim/mpl/for_each.hpp>
#include <corbasim/impl.hpp>

namespace corbasim 
{

/**
 * Tags
 */
typedef const int * tag_t;

template< typename T >
struct tag
{
    static inline tag_t value()
    {
        static const int value_ = 0;
        return &value_;
    }
};

template< typename T >
struct Arg_IN
{
    typedef T type;
};

template< typename T >
struct Arg_INOUT
{
    typedef T type;
};

template< typename T >
struct Arg_OUT
{
    typedef T type;
};

/**
 * @brief Espacio de nombres que contiene las metafunciones necesarias la
 *        implementación de los simuladores CORBASIM.
 */
namespace cs_mpl 
{

typedef boost::mpl::true_ true_;
typedef boost::mpl::false_ false_;

template< typename T >
struct is_string :
    public false_
{
};

template< >
struct is_string< orbimpl::String_Manager > : 
    public true_
{
};

template< >
struct is_string< CORBA::String_var > : 
    public true_
{
};

template< typename T >
struct is_bool :
    public false_
{
};

template< >
struct is_bool< bool > :
    public true_
{
};

template< typename T >
struct is_struct : 
    public boost::mpl::and_< 
        boost::is_class< T >,
        boost::mpl::is_sequence< T > >
{
};

template< typename Cond, typename Result, typename Else >
struct eval_if : 
    public boost::mpl::eval_if< Cond, Result, Else >
{
};

template< typename Cond, typename Result, typename Else >
struct eval_if_identity : 
    public boost::mpl::eval_if< Cond, 
        boost::mpl::identity< Result >, Else >
{
};

template< typename T, typename N >
struct type_of_member : 
    public boost::fusion::result_of::value_at< T, N >
{
};

template< typename T, typename N >
struct name_of_member :
    public boost::fusion::extension::struct_member_name < T, N::value >
{
};

template< typename T >
struct number_of_members : 
    public boost::fusion::result_of::size < T >
{
};

template< typename T >
struct is_inarg : public false_
{
};

template< typename T >
struct is_inarg< Arg_IN< T > > : public true_
{
};

template< typename T >
struct is_inarg< Arg_INOUT< T > > : public true_
{
};

} // namespace cs_mpl
} // namespace corbasim

#endif /* CORBASIM_MPL_HPP */


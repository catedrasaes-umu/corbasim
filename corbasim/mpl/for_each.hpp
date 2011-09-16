// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * for_each.hpp
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

#ifndef CORBASIM_MPL_FOR_EACH_HPP
#define CORBASIM_MPL_FOR_EACH_HPP

#include <corbasim/mpl/vector.hpp>
#include <boost/utility/value_init.hpp>

namespace corbasim 
{
namespace cs_mpl 
{

template< typename Sequence >
struct size
{
    typedef typename Sequence::size_type type;
};

namespace detail 
{
namespace iterator 
{

template < typename T >
struct Sequence;

template < typename S, typename N >
struct SequenceImpl
{
    typedef typename S::head_type head_type;
    typedef typename S::tail_type tail_type;

    template < typename Func >
    static inline void apply(Func f)
    {
        boost::value_initialized< head_type > val;
        f(boost::get(val));

        // Siguiente iteracion
        Sequence< tail_type >::apply(f);
    }
};

// Fin de la iteracion sobre estructuras.
template < typename S >
struct SequenceImpl < S, boost::mpl::int_< 0 > >
{
    template < typename Func >
    static inline void apply(Func f)
    {
        // Nada por hacer
    }
};

// Iterador sobre una estructura. Template fachada.
template < typename S >
struct Sequence: public SequenceImpl < S, typename size< S >::type >
{
};

} // namespace iterator
} // namespace detail

template < typename Sequence, typename Func >
void for_each(Func f)
{
    detail::iterator::Sequence< Sequence >::apply(f);
}

} // namespace cs_mpl
} // namespace corbasim

#endif /* CORBASIM_MPL_FOR_EACH_HPP */


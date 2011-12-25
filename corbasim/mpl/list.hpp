// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * list.hpp
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

#ifndef CORBASIM_MPL_LIST_HPP
#define CORBASIM_MPL_LIST_HPP

#include <boost/utility/value_init.hpp>

namespace corbasim 
{
namespace cs_mpl 
{

struct null_type {};

template< typename Head, typename Tail = null_type >
struct list
{
    typedef Head head_type;
    typedef Tail tail_type;
};

namespace detail 
{
namespace list_iterator 
{

template < typename S >
struct Sequence
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

template < >
struct Sequence < null_type >
{
    template < typename Func >
    static inline void apply(Func f) {}
};

} // namespace list_iterator
} // namespace detail

template < typename Sequence, typename Func >
inline void for_each_list(Func f)
{
    detail::list_iterator::Sequence< Sequence >::apply(f);
}


} // namespace cs_mpl
} // namespace corbasim

#endif /* CORBASIM_MPL_LIST_HPP */


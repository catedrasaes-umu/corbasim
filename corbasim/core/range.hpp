// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * range.hpp
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

#ifndef CORBASIM_CORE_RANGE_HPP
#define CORBASIM_CORE_RANGE_HPP

#include <limits>

namespace corbasim
{
namespace core
{
namespace detail
{

template < typename T >
struct range
{
    static inline T min()
    {
        return std::numeric_limits<T>::min();
    }
    static inline T max()
    {
        return std::numeric_limits<T>::max();
    }
};

// Float and doubles special meaning of min (minimum positive value)
// NOTE: min value implementation valid for IEEE 754 floating-point numbers
template < typename T >
struct range_float
{
    static inline T min()
    {
        return -(std::numeric_limits< T >::max());
    }
    static inline T max()
    {
        return std::numeric_limits< T >::max();
    }
};

template < >
struct range < float > : public range_float< float >
{};

template < >
struct range < double > : public range_float< double >
{};

} // namespace detail
} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_RANGE_HPP */


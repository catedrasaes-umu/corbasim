// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * vector.hpp
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

#ifndef CORBASIM_MPL_VECTOR_IMPL_HPP
#define CORBASIM_MPL_VECTOR_IMPL_HPP

#include <corbasim/core/config.hpp>

#if CORBASIM_MPL_VECTOR_MAX_SIZE <= 50
#   include <corbasim/mpl/vector50.hpp>
#elif CORBASIM_MPL_VECTOR_MAX_SIZE <= 100
#   include <corbasim/mpl/vector100.hpp>
#elif CORBASIM_MPL_VECTOR_MAX_SIZE <= 200
#   include <corbasim/mpl/vector200.hpp>
#else
#   error "You must generate a bigger vectorXXX.hpp file!"
#endif

#endif /* CORBASIM_MPL_VECTOR_IMPL_HPP */


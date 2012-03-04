// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * export.hpp
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

#ifndef CORBASIM_QWT_EXPORT_HPP
#define CORBASIM_QWT_EXPORT_HPP

#if defined(_MSC_VER)

    #if defined(corbasim_qwt_EXPORTS)
        #define CORBASIM_QWT_DECLSPEC __declspec(dllexport)
    #else
        #define CORBASIM_QWT_DECLSPEC __declspec(dllimport)
    #endif

#else
    #define CORBASIM_QWT_DECLSPEC 
#endif

#endif /* CORBASIM_QWT_EXPORT_HPP */


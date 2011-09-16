// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * macros.hpp
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

#ifndef CORBASIM_GUI_MACROS_HPP
#define CORBASIM_GUI_MACROS_HPP

#include <corbasim/gui/macros_impl.hpp>

// CORBASIM_{M = member, T = type}_{W = widget, T = tree}_...

#define CORBASIM_M_W_TYPE_AS_SERIALIZED(fqn) \
    CORBASIM_M_W_impl0(fqn, type_as_serialized) \
    /***/
#define CORBASIM_T_W_TYPE_AS_SERIALIZED(fqn) \
    CORBASIM_T_W_impl0(fqn, type_as_serialized) \
    /***/

#define CORBASIM_M_W_SPINBOX_WITH_AUTOINCREMENT(fqn) \
    CORBASIM_M_W_impl0(fqn, spinbox_with_autoincrement) \
    /***/
#define CORBASIM_T_W_SPINBOX_WITH_AUTOINCREMENT(fqn) \
    CORBASIM_T_W_impl0(fqn, spinbox_with_autoincrement) \
    /***/

#define CORBASIM_M_W_SEQUENCE_FROM_FILES(fqn, source_type, dst_type) \
    CORBASIM_M_W_impl2(fqn, sequence_from_files, source_type, dst_type) \
    /***/
#define CORBASIM_T_W_SEQUENCE_FROM_FILES(fqn, source_type, dst_type) \
    CORBASIM_T_W_impl2(fqn, sequence_from_files, source_type, dst_type) \
    /***/

/**
 * @brief
 *
 * @param fqn El fqn del miembro de una estructura. Ha de ser un array
 *            de tipo primitivo.
 * @param source_type Unidades a leer del fichero.
 */
#define CORBASIM_M_W_ARRAY_FROM_FILES(fqn, source_type) \
    CORBASIM_M_W_impl1(fqn, array_from_files, source_type) \
    /***/

/**
 * @brief
 *
 * @param fqn El fqn de un tipo array de tipo primitivo.
 * @param source_type Unidades a leer del fichero.
 */
#define CORBASIM_T_W_ARRAY_FROM_FILES(fqn, source_type) \
    CORBASIM_T_W_impl1(fqn, array_from_files, source_type) \
    /***/


#endif /* CORBASIM_GUI_MACROS_HPP */


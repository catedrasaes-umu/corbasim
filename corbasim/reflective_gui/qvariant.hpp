// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * qvariant.hpp
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

#ifndef CORBASIM_REFLECTIVE_GUI_QVARIANT_HPP
#define CORBASIM_REFLECTIVE_GUI_QVARIANT_HPP

#include <corbasim/core/reflective_fwd.hpp>
#include <QVariant>

namespace corbasim 
{
namespace reflective_gui 
{

    QVariant toQVariant(
            corbasim::core::reflective_base const * reflective,
            corbasim::core::holder& hold);

    bool fromQVariant(
            corbasim::core::reflective_base const * reflective,
            corbasim::core::holder& hold,
            const QVariant& var);

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_QVARIANT_HPP */


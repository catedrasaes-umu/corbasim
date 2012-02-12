// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * utils.cpp
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

#include "utils.hpp"

namespace corbasim 
{
namespace reflective_gui 
{

QString getFieldName(core::operation_reflective_base const * operation,
        const ReflectivePath_t& path)
{
    using namespace corbasim::core;

    QString res(operation->get_name());

    reflective_base const * reflective = operation;

    for (int i = 1; i < path.size(); i++) 
    {
        if (reflective->get_type() == TYPE_STRUCT)
        {
            res += QString(".") + reflective->get_child_name(path[i]);

            reflective = reflective->get_child(path[i]);
        }
        else if (reflective->is_repeated())
        {
            res += QString(".[%1]").arg(path[i]);
            
            reflective = reflective->get_slice();
        }
        else break;
    }

    return res;
}

} // namespace reflective_gui
} // namespace corbasim


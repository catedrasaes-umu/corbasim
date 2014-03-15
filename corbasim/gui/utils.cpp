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
#include <QLibrary>

namespace corbasim
{
namespace gui
{

QString getFieldName(OperationDescriptor_ptr operation,
        const ReflectivePath_t& path)
{
    using namespace corbasim::core;

    QString res(operation->get_name());

    reflective_base const * reflective = operation;

    for (int i = 1; i < path.size(); i++)
    {
        if (reflective->get_type() == TYPE_STRUCT ||
                reflective->get_type() == TYPE_UNION)
        {
            res += QString(".") + reflective->get_child_name(path[i]);

            reflective = reflective->get_child(path[i]);
        }
        else if (reflective->is_repeated())
        {
            res += QString("[%1]").arg(path[i]);

            reflective = reflective->get_slice();
        }
        else break;
    }

    return res;
}

TypeDescriptor_ptr followPath(
        OperationDescriptor_ptr operation,
        const ReflectivePath_t& path)
{
    TypeDescriptor_ptr res = operation;


    ReflectivePath_t::const_iterator it = path.begin();

    // Ignore operation index
    ++it;

    for (;it != path.end() && res; ++it)
    {
        res = res->get_child(*it);
    }

    return res;
}

bool followPath(
        OperationDescriptor_ptr operation,
        Holder holder,
        const ReflectivePath_t& path,
        TypeDescriptor_ptr& descriptor,
        Holder& value)
{
    value = holder;
    descriptor = operation;

    ReflectivePath_t::const_iterator it = path.begin();

    // Ignore operation index
    ++it;

    for (;it != path.end() && descriptor; ++it)
    {
        if (descriptor->is_variable_length())
            return false;

        value = descriptor->get_child_value(value, *it);
        descriptor = descriptor->get_child(*it);
    }

    // valid if descriptor not null
    return (descriptor);
}

InterfaceDescriptor_ptr
getReflectiveByFQN(const char * fqn)
{
    QString symbol (fqn);
    symbol.replace("::","_");
    symbol.prepend("corbasim_reflective_");

    typedef const corbasim::core::interface_reflective_base *
        (*get_reflective_t)();
    get_reflective_t get_reflective = NULL;

    QLibrary lib(symbol);

    if (lib.load() &&
            (get_reflective = (get_reflective_t)
                 lib.resolve(symbol.toStdString().c_str())) != NULL)
    {
        return get_reflective();
    }

    return NULL;
}


} // namespace gui
} // namespace corbasim


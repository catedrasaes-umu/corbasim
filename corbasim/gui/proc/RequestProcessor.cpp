// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestProcessor.cpp
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

#include "RequestProcessor.hpp"
#include <corbasim/gui/utils.hpp>
#include <iostream>

using namespace corbasim::gui;

RequestProcessor::RequestProcessor(Objref_ptr object,
        const ReflectivePath_t& path) :
    m_object(object), m_path(path)
{
    // Operation index
    const unsigned int idx =
        (unsigned int) m_path.front();

    const InterfaceDescriptor_ptr iface =
        m_object->interface();

    m_operation =
        iface->get_reflective_by_index(idx);

    m_descriptor =
        followPath(m_operation, m_path);
}

RequestProcessor::~RequestProcessor()
{
}

Objref_ptr RequestProcessor::object() const
{
    return m_object;
}

ObjectId RequestProcessor::id() const
{
    return m_object->id();
}

const ReflectivePath_t& RequestProcessor::path() const
{
    return m_path;
}

OperationDescriptor_ptr RequestProcessor::operation() const
{
    return m_operation;
}

TypeDescriptor_ptr RequestProcessor::descriptor() const
{
    return m_descriptor;
}


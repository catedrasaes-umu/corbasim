// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Objref.cpp
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

#include "Objref.hpp"
#include <corbasim/core/reflective_fwd.hpp>

using namespace corbasim::app::model;

Objref::Objref(const corbasim::app::ObjrefConfig& cfg, 
			   const corbasim::core::interface_reflective_base * factory,
               corbasim::gui::ObjectId objectId) :
    m_cfg(cfg), m_factory(factory), m_objectId(objectId)
{
    // Create a caller
    m_caller.reset(m_factory->create_caller());
    m_caller->set_reference(cfg.ref);
}

Objref::~Objref()
{
}

const corbasim::app::ObjrefConfig& Objref::getConfig() const
{
    return m_cfg;
}

corbasim::event::event* 
Objref::sendRequest(corbasim::event::request_ptr req)
{
    // TODO throw exceptions

    if (!m_caller || m_caller->is_nil())
        return new corbasim::event::message("Invalid reference!");

    return m_caller->do_call(req.get());
}

CORBA::Object_ptr Objref::updateReference(CORBA::Object_ptr ref)
{
    m_caller->set_reference(ref);

    // A duplicate
    m_cfg.ref = m_caller->get_reference();

    // Another duplicate
    return m_caller->get_reference();
}


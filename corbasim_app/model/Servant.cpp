// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Servant.cpp
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

#include "Servant.hpp"
#include <corbasim/core/factory_fwd.hpp>
#include <corbasim/impl.hpp>
#include "../AppController.hpp"

using namespace corbasim::app::model;

Servant::Servant(const ServantConfig& cfg, 
        const gui::gui_factory_base * factory) :
    m_controller(NULL),
    m_cfg(cfg), m_factory(factory), m_servant(NULL)
{
    m_servant = m_factory->get_core_factory()->create_servant(this);
}

Servant::~Servant()
{
    delete m_servant;
}

void Servant::setController(AppController * controller)
{
    m_controller = controller;
}

const corbasim::app::ServantConfig& Servant::getConfig() const
{
    return m_cfg;
}

corbasim::event::event_ptr Servant::operator()(event::request_ptr req,
        event::response_ptr resp)
{
    if (m_controller)
        m_controller->notifyRequestReceived(m_cfg.id.in(), req, resp);

    return boost::static_pointer_cast< event::event >(resp);
}

PortableServer::ServantBase * Servant::getServant() const
{
    return m_servant;
}

corbasim::event::event* 
Servant::sendRequest(corbasim::event::request_ptr req)
{
    if (!m_caller)
        m_caller.reset(m_factory->get_core_factory()->create_caller());

    if(m_caller->is_nil())
    {
        PortableServer::POA_var poa = m_servant->_default_POA();

        CORBA::Object_var obj = poa->servant_to_reference(m_servant);

        m_caller->set_reference(obj);
    }

    return m_caller->do_call(req.get());
}


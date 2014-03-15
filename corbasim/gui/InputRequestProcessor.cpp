// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * InputRequestProcessor.cpp
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

#include "InputRequestProcessor.hpp"
#include <corbasim/gui/utils.hpp>

using namespace corbasim::gui;

//
//
// Input Request Controller
//
//

InputRequestController::InputRequestController(QObject * parent) :
    QObject(parent)
{
}

InputRequestController::~InputRequestController()
{
}

void InputRequestController::registerInstance(Objref_ptr objref)
{
    if (objref->isServant())
    {
        connect(objref.get(),
                SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
                this,
                SLOT(processRequest(ObjectId, Request_ptr, Event_ptr)));
    }
    else
    {
        connect(objref.get(),
                SIGNAL(requestSent(ObjectId, Request_ptr, Event_ptr)),
                this,
                SLOT(processRequest(ObjectId, Request_ptr, Event_ptr)));
    }

    m_instances.add(objref);
}

void InputRequestController::unregisterInstance(ObjectId id)
{
    Objref_ptr objref = m_instances.find(id);

    if (objref)
    {
        if (objref->isServant())
        {
            disconnect(objref.get(),
                    SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
                    this,
                    SLOT(processRequest(ObjectId, Request_ptr, Event_ptr)));
        }
        else
        {
            disconnect(objref.get(),
                    SIGNAL(requestSent(ObjectId, Request_ptr, Event_ptr)),
                    this,
                    SLOT(processRequest(ObjectId, Request_ptr, Event_ptr)));
        }

        m_instances.del(id);

        // Remove its processors
        map_t::iterator it = m_processors.begin();

        for (; it != m_processors.end();)
        {
            map_t::iterator old = it++;

            if (old->first.first == id)
            {
                // Notify deletion of all its processors
                for (processors_t::const_iterator pit =
                        old->second.begin();
                        pit != old->second.end(); ++pit)
                {
                    emit removedProcessor(*pit);
                }

                m_processors.erase(old);
            }
        }
    }
}

void InputRequestController::processRequest(ObjectId id,
        Request_ptr req,
        Event_ptr res)
{
    // creates the key
    map_t::iterator it = m_processors.find(
            std::make_pair(id, req->get_tag()));

    if (it != m_processors.end() &&
            !it->second.empty())
    {
        // Iterates over its associated processors
        processors_t::const_iterator pit = it->second.begin();

        for (; pit != it->second.end(); ++pit)
        {
            const RequestProcessor_ptr processor = *pit;
            const ReflectivePath_t& path = processor->path();
            const OperationDescriptor_ptr op =
                processor->operation();

            Holder holder = op->get_holder(req);

            // Results
            TypeDescriptor_ptr descriptor = NULL;
            Holder value;

            bool res = followPath(op, holder, path,
                    // Results
                    descriptor, value);

            if (res)
                processor->process(req, descriptor, value);
        }
    }
}

void InputRequestController::addProcessor(
        RequestProcessor_ptr p)
{
    const OperationDescriptor_ptr op = p->operation();

    // Inserts the processor
    key_t key (p->id(), op->get_tag());
    m_processors[key].push_back(p);

    emit addedProcessor(p);
}

void InputRequestController::removeProcessor(
        RequestProcessor_ptr p)
{
    const OperationDescriptor_ptr op = p->operation();

    // Removes the processor
    key_t key (p->id(), op->get_tag());
    m_processors[key].removeAll(p);

    emit removedProcessor(p);
}



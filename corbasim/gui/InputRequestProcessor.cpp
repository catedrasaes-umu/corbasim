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

using namespace corbasim::gui;

InputRequestController * 
corbasim::gui::getDefaultInputRequestController()
{
    static InputRequestController _instance;
    return &_instance;
}

namespace  
{

void processRecursive(corbasim::core::reflective_base const * reflec,
        RequestProcessor_ptr processor,
        corbasim::event::request_ptr& req,
        corbasim::core::holder& hold,
        int level)
{
    using namespace corbasim;

    const ReflectivePath_t& path = processor->getPath();

    int size = path.size();

    core::holder tmp = hold;

    for (int i = 1; i < size; i++) 
    {
        // Unsupported case!
        if (reflec->is_variable_length()) return;

        tmp = reflec->get_child_value(tmp, path[i]);

        if (reflec->get_type() == core::TYPE_STRUCT)
        {
            reflec = reflec->get_child(path[i]);
        }
        else if(reflec->is_repeated())
        {
            reflec = reflec->get_slice();
        } 
        else
            return; // Unsupported case!
    }

    processor->process(req, reflec, tmp);
}

} // namespace 

RequestProcessor::RequestProcessor(Objref_ptr object,
        const ReflectivePath_t& path) :
    m_object(object), m_path(path)
{
}

RequestProcessor::~RequestProcessor() {}

Objref_ptr RequestProcessor::object() const
{
    return m_object;
}

ObjectId RequestProcessor::id() const
{
    return m_object->id();
}

const ReflectivePath_t& RequestProcessor::getPath() const
{
    return m_path;
}

InputRequestController::InputRequestController(QObject * parent) :
    QObject(parent)
{
}

InputRequestController::~InputRequestController()
{
}

void InputRequestController::registerInstance(Objref_ptr objref)
{
    connect(objref.get(),
            SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
            this, 
            SLOT(processRequest(ObjectId, Request_ptr, Event_ptr)));

    m_instances.add(objref);
}

void InputRequestController::unregisterInstance(ObjectId id)
{
    Objref_ptr objref = m_instances.find(id);

    if (objref)
    {
        disconnect(objref.get(),
                SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
                this, 
                SLOT(processRequest(ObjectId, Request_ptr, Event_ptr)));

        m_instances.del(id);
    }

    // TODO remove its processors
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
        for (processors_t::const_iterator pit = it->second.begin(); 
                pit != it->second.end(); ++pit) 
        {
            unsigned int idx = (unsigned int) (*pit)->getPath().front();

            OperationDescriptor_ptr op = 
                (*pit)->object()->interface()->get_reflective_by_index(idx);

            Holder hold = op->get_holder(req);
            
            processRecursive(op, *pit, req, hold, 1);
        }
    }
}

void InputRequestController::addProcessor(
        RequestProcessor_ptr p)
{
    OperationDescriptor_ptr op =
        p->object()->interface()->get_reflective_by_index(
                p->getPath().front());

    // Inserts the processor
    key_t key (p->id(), op->get_tag());
    m_processors[key].push_back(p);
}

void InputRequestController::removeProcessor(
        RequestProcessor_ptr p)
{
    OperationDescriptor_ptr op =
        p->object()->interface()->get_reflective_by_index(
                p->getPath().front());

    // Removes the processor
    key_t key (p->id(), op->get_tag());
    m_processors[key].removeAll(p);
}



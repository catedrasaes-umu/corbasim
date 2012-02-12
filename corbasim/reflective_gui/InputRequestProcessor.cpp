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

using namespace corbasim::reflective_gui;

InputRequestController * 
corbasim::reflective_gui::getDefaultInputRequestController()
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

RequestProcessor::RequestProcessor(const QString& id,
        const ReflectivePath_t& path) :
    m_id(id), m_path(path)
{
}

RequestProcessor::~RequestProcessor() {}

const QString& RequestProcessor::getId() const
{
    return m_id;
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

void InputRequestController::registerInstance(const QString& id, 
        const corbasim::core::interface_reflective_base * factory)
{
    m_instances.insert(std::make_pair(id, factory));
}

void InputRequestController::unregisterInstance(const QString& id)
{
    m_instances.erase(id);
}

void InputRequestController::processRequest(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr res)
{
    // creates the key
    map_t::iterator it = m_processors.find(
            std::make_pair(id, req->get_tag()));

    instances_t::const_iterator iface = m_instances.find(id);

    if (it != m_processors.end() && 
            iface != m_instances.end() &&
            !it->second.empty())
    {
        core::operation_reflective_base const * op =
            iface->second->get_reflective_by_tag(req->get_tag());

        core::holder hold = op->get_holder(req);

        for (int i = 0; i < it->second.size(); i++) 
        {
            // Must be optimized!!!
            processRecursive(op, it->second.at(i), req, hold, 1);
        }
    }
}

void InputRequestController::addProcessor(
        corbasim::reflective_gui::RequestProcessor_ptr p)
{
    instances_t::const_iterator iface = m_instances.find(p->getId());

    if (iface != m_instances.end())
    {
        core::operation_reflective_base const * op =
            iface->second->get_reflective_by_index(
                    p->getPath().front());

        // Inserts the processor
        key_t key (p->getId(), op->get_tag());
        m_processors[key].push_back(p);
    }
}

void InputRequestController::removeProcessor(
        corbasim::reflective_gui::RequestProcessor_ptr p)
{
    instances_t::const_iterator iface = m_instances.find(p->getId());

    if (iface != m_instances.end())
    {
        core::operation_reflective_base const * op =
            iface->second->get_reflective_by_index(
                    p->getPath().front());

        // Removes the processor
        key_t key (p->getId(), op->get_tag());
        m_processors[key].removeAll(p);
    }
}



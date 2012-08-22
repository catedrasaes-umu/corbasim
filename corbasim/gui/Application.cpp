// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Application.cpp
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

#include "Application.hpp"

using namespace corbasim::gui;

//
//
// Application
//
//

Application::Application(QObject * parent) :
    QObject(parent), 
    m_interfaces(this), 
    m_objrefs(this),
    m_servants(this)
{
    QObject::connect(&m_interfaces, 
            SIGNAL(loadedInterface(InterfaceDescriptor_ptr)),
            this, 
            SIGNAL(loadedInterface(InterfaceDescriptor_ptr)));

    QObject::connect(&m_objrefs, 
            SIGNAL(deleted(ObjectId)),
            this, 
            SIGNAL(objrefDeleted(ObjectId)));

    QObject::connect(&m_servants, 
            SIGNAL(deleted(ObjectId)),
            this, 
            SIGNAL(servantDeleted(ObjectId)));
}

Application::~Application()
{
}

void Application::loadScenario(const QString& file)
{
}

void Application::saveScenario(const QString& file)
{
}

void Application::loadDirectory(const QString& directory)
{
    m_interfaces.loadDirectory(directory);
}

void Application::loadInterface(const QString& fqn)
{
    InterfaceDescriptor_ptr interface = m_interfaces.getInterface(fqn);

    if (!interface)
    {
        emit error(QString("Unable to load interface %1").arg(fqn));
    }
}

void Application::createObjref(const ObjrefConfig& cfg)
{
    const QString name(cfg.name.c_str());

    if (m_servants.find(name) || m_objrefs.find(name))
    {
        emit error(QString("Object '%1' already exists!").arg(name));
        return;
    }

    InterfaceDescriptor_ptr factory = 
        m_interfaces.getInterface(cfg.fqn.c_str());

    if (factory)
    {
        Objref_ptr obj(new Objref(cfg, factory, this));

        m_objrefs.add(obj);

        emit objrefCreated(obj);
    }
}

void Application::createServant(const ServantConfig& cfg)
{
    const QString name(cfg.name.c_str());

    if (m_servants.find(name) || m_objrefs.find(name))
    {
        emit error(QString("Object '%1' already exists!").arg(name));
        return;
    }

    InterfaceDescriptor_ptr factory = 
        m_interfaces.getInterface(cfg.fqn.c_str());

    if (factory)
    {
        Servant_ptr obj(new Servant(cfg, factory, this));
        
#if 0
        // Temporal - Proof of concept

        PortableServer::ObjectId_var myObjID = 
            m_data->rootPOA->activate_object (obj->getServant());
    
        CORBA::Object_var objSrv = 
            m_data->rootPOA->servant_to_reference(obj->getServant());

        // Displaying reference
        CORBA::String_var ref = m_data->orb->object_to_string (objSrv);
        std::cout << cfg.id << ": " << ref << std::endl;
#endif

        // End temporal

        m_servants.add(obj);

        emit servantCreated(obj);

#if 0
        // Naming service registration
        if (std::strlen(cfg.entry.in()) > 0)
        {
            std::auto_ptr< core::ns_register > ptr_(
                    new core::ns_register(m_data->orb, 
                        cfg.entry.in(), objSrv));

            if (!ptr_->error())
            {
                // Assumes its ownership
                obj->set_ns_entry(ptr_.release());

                emit message(
                        QString("'%1' registred as '%2'").arg(id).
                            arg(cfg.entry.in()));
            }
            else
            {
                emit error(
                        QString("Unable to register '%1' as '%2'").
                            arg(id).arg(cfg.entry.in()));
            }
        }
#endif
    }
}

void Application::deleteObjref(ObjectId id)
{
    Objref_ptr obj = m_objrefs.find(id);

    if (obj)
    {
        m_objrefs.del(id);
    }
    else
    {
        emit error("Object not found!");
    }
}

void Application::deleteServant(ObjectId id)
{
    Objref_ptr obj = m_servants.find(id);

    if (obj)
    {
#if 0
        // Temporal - Proof of concept
        PortableServer::ObjectId_var myObjID = 
            m_data->rootPOA->servant_to_id(it->second->getServant()); 

        m_data->rootPOA->deactivate_object (myObjID);
        // End temporal
#endif
        m_servants.del(id);
    }
    else
    {
        emit error("Object not found!");
    }
}


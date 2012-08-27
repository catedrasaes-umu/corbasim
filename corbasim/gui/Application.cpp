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
#include <iostream>

using namespace corbasim::gui;

struct Application::ApplicationData
{
    Application& m_this;

    CORBA::ORB_var m_orb;
    PortableServer::POA_var m_rootPOA;
    PortableServer::POAManager_var m_manager; 

    ApplicationData(Application& this_) : 
        m_this(this_) 
    {
        int argc = 0;
        m_orb = CORBA::ORB_init(argc, NULL);

        CORBA::Object_var rootPOAObj = 
            m_orb->resolve_initial_references ("RootPOA");

        m_rootPOA = PortableServer::POA::_narrow(rootPOAObj.in());

        m_manager = m_rootPOA->the_POAManager();

        m_manager->activate();
    }

    ~ApplicationData()
    {
    }
};

//
//
// Application
//
//

namespace  
{
    using corbasim::gui::Application;

    Application *& currentApplication()
    {
        static Application * instance = NULL;
        return instance;
    }
} // namespace

Application * Application::currentApplication()
{
    return ::currentApplication();
}

Application::Application(QObject * parent) :
    QObject(parent), 
    m_interfaces(this), 
    m_objrefs(this),
    m_servants(this),
    m_data(new ApplicationData(*this))
{
    ::currentApplication() = this;

    connect(&m_interfaces, 
            SIGNAL(loadedInterface(InterfaceDescriptor_ptr)),
            this, 
            SIGNAL(loadedInterface(InterfaceDescriptor_ptr)));

    connect(&m_objrefs, 
            SIGNAL(deleted(ObjectId)),
            this, 
            SIGNAL(objrefDeleted(ObjectId)));

    connect(&m_servants, 
            SIGNAL(deleted(ObjectId)),
            this, 
            SIGNAL(servantDeleted(ObjectId)));
}

Application::~Application()
{
    delete m_data;
}

void Application::loadScenario(const QString& file)
{
    // clear scenario
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
    if (cfg.name.empty())
    {
        emit error("You must specify an object name");
        return;
    }

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

        const char * signal =
            SIGNAL(requestSent(ObjectId, Request_ptr, 
                        Event_ptr));

        connect(obj.get(), signal, this, signal);

        emit objrefCreated(obj);
    }
    else
    {
        emit error(QString("Unable to find '%1'!").arg(cfg.fqn.c_str()));
    }
}

void Application::createServant(const ServantConfig& cfg)
{
    if (cfg.name.empty())
    {
        emit error("You must specify an object name");
        return;
    }

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
        
        PortableServer::ObjectId_var myObjID = 
            m_data->m_rootPOA->activate_object (obj->getServant());
    
        CORBA::Object_var objSrv = 
            m_data->m_rootPOA->servant_to_reference(obj->getServant());

        // Displaying reference
        CORBA::String_var ref = m_data->m_orb->object_to_string (objSrv);
        std::cout << cfg.name << ": " << ref << std::endl;

        obj->setReference(objSrv);

        m_servants.add(obj);

        const char * signal =
            SIGNAL(requestReceived(ObjectId, Request_ptr, 
                        Event_ptr));

        connect(obj.get(), signal, this, signal);

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
        Servant_ptr servant = boost::static_pointer_cast< Servant >(obj);

        PortableServer::ObjectId_var myObjID = 
            m_data->m_rootPOA->servant_to_id(servant->getServant()); 

        m_data->m_rootPOA->deactivate_object (myObjID);

        m_servants.del(id);
    }
    else
    {
        emit error("Object not found!");
    }
}


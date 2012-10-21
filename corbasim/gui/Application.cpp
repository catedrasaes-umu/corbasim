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
#include <fstream>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/json.hpp>
#include <boost/thread/shared_mutex.hpp>

// Services
#include <corbasim/gui/InputRequestProcessor.hpp>
#include <corbasim/gui/Sender.hpp>
#include <corbasim/gui/script/TriggerEngine.hpp>
#include <corbasim/gui/NSManager.hpp>

#include <cassert>

using namespace corbasim::gui;

typedef boost::shared_lock< boost::shared_mutex > shared_lock;
typedef boost::unique_lock< boost::shared_mutex > unique_lock;

struct Application::ApplicationData
{
    Application& m_this;

    CORBA::ORB_var m_orb;
    PortableServer::POA_var m_rootPOA;
    PortableServer::POAManager_var m_manager; 

    // Services
    InputRequestController * m_inputReqCtl;
    QThread m_inputReqCtlThread;

    SenderController * m_senderCtl;
    QThread m_senderCtlThread;

    TriggerEngine * m_scriptEngine;
    QThread m_scriptEngineThread;

    NSManager * m_nameServiceManager;
    QThread m_nameServiceManagerThread;

    // Mutex
    boost::shared_mutex m_objrefsMutex;
    boost::shared_mutex m_servantsMutex;

    ApplicationData(Application& this_) : 
        m_this(this_) 
    {
        int argc = 0;
        m_orb = CORBA::ORB_init(argc, NULL);

        CORBA::Object_var rootPOAObj = 
            m_orb->resolve_initial_references ("RootPOA");

        m_rootPOA = 
            PortableServer::POA::_narrow(rootPOAObj.in());

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
    corbasim::gui::initialize();

    assert(!::currentApplication());

    ::currentApplication() = this;

    connect(&m_interfaces, 
            SIGNAL(loadedInterface(InterfaceDescriptor_ptr)),
            this, 
            SLOT(sLoadedInterface(InterfaceDescriptor_ptr)));
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

    // Services
    // Without parent because its own thread
    m_data->m_inputReqCtl = new InputRequestController();
    m_data->m_senderCtl = new SenderController();
    m_data->m_scriptEngine = new TriggerEngine();
    m_data->m_nameServiceManager = new NSManager(m_data->m_orb);

    // Input request controller
    connect(this, 
            SIGNAL(servantCreated(Objref_ptr)), 
            m_data->m_inputReqCtl, 
            SLOT(registerInstance(Objref_ptr)));
    connect(this, 
            SIGNAL(servantDeleted(ObjectId)), 
            m_data->m_inputReqCtl, 
            SLOT(unregisterInstance(ObjectId)));

    // Signals application <-> script engine
    connect(this, 
            SIGNAL(servantCreated(Objref_ptr)), 
            m_data->m_scriptEngine, 
            SLOT(servantCreated(Objref_ptr)));
    connect(this, 
            SIGNAL(servantDeleted(ObjectId)), 
            m_data->m_scriptEngine, 
            SLOT(servantDeleted(ObjectId)));
    connect(this, 
            SIGNAL(objrefCreated(Objref_ptr)), 
            m_data->m_scriptEngine, 
            SLOT(objrefCreated(Objref_ptr)));
    connect(this, SIGNAL(objrefDeleted(ObjectId)), 
            m_data->m_scriptEngine, 
            SLOT(objrefDeleted(ObjectId)));

    // Error notification
    connect(m_data->m_scriptEngine, 
            SIGNAL(error(const QString&)), 
            this, 
            SIGNAL(error(const QString&)));
    // End signals application <-> script engine

    // Signals application <-> name service
    connect(this, 
            SIGNAL(servantCreated(Objref_ptr)), 
            m_data->m_nameServiceManager, 
            SLOT(servantCreated(Objref_ptr)));
    connect(this, 
            SIGNAL(servantDeleted(ObjectId)), 
            m_data->m_nameServiceManager, 
            SLOT(servantDeleted(ObjectId)));
    connect(this, 
            SIGNAL(objrefCreated(Objref_ptr)), 
            m_data->m_nameServiceManager, 
            SLOT(objrefCreated(Objref_ptr)));
    connect(this, SIGNAL(objrefDeleted(ObjectId)), 
            m_data->m_nameServiceManager, 
            SLOT(objrefDeleted(ObjectId)));
    // Error notification
    connect(m_data->m_nameServiceManager, 
            SIGNAL(error(const QString&)), 
            this, 
            SIGNAL(error(const QString&)));
    connect(m_data->m_nameServiceManager, 
            SIGNAL(message(const QString&)), 
            this, 
            SIGNAL(message(const QString&)));
    // End signals application <-> name service

    // Sender Controller
    // Error notification
    connect(m_data->m_senderCtl, 
            SIGNAL(error(const QString&)), 
            this, 
            SIGNAL(error(const QString&)));

    // Services dedicated threads
    m_data->m_inputReqCtl->moveToThread(
            &m_data->m_inputReqCtlThread);
    m_data->m_senderCtl->moveToThread(
            &m_data->m_senderCtlThread);
    m_data->m_scriptEngine->moveToThread(
            &m_data->m_scriptEngineThread);
    m_data->m_nameServiceManager->moveToThread(
            &m_data->m_nameServiceManagerThread);

    m_data->m_nameServiceManager->start();

    m_data->m_inputReqCtlThread.start();
    
    m_data->m_senderCtl->start(); // its thread pool
    m_data->m_senderCtlThread.start();
    
    m_data->m_scriptEngineThread.start();
    m_data->m_nameServiceManagerThread.start();
}

Application::~Application()
{
    // Stop al the services
    m_data->m_inputReqCtlThread.quit();
    m_data->m_senderCtl->stop(); // its thread pool
    m_data->m_senderCtlThread.quit();
    m_data->m_scriptEngineThread.quit();
    m_data->m_nameServiceManagerThread.quit();

    m_data->m_inputReqCtlThread.wait();
    m_data->m_senderCtl->join(); // its thread pool
    m_data->m_senderCtlThread.wait();
    m_data->m_scriptEngineThread.wait();
    m_data->m_nameServiceManagerThread.wait();

    // Objrefs
    {
        unique_lock lock(m_data->m_objrefsMutex);

        // They shouldn't be referenced by others
        // but anyway... let shared_ptr work
        ObjrefRepository::iterator it = m_objrefs.begin();
        ObjrefRepository::iterator end = m_objrefs.end();

        for (; it != end; it++)
        {
            it.value()->setParent(0);
        }
    }

    // Servants
    {
        unique_lock lock(m_data->m_servantsMutex);

        ObjrefRepository::iterator it = m_servants.begin();
        ObjrefRepository::iterator end = m_servants.end();

        for (; it != end; it++)
        {
            it.value()->setParent(0);
        }
    }

    delete m_data->m_scriptEngine;
    delete m_data->m_nameServiceManager;
    delete m_data->m_inputReqCtl;
    delete m_data->m_senderCtl;
    delete m_data;
}

void Application::sLoadedInterface(InterfaceDescriptor_ptr interface)
{
    emit message(QString("Loaded interface %1").arg(interface->get_fqn()));
}

QObject * Application::inputRequestController() const
{
    return m_data->m_inputReqCtl;
}

QObject * Application::senderController() const
{
    return m_data->m_senderCtl;
}

QObject * Application::scriptEngine() const
{
    return m_data->m_scriptEngine;
}

QObject * Application::nameServiceManager() const
{
    return m_data->m_nameServiceManager;
}

void Application::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    // Objrefs
    {
        const QVariantList list = map["objects"].toList();

        QVariantList::const_iterator it = list.begin();
        QVariantList::const_iterator end = list.end();

        for (; it != end; it++)
        {
            const QVariantMap value = it->toMap();

            ObjrefConfig cfg;
            cfg.name = value["name"].toString().toStdString();
            cfg.fqn = value["fqn"].toString().toStdString();
            cfg.entry = value["entry"].toString().toStdString();

            try
            {
                const std::string ref =
                    value["reference"].toString().toStdString();

                cfg.reference =
                    m_data->m_orb->string_to_object(ref.c_str());
            }
            catch(...)
            {}

            createObjref(cfg);
        }
    }

    // Sevants
    {
        const QVariantList list = map["servants"].toList();

        QVariantList::const_iterator it = list.begin();
        QVariantList::const_iterator end = list.end();

        for (; it != end; it++)
        {
            const QVariantMap value = it->toMap();

            ServantConfig cfg;
            cfg.name = value["name"].toString().toStdString();
            cfg.fqn = value["fqn"].toString().toStdString();
            cfg.entry = value["entry"].toString().toStdString();

            createServant(cfg);
        }
    }
}

void Application::save(QVariant& settings) const
{
    QVariantMap map;

    // Objrefs
    {
        shared_lock lock(m_data->m_objrefsMutex);

        QVariantList list;

        ObjrefRepository::const_iterator it = m_objrefs.begin();
        ObjrefRepository::const_iterator end = m_objrefs.end();

        for (; it != end; it++)
        {
            QVariantMap value;

            value["name"] = (*it)->name();
            value["fqn"] = (*it)->interface()->get_fqn();
            
            CORBA::String_var ref = 
                m_data->m_orb->object_to_string((*it)->reference());

            value["reference"] = ref.in();
            value["entry"] = (*it)->nsEntry();

            list << value;
        }

        map["objects"] = list;
    }

    // Servants
    {
        shared_lock lock(m_data->m_servantsMutex);

        QVariantList list;

        ObjrefRepository::const_iterator it = 
            m_servants.begin();
        ObjrefRepository::const_iterator end = 
            m_servants.end();

        for (; it != end; it++)
        {
            QVariantMap value;

            value["name"] = (*it)->name();
            value["fqn"] = (*it)->interface()->get_fqn();
            value["entry"] = (*it)->nsEntry();

            // its reference doesn't matter

            list << value;
        }

        map["servants"] = list;
    }

    settings = map;
};

void Application::clearScenario()
{
    // Objrefs
    {
        unique_lock lock(m_data->m_objrefsMutex);
        m_objrefs.clear();
    }

    // Servants
    {
        unique_lock lock(m_data->m_servantsMutex);
        m_servants.clear();
    }

    emit message("Scenario cleared");
}

void Application::loadScenario(const QString& file)
{
    clearScenario();
    QVariant settings;
    
    bool res =
        fromJsonFile(file.toStdString().c_str(), settings);

    if (res)
    {
        load(settings);
        
        emit message(QString("Loaded scenario from %1").arg(file));
    }
    else
    {
        emit error(QString("Unable to load '%1'").arg(file));
    }
}

void Application::saveScenario(const QString& file)
{
    QVariant settings;
    save(settings);

    std::ofstream ofs(file.toStdString().c_str());
    json::ostream_writer_t ow(ofs, true);
    toJson(ow, settings);

    emit message(QString("Saved current scenario into %1").arg(file));
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
    else
    {
        emit message(QString("Loaded interface %1").arg(fqn));
    }
}

Objref_ptr Application::createObjref(const ObjrefConfig& cfg)
{
    unique_lock lock(m_data->m_objrefsMutex);

    if (cfg.name.empty())
    {
        emit error("You must specify an object name");
        return Objref_ptr();
    }

    const QString name(cfg.name.c_str());

    if (m_servants.find(name) || m_objrefs.find(name))
    {
        emit error(QString("Object '%1' already exists!")
                .arg(name));

        return Objref_ptr();
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

        emit message(QString("New object reference: %1")
                .arg(cfg.fqn.c_str()));

        return obj;
    }
    else
    {
        emit error(QString("Unable to find '%1'!")
                .arg(cfg.fqn.c_str()));
    }

    return Objref_ptr();
}

Objref_ptr Application::createServant(const ServantConfig& cfg)
{
    unique_lock lock(m_data->m_servantsMutex);

    if (cfg.name.empty())
    {
        emit error("You must specify an object name");
        return Objref_ptr();
    }

    const QString name(cfg.name.c_str());

    if (m_servants.find(name) || m_objrefs.find(name))
    {
        emit error(QString("Object '%1' already exists!")
                .arg(name));
        return Objref_ptr();
    }

    InterfaceDescriptor_ptr factory = 
        m_interfaces.getInterface(cfg.fqn.c_str());

    if (factory)
    {
        Servant_ptr obj(new Servant(cfg, factory, this));
        
        PortableServer::ObjectId_var myObjID = 
            m_data->m_rootPOA->activate_object(
                    obj->getServant());
    
        CORBA::Object_var objSrv = 
            m_data->m_rootPOA->servant_to_reference(
                    obj->getServant());

        // Displaying reference
        CORBA::String_var ref = 
            m_data->m_orb->object_to_string (objSrv);

        std::cout << cfg.name << ": " << ref.in() << std::endl;

        obj->setReference(objSrv);

        m_servants.add(obj);

        const char * signal =
            SIGNAL(requestReceived(ObjectId, Request_ptr, 
                        Event_ptr));

        connect(obj.get(), signal, this, signal);

        if (!cfg.saveFile.empty())
        {
            std::ofstream ofs(cfg.saveFile.c_str());
            ofs << ref.in();
        }

        emit servantCreated(obj);

        emit message(QString("New servant: %1")
                .arg(cfg.fqn.c_str()));

        return obj;
    }
    
    return Objref_ptr();
}

void Application::deleteObjref(ObjectId id)
{
    unique_lock lock(m_data->m_objrefsMutex);

    Objref_ptr obj = m_objrefs.find(id);

    if (obj)
    {
        m_objrefs.del(id);
        
        emit message(QString("Deleted object reference: %1").arg(obj->name()));
    }
    else
    {
        emit error("Object not found!");
    }
}

void Application::deleteServant(ObjectId id)
{
    unique_lock lock(m_data->m_servantsMutex);

    Objref_ptr obj = m_servants.find(id);

    if (obj)
    {
        Servant_ptr servant = boost::static_pointer_cast< Servant >(obj);

        PortableServer::ObjectId_var myObjID = 
            m_data->m_rootPOA->servant_to_id(servant->getServant()); 

        m_data->m_rootPOA->deactivate_object (myObjID);

        m_servants.del(id);

        emit message(QString("Deleted servant: %1").arg(obj->name()));
    }
    else
    {
        emit error("Object not found!");
    }
}


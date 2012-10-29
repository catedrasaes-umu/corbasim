// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ServerApp.cpp
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

#include "ServerApp.hpp"
#include <corbasim/gui/Application.hpp>
#include <corbasim/gui/server/Server.hpp>

#include <boost/thread.hpp>
#include <cassert>

using namespace corbasim::gui;


struct ServerApp::ServerData
{
    ServerApp& this_;
    QApplication app;
    Application application;
    ObjrefRepository clients;

    Server window;

    // Not needed yet!
    /*
    typedef PortableServer::ServantBase * servant_t;
    typedef std::map< std::string, servant_t > servants_t;
    servants_t servants;
    */

    CORBA::ORB_var orb;
    PortableServer::POA_var rootPOA;

    ServerData(ServerApp& this__, int& argc, char ** argv) : 
        this_(this__),
        app(argc, argv)
    {
        orb = CORBA::ORB_init(argc, argv);

        CORBA::Object_var rootPOAObj = 
            orb->resolve_initial_references ("RootPOA");

        rootPOA = PortableServer::POA::_narrow(rootPOAObj.in());
    }
};

ServerApp::ServerApp(int& argc, char ** argv) :
    m_impl(new ServerData(*this, argc, argv))
{
    // connect signals
    QObject::connect(&m_impl->application, SIGNAL(objrefCreated(Objref_ptr)), 
            &m_impl->window, SLOT(objrefCreated(Objref_ptr)));
    QObject::connect(&m_impl->application, SIGNAL(servantCreated(Objref_ptr)), 
            &m_impl->window, SLOT(servantCreated(Objref_ptr)));
    QObject::connect(&m_impl->application, SIGNAL(objrefDeleted(ObjectId)), 
            &m_impl->window, SLOT(objrefDeleted(ObjectId)));
    QObject::connect(&m_impl->application, SIGNAL(servantDeleted(ObjectId)), 
            &m_impl->window, SLOT(servantDeleted(ObjectId)));
    QObject::connect(&m_impl->application, SIGNAL(error(const QString&)), 
            &m_impl->window, SLOT(displayError(const QString&)));
    QObject::connect(&m_impl->application, SIGNAL(message(const QString&)), 
            &m_impl->window, SLOT(displayMessage(const QString&)));
}

ServerApp::~ServerApp()
{
    delete m_impl;
}

QWidget * ServerApp::window() const
{
    return &(m_impl->window);
}

void ServerApp::setPluginDirectory(const char * directory)
{
    m_impl->application.loadDirectory(directory);
}

CORBA::Object_var ServerApp::setClient(
        const char * fqn, 
        const char * clientName,
        const CORBA::Object_var& ref)
{
    const QString nameToFind = QString("corbasim hide servant %1").arg(clientName);

    Objref_ptr objref = m_impl->clients.find(nameToFind);

    CORBA::Object_var result;

    // Client exists
    if (objref)
    {
        // if the client exists we return its proxy servant
        // reference
        Servant * servant = 
            static_cast< Servant * >(objref.get());

        servant->proxy()->setReference(ref);

        result = servant->reference();
    }
    else
    {
        // New client
        // We create a new hidden servant
        ServantConfig scfg;
        scfg.fqn = fqn;
        scfg.name = std::string("corbasim hide servant ") + clientName;
        scfg.hide = true;

        Objref_ptr oServant = 
            m_impl->application.createServant(scfg);

        Servant * servant = 
            static_cast< Servant * >(oServant.get());

        // user must use this reference
        // all its calls will be derived to a proxy reference
        result = servant->reference();

        servant->setReference(result);

        // We create a visible client
        ObjrefConfig ccfg;
        ccfg.name = clientName;
        ccfg.fqn = fqn;
        ccfg.reference = ref;

        Objref_ptr proxy = 
            m_impl->application.createObjref(ccfg);

        servant->setProxy(proxy);

        m_impl->clients.add(oServant);
    }

    return result;
}

CORBA::Object_var ServerApp::setClient(
        const char * fqn, 
        const char * clientName,
        const char * nsEntry)
{
    const QString nameToFind = QString("corbasim hide servant %1").arg(clientName);

    Objref_ptr objref = m_impl->clients.find(nameToFind);

    CORBA::Object_var result;

    // Client exists
    if (objref)
    {
        // if the client exists we return its proxy servant
        // reference
        Servant * servant = 
            static_cast< Servant * >(objref.get());

        servant->proxy()->setNsEntry(nsEntry);

        result = servant->reference();
    }
    else
    {
        // New client
        // We create a new hidden servant
        ServantConfig scfg;
        scfg.fqn = fqn;
        scfg.name = std::string("corbasim hide servant ") + clientName;
        scfg.hide = true;

        Objref_ptr oServant = 
            m_impl->application.createServant(scfg);

        Servant * servant = 
            static_cast< Servant * >(oServant.get());

        // user must use this reference
        // all its calls will be derived to a proxy reference
        result = servant->reference();

        servant->setReference(result);

        // We create a visible client
        ObjrefConfig ccfg;
        ccfg.name = clientName;
        ccfg.fqn = fqn;
        ccfg.entry = nsEntry;

        Objref_ptr proxy = 
            m_impl->application.createObjref(ccfg);

        servant->setProxy(proxy);

        m_impl->clients.add(oServant);
    }

    return result;
}

CORBA::Object_var ServerApp::setServant(
        const char * fqn,
        const char * servantName,
        PortableServer::ServantBase * servant,
        const char * nsEntry)
{
    // We activate the real servant
    PortableServer::ObjectId_var myObjID = 
        m_impl->rootPOA->activate_object(servant);

    CORBA::Object_var realRef =  
        m_impl->rootPOA->servant_to_reference(servant);

    // We use a fake servant
    ServantConfig scfg;
    scfg.fqn = fqn;
    scfg.name = servantName;

    if (nsEntry)
        scfg.entry = nsEntry;

    Objref_ptr oServant = 
        m_impl->application.createServant(scfg);

    Servant * sServant = 
        static_cast< Servant * >(oServant.get());

    CORBA::Object_var result = sServant->reference();

    sServant->setReference(result);

    // create an objref with the real reference
    ObjrefConfig ocfg;
    ocfg.fqn = fqn;
    ocfg.name = std::string("corbasim hide client ") + servantName;
    ocfg.reference = realRef;
    ocfg.hide = true;

    Objref_ptr realObjref = 
        m_impl->application.createObjref(ocfg);
    
    sServant->setProxy(realObjref);
    // end create an objref with the real reference

    return result;
}

void ServerApp::setWindowTitle(const char * title)
{
    m_impl->window.setWindowTitle(title);
}

int ServerApp::exec()
{
    QThread appThread;

    m_impl->application.moveToThread(&appThread);
    appThread.start();

    m_impl->window.show();

    // ... and run
    // Qt event loop must be in the main thread
    boost::thread orbThread(
            boost::bind(&CORBA::ORB::run, m_impl->orb.in()));

    int res = m_impl->app.exec();

    appThread.quit();
    appThread.wait();

    m_impl->orb->shutdown(1);

    orbThread.join();

    delete m_impl; m_impl = NULL;

    return res;
}


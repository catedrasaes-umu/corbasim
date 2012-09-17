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

    PortableServer::ServantBase * servant;

    CORBA::ORB_var orb;
    PortableServer::POA_var rootPOA;
    PortableServer::POAManager_var manager; 

    ServerData(ServerApp& this__, int& argc, char ** argv) : 
        this_(this__),
        app(argc, argv), 
        servant(NULL) 
    {
        orb = CORBA::ORB_init(argc, argv);

        CORBA::Object_var rootPOAObj = 
            orb->resolve_initial_references ("RootPOA");

        rootPOA = PortableServer::POA::_narrow(rootPOAObj.in());

        manager = rootPOA->the_POAManager();

        manager->activate();
    }
};

ServerApp::ServerApp(int& argc, char ** argv) :
    m_impl(new ServerData(*this, argc, argv))
{
    // TODO connect signals
}

ServerApp::~ServerApp()
{
    delete m_impl;
}

QWidget * ServerApp::window() const
{
    return &(m_impl->window);
}

CORBA::Object_var ServerApp::setClient(
        const char * fqn, 
        const char * clientName,
        const CORBA::Object_var& ref)
{
    Objref_ptr objref = m_impl->clients.find(clientName);

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
        scfg.name = clientName;

        // TODO we can't do this because of duplicated name
        Objref_ptr oServant = 
            m_impl->application.createServant(scfg);

        Servant * servant = 
            static_cast< Servant * >(oServant.get());

        PortableServer::ObjectId_var myObjID = 
            m_impl->rootPOA->activate_object(
                    servant->getServant());

        // user must use this reference
        // all its calls will be derived to a proxy reference
        result =  
            m_impl->rootPOA->servant_to_reference(
                    servant->getServant());

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

CORBA::Object_var ServerApp::setServant(
        const char * fqn,
        PortableServer::ServantBase * servant)
{
    assert(!m_impl->servant);

    // We activate the real servant
    m_impl->servant = servant;

    PortableServer::ObjectId_var myObjID = 
        m_impl->rootPOA->activate_object(servant);

    CORBA::Object_var realRef =  
        m_impl->rootPOA->servant_to_reference(servant);

    // We use a fake servant
    ServantConfig scfg;
    scfg.fqn = fqn;
    scfg.name = "this"; // TODO

    Objref_ptr oServant = 
        m_impl->application.createServant(scfg);

    Servant * sServant = 
        static_cast< Servant * >(oServant.get());

    myObjID = m_impl->rootPOA->activate_object(
                sServant->getServant());

    CORBA::Object_var result =  
        m_impl->rootPOA->servant_to_reference(
                sServant->getServant());

    sServant->setReference(result);

    // TODO create an objref with the real reference
    Objref_ptr realObjref;

    sServant->setProxy(realObjref);

    return result;
}

int ServerApp::exec()
{
    assert(m_impl->servant);

    // TODO m_impl->window.initialize(m_impl->reflective);
    m_impl->window.show();

    // ... and run
    // Qt event loop must be in the main thread
    boost::thread orbThread(
            boost::bind(&CORBA::ORB::run, m_impl->orb.in()));

    int res = m_impl->app.exec();

    m_impl->orb->shutdown(1);

    orbThread.join();

    return res;
}


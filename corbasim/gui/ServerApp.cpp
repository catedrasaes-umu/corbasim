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
#include <QtGui>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <corbasim/qt/initialize.hpp>
#include <corbasim/gui/Server.hpp>

using namespace corbasim::gui;

struct ServerApp::ServerApp_i :
    public ::corbasim::core::request_processor
{
    ServerApp * this_;
    QApplication * app;
    PortableServer::ServantBase * servant;

    ::corbasim::core::interface_reflective_base const * reflective;

    CORBA::ORB_var orb;
    PortableServer::POA_var rootPOA;
    PortableServer::POAManager_var manager; 

    PortableServer::ServantBase * proxyServant;

    ::corbasim::core::interface_caller_ptr caller;

    ::corbasim::gui::Server * server;

    ServerApp_i(ServerApp * _this) : 
        this_(_this),
        app(NULL), 
        servant(NULL), 
        reflective(NULL), 
        proxyServant(NULL),
        server(NULL)
    {
    }

    ::corbasim::event::event_ptr operator()(
            ::corbasim::event::request_ptr req,
            ::corbasim::event::response_ptr)
    {
        ::corbasim::event::event_ptr ev(caller->do_call(req.get()));

        server->notifyRequestReceived(req, ev);
        
        return ev;
    }
};

ServerApp::ServerApp(int argc, char ** argv) :
    m_impl(new ServerApp_i(this))
{
    m_impl->app = new QApplication(argc, argv);

    m_impl->orb = CORBA::ORB_init(argc, argv);

    CORBA::Object_var rootPOAObj = 
        m_impl->orb->resolve_initial_references ("RootPOA");

    m_impl->rootPOA = PortableServer::POA::_narrow(rootPOAObj.in());

    m_impl->manager = m_impl->rootPOA->the_POAManager();

    m_impl->manager->activate();

    corbasim::qt::initialize();
}

ServerApp::~ServerApp()
{
    delete m_impl->server;
    delete m_impl->app;
    delete m_impl->proxyServant;
    delete m_impl;
}

CORBA::Object_var ServerApp::setClient(
        const char * fqn, 
        const char * clientName,
        const CORBA::Object_var& ref)
{
    return CORBA::Object::_nil();
}

CORBA::Object_var ServerApp::setServant(
        ::corbasim::core::interface_reflective_base const * reflective,
        PortableServer::ServantBase * servant)
{
    m_impl->reflective = reflective;
    m_impl->servant = servant;

    PortableServer::ObjectId_var myObjID = 
        m_impl->rootPOA->activate_object (m_impl->servant);

    CORBA::Object_var objSrv = 
        m_impl->rootPOA->servant_to_reference(m_impl->servant);

    m_impl->caller.reset(m_impl->reflective->create_caller());

    m_impl->caller->set_reference(objSrv);
        
    m_impl->proxyServant = m_impl->reflective->create_servant(m_impl);

    myObjID = m_impl->rootPOA->activate_object (m_impl->proxyServant);

    objSrv = m_impl->rootPOA->servant_to_reference(m_impl->proxyServant);

    CORBA::String_var strRef = m_impl->orb->object_to_string(objSrv.in());
    std::cout << strRef.in() << std::endl;

    return objSrv;
}

int ServerApp::exec()
{
    if (!m_impl->servant || !m_impl->reflective) 
        return -1;

    m_impl->server = new ::corbasim::gui::Server();
    m_impl->server->initialize(m_impl->reflective);
    m_impl->server->show();

    boost::thread orbThread(
            boost::bind(&CORBA::ORB::run, m_impl->orb.in()));

    int res = m_impl->app->exec();

    m_impl->orb->shutdown(1);

    orbThread.join();

    return res;
}


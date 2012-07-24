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
#include <iostream>
#include <map>
#include <string>

using namespace corbasim::gui;

namespace
{
    struct Client :
        public ::corbasim::core::request_processor
    {
        ::corbasim::gui::Server * server;
        const std::string clientName;
        ::corbasim::core::interface_reflective_base const * reflective;
        ::corbasim::core::interface_caller_ptr caller;
        CORBA::Object_var fakeRef;
        PortableServer::ServantBase * proxyServant;

        Client( ::corbasim::gui::Server * server_,
                const char * clientName_,
                ::corbasim::core::interface_reflective_base const * reflective_
                ) : 
            server(server_),
            clientName(clientName_),
            reflective(reflective_),
            caller(reflective->create_caller()),
            proxyServant(NULL)
        {
        }

        ~Client()
        {
            delete proxyServant;
        }

        ::corbasim::event::event_ptr operator()(
                ::corbasim::event::request_ptr req,
                ::corbasim::event::response_ptr)
        {
            ::corbasim::event::event_ptr ev;
            
            if (!caller->is_nil())
            {
                ev.reset(caller->do_call(req.get()));
            }
            else
            {
                ev.reset(new ::corbasim::event::message("Invalid reference!"));
            }

            server->notifyRequestSent(clientName.c_str(), req, ev);
            
            return ev;
        }
    };

    typedef boost::shared_ptr< Client > Client_ptr;

} // namespace

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

    typedef std::map< std::string, Client_ptr > clients_t;
    clients_t clients;

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

ServerApp::ServerApp(int& argc, char ** argv) :
    m_impl(new ServerApp_i(this))
{
    m_impl->orb = CORBA::ORB_init(argc, argv);

    m_impl->app = new QApplication(argc, argv);

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

namespace  
{
    ::corbasim::core::interface_reflective_base const * 
    getReflectiveByFQN(const char * fqn)
    {
        QString symbol (fqn);
        symbol.replace("::","_");
        symbol.prepend("corbasim_reflective_");

        typedef const corbasim::core::interface_reflective_base *
            (*get_reflective_t)();
        get_reflective_t get_reflective = NULL;

        QLibrary lib(symbol);

        if (lib.load() && 
                (get_reflective = (get_reflective_t) 
                     lib.resolve(symbol.toStdString().c_str())) != NULL)
        {
            return get_reflective();
        }

        return NULL;
    }
} // namespace 

CORBA::Object_var ServerApp::setClient(
        const char * fqn, 
        const char * clientName,
        const CORBA::Object_var& ref)
{
    ServerApp_i::clients_t::iterator it =
        m_impl->clients.find(clientName);

    if (it == m_impl->clients.end())
    {
        ::corbasim::core::interface_reflective_base const * reflective = 
            getReflectiveByFQN(fqn);
       
        if (reflective)
        {
            Client_ptr client(new Client(m_impl->server, clientName, reflective));

            client->proxyServant = reflective->create_servant(client.get());

            PortableServer::ObjectId_var myObjID = 
                m_impl->rootPOA->activate_object (client->proxyServant);

            client->fakeRef =  
                m_impl->rootPOA->servant_to_reference(client->proxyServant);

            client->caller->set_reference(ref);

            m_impl->clients.insert(std::make_pair(clientName, client));

            m_impl->server->notifyClientCreated(clientName, 
                    reflective, 
                    client->fakeRef);

            return client->fakeRef;
        }
        else
        {
            std::cerr << "Library not found!" << std::endl;
        }
    }
    else
    {
        it->second->caller->set_reference(ref);

        return it->second->fakeRef;
    }

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

    assert(m_impl->app);
    int res = m_impl->app->exec();

    m_impl->orb->shutdown(1);

    orbThread.join();

    return res;
}


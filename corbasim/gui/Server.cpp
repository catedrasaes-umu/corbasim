// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Server.cpp
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

#include "Server.hpp"
#include <corbasim/gui/FilteredLogView.hpp>
#include <corbasim/gui/OperationSequence.hpp>

using namespace corbasim::gui;

Server::Server(QWidget * parent) : 
    QMainWindow(parent), m_logModel(this)
{
    // Temporal
    m_view = new FilteredLogView();

    m_view->setLogModel(&m_logModel);

    setCentralWidget(m_view);

    QObject::connect(
            this,
            SIGNAL(requestReceived(
                corbasim::event::request_ptr,
                corbasim::event::event_ptr)),
            this,
            SLOT(appendRequestReceived(
                corbasim::event::request_ptr,
                corbasim::event::event_ptr)));

    QObject::connect(
            this,
            SIGNAL(requestSent(
                const QString&,
                corbasim::event::request_ptr,
                corbasim::event::event_ptr)),
            this,
            SLOT(appendRequestSent(
                const QString&,
                corbasim::event::request_ptr,
                corbasim::event::event_ptr)));

    QObject::connect(
            this,
            SIGNAL(clientCreated(
                const QString&,
                corbasim::core::interface_reflective_base const *,
                const CORBA::Object_var&)),
            this,
            SLOT(setClient(
                const QString&,
                corbasim::core::interface_reflective_base const *,
                const CORBA::Object_var&)));

    // Temporal
    QDialog * m_seqToolDlg = new QDialog(this);
    QVBoxLayout * layout = new QVBoxLayout();
    m_seqTool = new OperationSequenceTool();
    layout->addWidget(m_seqTool);
    m_seqToolDlg->setLayout(layout);
    m_seqToolDlg->show();

    QObject::connect(m_seqTool,
        SIGNAL(sendRequest(QString, corbasim::event::request_ptr)),
        this, 
        SLOT(sendRequest(const QString&, corbasim::event::request_ptr)));
}

Server::~Server() 
{
}

void Server::initialize( 
        ::corbasim::core::interface_reflective_base const * reflective)
{
    m_logModel.registerInstance("this", reflective);
    m_view->registerInstance("this", reflective);
}

void Server::appendRequestReceived(
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    m_logModel.inputRequest("this", req, resp);
}

void Server::appendRequestSent(
        const QString& id,
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    m_logModel.outputRequest(id, req, resp);
}


void Server::notifyRequestReceived(
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    emit requestReceived(req, resp);
}

void Server::notifyRequestSent(
        const QString& id,
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    emit requestSent(id, req, resp);
}

void Server::notifyClientCreated(
        const QString& clientName,
        ::corbasim::core::interface_reflective_base const * reflective,
        const CORBA::Object_var& ref)
{
    emit clientCreated(clientName, reflective, ref);
}

void Server::setClient(
        const QString& clientName,
        ::corbasim::core::interface_reflective_base const * reflective,
        const CORBA::Object_var& ref)
{
    clients_t::iterator it = m_clients.find(clientName);

    if (it != m_clients.end())
    {
        it->second.caller->set_reference(ref);
    }
    else
    {
        ::corbasim::core::interface_caller_ptr caller (reflective->create_caller());
        caller->set_reference(ref);

        const Client client = { reflective, caller};

        m_clients.insert(std::make_pair(clientName, client));

        m_seqTool->objrefCreated(clientName, reflective);
        m_logModel.registerInstance(clientName, reflective);
        m_view->registerInstance(clientName, reflective);

    }
}


void Server::sendRequest(const QString& id, corbasim::event::request_ptr req)
{
    clients_t::const_iterator it = m_clients.find(id);

    if (it != m_clients.end())
    {
        ::corbasim::event::event_ptr resp(it->second.caller->do_call(req.get()));
    }
}


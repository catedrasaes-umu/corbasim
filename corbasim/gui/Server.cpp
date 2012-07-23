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

using namespace corbasim::gui;

Server::Server(QWidget * parent) : 
    QMainWindow(parent) 
{
    // Temporal

    QTreeView * view = new QTreeView();

    view->setModel(&m_logModel);

    setCentralWidget(view);

    QObject::connect(
            this,
            SIGNAL(requestReceived(
                corbasim::event::request_ptr req,
                corbasim::event::event_ptr resp)),
            this,
            SLOT(appendRequestReceived(
                corbasim::event::request_ptr req,
                corbasim::event::event_ptr resp)));
}

Server::~Server() 
{
}

void Server::initialize( 
        ::corbasim::core::interface_reflective_base const * reflective)
{
    m_logModel.registerInstance("this", reflective);
}

void Server::appendRequestReceived(
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    m_logModel.inputRequest("this", req, resp);
}

void Server::notifyRequestReceived(
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    emit requestReceived(req, resp);
}


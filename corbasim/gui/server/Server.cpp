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
#include <corbasim/gui/DumpTool.hpp>

#include <cassert>

using namespace corbasim::gui;

Server::Server(QWidget * parent) : 
    QMainWindow(parent), m_logModel(this), m_objrefs(this)
{
    QTabWidget * tabs = new QTabWidget();

    // Log
    QTreeView * logView = new QTreeView();
    logView->setModel(&m_logModel);
    tabs->addTab(logView, "Log");

    // Filtered log
    m_view = new FilteredLogView();
    m_view->setLogModel(&m_logModel);
    tabs->addTab(m_view, "Filtered log");

    // Clients
    m_seqTool = new OperationSequenceTool();
    tabs->addTab(m_seqTool, "Clients");

    // Dump input
    m_dumpInput = new DumpTool();
    tabs->addTab(m_dumpInput, "Dump input");

#if 0
    // Dump output
    m_dumpOutput = new DumpTool();
    tabs->addTab(m_dumpOutput, "Dump output");
#endif

    // Centra widget
    setCentralWidget(tabs);
}

Server::~Server() 
{
}

void Server::objrefCreated(Objref_ptr objref)
{
    m_objrefs.add(objref);
    m_logModel.registerInstance(objref);

    m_view->registerInstance(objref);
    m_seqTool->objrefCreated(objref);
}

void Server::objrefDeleted(ObjectId id)
{
    m_objrefs.del(id);
    m_logModel.unregisterInstance(id);

    m_view->unregisterInstance(id);
    m_seqTool->objrefDeleted(id);
}

void Server::servantCreated(Objref_ptr servant)
{
    assert(!m_servant.get() && servant.get());
    
    m_servant = servant;
    m_logModel.registerInstance(servant);

    m_view->registerInstance(servant);
    m_dumpInput->registerInstance(servant);
}

void Server::servantDeleted(ObjectId id)
{
}

void Server::displayError(const QString& err)
{
}

void Server::displayMessage(const QString& msg)
{
}


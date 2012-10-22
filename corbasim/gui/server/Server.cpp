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
#include <corbasim/gui/tools/FilteredLogView.hpp>
#include <corbasim/gui/tools/OperationSequence.hpp>
#include <corbasim/gui/tools/DumpTool.hpp>
#include <corbasim/gui/item/TreeView.hpp>
#include <corbasim/gui/item/OperationsView.hpp>

#include <cassert>

using namespace corbasim::gui;

Server::Server(QWidget * parent) : 
    QMainWindow(parent), 
    m_logModel(this), 
    m_appLogModel(this),
    m_instanceModel(this),
    m_objrefs(this)
{
    setWindowIcon(QIcon(":/resources/images/csu.png"));

    QTabWidget * tabs = new QTabWidget();

    // Log
    QTreeView * logView = new TreeView();
    logView->setModel(&m_logModel);
    QDockWidget * logViewDock = new QDockWidget("Log", this);
    logViewDock->setWidget(logView);
    addDockWidget(Qt::BottomDockWidgetArea, logViewDock);

    // Column Width
    int columnCount = m_logModel.columnCount();
    for (int i = 0; i < columnCount; i++) 
    {
        logView->setColumnWidth(i, width() / columnCount);
    }

    // Application log view
    QDockWidget * appLogViewDock = new QDockWidget("Application log", this);
    QTreeView * appLogView = new TreeView();
    appLogView->setModel(&m_appLogModel);
    appLogViewDock->setWidget(appLogView);
    addDockWidget(Qt::BottomDockWidgetArea, appLogViewDock);

    // Column Width
    appLogView->setColumnWidth(0, 350);

    // Moves second dock widget on top of first dock widget, 
    // creating a tabbed docked area in the main window.
    tabifyDockWidget(appLogViewDock, logViewDock);

    // Instances view
    QDockWidget * instanceViewDock = new QDockWidget("Instances", this);
    QTreeView * instanceView = new OperationsView();
    instanceView->setHeaderHidden(true);
    instanceView->setModel(&m_instanceModel);
    instanceView->setExpandsOnDoubleClick(false);
    instanceViewDock->setWidget(instanceView);
    addDockWidget(Qt::LeftDockWidgetArea, instanceViewDock);

    // TODO
    /*
    connect(instanceView, 
            SIGNAL(selectedOperation(Objref_ptr, OperationDescriptor_ptr)),
            this,
            SLOT(selectedOperation(Objref_ptr, OperationDescriptor_ptr)));
     */

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

    // Central widget
    setCentralWidget(tabs);
}

Server::~Server() 
{
}

void Server::objrefCreated(Objref_ptr objref)
{
    m_objrefs.add(objref);
    m_logModel.registerInstance(objref);
    m_instanceModel.registerInstance(objref);

    m_view->registerInstance(objref);
    m_seqTool->objrefCreated(objref);

    connect(objref.get(), 
            SIGNAL(requestSent(ObjectId, Request_ptr, Event_ptr)),
            &m_logModel, 
            SLOT(outputRequest(ObjectId, Request_ptr, Event_ptr)));
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
    m_logModel.registerInstance(servant);
    m_instanceModel.registerInstance(servant);

    m_view->registerInstance(servant);
    m_dumpInput->registerInstance(servant);

    connect(servant.get(), 
            SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
            &m_logModel, 
            SLOT(inputRequest(ObjectId, Request_ptr, Event_ptr)));
}

void Server::servantDeleted(ObjectId id)
{
}

void Server::displayError(const QString& err)
{
    m_appLogModel.error(err);
}

void Server::displayMessage(const QString& msg)
{
    m_appLogModel.message(msg);
}


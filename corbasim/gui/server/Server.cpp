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
#include <corbasim/gui/tools/SenderSequence.hpp>
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

    m_tabs = new QTabWidget();

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
    QDockWidget * appLogViewDock = 
        new QDockWidget("Application log", this);
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

    connect(instanceView, 
            SIGNAL(selectedOperation(Objref_ptr, OperationDescriptor_ptr)),
            this,
            SLOT(selectedOperation(Objref_ptr, OperationDescriptor_ptr)));

    // Filtered log
    m_view = new FilteredLogView();
    m_view->setLogModel(&m_logModel);
    m_tabs->addTab(m_view, "Filtered log");

    // Clients
    m_seqTool = new OperationSequenceTool();
    // We don't register the objrefs in the tool because we don't 
    // use its tree view
    m_seqTool->setTreeVisible(false);
    m_seqIdx = m_tabs->addTab(m_seqTool, "Operations");

    m_senderSeqTool = new SenderSequenceTool();
    // We don't register the objrefs in the tool because we don't 
    // use its tree view
    m_senderSeqTool->setTreeVisible(false);
    m_senderIdx = m_tabs->addTab(m_senderSeqTool, "Senders");

    // Dump input
    m_dumpInput = new DumpTool();
    m_tabs->addTab(m_dumpInput, "Dump input");

    // Central widget
    setCentralWidget(m_tabs);

    // Status bar
    setStatusBar(new QStatusBar());

    // Actions
    // Clear log
    QAction * clearAction = new QAction(
            style()->standardIcon(QStyle::SP_TrashIcon),
            "&Clear log", this);
    connect(clearAction, SIGNAL(triggered()), 
            &m_logModel, SLOT(clearLog()));

    // Clear application log
    QAction * clearAppLogAction = new QAction(
            style()->standardIcon(QStyle::SP_TrashIcon),
            "&Clear application log", this);
    connect(clearAppLogAction, SIGNAL(triggered()), 
            &m_appLogModel, SLOT(clearLog()));

    // Menu bar
    QMenuBar * menuBar = new QMenuBar();
    setMenuBar(menuBar);

    // Tool bar
    QToolBar * toolBar = NULL;

    toolBar = addToolBar("Window");
    toolBar->addAction(clearAction);
    toolBar->addAction(clearAppLogAction);
}

Server::~Server() 
{
}

void Server::selectedOperation(Objref_ptr object, 
        OperationDescriptor_ptr op)
{
    int idx = m_tabs->currentIndex();

    if (idx == m_seqIdx)
    {
        m_seqTool->appendAbstractItem(object, op);
    }
    else if (idx == m_senderIdx)
    {
        m_senderSeqTool->appendAbstractItem(object, op);
    }
    else
    {
        // What?
    }
}

void Server::objrefCreated(Objref_ptr objref)
{
    // Models
    m_objrefs.add(objref);
    m_logModel.registerInstance(objref);
    m_instanceModel.registerInstance(objref);

    // Views
    m_view->registerInstance(objref);

    connect(objref.get(), 
            SIGNAL(requestSent(ObjectId, Request_ptr, Event_ptr)),
            &m_logModel, 
            SLOT(outputRequest(ObjectId, Request_ptr, Event_ptr)));
}

void Server::objrefDeleted(ObjectId id)
{
    // Models
    m_objrefs.del(id);
    m_logModel.unregisterInstance(id);

    // Views
    m_view->unregisterInstance(id);
}

void Server::servantCreated(Objref_ptr servant)
{
    // Models
    m_logModel.registerInstance(servant);
    m_instanceModel.registerInstance(servant);

    // Views
    m_view->registerInstance(servant);
    m_dumpInput->registerInstance(servant);

    connect(servant.get(), 
            SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
            &m_logModel, 
            SLOT(inputRequest(ObjectId, Request_ptr, Event_ptr)));
}

void Server::servantDeleted(ObjectId id)
{
    // Models
    m_logModel.unregisterInstance(id);
    m_instanceModel.unregisterInstance(id);

    // Views
    m_view->unregisterInstance(id);
    m_dumpInput->unregisterInstance(id);

    // TODO disconnect signal: we need the object
}

void Server::displayError(const QString& err)
{
    m_appLogModel.error(err);
}

void Server::displayMessage(const QString& msg)
{
    m_appLogModel.message(msg);
}


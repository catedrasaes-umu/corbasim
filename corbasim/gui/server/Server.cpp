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
#include <corbasim/gui/tools/StatusView.hpp>
#include <corbasim/gui/item/TreeView.hpp>
#include <corbasim/gui/item/OperationsView.hpp>
#include <corbasim/gui/tools/ValueViewerTool.hpp>
#include <corbasim/gui/json.hpp>

#include <corbasim/version.hpp>

#include <fstream>
#include <cassert>

using namespace corbasim::gui;

Server::Server(QWidget * parent) : 
    QMainWindow(parent), 
    m_logModel(this), 
    m_appLogModel(this),
    m_instanceModel(this),
    m_objrefs(this),

    // Tools
    m_plotTool(NULL),

    m_qwtLoaded(false)
{
    setWindowIcon(QIcon(":/resources/images/csu.png"));

    m_tabs = new QTabWidget();

    // StatusView
    m_statusView = new StatusView();
    m_tabs->addTab(m_statusView, "Status");

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
    m_seqTool->setTreeVisible(false);
    m_tabs->addTab(m_seqTool, "Operations");

    m_senderSeqTool = new SenderSequenceTool();
    m_senderSeqTool->setTreeVisible(false);
    m_tabs->addTab(m_senderSeqTool, "Senders");

    // Dump
    m_dumpTool = new DumpTool();
    m_tabs->addTab(m_dumpTool, "Dump");
    
    // Plot input
    QLabel * plotLabel = new QLabel("No corbasim_qwt library available");
    plotLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_plotIdx = m_tabs->addTab(plotLabel, "Plot");

    // Value viewer
    m_valueViewerTool = new ValueViewerTool();
    m_tabs->addTab(m_valueViewerTool, "Value viewer");

    // Central widget
    setCentralWidget(m_tabs);

    // Status bar
    setStatusBar(new QStatusBar());

    // Actions
    // New object
    QAction * newObjAction = new QAction(
            style()->standardIcon(QStyle::SP_FileIcon),
            "&New object reference", this);
    newObjAction->setShortcut(QKeySequence::New);
    connect(newObjAction, SIGNAL(triggered()), 
            this, SLOT(showCreateObjrefDialog()));

    // New servant
    QAction * newSrvAction = new QAction(
            style()->standardIcon(QStyle::SP_FileIcon),
            "N&ew servant", this);
    newSrvAction->setShortcut(QKeySequence::Save);
    connect(newSrvAction, SIGNAL(triggered()), 
            this, SLOT(showCreateServantDialog()));

    // Load configuration
    QAction * loadConfigurationAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogOpenButton),
            "&Load configuration", this);
    connect(loadConfigurationAction, SIGNAL(triggered()), 
            this, SLOT(doLoadConfiguration()));

    // Save configuration
    QAction * saveConfigurationAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogSaveButton),
            "&Save configuration", this);
    connect(saveConfigurationAction, SIGNAL(triggered()), 
            this, SLOT(doSaveConfiguration()));

    // Show log
    QAction * showLogAction = new QAction(
            "Show &log", this);
    connect(showLogAction, SIGNAL(triggered()), 
            logViewDock, SLOT(show()));

    // Show application log
    QAction * showAppLogAction = new QAction(
            "Show app&lication log", this);
    connect(showAppLogAction, SIGNAL(triggered()), 
            appLogViewDock, SLOT(show()));

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

    // About
    QAction * aboutAction = new QAction(
            "&About corbasim", this);
    connect(aboutAction, SIGNAL(triggered()), 
            this, SLOT(showAbout()));

    // Menu bar
    QMenuBar * menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QMenu * menuFile = menuBar->addMenu("&File");
    menuFile->addAction(newObjAction);
    menuFile->addAction(newSrvAction);
    menuFile->addSeparator();
    menuFile->addAction(loadConfigurationAction);
    menuFile->addAction(saveConfigurationAction);
    menuFile->addSeparator();
    QAction * closeAction = 
        menuFile->addAction("&Exit", this, SLOT(close()));
    closeAction->setShortcut(QKeySequence::Close);

    QMenu * menuWindow = menuBar->addMenu("&Window");
    menuWindow->addAction(showLogAction);
    menuWindow->addAction(clearAction);
    menuWindow->addSeparator();
    menuWindow->addAction(showAppLogAction);
    menuWindow->addAction(clearAppLogAction);
    menuWindow->addSeparator();
    menuWindow->addAction(aboutAction);

    // Tool bar
    QToolBar * toolBar = NULL;
    toolBar = addToolBar("File");
    toolBar->addAction(loadConfigurationAction);
    toolBar->addAction(saveConfigurationAction);

    toolBar = addToolBar("Window");
    toolBar->addAction(clearAction);
    toolBar->addAction(clearAppLogAction);

    connect(m_tabs, SIGNAL(currentChanged(int)),
            this, SLOT(currentIndexChanged(int)));
}

Server::~Server() 
{
}

void Server::selectedOperation(Objref_ptr object, 
        OperationDescriptor_ptr op)
{
    QWidget * w = m_tabs->currentWidget();

    if (w == m_seqTool)
    {
        m_seqTool->appendAbstractItem(object, op);
    }
    else if (w == m_senderSeqTool)
    {
        m_senderSeqTool->appendAbstractItem(object, op);
    }
    else
    {
        // What?
    }
}

void Server::currentIndexChanged(int index)
{
    if (index == m_plotIdx) loadPlotTool();
}

void Server::loadPlotTool()
{
    typedef AbstractInputTool* (*create_t)(QWidget*);

    if (!m_qwtLoaded)
    {
        // Loads the library
        QLibrary lib("corbasim_qwt");
        lib.load();

        create_t create = (create_t) lib.resolve("createPlotTool");

        if (create)
        {
            // Creates the tool
            m_plotTool = create(this);

            m_qwtLoaded = true;
            m_tabs->insertTab(m_plotIdx, m_plotTool, "Plot");
            m_tabs->removeTab(m_plotIdx + 1);

            // Initilizes the tool
            ObjrefRepository::const_iterator it = m_servants.begin();
            ObjrefRepository::const_iterator end = m_servants.end();

            for(; it != end; it++)
                m_plotTool->registerInstance(it.value());

            it = m_objrefs.begin();
            end = m_objrefs.end();

            for(; it != end; it++)
                m_plotTool->registerInstance(it.value());
        }
        else
        {
            QMessageBox::critical(this, "Error initializing plot tool", 
                    "Unable to load corbasim_qwt. "
                    "Ensure you have built corbasim with qwt.");
        }
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
    m_statusView->registerInstance(objref);
    m_dumpTool->registerInstance(objref);
    m_valueViewerTool->registerInstance(objref);
    m_seqTool->objrefCreated(objref);
    m_senderSeqTool->objrefCreated(objref);

    if (m_plotTool)
        m_plotTool->registerInstance(objref);

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
    m_statusView->unregisterInstance(id);
    m_dumpTool->unregisterInstance(id);
    m_valueViewerTool->unregisterInstance(id);
    m_seqTool->objrefDeleted(id);
    m_senderSeqTool->objrefDeleted(id);

    if (m_plotTool)
        m_plotTool->unregisterInstance(id);
}

void Server::servantCreated(Objref_ptr servant)
{
    // Models
    m_servants.add(servant);
    m_logModel.registerInstance(servant);
    m_instanceModel.registerInstance(servant);

    // Views
    m_view->registerInstance(servant);
    m_dumpTool->registerInstance(servant);
    m_valueViewerTool->registerInstance(servant);
    m_seqTool->objrefCreated(servant);
    m_senderSeqTool->objrefCreated(servant);

    if (m_plotTool)
        m_plotTool->registerInstance(servant);

    connect(servant.get(), 
            SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
            &m_logModel, 
            SLOT(inputRequest(ObjectId, Request_ptr, Event_ptr)));
}

void Server::servantDeleted(ObjectId id)
{
    // Models
    m_servants.del(id);
    m_logModel.unregisterInstance(id);
    m_instanceModel.unregisterInstance(id);

    // Views
    m_view->unregisterInstance(id);
    m_dumpTool->unregisterInstance(id);
    m_valueViewerTool->unregisterInstance(id);
    m_seqTool->objrefDeleted(id);
    m_senderSeqTool->objrefDeleted(id);

    if (m_plotTool)
        m_plotTool->unregisterInstance(id);

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

void Server::showAbout()
{
    static const char * aboutText = 
        "corbasim version " CORBASIM_VERSION "\n"
        "Build " __DATE__ "\n"
        "Developed by: Andres Senac <andres@senac.es>";

    QMessageBox::about(this, "About corbasim", 
            aboutText);
}

void Server::save(QVariant& settings)
{
    QVariantMap map;

    // Tools
    {
        m_view->save(map["filtered_log"]);

        m_senderSeqTool->save(map["sender_sequences"]);

        m_seqTool->save(map["sequences"]);

        m_dumpTool->save(map["dumpers"]);

        if (m_plotTool)
            m_plotTool->save(map["plots"]);

        m_valueViewerTool->save(map["viewers"]);
    }

    settings = map;
}

void Server::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    // Tools
    {
        if (map.contains("filtered_log"))
        {
            m_view->load(map["filtered_log"]);
        }

        if (map.contains("sender_sequences"))
        {
            m_senderSeqTool->load(map["sender_sequences"]);
        }

        if (map.contains("sequences"))
        {
            m_seqTool->load(map["sequences"]);
        }

        if (map.contains("dumpers"))
        {
            m_dumpTool->load(map["dumpers"]);
        }

        if (map.contains("plots") && m_plotTool)
        {
            m_plotTool->load(map["plots"]);
        }

        if (map.contains("viewers"))
        {
            m_valueViewerTool->load(map["viewers"]);
        }
    }
}

void Server::doLoadConfiguration()
{
    const QString file = 
        QFileDialog::getOpenFileName(0,
                "Select a file", ".",
                tr("CORBASIM generic application configuration (*.cfg)"));

    if (!file.isEmpty())
    {
        QVariant var;

        // Try to Read a JSON file
        bool res = 
            gui::fromJsonFile(file.toStdString().c_str(), var);

        if (res)
        {
            load(var);
        }
        else
        {
            QMessageBox::critical(this, 
                    "Error loading configuration", 
                    QString("Unable to load file ") +
                    file);
        }
    }
}

void Server::doSaveConfiguration()
{
    QString file = 
        QFileDialog::getSaveFileName(0, 
                "Select a file", ".",
                tr("CORBASIM generic application configuration (*.cfg)"));

    if (!file.isEmpty())
    {
        if(!file.endsWith(".cfg"))
            file.append(".cfg");

        QVariant settings;
        save(settings);

        std::ofstream ofs(file.toStdString().c_str());
        json::ostream_writer_t ow(ofs, true);

        gui::toJson(ow, settings);
    }
}

void Server::showCreateObjrefDialog() {}
void Server::showCreateServantDialog() {}


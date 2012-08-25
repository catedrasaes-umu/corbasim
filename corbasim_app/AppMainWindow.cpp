// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppMainWindow.cpp
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

#include "AppMainWindow.hpp"
#include <iostream>

// Tools
#include <corbasim/gui/FilteredLogView.hpp>
#include <corbasim/gui/OperationSequence.hpp>
#include <corbasim/gui/SenderSequence.hpp>
#include <corbasim/gui/DumpTool.hpp>
#include <corbasim/gui/dialog/CreateDialog.hpp>
#include <corbasim/gui/item/TreeView.hpp>

using namespace corbasim::app;

namespace  
{
    enum SubWindows
    {
        kCreateObjrefDialog,
        kCreateServantDialog,

        kFilteredLogView,
        kOperationSequenceTool,
        kSenderSequenceTool,
        kDumpTool,

        kSubWindowsMax
    };

    const char * SubWindowTitles[] = {
        "Create new object reference",
        "Create new servant",
        "Filtered log",
        "Operation sequence tool",
        "Sender sequence tool",
        "Dump tool"
    };
} // namespace

AppMainWindow::AppMainWindow(QWidget * parent) :
    QMainWindow(parent), 
    m_objrefs(this), 
    m_servants(this),
    m_logModel(this),
    m_actions(this),

    // Dialogs
    m_createObjrefDialog(NULL),
    m_createServantDialog(NULL),

    // Tools
    m_filteredLogView(NULL),
    m_operationSequenceTool(NULL),
    m_senderSequenceTool(NULL),
    m_dumpTool(NULL)

{
    setupUi(this);
    
    // TODO
    centralWidget()->layout()->setMargin(0);

    setWindowIcon(QIcon(":/resources/images/csu.png"));

    // Log view
    QDockWidget * logViewDock = new QDockWidget("Log", this);
    m_logView = new TreeView(this);
    m_logView->setModel(&m_logModel);
    logViewDock->setWidget(m_logView);
    addDockWidget(Qt::BottomDockWidgetArea, logViewDock);

    // Column Width
    int columnCount = m_logModel.columnCount();
    for (int i = 0; i < columnCount; i++) 
    {
        m_logView->setColumnWidth(i, width() / columnCount);
    }

    // No more window
    
    connect(menuBar(), SIGNAL(hovered(QAction *)),
            this, SLOT(actionHovered(QAction *)));

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

    // New servant
    QAction * clearAction = new QAction(
            style()->standardIcon(QStyle::SP_TrashIcon),
            "&Clear log", this);
    // clearAction->setShortcut(QKeySequence::Save);
    connect(clearAction, SIGNAL(triggered()), 
            &m_logModel, SLOT(clearLog()));

    // Load scenario
    QAction * loadScenarioAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogOpenButton),
            "&Load scenario", this);
    loadScenarioAction->setShortcut(QKeySequence::Open);
    connect(loadScenarioAction, SIGNAL(triggered()), 
            this, SLOT(showLoadScenario()));

    // Save scenario
    QAction * saveScenarioAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogSaveButton),
            "&Save scenario", this);
    saveScenarioAction->setShortcut(QKeySequence::SaveAs);
    connect(saveScenarioAction, SIGNAL(triggered()), 
            this, SLOT(showSaveScenario()));

    // Clear scenario
    QAction * clearScenarioAction = new QAction(
            style()->standardIcon(QStyle::SP_TrashIcon),
            "&Clear scenario", this);
    // clearScenarioAction->setShortcut(QKeySequence::SaveAs);
    connect(clearScenarioAction, SIGNAL(triggered()), 
            this, SIGNAL(clearScenario()));

    // Load directory
    QAction * loadDirectoryAction = new QAction(
            style()->standardIcon(QStyle::SP_FileDialogNewFolder),
            "&Load plug-in directory", this);
    loadDirectoryAction->setShortcut(QKeySequence::SelectAll);
    connect(loadDirectoryAction, SIGNAL(triggered()), 
            this, SLOT(showLoadDirectory()));

    // Show log
    QAction * showLogAction = new QAction(
            // style()->standardIcon(QStyle::SP_FileDialogNewFolder),
            "Show &log", this);
    // showLogAction->setShortcut(QKeySequence::SelectAll);
    connect(showLogAction, SIGNAL(triggered()), 
            logViewDock, SLOT(show()));

    // Tool bar
    QToolBar * toolBar = addToolBar("File");
    toolBar->addAction(loadScenarioAction);
    toolBar->addAction(saveScenarioAction);
    toolBar->addAction(clearScenarioAction);
    toolBar->addSeparator();
    toolBar->addAction(loadDirectoryAction);
    toolBar->addSeparator();
    toolBar->addAction(newObjAction);
    toolBar->addAction(newSrvAction);
    
    toolBar = addToolBar("Window");
    toolBar->addAction(clearAction);

    // Menus
    menuFile->addAction(newObjAction);
    menuFile->addAction(newSrvAction);
    menuFile->addSeparator();
    menuFile->addAction(loadScenarioAction);
    menuFile->addAction(saveScenarioAction);
    menuFile->addAction(clearScenarioAction);
    menuFile->addSeparator();
    menuFile->addAction(loadDirectoryAction);
    menuFile->addSeparator();
    QAction * closeAction = 
        menuFile->addAction("&Exit", this, SLOT(close()));
    closeAction->setShortcut(QKeySequence::Close);

    menuTool->addAction("&Operation sequences", 
            this, SLOT(showOperationSequenceTool()));
    menuTool->addAction("&Sender sequences", 
            this, SLOT(showSenderSequenceTool()));
    menuTool->addAction("&Dump tool", 
            this, SLOT(showDumpTool()));
    menuTool->addSeparator();
    menuTool->addAction("&Filtered log", 
            this, SLOT(showFilteredLogView()));

    menuWindow->addAction(showLogAction);
    menuWindow->addAction(clearAction);

    // Subwindows
    m_subWindows.resize(kSubWindowsMax, NULL);
}

AppMainWindow::~AppMainWindow()
{
}

void AppMainWindow::objrefCreated(Objref_ptr objref)
{
    if (m_subWindows[kCreateObjrefDialog])
        m_subWindows[kCreateObjrefDialog]->close();

    m_objrefs.add(objref);
    m_logModel.registerInstance(objref);

    ObjrefView_ptr view(new ObjrefView(mdiArea, objref, this));
    m_objrefViews.insert(objref->id(), view);
    menuObject_references->addMenu(view->getMenu());

    connect(view.get(), SIGNAL(deleteObjref(ObjectId)),
            this, SIGNAL(deleteObjref(ObjectId)));

    // connect signals
    connect(objref.get(), SIGNAL(requestSent(ObjectId, Request_ptr, Event_ptr)),
        &m_logModel, SLOT(outputRequest(ObjectId, Request_ptr, Event_ptr)));

    if (m_filteredLogView)
        m_filteredLogView->registerInstance(objref);

    if (m_operationSequenceTool)
        m_operationSequenceTool->objrefCreated(objref);

    if (m_senderSequenceTool)
        m_senderSequenceTool->objrefCreated(objref);
}

void AppMainWindow::objrefDeleted(ObjectId id)
{
    m_objrefs.del(id);
    m_logModel.unregisterInstance(id);

    m_objrefViews.remove(id);

    // Tools
    if (m_filteredLogView)
        m_filteredLogView->unregisterInstance(id);

    if (m_operationSequenceTool)
        m_operationSequenceTool->objrefDeleted(id);

    if (m_senderSequenceTool)
        m_senderSequenceTool->objrefDeleted(id);
}

void AppMainWindow::servantCreated(Objref_ptr servant)
{
    if (m_subWindows[kCreateServantDialog])
        m_subWindows[kCreateServantDialog]->close();

    m_servants.add(servant);
    m_logModel.registerInstance(servant);
    
    ServantView_ptr view(new ServantView(mdiArea, servant, this));
    m_servantViews.insert(servant->id(), view);
    menuServants->addMenu(view->getMenu());

    connect(view.get(), SIGNAL(deleteServant(ObjectId)),
            this, SIGNAL(deleteServant(ObjectId)));

    // connect signals
    connect(servant.get(), SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
        &m_logModel, SLOT(inputRequest(ObjectId, Request_ptr, Event_ptr)));

    if (m_filteredLogView)
        m_filteredLogView->registerInstance(servant);

    if (m_dumpTool)
        m_dumpTool->registerInstance(servant);
}

void AppMainWindow::servantDeleted(ObjectId id)
{
    m_servants.del(id);
    m_logModel.unregisterInstance(id);
    
    m_servantViews.remove(id);

    // Tools
    if (m_filteredLogView)
        m_filteredLogView->unregisterInstance(id);
    
    if (m_dumpTool)
        m_dumpTool->unregisterInstance(id);
}

void AppMainWindow::displayError(const QString& err)
{
    QMessageBox::critical(this, "Error", err);

    statusBar()->showMessage(err, 30000);
}

void AppMainWindow::displayMessage(const QString& msg)
{
    statusBar()->showMessage(msg, 30000);
}

//
//
// Dialogs
//
//
void AppMainWindow::showCreateObjrefDialog()
{
    if (!m_createObjrefDialog)
    {
        m_createObjrefDialog = new ObjrefCreateDialog(this);

        createToolSubWindow(kCreateObjrefDialog, m_createObjrefDialog);

        connect(m_createObjrefDialog, 
                SIGNAL(createObjref(const ObjrefConfig&)),
                this, 
                SIGNAL(createObjref(const ObjrefConfig&)));
    }

    showToolSubWindow(kCreateObjrefDialog);
}

void AppMainWindow::showCreateServantDialog()
{
    if (!m_createServantDialog)
    {
        m_createServantDialog = new ServantCreateDialog(this);

        createToolSubWindow(kCreateServantDialog, m_createServantDialog);

        connect(m_createServantDialog, 
                SIGNAL(createServant(const ServantConfig&)),
                this, 
                SIGNAL(createServant(const ServantConfig&)));
    }

    showToolSubWindow(kCreateServantDialog);
}

// 
//
// Tools
//
//

void AppMainWindow::createToolSubWindow(int tool, QWidget * widget)
{
    QMdiSubWindow *& sub = m_subWindows[tool];

    sub = new QMdiSubWindow();
    sub->setWidget(widget);
    sub->setWindowTitle(SubWindowTitles[tool]);
    sub->setWindowIcon(QIcon(":/resources/images/csu.png"));
    mdiArea->addSubWindow(sub);
}

void AppMainWindow::showToolSubWindow(int tool)
{
    QMdiSubWindow * sub = m_subWindows[tool];

    sub->showNormal();
    sub->widget()->show();
    mdiArea->setActiveSubWindow(sub);
}

void AppMainWindow::createFilteredLogView()
{
    if (!m_filteredLogView)
    {
        m_filteredLogView = new FilteredLogView();
        m_filteredLogView->setLogModel(&m_logModel);

        createToolSubWindow(kFilteredLogView, m_filteredLogView);

        // Initilizes the tool
        ObjrefRepository::const_iterator it = m_objrefs.begin();
        ObjrefRepository::const_iterator end = m_objrefs.end();

        for(; it != end; it++)
            m_filteredLogView->registerInstance(it.value());

        it = m_servants.begin();
        end = m_servants.end();

        for(; it != end; it++)
            m_filteredLogView->registerInstance(it.value());
    }
}

void AppMainWindow::showFilteredLogView()
{
    createFilteredLogView();
    showToolSubWindow(kFilteredLogView);
}

void AppMainWindow::createOperationSequenceTool()
{
    if (!m_operationSequenceTool)
    {
        m_operationSequenceTool = new OperationSequenceTool(this);

        createToolSubWindow(kOperationSequenceTool, m_operationSequenceTool);

        // Initilizes the tool
        ObjrefRepository::const_iterator it = m_objrefs.begin();
        ObjrefRepository::const_iterator end = m_objrefs.end();

        for(; it != end; it++)
            m_operationSequenceTool->objrefCreated(it.value());
    }
}

void AppMainWindow::showOperationSequenceTool()
{
    createOperationSequenceTool();
    showToolSubWindow(kOperationSequenceTool);
}

void AppMainWindow::createSenderSequenceTool()
{
    if (!m_senderSequenceTool)
    {
        m_senderSequenceTool = new SenderSequenceTool(this);

        createToolSubWindow(kSenderSequenceTool, m_senderSequenceTool);

        // Initilizes the tool
        ObjrefRepository::const_iterator it = m_objrefs.begin();
        ObjrefRepository::const_iterator end = m_objrefs.end();

        for(; it != end; it++)
            m_senderSequenceTool->objrefCreated(it.value());
    }
}

void AppMainWindow::showSenderSequenceTool()
{
    createSenderSequenceTool();
    showToolSubWindow(kSenderSequenceTool);
}

void AppMainWindow::createDumpTool()
{
    if (!m_dumpTool)
    {
        m_dumpTool = new DumpTool(this);

        createToolSubWindow(kDumpTool, m_dumpTool);

        // Initilizes the tool
        ObjrefRepository::const_iterator it = m_servants.begin();
        ObjrefRepository::const_iterator end = m_servants.end();

        for(; it != end; it++)
            m_dumpTool->registerInstance(it.value());
    }
}

void AppMainWindow::showDumpTool()
{
    createDumpTool();
    showToolSubWindow(kDumpTool);
}

void AppMainWindow::showLoadDirectory()
{
    const QString directory = 
        QFileDialog::getExistingDirectory(0, 
                "Select a directory", ".");

    if (!directory.isEmpty())
    {
        emit loadDirectory(directory);
    }
}

void AppMainWindow::showLoadScenario()
{
    const QString file = 
        QFileDialog::getOpenFileName(0,
                "Select a file", ".");

    if (!file.isEmpty())
    {
        emit loadScenario(file);
    }
}

void AppMainWindow::showSaveScenario()
{
    const QString file = 
        QFileDialog::getSaveFileName(0, 
                "Select a file", ".");

    if (!file.isEmpty())
    {
        emit saveScenario(file);
    }
}

void AppMainWindow::actionHovered(QAction * action)
{
    statusBar()->showMessage(action->text(), 30000);
}


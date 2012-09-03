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
#include <fstream>

// Tools
#include <corbasim/gui/tools/FilteredLogView.hpp>
#include <corbasim/gui/tools/OperationSequence.hpp>
#include <corbasim/gui/tools/SenderSequence.hpp>
#include <corbasim/gui/tools/DumpTool.hpp>
#include <corbasim/gui/dialog/CreateDialog.hpp>
#include <corbasim/gui/dialog/SetReferenceDialog.hpp>
#include <corbasim/gui/item/OperationsView.hpp>
#include <corbasim/gui/item/TreeView.hpp>
#include <corbasim/qt/initialize.hpp>
#include <corbasim/gui/json.hpp>

#include <corbasim/version.hpp>

using namespace corbasim::app;

namespace  
{
    enum SubWindows
    {
        kCreateObjrefDialog,
        kCreateServantDialog,
        kSetNameServiceDialog,

        kFilteredLogView,
        kOperationSequenceTool,
        kSenderSequenceTool,
        kDumpTool,
        kPlotTool,

        kSubWindowsMax
    };

    const char * SubWindowTitles[] = {
        "Create new object reference",
        "Create new servant",
        "Set Name Service",
        "Filtered log",
        "Operation sequence tool",
        "Sender sequence tool",
        "Dump tool",
        "Plot tool"
    };
} // namespace

AppMainWindow::AppMainWindow(QWidget * parent) :
    QMainWindow(parent), 
    m_objrefs(this), 
    m_servants(this),
    m_logModel(this),
    m_instanceModel(this),
    m_interfaceModel(this),
    m_actions(this),

    // Dialogs
    m_createObjrefDialog(NULL),
    m_createServantDialog(NULL),
    m_setNameServiceDialog(NULL),

    // Tools
    m_filteredLogView(NULL),
    m_operationSequenceTool(NULL),
    m_senderSequenceTool(NULL),
    m_dumpTool(NULL),
    m_plotTool(NULL)

{
    corbasim::qt::setDefaultInstanceModel(&m_instanceModel);

    setupUi(this);
    
    // TODO
    centralWidget()->layout()->setMargin(0);

    setWindowIcon(QIcon(":/resources/images/csu.png"));

    // Log view
    QDockWidget * logViewDock = new QDockWidget("Log", this);
    m_logView = new TreeView();
    m_logView->setModel(&m_logModel);
    logViewDock->setWidget(m_logView);
    addDockWidget(Qt::BottomDockWidgetArea, logViewDock);

    // Column Width
    int columnCount = m_logModel.columnCount();
    for (int i = 0; i < columnCount; i++) 
    {
        m_logView->setColumnWidth(i, width() / columnCount);
    }

    // Instances view
    QDockWidget * instanceViewDock = new QDockWidget("Instances", this);
    QTreeView * instanceView = new OperationsView();
    instanceView->setHeaderHidden(true);
    instanceView->setModel(&m_instanceModel);
    instanceViewDock->setWidget(instanceView);
    addDockWidget(Qt::LeftDockWidgetArea, instanceViewDock);

    connect(instanceView, 
            SIGNAL(selectedOperation(Objref_ptr, OperationDescriptor_ptr)),
            this,
            SLOT(selectedOperation(Objref_ptr, OperationDescriptor_ptr)));

    // Interfaces view
    QDockWidget * interfaceViewDock = new QDockWidget("Interfaces", this);
    TreeView * interfaceView = new TreeView();
    interfaceView->setHeaderHidden(true);
    interfaceView->setModel(&m_interfaceModel);
    interfaceViewDock->setWidget(interfaceView);
    addDockWidget(Qt::LeftDockWidgetArea, interfaceViewDock);

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

    // Set name service reference
    QAction * setNSAction = new QAction(
            style()->standardIcon(QStyle::SP_FileIcon),
            "Set Name Service reference", this);
    // setNSAction->setShortcut(QKeySequence::Save);
    connect(setNSAction, SIGNAL(triggered()), 
            this, SLOT(showSetNameServiceDialog()));

    // Clear log
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

    // Show instances
    QAction * showInstancesAction = new QAction(
            "Show &instances", this);
    connect(showInstancesAction, SIGNAL(triggered()), 
            instanceViewDock, SLOT(show()));

    // Show interfaces
    QAction * showInterfacesAction = new QAction(
            "Show i&nterfaces", this);
    connect(showInterfacesAction, SIGNAL(triggered()), 
            interfaceViewDock, SLOT(show()));

    // Stop
    QAction * stopAction = new QAction(
            style()->standardIcon(QStyle::SP_MediaStop),
            "&Stop all", this);
    // stopAction->setShortcut(QKeySequence::Cut);
    connect(stopAction, SIGNAL(triggered()), 
            this, SLOT(stopAll()));

    // About
    QAction * setMaxLogSizeAction = new QAction(
            "Set &max log size", this);
    connect(setMaxLogSizeAction, SIGNAL(triggered()), 
            this, SLOT(showSetMaxLogSize()));

    // About
    QAction * aboutAction = new QAction(
            "&About corbasim", this);
    connect(aboutAction, SIGNAL(triggered()), 
            this, SLOT(showAbout()));

    // Tool bar
    QToolBar * toolBar = addToolBar("File");
    toolBar->addAction(loadScenarioAction);
    toolBar->addAction(saveScenarioAction);
    toolBar->addAction(clearScenarioAction);
    toolBar->addSeparator();
    toolBar->addAction(loadConfigurationAction);
    toolBar->addAction(saveConfigurationAction);
    toolBar->addSeparator();
    toolBar->addAction(loadDirectoryAction);
    toolBar->addSeparator();
    toolBar->addAction(newObjAction);
    toolBar->addAction(newSrvAction);
    
    toolBar = addToolBar("Window");
    toolBar->addAction(clearAction);
    toolBar->addAction(stopAction);

    // Menus
    menuFile->addAction(newObjAction);
    menuFile->addAction(newSrvAction);
    menuFile->addSeparator();
    menuFile->addAction(loadScenarioAction);
    menuFile->addAction(saveScenarioAction);
    menuFile->addAction(clearScenarioAction);
    menuFile->addSeparator();
    menuFile->addAction(loadConfigurationAction);
    menuFile->addAction(saveConfigurationAction);
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
    menuTool->addSeparator();
    menuTool->addAction("&Dump tool", 
            this, SLOT(showDumpTool()));
    menuTool->addAction("&Plot tool", 
            this, SLOT(showPlotTool()));
    menuTool->addSeparator();
    menuTool->addAction("&Filtered log", 
            this, SLOT(showFilteredLogView()));

    menuWindow->addAction(setNSAction);
    menuWindow->addSeparator();
    menuWindow->addAction(setMaxLogSizeAction);
    menuWindow->addAction(showLogAction);
    menuWindow->addAction(clearAction);
    menuWindow->addSeparator();
    menuWindow->addAction(showInstancesAction);
    menuWindow->addAction(showInterfacesAction);
    menuWindow->addSeparator();
    menuWindow->addAction(stopAction);

    menuHelp->addAction(aboutAction);

    // Subwindows
    m_subWindows.resize(kSubWindowsMax, NULL);
}

AppMainWindow::~AppMainWindow()
{
}

void AppMainWindow::save(QVariant& settings)
{
    QVariantMap map;

    // objects
    {
        QVariantList objects;

        for (ObjrefViews_t::iterator it = m_objrefViews.begin(); 
                it != m_objrefViews.end(); ++it) 
        {
            QVariantMap value;
            value["name"] = (*it)->objref()->name();
            (*it)->save(value["value"]);

            objects << value;
        }

        map["objects"] = objects;
    }

    // Servants
    {
        QVariantList servants;

        for (ServantViews_t::iterator it = m_servantViews.begin(); 
                it != m_servantViews.end(); ++it) 
        {
            QVariantMap value;
            value["name"] = (*it)->servant()->name();
            (*it)->save(value["value"]);

            servants << value;
        }

        map["servants"] = servants;
    }

    // Tools
    {
        if (m_filteredLogView)
            m_filteredLogView->save(map["filtered_log"]);

        if (m_senderSequenceTool)
            m_senderSequenceTool->save(map["sender_sequences"]);

        if (m_operationSequenceTool)
            m_operationSequenceTool->save(map["sequences"]);

        if (m_dumpTool)
            m_dumpTool->save(map["dumpers"]);

        if (m_plotTool)
            m_plotTool->save(map["plots"]);
    }

    settings = map;
}

void AppMainWindow::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    // Objects
    {
        const QVariantList list = map["objects"].toList();

        for (QVariantList::const_iterator it = list.begin(); 
                it != list.end(); ++it) 
        {
            const QVariantMap value = it->toMap();
            const QString name = value["name"].toString();
            
            Objref_ptr objref = m_objrefs.find(name);

            if (objref)
            {
                m_objrefViews[objref->id()]->load(value["value"]);
            }
        }
    }

    // Servants
    {
        const QVariantList list = map["servants"].toList();

        for (QVariantList::const_iterator it = list.begin(); 
                it != list.end(); ++it) 
        {
            const QVariantMap value = it->toMap();
            const QString name = value["name"].toString();
            
            Objref_ptr servant = m_servants.find(name);

            if (servant)
            {
                m_servantViews[servant->id()]->load(value["value"]);
            }
        }
    }
    
    // Tools
    {
        if (map.contains("filtered_log"))
        {
            createFilteredLogView();
            m_filteredLogView->load(map["filtered_log"]);
        }

        if (map.contains("sender_sequences"))
        {
            createSenderSequenceTool();
            m_senderSequenceTool->load(map["sender_sequences"]);
        }

        if (map.contains("sequences"))
        {
            createOperationSequenceTool();
            m_operationSequenceTool->load(map["sequences"]);
        }

        if (map.contains("dumpers"))
        {
            createDumpTool();
            m_dumpTool->load(map["dumpers"]);
        }

        if (map.contains("plots"))
        {
            createPlotTool();
            m_plotTool->load(map["plots"]);
        }
    }
}

void AppMainWindow::loadedInterface(
        InterfaceDescriptor_ptr interface)
{
    m_interfaceModel.addInterface(interface);
}

void AppMainWindow::objrefCreated(Objref_ptr objref)
{
    if (m_subWindows[kCreateObjrefDialog])
        m_subWindows[kCreateObjrefDialog]->close();

    m_objrefs.add(objref);
    m_logModel.registerInstance(objref);
    m_instanceModel.registerInstance(objref);

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
    m_instanceModel.unregisterInstance(id);

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
    m_instanceModel.registerInstance(servant);
    
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

    if (m_plotTool)
        m_plotTool->registerInstance(servant);
}

void AppMainWindow::servantDeleted(ObjectId id)
{
    m_servants.del(id);
    m_logModel.unregisterInstance(id);
    m_instanceModel.unregisterInstance(id);
    
    m_servantViews.remove(id);

    // Tools
    if (m_filteredLogView)
        m_filteredLogView->unregisterInstance(id);
    
    if (m_dumpTool)
        m_dumpTool->unregisterInstance(id);

    if (m_plotTool)
        m_plotTool->unregisterInstance(id);
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
        m_createObjrefDialog->setFQNModel(&m_interfaceModel);

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
        m_createServantDialog->setFQNModel(&m_interfaceModel);

        createToolSubWindow(kCreateServantDialog, m_createServantDialog);

        connect(m_createServantDialog, 
                SIGNAL(createServant(const ServantConfig&)),
                this, 
                SIGNAL(createServant(const ServantConfig&)));
    }

    showToolSubWindow(kCreateServantDialog);
}

void AppMainWindow::showSetNameServiceDialog()
{
    if (!m_setNameServiceDialog)
    {
        m_setNameServiceDialog = new SetReferenceDialog(this);

        createToolSubWindow(kSetNameServiceDialog, m_setNameServiceDialog);

        connect(m_setNameServiceDialog, 
                SIGNAL(setReference(const CORBA::Object_var&)),
                this, 
                SIGNAL(setNameService(const CORBA::Object_var&)));
    }

    showToolSubWindow(kSetNameServiceDialog);
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

    if (sub)
    {
        sub->showNormal();
        sub->widget()->show();
        mdiArea->setActiveSubWindow(sub);
    }
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
        m_operationSequenceTool->setTreeVisible(false);

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
        m_senderSequenceTool->setTreeVisible(false);

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

void AppMainWindow::createPlotTool()
{
    typedef AbstractInputTool* (*create_t)(QWidget*);

    if (!m_plotTool)
    {
        // Loads the library
        QLibrary lib("corbasim_qwt");
        lib.load();

        create_t create = (create_t) lib.resolve("createPlotTool");

        if (create)
        {
            // Creates the tool
            m_plotTool = create(NULL);

            createToolSubWindow(kPlotTool, m_plotTool);

            // Initilizes the tool
            ObjrefRepository::const_iterator it = m_servants.begin();
            ObjrefRepository::const_iterator end = m_servants.end();

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

void AppMainWindow::showPlotTool()
{
    createPlotTool();
    showToolSubWindow(kPlotTool);
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

void AppMainWindow::doLoadConfiguration()
{
    const QString file = 
        QFileDialog::getOpenFileName(0,
                "Select a file", ".");

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

void AppMainWindow::doSaveConfiguration()
{
    const QString file = 
        QFileDialog::getSaveFileName(0, 
                "Select a file", ".");

    if (!file.isEmpty())
    {
        QVariant settings;
        save(settings);

        std::ofstream ofs(file.toStdString().c_str());
        json::ostream_writer_t ow(ofs, true);

        gui::toJson(ow, settings);
    }
}

void AppMainWindow::actionHovered(QAction * action)
{
    statusBar()->showMessage(action->text(), 30000);
}

void AppMainWindow::stopAll()
{
    for (ObjrefViews_t::iterator it = m_objrefViews.begin(); 
            it != m_objrefViews.end(); ++it) 
    {
        (*it)->stopAll();
    }
}

void AppMainWindow::selectedOperation(Objref_ptr object, 
        OperationDescriptor_ptr op)
{
    QMdiSubWindow * sub = mdiArea->activeSubWindow();

    if (!dynamic_cast< Servant * >(object.get()))
    {
        if (sub && m_subWindows[kOperationSequenceTool] == sub)
        {
            m_operationSequenceTool->appendAbstractItem(
                    object, op);
        }
        else if (sub && 
                m_subWindows[kSenderSequenceTool] == sub)
        {
            m_senderSequenceTool->appendAbstractItem(
                    object, op);
        }
        else
        {
            ObjrefViews_t::iterator it = 
                m_objrefViews.find(object->id());

            if (it != m_objrefViews.end())
            {
                (*it)->showRequestDialog(op);
            }
        }
    }
}

void AppMainWindow::showAbout()
{
    static const char * aboutText = 
        "corbasim version " CORBASIM_VERSION "\n"
        "Developed by: Andres Senac <andres@senac.es>";

    QMessageBox::about(this, "About corbasim", 
            aboutText);
}

void AppMainWindow::showSetMaxLogSize()
{   
    bool ok = false;
    int res = QInputDialog::getInt(this, "Max log size",
            "Insert the log maximum size", 
            m_logModel.maxEntries(),
            1, 10000, 1, &ok);

    if (ok)
    {
        m_logModel.setMaxEntries(res);
    }
}


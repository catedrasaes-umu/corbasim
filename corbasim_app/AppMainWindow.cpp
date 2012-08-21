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
#include "AppController.hpp"
#include "TriggerEngine.hpp"
#include "view/CreateDialog.hpp"
#include "AboutDialog.hpp"
#include <corbasim/qt/ScriptWindow.hpp>
#include <corbasim/gui/OperationSequence.hpp>
#include <corbasim/gui/SenderSequence.hpp>
#include <corbasim/gui/FilteredLogView.hpp>
#include <corbasim/qwt/ReflectivePlotTool.hpp>
#include <corbasim/gui/DumpTool.hpp>
#include <corbasim/gui/json.hpp>

#include <corbasim/version.hpp>

#include <QLibrary>
#include <QtScript>
#include <fstream>

using namespace corbasim::app;

AppMainWindow::AppMainWindow(QWidget * parent) :
    QMainWindow(parent), m_controller(NULL), m_engine(NULL),

    m_aboutDlg(NULL),

    // Subwindows
    m_sub_create_objref(NULL),
    m_sub_create_servant(NULL),
    m_sub_script(NULL),
    m_sub_seq_tool(NULL),
    m_sub_sender_seq_tool(NULL),

    // Widgets
    m_create_objref(NULL),
    m_create_servant(NULL),
    m_script(NULL),
    m_seq_tool(NULL),
    m_sender_seq_tool(NULL),

    m_filtered_log(NULL),

    m_dlg_dump_tool(NULL),
    m_dump_tool(NULL),
    m_plot_tool(NULL)
{
    m_mdi_area = new QMdiArea;

    // Log dock widget
    m_dock_log = new QDockWidget("Log", this);
    m_log = new QTreeView();

    m_dock_log->setWidget(m_log);
    addDockWidget(Qt::RightDockWidgetArea, m_dock_log);

    // Dock widgets
    m_dock_app_log = new QDockWidget("Application log", this);
    m_app_log = new QTreeWidget;
    m_dock_app_log->setWidget(m_app_log);
    addDockWidget(Qt::RightDockWidgetArea, m_dock_app_log);

    // FQNs
    m_dock_fqn = new QDockWidget("Available interfaces", this);
    m_fqn = new QTreeView;
    m_dock_fqn->setWidget(m_fqn);
    addDockWidget(Qt::RightDockWidgetArea, m_dock_fqn);

    // Disables the header
    // m_log->header()->hide();
    m_app_log->header()->hide();
    m_fqn->header()->hide();

    setCentralWidget(m_mdi_area);

    QMainWindow * filtered_log_dlg = new QMainWindow(this);
    // Filtered log
    {
        m_filtered_log = new gui::FilteredLogView();

        filtered_log_dlg->setCentralWidget(m_filtered_log);

        filtered_log_dlg->setWindowTitle("Filtered log");
    }
    // Actions
   
    // New object
    QAction * newObjAction = new QAction(
            style()->standardIcon(QStyle::SP_FileIcon),
            "&New object reference", this);
    newObjAction->setShortcut(QKeySequence::New);
    QObject::connect(newObjAction, SIGNAL(triggered()), 
            this, SLOT(showCreateObjref()));

    // New servant
    QAction * newSrvAction = new QAction(
            style()->standardIcon(QStyle::SP_FileIcon),
            "N&ew servant", this);
    newSrvAction->setShortcut(QKeySequence::Save);
    QObject::connect(newSrvAction, SIGNAL(triggered()), 
            this, SLOT(showCreateServant()));

    // Load
    QAction * loadScenarioAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogOpenButton),
            "&Load scenario", this);
    loadScenarioAction->setShortcut(QKeySequence::Open);
    QObject::connect(loadScenarioAction, SIGNAL(triggered()), 
            this, SLOT(showLoad()));

    // Save
    QAction * saveScenarioAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogSaveButton),
            "&Save scenario", this);
    saveScenarioAction->setShortcut(QKeySequence::SaveAs);
    QObject::connect(saveScenarioAction, SIGNAL(triggered()), 
            this, SLOT(showSave()));

    // Load
    QAction * loadAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogOpenButton),
            "&Load configuration", this);
    //loadAction->setShortcut(QKeySequence::Open);
    QObject::connect(loadAction, SIGNAL(triggered()), 
            this, SLOT(doLoad()));

    // Save
    QAction * saveAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogSaveButton),
            "&Save configuration", this);
    //saveAction->setShortcut(QKeySequence::SaveAs);
    QObject::connect(saveAction, SIGNAL(triggered()), 
            this, SLOT(doSave()));

    // Append
    QAction * appendAction = new QAction(
            style()->standardIcon(QStyle::SP_FileDialogNewFolder),
            "&Append plug-in directory", this);
    appendAction->setShortcut(QKeySequence::SelectAll);
    QObject::connect(appendAction, SIGNAL(triggered()), 
            this, SLOT(showLoadDirectory()));

    // Tool bar
    QToolBar * toolBar = addToolBar("File");
    toolBar->addAction(loadScenarioAction);
    toolBar->addAction(saveScenarioAction);
    toolBar->addAction(newObjAction);
    toolBar->addAction(newSrvAction);
   
    /*
    toolBar->addWidget(new QLabel("Operation dialog:"));
    m_completer = new QCompleter(this);
    QComboBox * opSelector = new QComboBox;
    opSelector->setEditable(true);
    opSelector->setInsertPolicy(QComboBox::NoInsert);
    opSelector->setCompleter(m_completer);
    toolBar->addWidget(opSelector);
    */

    // Menu
    QMenuBar * menu = new QMenuBar;
    setMenuBar(menu);

    QMenu * menuFile = menu->addMenu("&File");
    menuFile->addAction(newObjAction);
    menuFile->addAction(newSrvAction);
    menuFile->addSeparator();
    menuFile->addAction(loadScenarioAction);
    menuFile->addAction(saveScenarioAction);
    menuFile->addSeparator();
    menuFile->addAction(loadAction);
    menuFile->addAction(saveAction);
/*
    menuFile->addAction("&Clear configuration", this, 
            SLOT(clearConfig()));
 */
    menuFile->addSeparator();
    menuFile->addAction(appendAction);
    menuFile->addSeparator();
    QAction * closeAction = 
        menuFile->addAction("&Exit", this, SLOT(close()));
    closeAction->setShortcut(QKeySequence::Close);

    m_menuObjects = menu->addMenu("&Objects");
    m_menuServants = menu->addMenu("&Servants");
    
    QMenu * tools = menu->addMenu("&Tools");
    tools->addAction("&Load script", this, SLOT(showLoadScript()));
    // TODO tools->addAction("&Run script", this, SLOT(showScript()));
    tools->addSeparator();
    tools->addAction("&Operation sequences", 
            this, SLOT(showOpSequenceTool()));
    tools->addAction("&Sender sequences", 
            this, SLOT(showSenderSequenceTool()));
    tools->addAction("&Filtered log", 
            filtered_log_dlg, SLOT(show()));
    tools->addSeparator();
    tools->addAction("&Plot tool", 
            this, SLOT(showPlotTool()));
    tools->addAction("&Dump tool", 
            this, SLOT(showDumpTool()));

    QMenu * winMenu = menu->addMenu("&Window");
    winMenu->addAction("&Show log", m_dock_log, SLOT(show()));
    winMenu->addAction("&Clear log", this, SLOT(clearLog()));
    winMenu->addSeparator();
    winMenu->addAction("Show &application log", 
            m_dock_app_log, SLOT(show()));
    winMenu->addAction("Clear application &log", 
            m_app_log, SLOT(clear()));
    winMenu->addSeparator();
    winMenu->addAction("Show available &interfaces", 
            m_dock_fqn, SLOT(show()));
    QMenu * aboutMenu = menu->addMenu("&About");
    aboutMenu->addAction("&About corbasim generic application", 
            this, SLOT(showAboutDlg()));

    // Status bar
    m_statusBar = new QStatusBar;
    setStatusBar(m_statusBar);
    
    setWindowIcon(QIcon(":/resources/images/csu.png"));
    setWindowTitle("corbasim generic application");

    // Regiter types
    qRegisterMetaType< corbasim::app::ObjrefConfig >
        ("corbasim::app::ObjrefConfig");
    qRegisterMetaType< corbasim::app::ServantConfig >
        ("corbasim::app::ServantConfig");

    qRegisterMetaType< CORBA::Object_var >
        ("CORBA::Object_var");
}

AppMainWindow::~AppMainWindow()
{
    delete m_sub_create_objref;
    delete m_sub_create_servant;
    delete m_sub_script;
}


void AppMainWindow::showAboutDlg()
{
    if (!m_aboutDlg)
    {
        m_aboutDlg = new AboutDialog(this);
    }

    m_aboutDlg->show();
}

void AppMainWindow::clearLog()
{
    emit doClearLog();
}

void AppMainWindow::setController(AppController * controller)
{
    m_controller = controller;

    m_fqn->setModel(controller->getFQNModel());

    // Signals
    QObject::connect(
            m_controller,
            SIGNAL(objrefCreated(Objref_ptr)),
            this,
            SLOT(objrefCreated(Objref_ptr)));
    QObject::connect(
            m_controller,
            SIGNAL(objrefDeleted(ObjectId)),
            this,
            SLOT(objrefDeleted(ObjectId)));

    QObject::connect(
            m_controller,
            SIGNAL(servantCreated(Objref_ptr)),
            this,
            SLOT(servantCreated(Objref_ptr)));
    QObject::connect(
            m_controller,
            SIGNAL(servantDeleted(ObjectId)),
            this,
            SLOT(servantDeleted(ObjectId)));

    QObject::connect(m_controller, SIGNAL(error(QString)),
            this, SLOT(displayError(const QString&)));
    QObject::connect(m_controller, SIGNAL(message(QString)),
            this, SLOT(displayMessage(const QString&)));

    QObject::connect(this, SIGNAL(saveFile(QString)),
            m_controller, SLOT(saveFile(const QString&)));
    QObject::connect(this, SIGNAL(loadFile(QString)),
            m_controller, SLOT(loadFile(const QString&)));

    QObject::connect(this, SIGNAL(loadDirectory(QString)),
            m_controller, SLOT(loadDirectory(const QString&)));

#define CORBASIM_APP_CON(ev)                                         \
    QObject::connect(m_controller,                                   \
    SIGNAL(ev(QString, Request_ptr,                 \
            Event_ptr)),                            \
    this,                                                            \
    SLOT(ev(const QString&, Request_ptr,            \
            Event_ptr)));                           \
    /***/

    CORBASIM_APP_CON(requestSent);
    CORBASIM_APP_CON(requestReceived);

#undef CORBASIM_APP_CON

    QObject::connect(m_controller, 
            SIGNAL(updatedReference(QString, CORBA::Object_var)),
            this, SLOT(updatedReference(const QString&,
                    const CORBA::Object_var&)));

    // Filtered log
    {
        QObject::connect(
                m_controller,
                SIGNAL(objrefCreated(
                        QString, 
                        InterfaceDescriptor_ptr)),
                m_filtered_log,
                SLOT(registerInstance(
                        const QString&, const 
                        InterfaceDescriptor_ptr)));
        QObject::connect(
                m_controller,
                SIGNAL(objrefDeleted(QString)),
                m_filtered_log,
                SLOT(unregisterInstance(const QString&)));

        QObject::connect(
                m_controller,
                SIGNAL(servantCreated(
                        QString, 
                        InterfaceDescriptor_ptr)),
                m_filtered_log,
                SLOT(registerInstance(
                        const QString&, const 
                        InterfaceDescriptor_ptr)));
        QObject::connect(
                m_controller,
                SIGNAL(servantDeleted(QString)),
                m_filtered_log,
                SLOT(unregisterInstance(const QString&)));
    }
}

void AppMainWindow::setLogModel(QAbstractItemModel * model)
{
    m_log->setModel(model);
    m_log->setColumnWidth(0, 350);
    m_log->setColumnWidth(1, 350);
    m_log->setColumnWidth(2, 350);

    m_filtered_log->setLogModel(model);

    QObject::connect(this, SIGNAL(doClearLog()),
            model, SLOT(clearLog()));

    QObject::connect(model, SIGNAL(rowsInserted(const QModelIndex&, int, int)),
            this, SLOT(scrollToItem(const QModelIndex&, int, int)));
}

void AppMainWindow::scrollToItem(const QModelIndex & parent, int start, int end)
{
    QModelIndex index = m_log->model()->index(start, 0, parent);
    m_log->scrollTo(index);
}

void AppMainWindow::showPlotTool()
{
#if 0
    typedef qwt::ReflectivePlotTool* (*create_t)(QWidget*);
    typedef void (*init_t)(QWidget*, const QString&,
            corbasim::core::interface_reflective_base const *);

    if (!m_plot_tool)
    {
        QLibrary lib("corbasim_qwt");

        if (!lib.load())
            return;

        create_t create = (create_t) 
            lib.resolve("createReflectivePlotTool");

        if (!create)
            return;

        m_plot_tool = create(NULL);
        m_plot_tool->setWindowTitle("corbasim plotting tool");
        m_plot_tool->setWindowIcon(QIcon(":/resources/images/csu.png"));

        // Register current instances
        init_t init = (init_t) lib.resolve("registerInstanceInPlotTool");

        if (init)
        {
            for (servants_t::const_iterator it = m_servants.begin(); 
                    it != m_servants.end(); ++it) 
            {
                init(m_plot_tool, it->first, it->second->getFactory());
            }
        }

        QObject::connect(
                m_controller,
                SIGNAL(servantCreated(
                        QString, 
                        InterfaceDescriptor_ptr)),
                m_plot_tool,
                SLOT(registerInstance(
                        const QString&, 
                        InterfaceDescriptor_ptr)));
        QObject::connect(
                m_controller,
                SIGNAL(servantDeleted(QString)),
                m_plot_tool,
                SLOT(unregisterInstance(const QString&)));

    }

    if (m_plot_tool)
        m_plot_tool->show();
#endif
}

void AppMainWindow::showDumpTool()
{
    if (!m_dump_tool)
    {
        m_dlg_dump_tool = new QDialog(this);
        QVBoxLayout * layout = new QVBoxLayout();
        layout->setMargin(0);

        m_dump_tool = new gui::DumpTool(m_dlg_dump_tool);

        layout->addWidget(m_dump_tool);
        m_dlg_dump_tool->setLayout(layout);

        m_dlg_dump_tool->setWindowIcon(QIcon(":/resources/images/csu.png"));
        m_dlg_dump_tool->setWindowTitle("corbasim dump tool");

        QObject::connect(
                m_controller,
                SIGNAL(servantCreated(
                        QString, 
                        InterfaceDescriptor_ptr)),
                m_dump_tool,
                SLOT(registerInstance(
                        const QString&, const 
                        InterfaceDescriptor_ptr)));
        QObject::connect(
                m_controller,
                SIGNAL(servantDeleted(QString)),
                m_dump_tool,
                SLOT(unregisterInstance(const QString&)));
#if 0
        // Initializes the tool
        servants_t::const_iterator it = m_servants.begin();

        for (; it != m_servants.end(); it++)
            m_dump_tool->registerInstance(it->first,
                    it->second->getFactory());
#endif
    }

    m_dlg_dump_tool->show();
}

void AppMainWindow::setEngine(TriggerEngine * engine)
{
    m_engine = engine;

    QObject::connect(this, SIGNAL(loadScriptFile(QString)),
            m_engine, SLOT(runFile(const QString&)));
}

// Subwindow slot

void AppMainWindow::showOpSequenceTool()
{
    if (!m_sub_seq_tool)
    {
        m_sub_seq_tool = new QMdiSubWindow();
        m_seq_tool = new gui::OperationSequenceTool();

        m_seq_tool->setWindowTitle("");

        m_sub_seq_tool->setWidget(m_seq_tool);
        m_mdi_area->addSubWindow(m_sub_seq_tool);

#if 0
        QObject::connect(
                m_controller,
                SIGNAL(objrefCreated(
                        QString, 
                        InterfaceDescriptor_ptr)),
                m_seq_tool,
                SLOT(objrefCreated(
                        const QString&, const 
                        InterfaceDescriptor_ptr)));
        QObject::connect(
                m_controller,
                SIGNAL(objrefDeleted(QString)),
                m_seq_tool,
                SLOT(objrefDeleted(const QString&)));

        // Initializes the tool
        objrefs_t::const_iterator it = m_objrefs.begin();

        for (; it != m_objrefs.end(); it++)
            m_seq_tool->objrefCreated(it->first,
                    it->second->getFactory());
#endif
    }
    m_sub_seq_tool->showNormal();
    m_seq_tool->show();
    m_mdi_area->setActiveSubWindow(m_sub_seq_tool);
}

void AppMainWindow::showSenderSequenceTool()
{
    if (!m_sub_sender_seq_tool)
    {
        m_sub_sender_seq_tool = new QMdiSubWindow();
        m_sender_seq_tool = new gui::SenderSequenceTool();

        m_sender_seq_tool->setWindowTitle("");

        m_sub_sender_seq_tool->setWidget(m_sender_seq_tool);
        m_mdi_area->addSubWindow(m_sub_sender_seq_tool);

#if 0
        // Initializes the tool
        objrefs_t::const_iterator it = m_objrefs.begin();

        for (; it != m_objrefs.end(); it++)
            m_sender_seq_tool->objrefCreated(it->first,
                    it->second->getFactory());
#endif
    }
    m_sub_sender_seq_tool->showNormal();
    m_sender_seq_tool->show();
    m_mdi_area->setActiveSubWindow(m_sub_sender_seq_tool);
}


void AppMainWindow::showFilteredLog()
{
    m_filtered_log->show();
}


void AppMainWindow::showCreateObjref()
{
    if (!m_sub_create_objref)
    {
        m_sub_create_objref = new QMdiSubWindow();
        m_create_objref = new view::ObjrefCreateDialog();

        m_create_objref->setWindowTitle("Create object reference");

        m_sub_create_objref->setWidget(m_create_objref);
        m_mdi_area->addSubWindow(m_sub_create_objref);

        // completer
        QLineEdit *fqn = m_create_objref->findChild< QLineEdit *>("fqn");
        if (fqn)
        {
            QCompleter * completer = 
                new QCompleter(m_controller->getFQNModel());
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            fqn->setCompleter(completer);
        }

        QObject::connect(m_create_objref,
                SIGNAL(createObjref(corbasim::app::ObjrefConfig)),
                m_controller, 
                SLOT(createObjref(const corbasim::app::ObjrefConfig&)));
    }
    m_sub_create_objref->showNormal();
    m_create_objref->show();
    m_mdi_area->setActiveSubWindow(m_sub_create_objref);
}

void AppMainWindow::showCreateServant()
{
    if (!m_sub_create_servant)
    {
        m_sub_create_servant = new QMdiSubWindow();
        m_create_servant = new view::ServantCreateDialog();

        m_create_servant->setWindowTitle("Create servant");

        m_sub_create_servant->setWidget(m_create_servant);
        m_mdi_area->addSubWindow(m_sub_create_servant);

        // completer
        QLineEdit *fqn = m_create_servant->findChild< QLineEdit *>("fqn");
        if (fqn)
        {
            QCompleter * completer = 
                new QCompleter(m_controller->getFQNModel());
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            fqn->setCompleter(completer);
        }

        QObject::connect(m_create_servant,
                SIGNAL(createServant(corbasim::app::ServantConfig)),
                m_controller, 
                SLOT(createServant(const corbasim::app::ServantConfig&)));
    }
    m_sub_create_servant->showNormal();
    m_create_servant->show();
    m_mdi_area->setActiveSubWindow(m_sub_create_servant);
}

void AppMainWindow::clearConfig()
{
    // TODO
}

// Notificaciones del controlador

void AppMainWindow::objrefCreated(Objref_ptr objref)
{
#if 0
    view::Objref_ptr objref(
            new view::Objref(m_mdi_area, id, factory, this));
    m_menuObjects->addMenu(objref->getMenu());

#if 0
    QObject::connect(objref.get(),
        SIGNAL(sendRequest(QString, Request_ptr)),
        m_controller, 
        SLOT(sendRequest(const QString&, Request_ptr)));
#endif

    QObject::connect(objref.get(),
                SIGNAL(deleteObjref(QString)),
                m_controller, 
                SLOT(deleteObjref(const QString&)));

    QObject::connect(objref.get(),
                SIGNAL(updatedReference(QString, CORBA::Object_var)),
                m_controller, 
                SLOT(updateReference(const QString&,
                        const CORBA::Object_var&)));

    m_objrefs.insert(std::make_pair(id, objref));

    displayMessage(QString("Object '%1' created").arg(id));
#endif
}

void AppMainWindow::objrefDeleted(ObjectId id)
{
#if 0
    objrefs_t::iterator it = m_objrefs.find(id);

    if (it != m_objrefs.end())
    {
        // Removes the submenu and deletes the objref instance
        m_menuObjects->removeAction(it->second->getMenu()->menuAction());
        m_objrefs.erase(it);

        displayMessage(QString("Object '%1' deleted").arg(id));
    }
#endif
}

void AppMainWindow::servantCreated(Objref_ptr servant)
{
#if 0
    view::Servant_ptr servant(
            new view::Servant(m_mdi_area, id, factory, this));
    m_menuServants->addMenu(servant->getMenu());
#if 0
    QObject::connect(servant.get(),
        SIGNAL(sendRequest(QString, Request_ptr)),
        m_controller, 
        SLOT(sendRequest(const QString&, Request_ptr)));
#endif
    QObject::connect(servant.get(),
                SIGNAL(deleteServant(QString)),
                m_controller, 
                SLOT(deleteServant(const QString&)));

    m_servants.insert(std::make_pair(id, servant));
    
    displayMessage(QString("Servant '%1' created").arg(id));
#endif
}

void AppMainWindow::servantDeleted(ObjectId id)
{
#if 0
    servants_t::iterator it = m_servants.find(id);

    if (it != m_servants.end())
    {
        // Removes the submenu and deletes the servant instance
        m_menuServants->removeAction(it->second->getMenu()->menuAction());
        m_servants.erase(it);

        displayMessage(QString("Servant '%1' deleted").arg(id));
    }
#endif
}

void AppMainWindow::displayError(const QString& err)
{
    QMessageBox::critical(this, "Error", err);
}

void AppMainWindow::displayMessage(const QString& msg)
{
    QTreeWidgetItem * item = new QTreeWidgetItem(QStringList(msg));
    appendToAppLog(item);
}

void AppMainWindow::updatedReference(const QString& id,
        const CORBA::Object_var& ref)
{
    displayMessage(QString("Updated reference for '%1'").arg(id));
}

// Dialogs

void AppMainWindow::showLoad()
{
    QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select a file"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    emit loadFile(file);
}

void AppMainWindow::showLoadDirectory()
{
    QString file = QFileDialog::getExistingDirectory( 0, tr(
                "Select a file"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    emit loadDirectory(file);
}

void AppMainWindow::showLoadScript()
{
    QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select a script file"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    emit loadScriptFile(file);
}

void AppMainWindow::showSave()
{
    QString file = QFileDialog::getSaveFileName( 0, tr(
                "Select a file"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    emit saveFile(file);
}

void AppMainWindow::appendToAppLog(QTreeWidgetItem * item)
{
    // check log size
    if (m_app_log->topLevelItemCount() >= 200)
        delete m_app_log->takeTopLevelItem(0);

    m_app_log->addTopLevelItem(item);
    m_app_log->scrollToItem(item);
}

void AppMainWindow::showScript()
{
    if (!m_sub_script)
    {
        m_sub_script = new QMdiSubWindow;
        m_script = new qt::ScriptWindow;

        m_sub_script->setWindowTitle("Run script");

        m_sub_script->setWidget(m_script);
        m_mdi_area->addSubWindow(m_sub_script);
/*  
        QObject::connect(m_script,
                SIGNAL(createServant(corbasim::app::ServantConfig)),
                m_controller, 
                SLOT(createServant(const corbasim::app::ServantConfig&)));
 */
    }
    m_sub_script->showNormal();
    m_script->show();
    m_mdi_area->setActiveSubWindow(m_sub_script);
}

// Settings
void AppMainWindow::doLoad() 
{
    const QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select some files"), ".");

    // User cancels
    if (file.isEmpty())
        return;

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
        // TODO display error
    }
}

void AppMainWindow::doSave() 
{
    QString file = QFileDialog::getSaveFileName( 0, tr(
                "Select a file"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    QVariant v;
    save(v);

    std::ofstream ofs(file.toStdString().c_str());
    json::ostream_writer_t ow(ofs, true);

    gui::toJson(ow, v);
}

void AppMainWindow::save(QVariant& settings) 
{
    QVariantMap window;
    QVariantMap objrefs;
    QVariantMap servants;

    // corbasim header
    {
        QVariantMap header;
        header["version"] = CORBASIM_VERSION; 
        header["built"] = __DATE__; 

        window["corbasim"] = header;
    }

    // configuration metadat
    {
        QVariantMap header;
        header["saved"] = QDateTime::currentDateTime().toString(); 
        window["metadata"] = header;
    }

    for (objrefs_t::iterator it = m_objrefs.begin(); 
	    it != m_objrefs.end(); ++it) 
    {
        // TODO it->second->save(objrefs[it->first]);
    }

    for (servants_t::iterator it = m_servants.begin(); 
	    it != m_servants.end(); ++it) 
    {
        // TODO it->second->save(servants[it->first]);
    }

    window["objrefs"] = objrefs;
    window["servants"] = servants;

    if (m_seq_tool)
    {
        m_seq_tool->save(window["sequences"]);
    }

    if (m_sender_seq_tool)
    {
        m_sender_seq_tool->save(window["sender_sequences"]);
    }

    if (m_filtered_log)
    {
        m_filtered_log->save(window["filtered_log"]);
    }

    if (m_dump_tool)
    {
        m_dump_tool->save(window["dumpers"]);
    }

    if (m_plot_tool)
    {
        typedef void (*save_t)(QWidget * tool, QVariant& settings);
        save_t savefn = (save_t) QLibrary::resolve("corbasim_qwt", 
                "saveReflectivePlotTool");

        if (savefn)
        {
            savefn(m_plot_tool, window["plots"]);
        }
    }

    settings = window;
}

void AppMainWindow::load(const QVariant& settings)
{
    const QVariantMap window = settings.toMap();

    if (window.contains("sequences"))
    {
        const QVariant seq = window.value("sequences");

        // TODO do not show but ensure created
        if (!m_seq_tool) showOpSequenceTool();

        m_seq_tool->load(seq);
    }

    if (window.contains("sender_sequences"))
    {
        const QVariant seq = window.value("sender_sequences");

        // TODO do not show but ensure created
        if (!m_sender_seq_tool) showOpSequenceTool();

        m_sender_seq_tool->load(seq);
    }
#if 0
    if (window.contains("objrefs"))
    {
        const QVariantMap map = window.value("objrefs").toMap();

        for (QVariantMap::const_iterator it = map.begin(); 
                it != map.end(); ++it) 
        {
            objrefs_t::iterator found = m_objrefs.find(it.key());

            if (found != m_objrefs.end())
            {
                found->second->load(it.value());
            }
        }
    }

    if (window.contains("servants"))
    {
        const QVariantMap map = window.value("servants").toMap();

        for (QVariantMap::const_iterator it = map.begin(); 
                it != map.end(); ++it) 
        {
            servants_t::iterator found = m_servants.find(it.key());

            if (found != m_servants.end())
            {
                found->second->load(it.value());
            }
        }
    }
#endif
    if (window.contains("filtered_log"))
    {
        m_filtered_log->load(window["filtered_log"]);
    }

    if (window.contains("dumpers"))
    {
        // TODO do not show but ensure created
        if (!m_dump_tool) showDumpTool();

        m_dump_tool->load(window["dumpers"]);
    }

    if (window.contains("plots"))
    {
        if (!m_plot_tool) showPlotTool();

        if (m_plot_tool)
        {
            typedef void (*load_t)(QWidget * tool, const QVariant& settings);
            load_t loadfn = (load_t) QLibrary::resolve("corbasim_qwt", 
                    "loadReflectivePlotTool");

            if (loadfn)
            {
                loadfn(m_plot_tool, window["plots"]);
            }
        }
    }
}


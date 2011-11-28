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
#include <corbasim/qt/ScriptWindow.hpp>

using namespace corbasim::app;

AppMainWindow::AppMainWindow(QWidget * parent) :
    QMainWindow(parent), m_controller(NULL), m_engine(NULL),

    // Subwindows
    m_sub_create_objref(NULL),
    m_sub_create_servant(NULL),
    m_sub_log(NULL),
    m_sub_script(NULL),

    // Widgets
    m_create_objref(NULL),
    m_create_servant(NULL),
    m_log(NULL),
    m_script(NULL)
{
    m_mdi_area = new QMdiArea;
    m_sub_log = new QMdiSubWindow;
    m_log = new QTreeWidget;

    m_log->setWindowTitle("Log");
    m_log->setHeaderLabel("Timeline");
    m_log->setColumnWidth(0, 800);
    m_sub_log->resize(400, 500);

    m_sub_log->setWidget(m_log);
    m_mdi_area->addSubWindow(m_sub_log);

    setCentralWidget(m_mdi_area);

    // Menu
    QMenuBar * menu = new QMenuBar;
    setMenuBar(menu);

    QMenu * menuFile = menu->addMenu("&File");
    menuFile->addAction("New &object", this, SLOT(showCreateObjref()));
    menuFile->addAction("&New servant", this, SLOT(showCreateServant()));
    menuFile->addSeparator();
    menuFile->addAction("&Load configuration", this, SLOT(showLoad()));
    menuFile->addAction("&Save configuration", this, SLOT(showSave()));
    menuFile->addAction("&Clear configuration", this, SLOT(clearConfig()));
    menuFile->addSeparator();
    menuFile->addAction("&Exit", this, SLOT(close()));

    m_menuObjects = menu->addMenu("&Objects");
    m_menuServants = menu->addMenu("&Servants");
    
    QMenu * tools = menu->addMenu("&Tools");
    tools->addAction("&Load script", this, SLOT(showLoadScript()));
    tools->addAction("&Run script", this, SLOT(showScript()));

    QMenu * winMenu = menu->addMenu("&Window");
    winMenu->addAction("Show &log", this, SLOT(showLog()));
    winMenu->addAction("&Clear log", m_log, SLOT(clear()));
    menu->addMenu("&About");

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
}

void AppMainWindow::setController(AppController * controller)
{
    m_controller = controller;

    // Signals
    QObject::connect(
            m_controller,
            SIGNAL(objrefCreated(
                    QString, corbasim::gui::gui_factory_base *)),
            this,
            SLOT(objrefCreated(
                    const QString&, corbasim::gui::gui_factory_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(objrefDeleted(QString)),
            this,
            SLOT(objrefDeleted(const QString&)));

    QObject::connect(
            m_controller,
            SIGNAL(servantCreated(
                    QString, corbasim::gui::gui_factory_base *)),
            this,
            SLOT(servantCreated(
                    const QString&, corbasim::gui::gui_factory_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(servantDeleted(QString)),
            this,
            SLOT(servantDeleted(const QString&)));

    QObject::connect(m_controller, SIGNAL(error(QString)),
            this, SLOT(displayError(const QString&)));

    QObject::connect(this, SIGNAL(saveFile(QString)),
            m_controller, SLOT(saveFile(const QString&)));
    QObject::connect(this, SIGNAL(loadFile(QString)),
            m_controller, SLOT(loadFile(const QString&)));

#define CORBASIM_APP_CON(ev)                                         \
    QObject::connect(m_controller,                                   \
    SIGNAL(ev(QString, corbasim::event::request_ptr,                 \
            corbasim::event::event_ptr)),                            \
    this,                                                            \
    SLOT(ev(const QString&, corbasim::event::request_ptr,            \
            corbasim::event::event_ptr)));                           \
    /***/

    CORBASIM_APP_CON(requestSent);
    CORBASIM_APP_CON(requestReceived);

#undef CORBASIM_APP_CON
}

void AppMainWindow::setEngine(TriggerEngine * engine)
{
    m_engine = engine;

    QObject::connect(this, SIGNAL(loadScriptFile(QString)),
            m_engine, SLOT(runFile(const QString&)));
}

// Subwindow slot

void AppMainWindow::showCreateObjref()
{
    if (!m_sub_create_objref)
    {
        m_sub_create_objref = new QMdiSubWindow;
        m_create_objref = new view::ObjrefCreateDialog;

        m_create_objref->setWindowTitle("Create object reference");

        m_sub_create_objref->setWidget(m_create_objref);
        m_mdi_area->addSubWindow(m_sub_create_objref);

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
        m_sub_create_servant = new QMdiSubWindow;
        m_create_servant = new view::ServantCreateDialog;

        m_create_servant->setWindowTitle("Create servant");

        m_sub_create_servant->setWidget(m_create_servant);
        m_mdi_area->addSubWindow(m_sub_create_servant);

        QObject::connect(m_create_servant,
                SIGNAL(createServant(corbasim::app::ServantConfig)),
                m_controller, 
                SLOT(createServant(const corbasim::app::ServantConfig&)));
    }
    m_sub_create_servant->showNormal();
    m_create_servant->show();
    m_mdi_area->setActiveSubWindow(m_sub_create_servant);
}

void AppMainWindow::showLog()
{
    m_sub_log->showNormal();
    m_log->show();
    m_mdi_area->setActiveSubWindow(m_sub_log);
}

void AppMainWindow::clearConfig()
{
    // TODO
}

// Notificaciones del controlador

void AppMainWindow::objrefCreated(const QString& id,
    corbasim::gui::gui_factory_base * factory)
{
    view::Objref_ptr objref(
            new view::Objref(m_mdi_area, id, factory, this));
    m_menuObjects->addMenu(objref->getMenu());

    QObject::connect(objref.get(),
        SIGNAL(sendRequest(QString, corbasim::event::request_ptr)),
        m_controller, 
        SLOT(sendRequest(const QString&, corbasim::event::request_ptr)));

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
}

void AppMainWindow::objrefDeleted(const QString& id)
{
    objrefs_t::iterator it = m_objrefs.find(id);

    if (it != m_objrefs.end())
    {
        // Removes the submenu and deletes the objref instance
        m_menuObjects->removeAction(it->second->getMenu()->menuAction());
        m_objrefs.erase(it);
    }
}

void AppMainWindow::servantCreated(const QString& id,
    corbasim::gui::gui_factory_base * factory)
{
    view::Servant_ptr servant(
            new view::Servant(m_mdi_area, id, factory, this));
    m_menuServants->addMenu(servant->getMenu());

    QObject::connect(servant.get(),
        SIGNAL(sendRequest(QString, corbasim::event::request_ptr)),
        m_controller, 
        SLOT(sendRequest(const QString&, corbasim::event::request_ptr)));

    QObject::connect(servant.get(),
                SIGNAL(deleteServant(QString)),
                m_controller, 
                SLOT(deleteServant(const QString&)));

    m_servants.insert(std::make_pair(id, servant));
}

void AppMainWindow::servantDeleted(const QString& id)
{
    servants_t::iterator it = m_servants.find(id);

    if (it != m_servants.end())
    {
        // Removes the submenu and deletes the servant instance
        m_menuServants->removeAction(it->second->getMenu()->menuAction());
        m_servants.erase(it);
    }
}

void AppMainWindow::requestSent(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    objrefs_t::iterator it = m_objrefs.find(id);
    
    if (it != m_objrefs.end())
    {
        gui::gui_factory_base * factory = it->second->getFactory();
        QTreeWidgetItem * item = factory->create_tree(req.get());

        QString text (item->text(0));
        text.prepend(QString("Sent to %1: ").arg(id));

        if (resp)
        {
            using namespace corbasim::event;

            if (resp->get_type() == RESPONSE)
            {
                response_ptr ptr_ = 
                    boost::dynamic_pointer_cast< response >(resp);

                QTreeWidgetItem * resp_item = 
                    factory->create_tree(ptr_.get());

                resp_item->setText(0, "Response");
                item->addChild(resp_item);
            }
            else if (resp->get_type() == EXCEPTION)
                text.append(" (Exception!)");
            else if (resp->get_type() == MESSAGE)
            {
                message_ptr ptr_ = 
                    boost::dynamic_pointer_cast< message >(resp);

                text.append(QString(" (%1)").arg(ptr_->get_message()));
            }
        }

        // Add to log
        item->setText(0, text);
        appendToLog(item);
    }
}

void AppMainWindow::requestReceived(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    servants_t::iterator it = m_servants.find(id);
    
    if (it != m_servants.end())
    {
        gui::gui_factory_base * factory = it->second->getFactory();
        QTreeWidgetItem * item = factory->create_tree(req.get());

        QString text (item->text(0));
        text.prepend(QString("Received to %1: ").arg(id));

        // Add to log
        item->setText(0, text);
        appendToLog(item);
    }
}

void AppMainWindow::displayError(const QString& err)
{
    QMessageBox::critical(this, "Error", err);
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

void AppMainWindow::appendToLog(QTreeWidgetItem * item)
{
    // check log size
    if (m_log->topLevelItemCount() >= 200)
        delete m_log->takeTopLevelItem(0);

    m_log->addTopLevelItem(item);
    m_log->scrollToItem(item);
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


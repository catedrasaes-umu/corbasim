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
#include "view/CreateDialog.hpp"
#include "view/Objref.hpp"

using namespace corbasim::app;

AppMainWindow::AppMainWindow(QWidget * parent) :
    QMainWindow(parent), m_controller(NULL),

    // Subwindows
    m_sub_create_objref(NULL),

    // Widgets
    m_create_objref(NULL)
{
    m_mdi_area = new QMdiArea;

    setCentralWidget(m_mdi_area);

    // Menu
    QMenuBar * menu = new QMenuBar;
    setMenuBar(menu);

    QMenu * menuFile = menu->addMenu("&File");
    menuFile->addAction("New &object", this, SLOT(showCreateObjref()));
    menuFile->addAction("&New servant");
    menuFile->addSeparator();
    menuFile->addAction("&Load configuration");
    menuFile->addAction("&Save configuration");
    menuFile->addSeparator();
    menuFile->addAction("&Close", this, SLOT(close()));

    m_menuObjects = menu->addMenu("&Objects");
    m_menuServants = menu->addMenu("&Servants");

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

    QObject::connect(m_controller, SIGNAL(error(QString)),
            this, SLOT(displayError(const QString&)));
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

// Notificaciones del controlador
void AppMainWindow::objrefCreated(const QString& id,
    corbasim::gui::gui_factory_base * factory)
{
    view::Objref * objref = new view::Objref(m_mdi_area, id, factory, this);
    m_menuObjects->addMenu(objref->getMenu());

    QObject::connect(objref,
                SIGNAL(sendRequest(QString, corbasim::event::request_ptr)),
                m_controller, 
                SLOT(sendRequest(const QString&, corbasim::event::request_ptr)));

    QObject::connect(objref,
                SIGNAL(deleteObjref(QString)),
                m_controller, 
                SLOT(deleteObjref(const QString&)));

    // TODO
}

void AppMainWindow::displayError(const QString& err)
{
    QMessageBox::critical(this, "Error", err);
}


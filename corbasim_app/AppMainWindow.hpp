// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppMainWindow.hpp
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

#ifndef CORBASIM_APP_APPMAINWINDOW_HPP
#define CORBASIM_APP_APPMAINWINDOW_HPP

#include <map>
#include <QtGui>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include "view/Objref.hpp"
#include "view/Servant.hpp"

namespace corbasim 
{
namespace app 
{

class AppController;

class TriggerEngine;

class AppMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    AppMainWindow(QWidget * parent = 0);
    virtual ~AppMainWindow();

    void setController(AppController * controller);
    void setEngine(TriggerEngine * engine);

public slots:

    void showCreateObjref();
    void showCreateServant();

    void showLoad();
    void showSave();
    
    void showLoadDirectory();
    
    void showLoadScript();
    void showScript();

    void clearConfig();

    // Notificaciones del controlador

    void objrefCreated(const QString& id,
        const corbasim::gui::gui_factory_base * factory);
    void objrefDeleted(const QString& id);

    void servantCreated(const QString& id,
        const corbasim::gui::gui_factory_base * factory);
    void servantDeleted(const QString& id);

    void requestSent(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);
    void requestReceived(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    void displayError(const QString& err);
    void displayMessage(const QString& msg);

    void updatedReference(const QString& id,
            const CORBA::Object_var& ref);

signals:

    void saveFile(QString);
    void loadFile(QString);
    
    void loadDirectory(QString);
    
    void loadScriptFile(QString);

protected:
    AppController * m_controller;
    TriggerEngine * m_engine;
    QMdiArea * m_mdi_area;

    typedef std::map< QString, view::Objref_ptr > objrefs_t;
    objrefs_t m_objrefs;

    typedef std::map< QString, view::Servant_ptr > servants_t;
    servants_t m_servants;

    QMenu * m_menuObjects;
    QMenu * m_menuServants;

    QStatusBar * m_statusBar;

    // Subwindows
    QMdiSubWindow * m_sub_create_objref;
    QMdiSubWindow * m_sub_create_servant;
    QMdiSubWindow * m_sub_script;
    
    // Subwindows widgets
    QWidget * m_create_objref;
    QWidget * m_create_servant;
    QWidget * m_script;

    // Dock widgets
    QDockWidget * m_dock_app_log;
    QTreeWidget * m_app_log;

    QDockWidget * m_dock_log;
    QTreeWidget * m_log;
    
    QDockWidget * m_dock_fqn;
    QTreeView * m_fqn;

    QCompleter * m_completer;
    QStringList m_op_list;

    void appendToLog(QTreeWidgetItem * item);
    void appendToAppLog(QTreeWidgetItem * item);
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPMAINWINDOW_HPP */


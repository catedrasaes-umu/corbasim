// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SimpleClient.hpp
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

#ifndef CORBASIM_REFLECTIVE_GUI_SIMPLECLIENT_HPP
#define CORBASIM_REFLECTIVE_GUI_SIMPLECLIENT_HPP

#include <vector>
#include <QtGui>

#include <corbasim/core/caller_fwd.hpp>
#include <corbasim/core/reflective_fwd.hpp>

#include <corbasim/qt/ObjrefWidget.hpp>
#include <corbasim/reflective_gui/LogModel.hpp>

#include <corbasim/qt/ReferenceFinder.hpp>

namespace corbasim 
{
namespace reflective_gui
{

class RequestDialog;
class SimpleScriptEditor;

class SimpleClient : public QMainWindow
{
    Q_OBJECT
public:
    SimpleClient(QWidget * parent = 0);
    virtual ~SimpleClient();

    void initialize(core::interface_reflective_base const *);
    void setReference(CORBA::Object_ptr ref);

public slots:

    void sendRequest(corbasim::event::request_ptr);
    void clearAll();
    void stopAllTimers();
    void pasteIOR();

    void showScriptEditor();
    void showDialog(int);
    void showDialog(QAction *);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void doLoad();
    void doSave();
    
    void updateReference(const CORBA::Object_var& ref);

protected:

    LogModel m_log_model;

    qt::ReferenceFinder m_finder;

    core::interface_caller_ptr m_caller;
    core::interface_reflective_base const * m_factory;

    QTabWidget * m_tab;
    QTreeView * m_tree;
    qt::ObjrefWidget * m_ref;

    QButtonGroup m_buttons;
    QActionGroup m_actions;

    QSplitter * m_mainSplitter;

    SimpleScriptEditor * m_script_editor;

    // Menu
    QMenuBar * m_menu;
    QMenu * m_operations_menu;

    typedef std::vector< RequestDialog * > dialogs_t;
    dialogs_t m_dialogs;

    static const int _max_btns_per_row = 4;
    static const int _max_btns_per_page = 16;

    RequestDialog * getRequestDialog(int idx);

    void resizeEvent(QResizeEvent * event);
};

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_SIMPLECLIENT_HPP */


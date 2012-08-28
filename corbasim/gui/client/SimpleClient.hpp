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

#ifndef CORBASIM_GUI_SIMPLECLIENT_HPP
#define CORBASIM_GUI_SIMPLECLIENT_HPP

#include <vector>
#include <QtGui>

#include <corbasim/core/caller_fwd.hpp>
#include <corbasim/core/reflective_fwd.hpp>

#include <corbasim/qt/ObjrefWidget.hpp>
#include <corbasim/gui/item/LogModel.hpp>

#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>

namespace corbasim 
{
namespace gui
{

class RequestDialog;
class SimpleScriptEditor;
class OperationSequenceTool;
class FilteredLogView;

class CORBASIM_GUI_DECLSPEC SimpleClient : public QMainWindow
{
    Q_OBJECT
public:
    SimpleClient(QWidget * parent = 0);
    virtual ~SimpleClient();

    void setReference(CORBA::Object_ptr ref);

public slots:

    void initialize(Objref_ptr objref);

    void clearAll();
    void stopAllTimers();
    void pasteIOR();

    void showOperationSequenceTool();
    void showScriptEditor();
    void showDialog(int);
    void showDialog(QAction *);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void doLoad();
    void doSave();
    
    void updateReference(const CORBA::Object_var& ref);

signals:

    void applyUpdateReference(const CORBA::Object_var& ref);
    void sendRequest(Request_ptr);

protected:

    LogModel m_log_model;

    Objref_ptr m_objref;
    Caller_ptr m_validator;

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

    FilteredLogView * m_filtered_log;

    QDialog * m_dlg_seq_tool;
    OperationSequenceTool * m_seq_tool;

    static const int _max_btns_per_row = 4;
    static const int _max_btns_per_page = 16;

    RequestDialog * getRequestDialog(int idx);

    void resizeEvent(QResizeEvent * event);
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SIMPLECLIENT_HPP */


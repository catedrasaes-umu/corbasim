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

#ifndef CORBASIM_QT_CIENT_SIMPLECLIENT_HPP
#define CORBASIM_QT_CIENT_SIMPLECLIENT_HPP

#include <vector>
#include <QtGui>

#include <corbasim/core/caller_fwd.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>

#include <corbasim/qt/ObjrefWidget.hpp>

namespace corbasim 
{
namespace qt 
{

class RequestDialog;
class MultiSenderDialog;
class SimpleScriptEditor;
class LogTreeWidget;

namespace client 
{

class SimpleClient : public QMainWindow
{
    Q_OBJECT
public:
    SimpleClient(QWidget * parent = 0);
    virtual ~SimpleClient();

    void initialize(gui::gui_factory_base const *);
    void setReference(CORBA::Object_ptr ref);

public slots:
    void sendRequest(corbasim::event::request_ptr);
    void clearAll();
    void stopAllTimers();
    void pasteIOR();

    void showScriptEditor();
    void showMultiSender();
    void showDialog(int);
    void showDialog(QAction *);

protected:
    core::interface_caller_ptr m_caller;
    gui::gui_factory_base const * m_factory;
    QTabWidget * m_tab;
    LogTreeWidget * m_tree;
    ObjrefWidget * m_ref;

    QButtonGroup m_buttons;
    QActionGroup m_actions;

    QSplitter * m_mainSplitter;

    MultiSenderDialog * m_multi_sender;
    SimpleScriptEditor * m_script_editor;

    // Menu
    QMenuBar * m_menu;
    QMenu * m_operations_menu;

    typedef std::vector< RequestDialog * > dialogs_t;
    dialogs_t m_dialogs;

    static const int _max_btns_per_row = 4;
    static const int _max_btns_per_page = 16;

    RequestDialog * getRequestDialog(int idx);
};

} // namespace client
} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_CIENT_SIMPLECLIENT_HPP */


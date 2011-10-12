// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AutoResponseMainWindow.hpp
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

#ifndef CORBASIM_QT_PYTHON_AUTORESPONSEMAINWINDOW_HPP
#define CORBASIM_QT_PYTHON_AUTORESPONSEMAINWINDOW_HPP

#include <QtGui>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/event.hpp>
#include <corbasim/core/caller.hpp>
#include <corbasim/qt/python/AutoResponse.hpp>
#include <corbasim/qt/LogWidget.hpp>
#include <corbasim/qt/SimpleScriptEditor.hpp>

namespace corbasim 
{
namespace qt 
{
namespace python 
{

class AutoResponseMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    AutoResponseMainWindow(QWidget * parent = 0);
    virtual ~AutoResponseMainWindow();

    void initialize(gui::gui_factory_base * input_factory,
            gui::gui_factory_base* output_factory);

public slots:

    void showInputEstimulator();
    void showOutputEstimulator();
    void showOutputReference();

protected:

    AutoResponseWidget * m_auto_response;
    LogWidget * m_input_log;
    LogWidget * m_output_log;

    gui::gui_factory_base * m_input_factory;
    gui::gui_factory_base * m_output_factory;

    SimpleScriptEditor * m_input_stim;
    SimpleScriptEditor * m_output_stim;
    
    // Callers
    core::interface_caller_ptr m_output_caller;
};

} // namespace python
} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_PYTHON_AUTORESPONSEMAINWINDOW_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestProcessor.hpp
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

#ifndef CORBASIM_QT_REQUESTPROCESSOR_HPP
#define CORBASIM_QT_REQUESTPROCESSOR_HPP

#include <QtGui>
#include <vector>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/event.hpp>
#include <corbasim/core/caller.hpp>
#include <corbasim/qt/LogWidget.hpp>
#include <corbasim/qt/SimpleScriptEditor.hpp>

#include <corbasim/scripting/request_processor.hpp>

namespace corbasim 
{
namespace qt 
{

class TriggerConfigurator;

class RequestProcessor : public QWidget
{
    Q_OBJECT
public:

    RequestProcessor(QWidget * parent = 0);
    virtual ~RequestProcessor();

    void initialize(gui::gui_factory_base * input_factory,
            gui::gui_factory_base* output_factory);

public slots:

    void requestReceived(corbasim::event::request_ptr);

    void saveConfig(int);

signals:

    void sendRequest(corbasim::event::request_ptr);

protected:
    
    void notifyRequest(corbasim::event::request_ptr);

    // Data
    QButtonGroup * m_buttons;
    std::vector< TriggerConfigurator* > m_triggers;
};

class TriggerConfigurator : public QWidget
{
    Q_OBJECT
public:
    TriggerConfigurator(QWidget * parent = 0);
    virtual ~TriggerConfigurator();

    QPushButton * getSaveButton();

    void initialize(gui::operation_factory_base * factory);

protected slots:

    void enableSave();
    void doSave();

protected:

    QPushButton * m_save_button;
    QCheckBox * m_enabled;
    QTextEdit * m_code;
};

class RequestProcessorMain : public QMainWindow
{
    Q_OBJECT
public:
    RequestProcessorMain(QWidget * parent = 0);
    virtual ~RequestProcessorMain();

    void initialize(gui::gui_factory_base * input_factory,
            gui::gui_factory_base* output_factory);

public slots:

    void showInputEstimulator();
    void showOutputEstimulator();
    void showOutputReference();

    void setInputRequest(corbasim::event::request_ptr);
    void setOutputRequest(corbasim::event::request_ptr);

protected:

    RequestProcessor * m_request_processor;
    LogWidget * m_input_log;
    LogWidget * m_output_log;

    gui::gui_factory_base * m_input_factory;
    gui::gui_factory_base * m_output_factory;

    SimpleScriptEditor * m_input_stim;
    SimpleScriptEditor * m_output_stim;
    
    // Callers
    core::interface_caller_ptr m_output_caller;

    QDialog * m_output_ref_dlg;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_REQUESTPROCESSOR_HPP */


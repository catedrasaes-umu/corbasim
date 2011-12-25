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
#include <corbasim/qt/Interpreter.hpp>

#include <corbasim/scripting/request_processor.hpp>

namespace corbasim 
{
namespace qt 
{

class ScriptEditor;

class TriggerConfigurator;

class RequestProcessor : public QWidget
{
    Q_OBJECT
public:

    RequestProcessor(QWidget * parent = 0);
    virtual ~RequestProcessor();

    void initialize(gui::gui_factory_base const * input_factory,
            gui::gui_factory_base const * output_factory);

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

    scripting::request_processor_ptr m_processor;
};

class TriggerConfigurator : public QWidget
{
    Q_OBJECT
public:
    TriggerConfigurator(QWidget * parent = 0);
    virtual ~TriggerConfigurator();

    QPushButton * getSaveButton();

    void initialize(gui::operation_factory_base const * factory);

    QString getCode();
    bool isEnabled();
    tag_t getTag();

protected slots:

    void enableSave();
    void doSave();

protected:

    QPushButton * m_save_button;
    QCheckBox * m_enabled;
    QTextEdit * m_code;

    gui::operation_factory_base const * m_factory;
};

class RequestProcessorMain : public QMainWindow
{
    Q_OBJECT
public:
    RequestProcessorMain(QWidget * parent = 0);
    virtual ~RequestProcessorMain();

    void initialize(gui::gui_factory_base const * input_factory,
            gui::gui_factory_base const * output_factory);

public slots:

    void showInputTriggers();
    void showInputEstimulator();
    void showOutputEstimulator();
    void showOutputReference();
    
    void showScriptEditor();

    void showInputEvents();
    void showOutputEvents();

    void showConsoleOutput();
    void showInterpreter();

    void setInputRequest(corbasim::event::request_ptr);
    void setOutputRequest(corbasim::event::request_ptr);

protected:

    QMdiArea * m_mdi_area;
    QMdiSubWindow * m_sub_out_ref;
    QMdiSubWindow * m_sub_in_stim;
    QMdiSubWindow * m_sub_out_stim;
    QMdiSubWindow * m_sub_in_log;
    QMdiSubWindow * m_sub_out_log;
    QMdiSubWindow * m_sub_req_proc;
    QMdiSubWindow * m_sub_console_output;
    QMdiSubWindow * m_sub_interpreter;
    QMdiSubWindow * m_sub_script_editor;

    RequestProcessor * m_request_processor;
    LogWidget * m_input_log;
    LogWidget * m_output_log;

    gui::gui_factory_base const * m_input_factory;
    gui::gui_factory_base const * m_output_factory;

    SimpleScriptEditor * m_input_stim;
    SimpleScriptEditor * m_output_stim;
    ScriptEditor * m_script_editor;
    
    QWidget * m_output_ref;
    QScrollArea * m_input_triggers;
    Interpreter * m_interpreter;
    QWidget * m_console_output;

    // Callers
    core::interface_caller_ptr m_output_caller;

};

class ConsoleOutput : public QWidget
{
    Q_OBJECT
public:
    ConsoleOutput(QWidget * parent = 0);
    virtual ~ConsoleOutput();

    void write(const std::string& str);

signals:

    void append(QString);

protected:
    QTextEdit * m_output;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_REQUESTPROCESSOR_HPP */


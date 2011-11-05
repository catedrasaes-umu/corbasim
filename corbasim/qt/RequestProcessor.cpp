// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestProcessor.cpp
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

#include "RequestProcessor.hpp"
#include <corbasim/qt/initialize.hpp>
#include <corbasim/qt/ObjrefWidget.hpp>
#include <corbasim/qt/ScriptEditor.hpp>

using namespace corbasim;
using namespace corbasim::qt;

RequestProcessor::RequestProcessor(QWidget * parent) :
    QWidget(parent)
{
    m_buttons = new QButtonGroup;
    
    QObject::connect(m_buttons, SIGNAL(buttonClicked(int)),
            this, SLOT(saveConfig(int)));
}

RequestProcessor::~RequestProcessor()
{
}

void RequestProcessor::initialize(
        gui::gui_factory_base * input_factory,
        gui::gui_factory_base * output_factory)
{
    unsigned int count = input_factory->operation_count();

    m_triggers.reserve(count);

    QVBoxLayout * layout = new QVBoxLayout;

    for (unsigned int i = 0; i < count; i++) 
    {
        TriggerConfigurator * trigger = new TriggerConfigurator;
        m_triggers.push_back(trigger);

        gui::operation_factory_base * op =
            input_factory->get_factory_by_index(i);

        QGroupBox * gb = new QGroupBox(op->get_name());
        QVBoxLayout * gl = new QVBoxLayout;

        trigger->initialize(op);

        m_buttons->addButton(trigger->getSaveButton(), i);

        gl->addWidget(trigger);
        gb->setLayout(gl);
        layout->addWidget(gb);
    }

    setLayout(layout);

    // Prepare the interpreter
    scripting::interpreter_ptr interpreter_ =
        scripting::get_default_interpreter();

    m_processor.reset(
            new scripting::request_processor(
                interpreter_,
                input_factory->get_core_factory()));

    interpreter_->request_signal.connect(
            boost::bind(&RequestProcessor::notifyRequest,
                this, _1));

    interpreter_->register_factory(output_factory->get_core_factory());
}

void RequestProcessor::requestReceived(event::request_ptr req)
{
    if (m_processor)
        m_processor->process_message(req);
}

void RequestProcessor::notifyRequest(event::request_ptr req)
{
    emit sendRequest(req);
}

void RequestProcessor::saveConfig(int idx)
{
    TriggerConfigurator * trigger = m_triggers[idx];

    scripting::request_processor::configuration_ptr config(
            new scripting::request_processor::configuration);

    config->active = trigger->isEnabled();
    config->request_type = trigger->getTag();
    config->code = trigger->getCode().toStdString();

    m_processor->configure(config);
}

// Trigger Configurator

TriggerConfigurator::TriggerConfigurator(QWidget * parent) :
    QWidget(parent)
{
    QGridLayout * layout = new QGridLayout;
    
    m_save_button = new QPushButton("Save");
    m_enabled = new QCheckBox;
    m_code = new QTextEdit;

    m_code->setMinimumHeight(200);
    m_save_button->setMinimumWidth(50);

    m_save_button->setEnabled(false);

    layout->addWidget(new QLabel("Enabled"), 0, 0);
    layout->addWidget(m_enabled, 0, 1);
    layout->addWidget(new QLabel("Trigger"), 1, 0);
    layout->addWidget(m_code, 1, 1);

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addItem(new QSpacerItem(40, 20, 
                QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout->addWidget(m_save_button);

    layout->addLayout(hLayout, 2, 1);

    setLayout(layout);

    // Signals
    QObject::connect(m_save_button, SIGNAL(clicked()),
            this, SLOT(doSave()));

    QObject::connect(m_code, SIGNAL(textChanged()),
            this, SLOT(enableSave()));

    QObject::connect(m_enabled, SIGNAL(stateChanged(int)),
            this, SLOT(enableSave()));
}

TriggerConfigurator::~TriggerConfigurator()
{
}

void TriggerConfigurator::initialize(gui::operation_factory_base * factory)
{
    m_factory = factory;
}

corbasim::tag_t TriggerConfigurator::getTag()
{
    return m_factory->get_tag();
}

bool TriggerConfigurator::isEnabled()
{
    return m_enabled->isChecked();
}

QString TriggerConfigurator::getCode()
{
    return m_code->toPlainText();
}

void TriggerConfigurator::enableSave()
{
    m_save_button->setEnabled(true);
}

void TriggerConfigurator::doSave()
{
    m_save_button->setEnabled(false);
}

QPushButton * TriggerConfigurator::getSaveButton()
{
    return m_save_button;
}

// Main Window

RequestProcessorMain::RequestProcessorMain(QWidget * parent) :
    QMainWindow(parent), 

    // Subwindows
    m_sub_out_ref(NULL),
    m_sub_in_stim(NULL),
    m_sub_out_stim(NULL),
    m_sub_in_log(NULL),
    m_sub_out_log(NULL),
    m_sub_req_proc(NULL),
    m_sub_console_output(NULL),
    m_sub_interpreter(NULL),
    m_sub_script_editor(NULL),

    // Widgets
    m_request_processor(NULL),
    m_input_factory(NULL),
    m_output_factory(NULL),
    m_input_stim(NULL), 
    m_output_stim(NULL),
    m_script_editor(NULL),
    m_output_ref(NULL),
    m_input_triggers(NULL),
    m_interpreter(NULL),
    m_console_output(NULL)
{
    corbasim::qt::initialize();

    m_mdi_area = new QMdiArea();

    m_sub_req_proc = new QMdiSubWindow;
    m_sub_req_proc->setWindowTitle("Input triggers");

    m_input_triggers = new QScrollArea;
    m_request_processor = new RequestProcessor;
    m_input_triggers->setWidget(m_request_processor);
    m_input_triggers->setWidgetResizable(true);

    m_sub_req_proc->setWidget(m_input_triggers);
    m_mdi_area->addSubWindow(m_sub_req_proc);
    m_sub_req_proc->hide();

    // Logs
    m_sub_in_log = new QMdiSubWindow;
    m_sub_out_log = new QMdiSubWindow;
    m_sub_in_log->setWindowTitle("Input events");
    m_sub_out_log->setWindowTitle("Output events");

    m_input_log = new LogWidget;
    m_output_log = new LogWidget;

    m_sub_in_log->setWidget(m_input_log);
    m_sub_out_log->setWidget(m_output_log);

    m_mdi_area->addSubWindow(m_sub_in_log);
    m_mdi_area->addSubWindow(m_sub_out_log);

    m_sub_in_log->hide();
    m_sub_out_log->hide();
    
    // Console output
    m_sub_console_output = new QMdiSubWindow;
    m_sub_console_output->setWindowTitle("Console output");
    m_console_output = new ConsoleOutput;
    m_sub_console_output->setWidget(m_console_output);
    m_mdi_area->addSubWindow(m_sub_console_output);
    m_sub_console_output->hide();

    setCentralWidget(m_mdi_area);

    // Menu
    QMenuBar * menu = new QMenuBar;
    setMenuBar(menu);

    QMenu * menuFile = menu->addMenu("&File");
    menuFile->addAction("&Close", this, SLOT(close()));

    QMenu * menuWin = menu->addMenu("&Window");
    menuWin->addAction("&Input stimulator", this, 
            SLOT(showInputEstimulator()));
    menuWin->addAction("&Output stimulator", this, 
            SLOT(showOutputEstimulator()));
    menuWin->addSeparator();
    menuWin->addAction("&Script editor", this, 
            SLOT(showScriptEditor()));
    menuWin->addSeparator();
    menuWin->addAction("Output &reference", this, 
            SLOT(showOutputReference()));
    menuWin->addSeparator();
    menuWin->addAction("Input &triggers", this, 
            SLOT(showInputTriggers()));
    menuWin->addSeparator();
    menuWin->addAction("Input events", this, 
            SLOT(showInputEvents()));
    menuWin->addAction("Output events", this, 
            SLOT(showOutputEvents()));
    menuWin->addSeparator();
    menuWin->addAction("Console output", this, 
            SLOT(showConsoleOutput()));
    menuWin->addAction("Interpreter", this, 
            SLOT(showInterpreter()));
    menuWin->addSeparator();
    menuWin->addAction("Cascade", m_mdi_area, 
            SLOT(cascadeSubWindows()));
    menuWin->addAction("Tile", m_mdi_area, 
            SLOT(tileSubWindows()));
    
    QMenu * menuAbout = menu->addMenu("&About");

    // Signals
    QObject::connect(m_request_processor, 
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            this,
            SLOT(setOutputRequest(corbasim::event::request_ptr)));

    setWindowTitle("corbasim");
    setWindowIcon(QIcon(":/resources/images/csu.png"));
}

void RequestProcessorMain::showInputEvents()
{
    m_sub_in_log->showNormal();
    m_input_log->show();
    m_mdi_area->setActiveSubWindow(m_sub_in_log);
}

void RequestProcessorMain::showOutputEvents()
{
    m_sub_out_log->showNormal();
    m_output_log->show();
    m_mdi_area->setActiveSubWindow(m_sub_out_log);
}

void RequestProcessorMain::showInputTriggers()
{
    m_sub_req_proc->showNormal();
    m_input_triggers->show();
    m_mdi_area->setActiveSubWindow(m_sub_req_proc);
}

void RequestProcessorMain::showConsoleOutput()
{
    m_sub_console_output->showNormal();
    m_console_output->show();
    m_mdi_area->setActiveSubWindow(m_sub_console_output);
}

void RequestProcessorMain::showInterpreter()
{
    if (!m_sub_interpreter)
    {
        m_sub_interpreter = new QMdiSubWindow;
        m_interpreter = new Interpreter;

        // Assign the default interpreter
        m_interpreter->initialize(
                scripting::get_default_interpreter());

        m_sub_interpreter->setWidget(m_interpreter);
        m_mdi_area->addSubWindow(m_sub_interpreter);
        
        m_sub_interpreter->setWindowTitle("Interpreter");
    }
    m_sub_interpreter->showNormal();
    m_interpreter->show();
    m_mdi_area->setActiveSubWindow(m_sub_interpreter);
}

void RequestProcessorMain::showOutputReference()
{
    if (!m_sub_out_ref)
    {
        m_sub_out_ref = new QMdiSubWindow;
        m_output_ref = new ObjrefWidget(m_output_caller.get());
        m_sub_out_ref->setWidget(m_output_ref);
        m_mdi_area->addSubWindow(m_sub_out_ref);
    
        m_sub_out_ref->setWindowTitle("Output reference");
    }
    m_sub_out_ref->showNormal();
    m_output_ref->show();
    m_mdi_area->setActiveSubWindow(m_sub_out_ref);
}

void RequestProcessorMain::showInputEstimulator()
{
    if (!m_input_stim)
    {
        m_input_stim = new SimpleScriptEditor;
        m_input_stim->initialize(m_input_factory);
        m_input_stim->setWindowTitle("Input stimulator");

        QObject::connect(m_input_stim, 
                SIGNAL(sendRequest(corbasim::event::request_ptr)),
                this,
                SLOT(setInputRequest(corbasim::event::request_ptr)));

        m_sub_in_stim = new QMdiSubWindow;
        m_sub_in_stim->setWidget(m_input_stim);

        m_mdi_area->addSubWindow(m_sub_in_stim);
    }
    m_sub_in_stim->showNormal();
    m_input_stim->show();
    m_mdi_area->setActiveSubWindow(m_sub_in_stim);
}

void RequestProcessorMain::showOutputEstimulator()
{
    if (!m_output_stim)
    {
        m_output_stim = new SimpleScriptEditor;
        m_output_stim->initialize(m_output_factory);
        m_output_stim->setWindowTitle("Output stimulator");

        QObject::connect(m_output_stim, 
                SIGNAL(sendRequest(corbasim::event::request_ptr)),
                this,
                SLOT(setOutputRequest(corbasim::event::request_ptr)));
        
        m_sub_out_stim = new QMdiSubWindow;
        m_sub_out_stim->setWidget(m_output_stim);

        m_mdi_area->addSubWindow(m_sub_out_stim);
    }
    m_sub_out_stim->showNormal();
    m_output_stim->show();
    m_mdi_area->setActiveSubWindow(m_sub_out_stim);
}

void RequestProcessorMain::showScriptEditor()
{
    if (!m_script_editor)
    {
        m_script_editor = new ScriptEditor;
        m_script_editor->initialize(m_output_factory);
        m_script_editor->setWindowTitle("Script editor");

        QObject::connect(m_script_editor, 
                SIGNAL(sendRequest(corbasim::event::request_ptr)),
                this,
                SLOT(setOutputRequest(corbasim::event::request_ptr)));
        
        m_sub_script_editor = new QMdiSubWindow;
        m_sub_script_editor->setWidget(m_script_editor);

        m_mdi_area->addSubWindow(m_sub_script_editor);
    }
    m_sub_script_editor->showNormal();
    m_script_editor->show();
    m_mdi_area->setActiveSubWindow(m_sub_script_editor);
}


RequestProcessorMain::~RequestProcessorMain()
{
    delete m_sub_out_ref;
    delete m_sub_in_stim;
    delete m_sub_out_stim;
    delete m_sub_in_log;
    delete m_sub_out_log;
    delete m_sub_req_proc;
}

void RequestProcessorMain::initialize(
        gui::gui_factory_base * input_factory,
        gui::gui_factory_base* output_factory)
{
    m_input_factory = input_factory;
    m_output_factory = output_factory;

    m_request_processor->initialize(input_factory, output_factory);
    m_input_log->initialize(input_factory);
    m_output_log->initialize(output_factory);

    m_output_caller.reset(
            output_factory->get_core_factory()->create_caller());
}

void RequestProcessorMain::setInputRequest(corbasim::event::request_ptr req)
{
    m_input_log->notifyRequest(req);
    m_request_processor->requestReceived(req);
}

void RequestProcessorMain::setOutputRequest(
        corbasim::event::request_ptr req)
{
    if (!m_output_caller || m_output_caller->is_nil())
    {
        m_output_log->notifyEvent(event::event_ptr(
                    new event::message("Reference not set yet!")));
    }
    else
    {
        m_output_log->notifyRequest(req);

        // Send the request through the output caller
        event::event_ptr ev(m_output_caller->do_call(req.get()));

        if (ev)
            m_output_log->notifyEvent(ev);
    }
}

// Console output
ConsoleOutput::ConsoleOutput(QWidget * parent) :
    QWidget(parent)
{
    QVBoxLayout * l = new QVBoxLayout;
    m_output = new QTextEdit;
    l->addWidget(m_output);
    setLayout(l);

    QObject::connect(this, SIGNAL(append(QString)),
            m_output, SLOT(append(const QString&)));
                
    scripting::get_default_interpreter()->output_signal.connect(
            boost::bind(&ConsoleOutput::write, this, _1));
}

ConsoleOutput::~ConsoleOutput()
{
}

void ConsoleOutput::write(const std::string& str)
{
    QString str_(str.c_str());
    emit append(str_);
}


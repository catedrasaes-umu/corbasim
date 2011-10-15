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
}

void RequestProcessor::requestReceived(event::request_ptr req)
{
}

void RequestProcessor::notifyRequest(event::request_ptr req)
{
    emit sendRequest(req);
}

void RequestProcessor::saveConfig(int idx)
{
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
    m_input_factory(NULL), m_output_factory(NULL),
    m_input_stim(NULL), m_output_stim(NULL),
    m_output_ref_dlg(NULL)
{
    corbasim::qt::initialize();

    QSplitter * w = new QSplitter(Qt::Vertical, this);

    QGroupBox * gb = new QGroupBox("Triggers");
    QVBoxLayout * vLayout = new QVBoxLayout;
    QScrollArea * sc = new QScrollArea;
    m_request_processor = new RequestProcessor;
    sc->setWidget(m_request_processor);
    sc->setWidgetResizable(true);
    vLayout->addWidget(sc);
    gb->setLayout(vLayout);
    w->addWidget(gb);

    // Logs
    QGroupBox * igb = new QGroupBox("Input events");
    QGroupBox * ogb = new QGroupBox("Output events");
    QHBoxLayout * il = new QHBoxLayout;
    QHBoxLayout * ol = new QHBoxLayout;
    m_input_log = new LogWidget;
    m_output_log = new LogWidget;
    QHBoxLayout * hLayout = new QHBoxLayout;
    il->addWidget(m_input_log);
    ol->addWidget(m_output_log);
    igb->setLayout(il);
    ogb->setLayout(ol);
    
    QWidget * logWidget = new QWidget;
    hLayout->addWidget(igb);
    hLayout->addWidget(ogb);
    logWidget->setLayout(hLayout);
    w->addWidget(logWidget);

    setCentralWidget(w);

    // Menu
    QMenuBar * menu = new QMenuBar;
    setMenuBar(menu);

    QMenu * menuFile = menu->addMenu("&File");
    menuFile->addAction("&Input stimulator", this, 
            SLOT(showInputEstimulator()));
    menuFile->addAction("&Output stimulator", this, 
            SLOT(showOutputEstimulator()));
    menuFile->addSeparator();
    menuFile->addAction("Output &reference", this, 
            SLOT(showOutputReference()));
    menuFile->addSeparator();
    menuFile->addAction("&Close", this, SLOT(close()));

    // Signals
    QObject::connect(m_request_processor, 
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            this,
            SLOT(setOutputRequest(corbasim::event::request_ptr)));
}

void RequestProcessorMain::showOutputReference()
{
    if (!m_output_ref_dlg)
    {
        m_output_ref_dlg = new QDialog(this);
        QVBoxLayout * l = new QVBoxLayout;
        ObjrefWidget * ref = new ObjrefWidget(m_output_caller.get());
        l->addWidget(ref);
        m_output_ref_dlg->setLayout(l);
        m_output_ref_dlg->setWindowTitle("Output reference");
    }
    m_output_ref_dlg->show();
}

void RequestProcessorMain::showInputEstimulator()
{
    if (!m_input_stim)
    {
        m_input_stim = new SimpleScriptEditor(this);
        m_input_stim->initialize(m_input_factory);
        m_input_stim->setWindowTitle("Input stimulator");

        QObject::connect(m_input_stim, 
                SIGNAL(sendRequest(corbasim::event::request_ptr)),
                this,
                SLOT(setInputRequest(corbasim::event::request_ptr)));
    }
    m_input_stim->show();
}

void RequestProcessorMain::showOutputEstimulator()
{
    if (!m_output_stim)
    {
        m_output_stim = new SimpleScriptEditor(this);
        m_output_stim->initialize(m_output_factory);
        m_output_stim->setWindowTitle("Output stimulator");

        QObject::connect(m_output_stim, 
                SIGNAL(sendRequest(corbasim::event::request_ptr)),
                this,
                SLOT(setOutputRequest(corbasim::event::request_ptr)));
    }
    m_output_stim->show();
}

RequestProcessorMain::~RequestProcessorMain()
{
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


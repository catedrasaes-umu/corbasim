// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AutoResponseMainWindow.cpp
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

#include "AutoResponseMainWindow.hpp"
#include <corbasim/qt/initialize.hpp>

using namespace corbasim::qt::python;

AutoResponseMainWindow::AutoResponseMainWindow(QWidget * parent) :
    QMainWindow(parent), 
    m_input_factory(NULL), m_output_factory(NULL),
    m_input_stim(NULL), m_output_stim(NULL)
{
    corbasim::qt::initialize();

    QSplitter * w = new QSplitter(Qt::Vertical, this);

    QGroupBox * gb = new QGroupBox("Automatic response");
    QVBoxLayout * vLayout = new QVBoxLayout;
    QScrollArea * sc = new QScrollArea;
    m_auto_response = new AutoResponseWidget;
    sc->setWidget(m_auto_response);
    sc->setWidgetResizable(true);
    vLayout->addWidget(sc);
    gb->setLayout(vLayout);
    w->addWidget(gb);

    // Logs
    m_input_log = new LogWidget;
    m_output_log = new LogWidget;
    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(m_input_log);
    hLayout->addWidget(m_output_log);
    QWidget * logWidget = new QWidget;
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
    QObject::connect(m_auto_response, 
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            this,
            SLOT(setOutputRequest(corbasim::event::request_ptr)));
}

void AutoResponseMainWindow::showOutputReference()
{
}

void AutoResponseMainWindow::showInputEstimulator()
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

void AutoResponseMainWindow::showOutputEstimulator()
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

AutoResponseMainWindow::~AutoResponseMainWindow()
{
}

void AutoResponseMainWindow::initialize(
        gui::gui_factory_base * input_factory,
        gui::gui_factory_base* output_factory)
{
    m_input_factory = input_factory;
    m_output_factory = output_factory;

    m_auto_response->initialize(input_factory, output_factory);
    m_input_log->initialize(input_factory);
    m_output_log->initialize(output_factory);
}


void AutoResponseMainWindow::setInputRequest(corbasim::event::request_ptr req)
{
    m_input_log->notifyRequest(req);
    m_auto_response->requestReceived(req);
}

void AutoResponseMainWindow::setOutputRequest(corbasim::event::request_ptr req)
{
    m_output_log->notifyRequest(req);

    // TODO send through the caller
}



// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestDialog.cpp
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

#include "RequestDialog.hpp"
#include <corbasim/gui/dialogs.hpp>

using namespace corbasim::qt;

RequestDialog::RequestDialog(dialogs::input_base* dlg, 
        QWidget * parent) :
    QDialog(parent), m_dlg(dlg)
{
    QVBoxLayout * layout = new QVBoxLayout;

    QScrollArea * scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(m_dlg->get_qwidget());
    layout->addWidget(scroll); 

    QHBoxLayout * periodicLayout = new QHBoxLayout;

    periodicLayout->addWidget(new QLabel("Period (ms)"));
    m_sbPeriod = new QSpinBox;
    m_sbPeriod->setRange(0, 999999);
    m_sbPeriod->setValue(100);
    periodicLayout->addWidget(m_sbPeriod);

    periodicLayout->addWidget(new QLabel("Times"));
    m_sbTimes = new QSpinBox;
    m_sbTimes->setRange(-1, 999999);
    m_sbTimes->setValue(-1);
    periodicLayout->addWidget(m_sbTimes);

    periodicLayout->addWidget(new QLabel("Use stored value"));
    m_cbUseStored = new QCheckBox;
    m_cbUseStored->setChecked(true);
    periodicLayout->addWidget(m_cbUseStored);

    layout->addLayout(periodicLayout);
   
    // Botones 
    QHBoxLayout * btnsLayout = new QHBoxLayout;

    // Start stop
    m_pbStartStop = new QPushButton("S&tart/Stop");
    m_pbStartStop->setCheckable(true);
    QObject::connect(m_pbStartStop, SIGNAL(toggled(bool)), 
            this, SLOT(startStopChecked(bool)));
    btnsLayout->addWidget(m_pbStartStop);

    // Update
    m_pbUpdate = new QPushButton("&Update");
    QObject::connect(m_pbUpdate, SIGNAL(clicked()), 
            this, SLOT(storeRequest()));
    btnsLayout->addWidget(m_pbUpdate);

    // Send button
    QPushButton * btn = new QPushButton("&Send");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(sendClicked())); 
    btnsLayout->addWidget(btn);

    // Close button
    btn = new QPushButton("&Close");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(hide())); 
    btnsLayout->addWidget(btn);

    layout->addLayout(btnsLayout);
   
    // Timer
    QObject::connect(&m_timer, SIGNAL(timeout()), 
            this, SLOT(sendStored()));

    setLayout(layout);

    // TODO registrar en otro sitio una sola vez
    int id = qRegisterMetaType< event::request_ptr >("corbasim::event::request_ptr");
}

RequestDialog::~RequestDialog()
{
    delete m_dlg;
}

void RequestDialog::stopTimer()
{
    m_pbStartStop->setChecked(false);
}

void RequestDialog::sendClicked()
{
    emit sendRequest(event::request_ptr(m_dlg->create_request()));
}

void RequestDialog::startStopChecked(bool chk)
{
    if (chk)
    {
        storeRequest();
        m_currentPeriodicRequest = 0;
        m_timer.start(m_sbPeriod->value());
    }
    else
    {
        m_timer.stop();
    }
}

void RequestDialog::storeRequest()
{
    m_storedRequest = event::request_ptr(m_dlg->create_request());
}

void RequestDialog::sendStored()
{
    if (m_cbUseStored->isChecked())
        emit sendRequest(m_storedRequest);
    else
        emit sendRequest(event::request_ptr(m_dlg->create_request()));

    ++m_currentPeriodicRequest;
    if (m_sbTimes->value() >= 0 && 
            m_currentPeriodicRequest >= m_sbTimes->value())
        m_pbStartStop->setChecked(false);
}


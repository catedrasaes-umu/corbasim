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
#include <corbasim/gui/dialogs_fwd.hpp>
#include <corbasim/qt/initialize.hpp>

// Qt widgets
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include <iostream>

using namespace corbasim;
using namespace corbasim::reflective_gui;

RequestDialog::RequestDialog( 
        core::operation_reflective_base const * reflective,
        QWidget * parent) :
    QDialog(parent), m_dlg(new OperationInputForm(reflective, this))
{
    corbasim::qt::initialize();

    QVBoxLayout * layout = new QVBoxLayout();

    // Input scroll
    QScrollArea * scroll = new QScrollArea();
    scroll->setObjectName("scroll");
    scroll->setWidgetResizable(true);
    m_dlg->setObjectName("form");
    
    QWidget * scrollWidget = new QWidget();
    QVBoxLayout * scrollLayout = new QVBoxLayout();
    scrollLayout->setMargin(0);
    scrollWidget->setLayout(scrollLayout);
    scrollLayout->addWidget(m_dlg);
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollLayout->addItem(spacer);
    scroll->setWidget(scrollWidget);
    layout->addWidget(scroll); 
    scroll->setLineWidth(0);
    scroll->setFrameStyle(QFrame::NoFrame);
    // End scroll

    QHBoxLayout * periodicLayout = new QHBoxLayout;

    spacer = new QSpacerItem(20, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    periodicLayout->addItem(spacer);

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

    spacer = new QSpacerItem(20, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    btnsLayout->addItem(spacer);

    // Start stop
    m_pbStartStop = new QPushButton("S&tart/Stop");
    m_pbStartStop->setCheckable(true);
    QObject::connect(m_pbStartStop, SIGNAL(toggled(bool)), 
            this, SLOT(startStopChecked(bool)));
    btnsLayout->addWidget(m_pbStartStop);

    // Update
    m_pbUpdate = new QPushButton("&Update");
    m_pbUpdate->setObjectName("updateButton");
    QObject::connect(m_pbUpdate, SIGNAL(clicked()), 
            this, SLOT(storeRequest()));
    btnsLayout->addWidget(m_pbUpdate);

    // Send button
    QPushButton * btn = new QPushButton("&Send");
    btn->setObjectName("sendButton");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(sendClicked())); 
    btnsLayout->addWidget(btn);

    // Close button
    btn = new QPushButton("&Close");
    btn->setObjectName("closeButton");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(hide())); 
    btnsLayout->addWidget(btn);

    layout->addLayout(btnsLayout);
   
    // Timer
    QObject::connect(&m_timer, SIGNAL(timeout()), 
            this, SLOT(sendStored()));

    setLayout(layout);
}

RequestDialog::~RequestDialog()
{
}

void RequestDialog::stopTimer()
{
    m_pbStartStop->setChecked(false);
}

void RequestDialog::sendClicked()
{
    emit sendRequest(m_dlg->createRequest());
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
    m_storedRequest = m_dlg->createRequest();
}

void RequestDialog::sendStored()
{
    if (m_cbUseStored->isChecked())
        emit sendRequest(m_storedRequest);
    else
        sendClicked();

    ++m_currentPeriodicRequest;
    if (m_sbTimes->value() >= 0 && 
            m_currentPeriodicRequest >= m_sbTimes->value())
        m_pbStartStop->setChecked(false);
}

void RequestDialog::hideEvent(QHideEvent * event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}

corbasim::core::operation_reflective_base const * 
RequestDialog::getReflective() const
{
    return m_dlg->getReflective();
}

// Settings
void RequestDialog::save(QVariant& settings) 
{
    QVariantMap map;

    map["period"] = m_sbPeriod->value();
    map["times"] = m_sbTimes->value();
    map["use_stored"] = m_cbUseStored->isChecked();
    map["start_stop"] = m_pbStartStop->isChecked();

    m_dlg->save(map["form"]);

    settings = map;
}

void RequestDialog::load(const QVariant& settings) {}


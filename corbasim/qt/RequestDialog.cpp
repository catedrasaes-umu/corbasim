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
#include <corbasim/qt/initialize.hpp>

#include <QtScript>
#include <iostream>

using namespace corbasim;
using namespace corbasim::qt;

RequestDialog::RequestDialog(dialogs::input_base* dlg, 
        QWidget * parent) :
    QDialog(parent), m_dlg(dlg)
{
    corbasim::qt::initialize();

    QVBoxLayout * layout = new QVBoxLayout;

    QScrollArea * scroll = new QScrollArea;
    scroll->setObjectName("scroll");
    scroll->setWidgetResizable(true);
    m_dlg->get_qwidget()->setObjectName("form");
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

#if 0
    // Prueba QtScript
    QFile file(QString(m_dlg->get_name())+ ".js");

    if (!file.exists())
    {
        std::cout << "Could not find program file!" << std::endl;
        return;
    }
 
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Could not open program file!";
        return;
    }

    QScriptEngine * engine = new QScriptEngine;
    QScriptValue m_thisObject = engine->newQObject(this);

    QString strProgram = file.readAll();
 
    // do static check so far of code:
    if (! engine->canEvaluate(strProgram) )
    {
        QMessageBox::critical(0, "Error", "canEvaluate returned false!");
        return;
    }
 
    // actually do the eval:
    engine->evaluate(strProgram);

    // uncaught exception?
    if (engine->hasUncaughtException())
    {
        QScriptValue exception = engine->uncaughtException();
        QMessageBox::critical(0, "Script error", 
                QString("Script threw an uncaught exception: ") 
                + exception.toString());
        return;
    }

    QScriptValue createFunc = engine->evaluate("create");

    if (engine->hasUncaughtException())
    {
        QScriptValue exception = engine->uncaughtException();
        QMessageBox::critical(0, "Script error", 
                QString("Script threw an uncaught exception while"
                    " looking for create func: ") 
                + exception.toString());
        return;
    }

    if (!createFunc.isFunction())
    {
        QMessageBox::critical(0, "Script Error", 
                "createFunc is not a function!");
    }

    createFunc.call(m_thisObject);

    if (engine->hasUncaughtException())
    {
        QScriptValue exception = engine->uncaughtException();
        QMessageBox::critical(0, "Script error", 
                QString("Script threw an uncaught exception while"
                    " looking for create func: ") 
                + exception.toString());
        return;
    }
#endif
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


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * OperationSequence.cpp
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

#include "OperationSequence.hpp"
#include <corbasim/gui/ReflectiveGUI.hpp>

using namespace corbasim::gui;

OperationSequenceItem::OperationSequenceItem(
        Objref_ptr object,
        OperationDescriptor_ptr operation,
        QWidget * parent) : 
    AbstractSequenceItem(object, operation, parent)
{
    QVBoxLayout * layout = 
        qobject_cast< QVBoxLayout * >(QWidget::layout());

    // Editor
    m_dlg = new OperationInputForm(operation);
    m_dlg->hide();
    layout->addWidget(m_dlg);

    // Bottom buttons and options
    QHBoxLayout * bLayout = new QHBoxLayout();

    // Horizontal spacer
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    bLayout->addItem(spacer);

    // periodic
    bLayout->addWidget(new QLabel("Period (ms)"));
    m_sbPeriod = new QSpinBox;
    m_sbPeriod->setRange(0, 999999);
    m_sbPeriod->setValue(100);
    bLayout->addWidget(m_sbPeriod);

    bLayout->addWidget(new QLabel("Times"));
    m_sbTimes = new QSpinBox;
    m_sbTimes->setRange(-1, 999999);
    m_sbTimes->setValue(-1);
    bLayout->addWidget(m_sbTimes);

    bLayout->addWidget(new QLabel("Use stored value"));
    m_cbUseStored = new QCheckBox;
    m_cbUseStored->setChecked(true);
    bLayout->addWidget(m_cbUseStored);

    layout->addLayout(bLayout);

    bLayout = new QHBoxLayout();

    // Horizontal spacer
    spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    bLayout->addItem(spacer);

    m_pbStartStop = new QPushButton("S&tart/Stop");
    m_pbStartStop->setCheckable(true);
    m_pbStartStop->setObjectName("start-stop");
    bLayout->addWidget(m_pbStartStop);

    m_pbUpdate = new QPushButton("&Update");
    bLayout->addWidget(m_pbUpdate);
    // end periodic

    QPushButton * btSend = new QPushButton("Send");
    // QPushButton * btSendNext = new QPushButton("Send and next");

    bLayout->addWidget(btSend);
    // bLayout->addWidget(btSendNext);
   
    connect(btSend, SIGNAL(clicked()),
            this, SLOT(sendClicked()));
    connect(m_pbUpdate, SIGNAL(clicked()), 
            this, SLOT(storeRequest()));
    connect(m_pbStartStop, SIGNAL(toggled(bool)), 
            this, SLOT(startStopChecked(bool)));
    connect(&m_timer, SIGNAL(timeout()), 
            this, SLOT(sendStored()));

    layout->addLayout(bLayout);
    // End buttons
}

OperationSequenceItem::~OperationSequenceItem()
{
}

void OperationSequenceItem::showDetails(bool show)
{
    m_dlg->setVisible(show);
}

void OperationSequenceItem::sendClicked()
{
     emit sendRequest(m_dlg->createRequest());
}

void OperationSequenceItem::startStopChecked(bool chk)
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

void OperationSequenceItem::storeRequest()
{
    m_storedRequest = m_dlg->createRequest();
}

void OperationSequenceItem::sendStored()
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

void OperationSequenceItem::stopTimer()
{
    m_pbStartStop->setChecked(false);
}

// Tool
OperationSequenceTool::OperationSequenceTool(QWidget * parent) :
    AbstractSequenceTool(parent)
{
}

OperationSequenceTool::~OperationSequenceTool()
{
}

AbstractSequenceItem * 
OperationSequenceTool::createAbstractItem(
        Objref_ptr object, 
        OperationDescriptor_ptr op)
{
    OperationSequenceItem * item = 
        new OperationSequenceItem(object, op);

    connect(item, SIGNAL(sendRequest(Request_ptr)),
            object.get(), SLOT(sendRequest(Request_ptr)));

    return item;
}


// Settings
void OperationSequenceItem::doSave(QVariantMap& map)
{
    map["period"] = m_sbPeriod->value();
    map["times"] = m_sbTimes->value();
    map["use_stored"] = m_cbUseStored->isChecked();
    map["start_stop"] = m_pbStartStop->isChecked();

    m_dlg->save(map["form"]);
}

void OperationSequenceItem::doLoad(const QVariantMap& map)
{
    m_dlg->load(map.value("form"));

    m_sbPeriod->setValue(map.value("period").toInt());

    m_sbTimes->setValue(map.value("times").toInt());

    m_cbUseStored->setChecked(map.value("use_stored").toBool());
    m_pbStartStop->setChecked(map.value("start_stop").toBool());
}


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SenderSequence.cpp
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

#include "SenderSequence.hpp"
#include <corbasim/gui/OperationForm.hpp>

using namespace corbasim::gui;

SenderSequenceItem::SenderSequenceItem(Objref_ptr object,
        OperationDescriptor_ptr operation,
        QWidget * parent) : 
    AbstractSequenceItem(object, operation, parent), 
    m_dlg(NULL)
{
    QVBoxLayout * layout = 
        qobject_cast< QVBoxLayout * >(QWidget::layout());

    m_dlg = new OperationSender(object);
    m_dlg->initialize(operation);

    m_dlg->getForm()->hide();
    m_dlg->layout()->setMargin(0);

    layout->addWidget(m_dlg);
}

SenderSequenceItem::~SenderSequenceItem()
{
}

void SenderSequenceItem::showDetails(bool show)
{
    m_dlg->getForm()->setVisible(show);
}

// Tool
SenderSequenceTool::SenderSequenceTool(QWidget * parent) :
    AbstractSequenceTool(parent)
{
    m_filter = tr("CORBASIM Sender Sequence Tool (*.sst)");
    m_extension = ".sst";
}

SenderSequenceTool::~SenderSequenceTool()
{
}

AbstractSequenceItem * 
SenderSequenceTool::createAbstractItem(
        Objref_ptr object, 
		OperationDescriptor_ptr op)
{
    SenderSequenceItem * item = 
        new SenderSequenceItem(object, op);

    return item;
}

// Settings

void SenderSequenceItem::doSave(QVariantMap& map)
{
    m_dlg->save(map["form"]);
}

void SenderSequenceItem::doLoad(const QVariantMap& map)
{
    m_dlg->load(map.value("form"));
}



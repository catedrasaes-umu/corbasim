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
#include <corbasim/gui/json.hpp>

#include <fstream>

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

    OperationForm * form = m_dlg->getForm();
    form->showSizeGrip(true);

    form->hide();
    m_dlg->layout()->setMargin(0);
    layout->addWidget(m_dlg);
}

SenderSequenceItem::~SenderSequenceItem()
{
}

OperationSender * SenderSequenceItem::sender() const
{
    return m_dlg;
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

    // Additional actions
    m_menuCurrentItem->addSeparator();
    m_currentItemActions.push_back(
            m_menuCurrentItem->addAction("Load form value",
                this, SLOT(loadCurrentItemFormValue())));
    m_currentItemActions.push_back(
            m_menuCurrentItem->addAction("Save form value",
                this, SLOT(saveCurrentItemFormValue())));
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

void SenderSequenceTool::saveCurrentItemFormValue()
{
    if (m_currentItem)
    {
        SenderSequenceItem * sender =
            static_cast< SenderSequenceItem * >(m_currentItem);

        QString file = QFileDialog::getSaveFileName(
                0, tr("Select a file"), ".");

        // User cancels
        if (file.isEmpty())
            return;

        QVariant v;
        sender->sender()->getForm()->getWidget()->save(v);

        std::ofstream ofs(file.toStdString().c_str());
        json::ostream_writer_t ow(ofs, true);

        toJson(ow, v);
    }
}

void SenderSequenceTool::loadCurrentItemFormValue()
{
    if (m_currentItem)
    {
        SenderSequenceItem * sender =
            static_cast< SenderSequenceItem * >(m_currentItem);

        const QString file = QFileDialog::getOpenFileName(
                0, tr("Select some file"), ".");

        // User cancels
        if (file.isEmpty())
            return;

        QVariant var;

        // Try to Read a JSON file
        bool res = fromJsonFile(file.toStdString().c_str(), var);

        if (res)
        {
            sender->sender()->getForm()->getWidget()->load(var);
        }
        else
        {
            // TODO display error
        }
    }
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



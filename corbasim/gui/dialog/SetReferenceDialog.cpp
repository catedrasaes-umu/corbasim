// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SetReferenceDialog.cpp
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

#include "SetReferenceDialog.hpp"
#include <cassert>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QMdiSubWindow>

using namespace corbasim::gui;

SetReferenceDialog::SetReferenceDialog(QWidget * parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QGridLayout * grid = new QGridLayout();

    {
        QGroupBox * group = new QGroupBox("New object reference");
        QVBoxLayout * groupLayout = new QVBoxLayout();
        groupLayout->setMargin(0);

        m_reference = new ObjrefWidget();
        m_reference->setObjectName("reference");
        groupLayout->addWidget(m_reference);
        group->setLayout(groupLayout);

        grid->addWidget(group, 1, 0, 1, 2);
    }

    layout->addLayout(grid);

    // Buttons
    QDialogButtonBox * btns = new QDialogButtonBox();
    QPushButton * pasteButton =
        btns->addButton("&Paste IOR from clipboard", QDialogButtonBox::ActionRole);
    QPushButton * createButton =
        btns->addButton("&Apply", QDialogButtonBox::AcceptRole);
    QPushButton * cancelButton =
        btns->addButton("C&ancel", QDialogButtonBox::RejectRole);
    layout->addWidget(btns);

    connect(pasteButton, SIGNAL(clicked()),
            m_reference, SLOT(pasteIOR()));
    connect(createButton, SIGNAL(clicked()),
            this, SLOT(update()));
    connect(cancelButton, SIGNAL(clicked()),
            window(), SLOT(hide()));
    // End buttons

    setLayout(layout);
}

SetReferenceDialog::~SetReferenceDialog()
{
}

void SetReferenceDialog::setInterface(InterfaceDescriptor_ptr interface)
{
    m_reference->setInterface(interface);
}

void SetReferenceDialog::hideEvent(QHideEvent* event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}

void SetReferenceDialog::updatedReference(const CORBA::Object_var& reference)
{
    m_reference->setReference(reference);
}

void SetReferenceDialog::update()
{
    emit setReference(m_reference->reference());
}


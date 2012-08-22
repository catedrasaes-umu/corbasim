// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * CreateDialog.cpp
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

#include "CreateDialog.hpp"
#include <corbasim/core/reflective.hpp>

using namespace corbasim::app;

ObjrefCreateDialog::ObjrefCreateDialog(QWidget * parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    QDialogButtonBox * btns = new QDialogButtonBox();

    QPushButton * createButton = 
        btns->addButton("&Create", QDialogButtonBox::AcceptRole);
    QPushButton * cancelButton = 
        btns->addButton("C&ancel", QDialogButtonBox::RejectRole);

    layout->addWidget(btns);

    connect(createButton, SIGNAL(clicked()),
            this, SLOT(createClicked()));

    connect(cancelButton, SIGNAL(clicked()),
            window(), SLOT(hide()));

    setLayout(layout);
}

ObjrefCreateDialog::~ObjrefCreateDialog()
{
}

void ObjrefCreateDialog::createClicked()
{
}

void ObjrefCreateDialog::hideEvent(QHideEvent* event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}

// Servant

ServantCreateDialog::ServantCreateDialog(QWidget * parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    QDialogButtonBox * btns = new QDialogButtonBox();

    QPushButton * createButton = 
        btns->addButton("&Create", QDialogButtonBox::AcceptRole);
    QPushButton * cancelButton = 
        btns->addButton("C&ancel", QDialogButtonBox::RejectRole);

    layout->addWidget(btns);

    connect(createButton, SIGNAL(clicked()),
            this, SLOT(createClicked()));

    connect(cancelButton, SIGNAL(clicked()),
            window(), SLOT(hide()));

    setLayout(layout);

    setMinimumWidth(400);
}

ServantCreateDialog::~ServantCreateDialog()
{
}

void ServantCreateDialog::createClicked()
{
}

void ServantCreateDialog::hideEvent(QHideEvent* event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}

ReferenceValidatedWidget::ReferenceValidatedWidget(
	corbasim::core::reference_validator_base * validator,
        QWidget * parent) :
    QWidget(parent), m_validator(validator)
{
    QVBoxLayout * l = new QVBoxLayout;

    m_widget = new qt::ObjrefWidget(validator, this);
    l->addWidget(m_widget);

    // TODO use QDialogButtonBox
    
    QPushButton * applyBtn = new QPushButton("&Apply", this);
    QPushButton * pasteBtn = new QPushButton("&Paste IOR from clipboard", this);

    connect(applyBtn, SIGNAL(clicked()),
            this, SLOT(applyClicked()));
    connect(pasteBtn, SIGNAL(clicked()),
            m_widget, SLOT(pasteIOR()));

    QHBoxLayout * hl = new QHBoxLayout;

    // Horizontal spacer
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    hl->addItem(spacer);

    hl->addWidget(applyBtn);
    hl->addWidget(pasteBtn);

    l->addLayout(hl);

    setLayout(l);
}

ReferenceValidatedWidget::~ReferenceValidatedWidget()
{
    delete m_validator;
}

void ReferenceValidatedWidget::updateReference(const CORBA::Object_var& ref)
{
    m_validator->set_reference(ref);
    m_widget->validatorHasChanged();
}

void ReferenceValidatedWidget::applyClicked()
{
    CORBA::Object_var ref = m_validator->get_reference();

    emit updatedReference(ref);
}



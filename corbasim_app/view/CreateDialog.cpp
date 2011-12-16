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

using namespace corbasim::app::view;

ObjrefCreateDialog::ObjrefCreateDialog(QWidget * parent) :
    QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    layout->addWidget(m_widget.getWidget());

    QHBoxLayout * hLayout = new QHBoxLayout;

    QPushButton * createButton = new QPushButton("&Create");
    QPushButton * cancelButton = new QPushButton("C&ancel");

    QObject::connect(createButton, SIGNAL(clicked()),
            this, SLOT(createClicked()));

    QObject::connect(cancelButton, SIGNAL(clicked()),
            window(), SLOT(hide()));

    hLayout->addWidget(createButton);
    hLayout->addWidget(cancelButton);

    layout->addLayout(hLayout);
    setLayout(layout);
}

ObjrefCreateDialog::~ObjrefCreateDialog()
{
}

void ObjrefCreateDialog::createClicked()
{
    ObjrefConfig config;
    m_widget.get_value(config);

    // TODO validate

    emit createObjref(config);

    hide();
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
    QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    layout->addWidget(m_widget.getWidget());

    QHBoxLayout * hLayout = new QHBoxLayout;

    QPushButton * createButton = new QPushButton("&Create");
    QPushButton * cancelButton = new QPushButton("C&ancel");

    QObject::connect(createButton, SIGNAL(clicked()),
            this, SLOT(createClicked()));

    QObject::connect(cancelButton, SIGNAL(clicked()),
            window(), SLOT(hide()));

    hLayout->addWidget(createButton);
    hLayout->addWidget(cancelButton);

    layout->addLayout(hLayout);
    setLayout(layout);
}

ServantCreateDialog::~ServantCreateDialog()
{
}

void ServantCreateDialog::createClicked()
{
    ServantConfig config;
    m_widget.get_value(config);

    // TODO validate

    emit createServant(config);

    hide();
}

void ServantCreateDialog::hideEvent(QHideEvent* event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}

ReferenceValidatedWidget::ReferenceValidatedWidget(
        core::reference_validator_base * validator,
        QWidget * parent) :
    QWidget(parent), m_validator(validator)
{
    QVBoxLayout * l = new QVBoxLayout;

    m_widget = new qt::ObjrefWidget(validator, this);
    l->addWidget(m_widget);

    QPushButton * applyBtn = new QPushButton("&Apply", this);

    QObject::connect(applyBtn, SIGNAL(clicked()),
            this, SLOT(applyClicked()));

    // TODO spacer
    l->addWidget(applyBtn);

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



// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UpdateReferenceDialog.cpp
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

#include "UpdateReferenceDialog.hpp"
#include <corbasim/adapted.hpp>
#include <corbasim/corba_adapted.hpp>
#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>
#include <corbasim/gui/Model.hpp>

using namespace corbasim::gui;

UpdateReferenceDialog::UpdateReferenceDialog(QWidget * parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QGridLayout * grid = new QGridLayout();

    {
        QGroupBox * group = new QGroupBox("Current object reference");
        QVBoxLayout * groupLayout = new QVBoxLayout();
        groupLayout->setMargin(0);

        m_status = new qt::ObjrefWidget();
        m_status->setObjectName("status");
        groupLayout->addWidget(m_status);
        group->setLayout(groupLayout);
        
        grid->addWidget(group, 0, 0, 1, 2);
    }
    {
        QGroupBox * group = new QGroupBox("New object reference");
        QVBoxLayout * groupLayout = new QVBoxLayout();
        groupLayout->setMargin(0);

        m_reference = new qt::ObjrefWidget();
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

UpdateReferenceDialog::~UpdateReferenceDialog()
{
}

void UpdateReferenceDialog::hideEvent(QHideEvent* event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}

void UpdateReferenceDialog::setObjref(Objref_ptr objref)
{
    if (m_objref)
    {
        disconnect(m_objref.get(), 
                SIGNAL(updatedReference(const CORBA::Object_var&)),
                this,
                SLOT(updatedReference(const CORBA::Object_var&)));
        disconnect(this, 
                SIGNAL(updateReference(const CORBA::Object_var&)),
                m_objref.get(),
                SLOT(setReference(const CORBA::Object_var&)));
    }

    m_objref = objref;

    if (m_objref)
    {
        m_statusValidator.reset(objref->interface()->create_validator());
        m_referenceValidator.reset(objref->interface()->create_validator());
        m_status->setValidator(m_statusValidator.get());
        m_reference->setValidator(m_referenceValidator.get());

        updatedReference(objref->reference());

        connect(m_objref.get(), 
                SIGNAL(updatedReference(const CORBA::Object_var&)),
                this,
                SLOT(updatedReference(const CORBA::Object_var&)));
        connect(this, 
                SIGNAL(updateReference(const CORBA::Object_var&)),
                m_objref.get(),
                SLOT(setReference(const CORBA::Object_var&)));
    }
}

void UpdateReferenceDialog::updatedReference(const CORBA::Object_var& reference)
{
    m_statusValidator->set_reference(reference);
    m_status->validatorHasChanged();
}

void UpdateReferenceDialog::update()
{
    emit updateReference(m_referenceValidator->get_reference());
}


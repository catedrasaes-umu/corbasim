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
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    layout->addWidget(m_widget.getWidget());

    QHBoxLayout * hLayout = new QHBoxLayout;

    QPushButton * createButton = new QPushButton("&Create");
    QPushButton * cancelButton = new QPushButton("C&ancel");

    QObject::connect(createButton, SIGNAL(clicked()),
            this, SLOT(createClicked()));
/* 
    QObject::connect(cancelButton, SIGNAL(clicked()),
            window(), SLOT(hide()));
 */

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

    // window()->hide();
}


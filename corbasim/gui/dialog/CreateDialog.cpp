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
#include <corbasim/adapted.hpp>
#include <corbasim/corba_adapted.hpp>
#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>

using namespace corbasim::gui;

ObjrefCreateDialog::ObjrefCreateDialog(QWidget * parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QGridLayout * grid = new QGridLayout();

    // Name
    grid->addWidget(new QLabel("Object name"), 0, 0);
    m_name = new QLineEdit();
    m_name->setObjectName("name");
    grid->addWidget(m_name, 0, 1);
 
    // Interface
    grid->addWidget(new QLabel("Interface"), 1, 0);
    m_fqn = new QComboBox();
    m_fqn->setEditable(true);
    m_fqn->setObjectName("fqn");
    grid->addWidget(m_fqn, 1, 1); 

    // Reference
    QGroupBox * group = new QGroupBox("Object reference");
    m_fqn->setObjectName("reference_group");
    QVBoxLayout * groupLayout = new QVBoxLayout();
    groupLayout->setMargin(0);

    m_reference = new ObjrefWidget();
    m_reference->setObjectName("reference");
    groupLayout->addWidget(m_reference);
    group->setLayout(groupLayout);
    
    grid->addWidget(group, 2, 0, 1, 2);
    // End reference

    // Watch file
    QHBoxLayout * watchFileLayout = new QHBoxLayout();
    grid->addWidget(new QLabel("Watch file"), 3, 0);

    m_watchFile = new QLineEdit();
    m_watchFile->setObjectName("watch-file");
    watchFileLayout->addWidget(m_watchFile);
    QPushButton * browseButton = new QPushButton("Browse");
    watchFileLayout->addWidget(browseButton);
    grid->addLayout(watchFileLayout, 3, 1);

    connect(browseButton, SIGNAL(clicked()), 
            this, SLOT(browse()));
    // End watch file


    layout->addLayout(grid);

    // Buttons
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
    // End buttons

    setLayout(layout);

    // TODO deprecated
    /*
    ::corbasim::core::detail::objrefvar_reflective< CORBA::Object_var > iface;
    m_validator.reset(iface.create_validator());
    m_reference->setValidator(m_validator.get());
     */
}

ObjrefCreateDialog::~ObjrefCreateDialog()
{
}

void ObjrefCreateDialog::setFQNModel(QAbstractItemModel * model)
{
    m_fqn->setModel(model);
}

void ObjrefCreateDialog::createClicked()
{
    ObjrefConfig cfg;

    cfg.name = m_name->text().toStdString();
    cfg.fqn = m_fqn->currentText().toStdString();
    cfg.reference = m_reference->reference();
    cfg.entry = m_reference->getNSEntry().toStdString();
    cfg.watchFile = m_watchFile->text().toStdString();

    emit createObjref(cfg);
}

void ObjrefCreateDialog::browse()
{
    const QString file = 
        QFileDialog::getOpenFileName(0, 
                "Select a file", ".");

    m_watchFile->setText(file);
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

    QGridLayout * grid = new QGridLayout();

    // Name
    grid->addWidget(new QLabel("Servant name"), 0, 0);
    m_name = new QLineEdit();
    m_name->setObjectName("name");
    grid->addWidget(m_name, 0, 1);
 
    // Interface
    grid->addWidget(new QLabel("Interface"), 1, 0);
    m_fqn = new QComboBox();
    m_fqn->setObjectName("fqn");
    m_fqn->setEditable(true);
    grid->addWidget(m_fqn, 1, 1); 

    // Name service
    grid->addWidget(new QLabel("Name service key"), 2, 0);
    m_entry = new QLineEdit();
    m_entry->setObjectName("entry");
    grid->addWidget(m_entry, 2, 1);

    // Reference file
    QHBoxLayout * saveFileLayout = new QHBoxLayout();
    grid->addWidget(new QLabel("Save reference"), 3, 0);
    m_saveFile = new QLineEdit();
    m_saveFile->setObjectName("save-reference");
    saveFileLayout->addWidget(m_saveFile);
    QPushButton * browseButton = new QPushButton("Browse");
    saveFileLayout->addWidget(browseButton);
    grid->addLayout(saveFileLayout, 3, 1);

    connect(browseButton, SIGNAL(clicked()), 
            this, SLOT(browse()));

    layout->addLayout(grid);

#if 0
    QGroupBox * group = new QGroupBox("Object reference");
    m_fqn->setObjectName("reference_group");
    QVBoxLayout * groupLayout = new QVBoxLayout();
    groupLayout->setMargin(0);

    m_reference = new ObjrefWidget();
    m_reference->setObjectName("reference");
    groupLayout->addWidget(m_reference);
    group->setLayout(groupLayout);

    grid->addWidget(group, 2, 0, 1, 2);
#endif

    // Buttons
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

void ServantCreateDialog::setFQNModel(QAbstractItemModel * model)
{
    m_fqn->setModel(model);
}

void ServantCreateDialog::createClicked()
{
    ServantConfig cfg;

    cfg.name = m_name->text().toStdString();
    cfg.fqn = m_fqn->currentText().toStdString();
    cfg.entry = m_entry->text().toStdString();
    cfg.saveFile = m_saveFile->text().toStdString();

    emit createServant(cfg);
}

void ServantCreateDialog::browse()
{
    const QString file = 
        QFileDialog::getSaveFileName(0, 
                "Select a file", ".");

    m_saveFile->setText(file);
}

void ServantCreateDialog::hideEvent(QHideEvent* event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}



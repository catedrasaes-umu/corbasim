// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * MultiInputWidget.cpp
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

#include "MultiInputWidget.hpp"

#include <QtGui>

using namespace corbasim;
using namespace corbasim::qt;

MultiInputWidget::MultiInputWidget(QWidget * parent) :
    QWidget(parent), m_factory(NULL)
{
    QVBoxLayout * layout = new QVBoxLayout;

    m_stack = new QStackedWidget;
    layout->addWidget(m_stack);

    setLayout(layout);
}

MultiInputWidget::~MultiInputWidget()
{
}

void MultiInputWidget::initialize(gui::gui_factory_base const * factory)
{
    m_factory = factory;

    unsigned int count = factory->operation_count();

#if 1
    for (unsigned int i = 0; i < count; i++) 
    {
        dialogs::input_base * _input = 
            factory->get_factory_by_index(i)->create_input();

        // Envuelve el formulario en un scroll area
        QScrollArea * scroll = new QScrollArea;
        scroll->setWidgetResizable(true);
        scroll->setWidget(_input->get_qwidget());

        // Añade el fomulario al stacked widget
        m_stack->addWidget(scroll);
        m_inputs.push_back(dialogs::input_ptr(_input));
    }
#else

    m_inputs.resize(count);

    // Inicializa el primero
    if (count)
        getDialog(0);
#endif
}

void MultiInputWidget::changeInputForm(int index)
{ 
    if (m_inputs.empty() || !getDialog(index))
        return;

    m_stack->setCurrentIndex(index);
}

corbasim::dialogs::input_ptr MultiInputWidget::getCurrentDialog()
{
    return getDialog(m_stack->currentIndex());
}

corbasim::dialogs::input_ptr MultiInputWidget::getDialog(int index)
{
    if (!m_inputs[index])
    {
        dialogs::input_ptr _input( 
            m_factory->get_factory_by_index(index)->create_input());

        // Envuelve el formulario en un scroll area
        QScrollArea * scroll = new QScrollArea;
        scroll->setWidgetResizable(true);
        scroll->setWidget(_input->get_qwidget());

        // Añade el fomulario al stacked widget
        m_stack->insertWidget(index, scroll);
        m_inputs[index] = _input;
    }

    return  m_inputs[index];
}

MultiInputForm::MultiInputForm(QWidget * parent) :
    QWidget(parent)
{
    QGridLayout * layout = new QGridLayout;

    // Selector
    layout->addWidget(new QLabel("Operation"), 0, 0);
    m_selector = new QComboBox;
    layout->addWidget(m_selector, 0, 1);

    m_multi = new MultiInputWidget;
    layout->addWidget(m_multi, 1, 0, 1, 2);

    setLayout(layout);

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)), 
            m_multi, SLOT(changeInputForm(int)));
}

MultiInputForm::~MultiInputForm()
{
}

void MultiInputForm::initialize(gui::gui_factory_base const * factory)
{
    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
        m_selector->addItem(factory->get_factory_by_index(i)->get_name());

    m_multi->initialize(factory);
}

MultiSenderDialog::MultiSenderDialog(QWidget * parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    // Selector
    QHBoxLayout * selLayout = new QHBoxLayout;
    selLayout->addWidget(new QLabel("Operation"));
    m_selector = new QComboBox;
    selLayout->addWidget(m_selector);
    layout->addLayout(selLayout);

    m_multi = new MultiInputWidget;
    layout->addWidget(m_multi);

    // Send
    QHBoxLayout * btnLayout = new QHBoxLayout;
    QPushButton * btnSend = new QPushButton("&Send");
    QObject::connect(btnSend, SIGNAL(clicked()),
            this, SLOT(sendClicked()));
    btnLayout->addWidget(btnSend);

    // Close
    QPushButton * btnClose = new QPushButton("&Close");
    QObject::connect(btnClose, SIGNAL(clicked()),
            this, SLOT(hide()));
    btnLayout->addWidget(btnClose);

    layout->addLayout(btnLayout);

    setLayout(layout);

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)), 
            m_multi, SLOT(changeInputForm(int)));
}

MultiSenderDialog::~MultiSenderDialog()
{
}

void MultiSenderDialog::initialize(gui::gui_factory_base const * factory)
{
    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
        m_selector->addItem(factory->get_factory_by_index(i)->get_name());

    m_multi->initialize(factory);
}

void MultiSenderDialog::sendClicked()
{
    // Obtiene el dialogo seleccionado
    dialogs::input_ptr dlg = m_multi->getCurrentDialog();

    // Crea una request del tipo seleccionado con los valores
    // del dialogo
    emit sendRequest(event::request_ptr(dlg->create_request()));
}


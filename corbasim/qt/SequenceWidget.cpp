// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SequenceWidget.cpp
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

#include "SequenceWidget.hpp"

using namespace corbasim;
using namespace corbasim::qt;

SequenceWidget::SequenceWidget(gui::widget_factory_base const * factory, QWidget * parent) :
    QWidget(parent), m_factory(factory)
{
    QVBoxLayout * layout = new QVBoxLayout;
 
    QHBoxLayout * headerLayout = new QHBoxLayout;
    m_sbLength = new QSpinBox;
    m_sbCurrentIndex = new QSpinBox;

    headerLayout->addWidget(new QLabel("Length"));
    headerLayout->addWidget(m_sbLength);

    headerLayout->addWidget(new QLabel("Index"));
    headerLayout->addWidget(m_sbCurrentIndex);

    layout->addLayout(headerLayout);

    m_stack = new QStackedWidget;
    layout->addWidget(m_stack);

    setLayout(layout);

    QObject::connect(m_sbLength, SIGNAL(valueChanged(int)),
            this, SLOT(lengthChanged(int)));
    QObject::connect(m_sbCurrentIndex, SIGNAL(valueChanged(int)),
            this, SLOT(indexChanged(int)));

    // TODO maximo razonable
    m_sbLength->setRange(0, 9999999);
    m_sbLength->setValue(0);
}

SequenceWidget::~SequenceWidget()
{
}

SequenceWidget::widgets_t& SequenceWidget::getWidgets()
{
    return m_widgets;
}

void SequenceWidget::lengthChanged(int len)
{
    int old_length = m_widgets.size();

    if (len > old_length)
    {
        for (int i = 0; i < len - old_length; i++) 
        {
            widgets::widget_ptr _ptr(m_factory->create_widget());
            m_widgets.push_back(_ptr);
            m_stack->addWidget(_ptr->getWidget());
        }
    }
    else
    {
        for (int i = len; i < old_length; i++) 
        {
            widgets::widget_ptr _ptr = m_widgets[i];
            m_stack->removeWidget(_ptr->getWidget());
        }

        m_widgets.resize(len);
    }

    m_sbCurrentIndex->setRange(0, len-1);
    m_sbLength->setValue(len);
}

void SequenceWidget::indexChanged(int idx)
{
    if (m_widgets.empty())
        return;

    m_stack->setCurrentIndex(idx);
}

SequenceWidget2::SequenceWidget2(widgets::abstract_sequence_widget * factory, 
        QWidget * parent) :
    QWidget(parent), m_factory(factory)
{
    QVBoxLayout * layout = new QVBoxLayout;
 
    QHBoxLayout * headerLayout = new QHBoxLayout;
    m_sbLength = new QSpinBox;
    m_sbCurrentIndex = new QSpinBox;

    headerLayout->addWidget(new QLabel("Length"));
    headerLayout->addWidget(m_sbLength);

    headerLayout->addWidget(new QLabel("Index"));
    headerLayout->addWidget(m_sbCurrentIndex);

    layout->addLayout(headerLayout);

    m_widget = m_factory->get_child_widget();
    m_widget->setVisible(false);
    layout->addWidget(m_widget);

    setLayout(layout);

    QObject::connect(m_sbLength, SIGNAL(valueChanged(int)),
            this, SLOT(lengthChanged(int)));
    QObject::connect(m_sbCurrentIndex, SIGNAL(valueChanged(int)),
            this, SLOT(indexChanged(int)));

    // TODO maximo razonable
    m_sbLength->setRange(0, 9999999);
    m_sbLength->setValue(0);
    
    m_sbCurrentIndex->setRange(0, 0);
}

SequenceWidget2::~SequenceWidget2()
{
}

void SequenceWidget2::notifyValueHasChanged(int length)
{
    m_sbLength->setValue(length);

    if (length)
        m_sbCurrentIndex->setValue(0);
    
    m_sbCurrentIndex->setRange(0, length-1);

    m_widget->setVisible(length != 0);
}

void SequenceWidget2::lengthChanged(int len)
{
    notifyValueHasChanged(len);
    m_factory->set_length(len);
}

void SequenceWidget2::indexChanged(int idx)
{
    m_factory->change_to(idx);
}



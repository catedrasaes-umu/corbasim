// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectiveGUI.cpp
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

#include "ReflectiveGUI.hpp"
#include <cassert>

using namespace corbasim::reflective_gui;

// should be a singleton instance of a factory
QWidget * createWidget(corbasim::core::reflective_base const * reflective,
        QWidget * parent)
{
    using namespace corbasim::core;

    if (!reflective)
        return new QLabel("Null reflective type!", parent);

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            return new BoolWidget(reflective, parent);

            // Integer types
        case TYPE_OCTET:
        case TYPE_CHAR:
        case TYPE_SHORT:
        case TYPE_USHORT:
        case TYPE_LONG:
        case TYPE_ULONG:
        case TYPE_LONGLONG:
        case TYPE_ULONGLONG:
            return new IntegerWidget(reflective, parent);
        
        case TYPE_STRING:
        case TYPE_WSTRING:
            return new StringWidget(reflective, parent);

        case TYPE_OBJREF:
        case TYPE_ARRAY:
        case TYPE_UNION:
            break;

        case TYPE_SEQUENCE:
            return new SequenceWidget(reflective, parent);

        case TYPE_DOUBLE:
        case TYPE_FLOAT:
            return new FloatWidget(reflective, parent);
        case TYPE_STRUCT:
            return new StructWidget(reflective, parent);
        case TYPE_ENUM:
            return new EnumWidget(reflective, parent);
        default:
            break;
    }

    return new QLabel("Unsupported item!", parent);
}

FloatWidget::FloatWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QDoubleSpinBox(parent), m_reflective(reflective)
{
}

FloatWidget::~FloatWidget()
{
}

IntegerWidget::IntegerWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QSpinBox(parent), m_reflective(reflective)
{
}

IntegerWidget::~IntegerWidget()
{
}

StringWidget::StringWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QLineEdit(parent), m_reflective(reflective)
{
}

StringWidget::~StringWidget()
{
}

EnumWidget::EnumWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QComboBox(parent), m_reflective(reflective)
{
    assert(reflective->is_enum());

    unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        addItem(reflective->get_child_name(i));
    }
}

EnumWidget::~EnumWidget()
{
}

BoolWidget::BoolWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QCheckBox(parent), m_reflective(reflective)
{
}

BoolWidget::~BoolWidget()
{
}

StructWidget::StructWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QWidget(parent), m_reflective(reflective)
{
    assert(reflective->get_type() == core::TYPE_STRUCT);

    QGridLayout * layout = new QGridLayout(this);

    unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        core::reflective_base const * child = 
            reflective->get_child(i);

        const char * child_name = reflective->get_child_name(i);

        QWidget * child_widget = createWidget(child, this);

        child_widget->setObjectName(child_name);

        if (child->is_primitive())
        {
            layout->addWidget(new QLabel(child_name, this), i, 0);
            layout->addWidget(child_widget, i, 1);
        }
        else
        {
            QGroupBox * gb = new QGroupBox(child_name, this);
            QHBoxLayout * cLayout = new QHBoxLayout(gb);

            cLayout->addWidget(child_widget);

            gb->setLayout(cLayout);
            layout->addWidget(gb, i, 0, 1, 2);
        }
    }

    setLayout(layout);
}

StructWidget::~StructWidget()
{
}

SequenceWidget::SequenceWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QWidget(parent), m_reflective(reflective)
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

void SequenceWidget::lengthChanged(int len)
{
    int old_length = m_widgets.size();

    if (len > old_length)
    {
        for (int i = 0; i < len - old_length; i++) 
        {
            QWidget * w = createWidget(m_reflective->get_slice(), this);
            m_widgets.push_back(w);
            m_stack->addWidget(w);
        }
    }
    else
    {
        for (int i = len; i < old_length; i++) 
        {
            QWidget * w = m_widgets[i];
            m_stack->removeWidget(w);
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



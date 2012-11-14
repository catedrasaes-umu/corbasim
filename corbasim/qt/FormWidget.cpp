// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FormWidget.cpp
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

#include "FormWidget.hpp"
#include <limits>

using namespace corbasim::qt;

FormWidget::FormWidget(QWidget * parent) :
    QWidget(parent), m_minWidth(std::numeric_limits< int >::min())
{
    m_layout = new QGridLayout(this);
    setLayout(m_layout);
    // reallocate(width());
}

FormWidget::~FormWidget()
{
}

void FormWidget::resizeEvent(QResizeEvent * event)
{
    reallocate(event->size().width());
}

void FormWidget::addField(const QString& text, QWidget * widget)
{
    Item item;
    
    item.label = new QLabel(text);
    item.widget = widget;

    m_minWidth = std::max(m_minWidth, item.label->minimumWidth());
    m_minWidth = std::max(m_minWidth, item.widget->minimumWidth());

    m_items.push_back(item);
    
    reallocate(width());
}

void FormWidget::addMediumField(const QString& text, QWidget * widget)
{
    Item item;
    
    item.label = new QLabel(text);
    item.widget = widget;
    item.medium = true;

    m_items.push_back(item);
    
    reallocate(width());
}

void FormWidget::addBigField(const QString& text, QWidget * widget)
{
    Item item;
    
    QGroupBox * gb = new QGroupBox(text, this);
    QHBoxLayout * cLayout = new QHBoxLayout(gb);
    cLayout->addWidget(widget);
    gb->setLayout(cLayout);

    item.widget = widget;
    item.group = gb;

    m_items.push_back(item);
    
    reallocate(width());
}

void FormWidget::reallocate(int width)
{
    for (int i = m_layout->count() - 1; i >= 0; i--) 
    {
        m_layout->takeAt(i);
    }

    if (m_minWidth <= 0)
        m_minWidth = 150;

    const int columnWidth = width / m_minWidth;
    int rowWidth = (columnWidth / 2) * 2;
    int row = 0;
    int column = 0;

    /*
    for (int i = 0; i < rowWidth; i++) 
    {
        m_layout->setColumnMinimumWidth(i, columnWidth);
    }
    */

    for (unsigned int i = 0; i < m_items.size(); i++) 
    {
        if (m_items[i].label && !m_items[i].medium)
        {
            m_layout->addWidget(m_items[i].label, row, column++);
            m_layout->addWidget(m_items[i].widget, row, column++);

            if (column == rowWidth)
            {
                row++;
                column = 0;
            }
        }
        else if (m_items[i].label)
        {
            if (column != 0) row++;
            column = 0;

            m_layout->addWidget(m_items[i].label, row, 0);
            m_layout->addWidget(m_items[i].widget, row, 1, 1, rowWidth - 1);

            row++;
        }
        else
        {
            if (column != 0) row++;
            column = 0;

            m_layout->addWidget(m_items[i].group, row++, 0, 1, rowWidth);
        }
    }

    setMinimumWidth(2 * m_minWidth);
}

void FormWidget::addField(const QString& text, QLayout * layout)
{
    QWidget * w = new QWidget(this);
    w->setLayout(layout);
    addField(text, w);
}

void FormWidget::addMediumField(const QString& text, QLayout * layout)
{
    QWidget * w = new QWidget(this);
    w->setLayout(layout);
    addMediumField(text, w);
}

void FormWidget::addBigField(const QString& text, QLayout * layout)
{
    QWidget * w = new QWidget(this);
    w->setLayout(layout);
    addBigField(text, w);
}


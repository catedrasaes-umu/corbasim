// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * LogTreeWidget.cpp
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

#include "LogTreeWidget.hpp"

#include <QTreeWidget>
#include <QVBoxLayout>

using namespace corbasim::qt;

LogTreeWidget::LogTreeWidget(int max_items, QWidget * parent) :
    QWidget(parent), m_max_items(max_items)
{
    QVBoxLayout * layout = new QVBoxLayout;
    m_tree = new QTreeWidget;
    m_tree->setHeaderLabel("Timeline");
    layout->addWidget(m_tree);
    setLayout(layout);
}

LogTreeWidget::~LogTreeWidget()
{
}

void LogTreeWidget::appendItem(QTreeWidgetItem * item)
{
    if (m_tree->topLevelItemCount() >= m_max_items)
        delete m_tree->takeTopLevelItem(0);

    m_tree->addTopLevelItem(item);
    m_tree->scrollToItem(item);
}

void LogTreeWidget::clear()
{
    m_tree->clear();
}


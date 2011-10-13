// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * LogWidget.cpp
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

#include "LogWidget.hpp"

using namespace corbasim::qt;

LogWidget::LogWidget(QWidget * parent) :
    QWidget(parent), m_factory(NULL)
{
    QHBoxLayout * layout = new QHBoxLayout;
    m_tree = new LogTreeWidget(100);
    layout->addWidget(m_tree);
    setLayout(layout);
}

LogWidget::~LogWidget()
{
}

void LogWidget::initialize(gui::gui_factory_base * factory)
{
    m_factory = factory;
}

void LogWidget::notifyEvent(corbasim::event::event_ptr ev)
{
    QTreeWidgetItem * item = m_factory->create_tree(ev.get());
    if (item)
        m_tree->appendItem(item);
}

void LogWidget::notifyRequest(corbasim::event::request_ptr ev)
{
    QTreeWidgetItem * item = m_factory->create_tree(ev.get());
    if (item)
        m_tree->appendItem(item);
}

void LogWidget::notifyResponse(corbasim::event::response_ptr ev)
{
    QTreeWidgetItem * item = m_factory->create_tree(ev.get());
    if (item)
        m_tree->appendItem(item);
}

void LogWidget::notifyException(corbasim::event::exception_ptr ev)
{
    QTreeWidgetItem * item = m_factory->create_tree(ev.get());
    if (item)
        m_tree->appendItem(item);
}


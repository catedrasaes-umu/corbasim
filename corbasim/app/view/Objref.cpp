// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Objref.cpp
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

#include "Objref.hpp"

using namespace corbasim::app::view;

Objref::Objref(const QString& id, gui::gui_factory_base* factory,
        QObject * parent) :
    QObject(parent), m_id(id), m_factory(factory)
{
    m_menu = new QMenu(m_id);
    QMenu * operation = m_menu->addMenu("Operations");
    
    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        gui::operation_factory_base * op = 
            factory->get_factory_by_index(i);

        const char * name = op->get_name();

        operation->addAction(name);
    }

    m_menu->addAction("Delete");
}

Objref::~Objref()
{
}

QMenu * Objref::getMenu() const
{
    return m_menu;
}

void Objref::sendRequest(corbasim::event::request_ptr req)
{
    emit sendRequest(m_id, req);
}


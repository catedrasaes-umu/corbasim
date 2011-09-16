// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * tree_factory.hpp
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

#include "tree_factory.hpp"

using namespace corbasim::gui;

tree_factory_base::~tree_factory_base()
{
}

QTreeWidgetItem * tree_factory_interface::create_tree(
        corbasim::event::event* ev)
{
    QTreeWidgetItem * item = NULL;

    switch (ev->get_type())
    {
    case event::REQUEST:
    case event::RESPONSE:
    {
        factories_t::iterator it = 
            m_factories.find(ev->get_tag());

        if (it != m_factories.end())
            item = it->second->create_tree(ev);
        break;
    }
    case event::EXCEPTION:
        item = new QTreeWidgetItem(QStringList("Exception"));
    default:
        break;
    }

    return item;
}



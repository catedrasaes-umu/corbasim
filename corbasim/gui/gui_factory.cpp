// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * gui_factory.hpp
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

#include "gui_factory_fwd.hpp"

using namespace corbasim::gui;

operation_factory_base::~operation_factory_base()
{
}

gui_factory_base::~gui_factory_base()
{
}

void gui_factory_base::insert_factory(const std::string& name,
        tag_t tag, operation_factory_base * factory)
{
    m_factories.push_back(factory);

    // Maps
    m_factories_by_name.insert(std::make_pair(name, factory));
    m_factories_by_tag.insert(std::make_pair(tag, factory));
}

unsigned int gui_factory_base::operation_count() const
{
    return m_factories.size();
}

operation_factory_base * gui_factory_base::get_factory_by_index(
        unsigned int idx) const
{
    return m_factories[idx];
}

operation_factory_base * gui_factory_base::get_factory_by_name(
        const std::string& name) const
{
    factories_by_name_t::const_iterator it;
    it = m_factories_by_name.find(name);

    if (it != m_factories_by_name.end())
        return it->second;

    return NULL;
}

operation_factory_base * gui_factory_base::get_factory_by_tag(
        tag_t tag) const
{
    factories_by_tag_t::const_iterator it;
    it = m_factories_by_tag.find(tag);

    if (it != m_factories_by_tag.end())
        return it->second;

    return NULL;
}

QTreeWidgetItem * gui_factory_base::create_tree(event::event* ev) const
{
    QTreeWidgetItem * item = NULL;

    switch (ev->get_type())
    {
    case event::REQUEST:
    case event::RESPONSE:
    {
        factories_by_tag_t::const_iterator it = 
            m_factories_by_tag.find(ev->get_tag());

        if (it != m_factories_by_tag.end())
            item = it->second->create_tree(ev);

        break;
    }
    case event::EXCEPTION:
        item = new QTreeWidgetItem(QStringList("Exception"));
        break;
    case event::MESSAGE:
        item = new QTreeWidgetItem(QStringList(
                    static_cast< event::message* >(ev)->get_message()));
        break;
    default:
        break;
    }

    return item;
}


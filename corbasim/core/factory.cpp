// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * factory.hpp
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

#include "factory_fwd.hpp"

using namespace corbasim::core;

operation_factory_base::~operation_factory_base()
{
}

factory_base::~factory_base()
{
}

void factory_base::insert_factory(const std::string& name,
        tag_t tag, operation_factory_base * factory)
{
    m_factories.push_back(factory);

    // Maps
    m_factories_by_name.insert(std::make_pair(name, factory));
    m_factories_by_tag.insert(std::make_pair(tag, factory));
}

unsigned int factory_base::operation_count() const
{
    return m_factories.size();
}

operation_factory_base * factory_base::get_factory_by_index(
        unsigned int idx) const
{
    return m_factories[idx];
}

operation_factory_base * factory_base::get_factory_by_name(
        const std::string& name) const
{
    factories_by_name_t::const_iterator it;
    it = m_factories_by_name.find(name);

    if (it != m_factories_by_name.end())
        return it->second;

    return NULL;
}

operation_factory_base * factory_base::get_factory_by_tag(
        tag_t tag) const
{
    factories_by_tag_t::const_iterator it;
    it = m_factories_by_tag.find(tag);

    if (it != m_factories_by_tag.end())
        return it->second;

    return NULL;
}



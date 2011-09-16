// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * request_serializer.cpp
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

#include "request_serializer.hpp"

using namespace corbasim::core;

void request_serializer_impl::save(std::ostream& os, 
        corbasim::event::request * req) const
{
    serializers_t::const_iterator it;
    it = m_serializers.find(req->get_tag());

    if (it != m_serializers.end())
    {
        os << req->get_name() << ' ';
        it->second->save(os, req);
    }
}

corbasim::event::request * request_serializer_impl::load(
        std::istream& is) const
{
    std::string name;
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);

    iss >> name;

    serializers_by_name_t::const_iterator it;
    it = m_serializers_by_name.find(name);

    if (it != m_serializers_by_name.end())
        return it->second->load(iss);

    return NULL;
}



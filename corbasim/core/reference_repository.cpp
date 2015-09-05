// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reference_repository.hpp
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

#include "reference_repository.hpp"
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <corbasim/json/parser.hpp>

using namespace corbasim::core;

reference_repository * reference_repository::get_instance()
{
    static reference_repository _instance;
    return &_instance;
}

void reference_repository::load_file(const std::string& file)
{
    std::size_t length;
    std::vector< char > buffer;

    try {
        std::ifstream is(file.c_str());

        // get length of file:
        is.seekg (0, std::ios::end);
        length = is.tellg();
        is.seekg (0, std::ios::beg);

        // allocate memory:
        buffer.resize(length);

        // read data as a block:
        is.read (&(*buffer.begin()), length);
        is.close();

        corbasim::json::parse(m_loaded_entries, &(*buffer.begin()), length);
    } catch (...) {
    }
}

void reference_repository::update()
{
    entries_t::const_iterator end;
    for (entries_t::const_iterator it = m_entries.begin();
            it != end; ++it)
    {
        CORBA::Object_var obj = update_entry(it->first);
    }
}

CORBA::Object_ptr
reference_repository::get_reference(const std::string& name)
{
    entries_t::const_iterator it = m_entries.find(name);
    if (it != m_entries.end())
        return CORBA::Object::_duplicate(it->second);

    return update_entry(name);
}

reference_repository::reference_repository() :
    m_ns_available(true)
{
    int argc = 0;
    // get the default ORB
    m_orb = CORBA::ORB_init(argc, NULL);
}

CosNaming::NamingContextExt_ptr reference_repository::get_name_service()
{
    if (CORBA::is_nil(m_nc) && m_ns_available)
    {
        try {
            // get the name service reference
            CORBA::Object_var obj =
                m_orb->resolve_initial_references("NameService");

            m_nc = CosNaming::NamingContextExt::_narrow(obj);
        } catch (...)
        {
            m_ns_available = false;
        }
    }

    return m_nc;
}

CORBA::Object_ptr
reference_repository::update_entry(const std::string& name)
{
    if (CORBA::is_nil(get_name_service()))
        return CORBA::Object::_nil();

    loaded_entries_t::const_iterator it =
        m_loaded_entries.find(name);

    if (it != m_loaded_entries.end())
    {
        try {
           CORBA::Object_var obj = m_nc->resolve(it->second);

           m_entries.insert(std::make_pair(name, obj));

            return CORBA::Object::_duplicate(obj);
        } catch (...)
        {
        }
    }

    return CORBA::Object::_nil();
}

CORBA::Object_ptr
reference_repository::resolve(const CosNaming::Name& name)
{
    if (!CORBA::is_nil(get_name_service()))
        return m_nc->resolve(name);

    return CORBA::Object::_nil();
}

CORBA::Object_ptr
reference_repository::resolve_str(const std::string& name)
{
    if (!CORBA::is_nil(get_name_service()))
        return m_nc->resolve_str(name.c_str());

    return CORBA::Object::_nil();
}

CORBA::Object_ptr
reference_repository::string_to_object(const std::string& str)
{
    return m_orb->string_to_object(str.c_str());
}

char * reference_repository::object_to_string(CORBA::Object_ptr obj)
{
    return m_orb->object_to_string(obj);
}


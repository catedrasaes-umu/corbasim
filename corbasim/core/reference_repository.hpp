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

#ifndef CORBASIM_CORE_REFERENCE_REPOSITORY_HPP
#define CORBASIM_CORE_REFERENCE_REPOSITORY_HPP

#include <map>
#include <string>
#include <corbasim/impl.hpp>
#include <corbasim/cosnaming/CosnamingC.h>
#include <corbasim/core/export.hpp>

namespace corbasim 
{
namespace core 
{

class CORBASIM_CORE_DECLSPEC reference_repository
{
public:

    typedef std::map< std::string, CosNaming::Name > loaded_entries_t;
    typedef std::map< std::string, CORBA::Object_var > entries_t;

    static reference_repository * get_instance();

    void load_file(const std::string& file);

    void update();

    CORBA::Object_ptr get_reference(const std::string& name);

    CORBA::Object_ptr resolve(const CosNaming::Name& name);
    CORBA::Object_ptr resolve_str(const std::string& name);
    CORBA::Object_ptr string_to_object(const std::string& str);
    char * object_to_string(CORBA::Object_ptr obj);


protected:

    CosNaming::NamingContextExt_ptr get_name_service();

    reference_repository();

    CORBA::Object_ptr update_entry(const std::string& name);

    loaded_entries_t m_loaded_entries;
    entries_t m_entries;

    CORBA::ORB_var m_orb;
    CosNaming::NamingContextExt_var m_nc;

    bool m_ns_available;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_REFERENCE_REPOSITORY_HPP */


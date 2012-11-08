// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ns_register.hpp
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

#ifndef CORBASIM_CORE_NS_REGISTER_HPP
#define CORBASIM_CORE_NS_REGISTER_HPP

#include <boost/shared_ptr.hpp>

#include <corbasim/impl.hpp>
#include <corbasim/cosnaming/CosnamingC.h>

#include <corbasim/core/export.hpp>

namespace corbasim 
{
namespace core 
{

class CORBASIM_CORE_DECLSPEC ns_register 
{
public :
   
    ns_register(CORBA::ORB_ptr orb, 
            const std::string& key, 
            CORBA::Object_ptr ref, 
            bool release_at_exit = true);

    ns_register(const CosNaming::NamingContextExt_var& ns,
            const std::string& key, 
            CORBA::Object_ptr ref, 
            bool release_at_exit = true);
    
    ~ns_register();
    
    bool error();

protected :

    void do_register(const std::string& key, 
            CORBA::Object_ptr ref);

    bool m_error;
    
    bool m_release;
    
    CosNaming::NamingContextExt_var m_nsObj; 
    
    CosNaming::Name_var m_name; 
};

typedef boost::shared_ptr< ns_register > ns_register_ptr;

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_NS_REGISTER_HPP */


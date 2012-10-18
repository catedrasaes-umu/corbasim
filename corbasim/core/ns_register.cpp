// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ns_register.cpp
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

#include "ns_register.hpp"
#include <iostream>

using namespace corbasim::core;

ns_register::ns_register(CORBA::ORB_ptr orb, 
        const std::string& key, 
        CORBA::Object_ptr ref, 
        bool release_at_exit) : 
    m_error(false), m_release(release_at_exit) 
{
    try {

        CORBA::Object_var obj = 
            orb->resolve_initial_references("NameService");
        m_nsObj = CosNaming::NamingContextExt::_narrow(obj);
        
        do_register(key, ref);
        
    } catch (...) { 
        std::cerr << "Error during registration into Naming Service!" 
            << std::endl;
        m_error = true;
    }
}

ns_register::ns_register(const CosNaming::NamingContextExt_var& ns,
        const std::string& key, 
        CORBA::Object_ptr ref, 
        bool release_at_exit) :
    m_error(false), m_release(release_at_exit), m_nsObj(ns)
{
    do_register(key, ref);
}

void ns_register::do_register(const std::string& key, 
        CORBA::Object_ptr ref)
{
    try {
        if (CORBA::is_nil(m_nsObj))
        {
            std::cerr << "Unable to get Naming Service reference!" 
                << std::endl;
            m_error = true;
            return;
        }
        
        m_name = m_nsObj->to_name(key.c_str());
         
        // Registra los contextos
        for (unsigned int i = 0; i < m_name->length()-1; i++)
        { 
            CosNaming::Name ctx(m_name);
            ctx.length(i + 1);
            
            try {
                CORBA::Object_var ctxObj = m_nsObj->resolve(ctx); 
                CosNaming::NamingContextExt_var ctxVar = 
                    CosNaming::NamingContextExt::_narrow(ctxObj);
                
                // Si no salta la excepcion y no es un contexto
                // no puede registarse nada bajo el
                if (CORBA::is_nil(ctxVar))
                {
                    std::cerr << "Invalid key!" << std::endl;
                    m_error = true;
                    return;
                }
                
            } catch (...) {
                m_nsObj->bind_new_context(ctx);
            }
        }
        
        m_nsObj->rebind(m_name, ref);  
        
    } catch (...) { 
        std::cerr << "Error during registration into Naming Service!" 
            << std::endl;
        m_error = true;
    }
    
    if (!m_error)
    {
        std::cout << "Registred successfully into Naming Service!" 
            << std::endl;
    }
}

ns_register::~ns_register() 
{
    if (!m_error && m_release)
    {
        try {
            
            m_nsObj->unbind(m_name);                         
            
            std::cout << "Unregistred object!" << std::endl;
            
            // Des-registra los contextos
            // Estrategia: el ultimo que cierre
            for (unsigned int i = 0; i < m_name->length()-1; i++)
            { 
                CosNaming::Name ctx(m_name);
                ctx.length(i + 1);
                
                CORBA::Object_var ctxObj = m_nsObj->resolve(ctx);           
                CosNaming::NamingContextExt_var ctxVar = 
                    CosNaming::NamingContextExt::_narrow(ctxObj);
                    
                // Si no salta la excepcion y no es un contexto
                // no puede registarse nada bajo el
                if (CORBA::is_nil(ctxVar))
                {
                    break;
                }
                    
                // Lo destruye si esta vacio
                ctxVar->destroy(); 
                
                m_nsObj->unbind(ctx);
                
                std::cout << "Unregistred context!" << std::endl;
            }
        
        } catch (const CosNaming::NamingContext::NotEmpty& ex) {
        
            // No es un error               
            
        } catch (...) {
        
            std::cerr << "Error during unregistering!" << std::endl;
            
        }
    }
}

bool ns_register::error() 
{
    return m_error;
}


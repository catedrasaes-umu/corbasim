// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * factory_fwd.hpp
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

#ifndef CORBASIM_CORE_FACTORY_FWD_HPP
#define CORBASIM_CORE_FACTORY_FWD_HPP

#include <vector>
#include <string>
#include <map>
#include <corbasim/event.hpp>
#include <corbasim/impl.hpp> // For PortableServer::ServantBase

namespace corbasim 
{
namespace core 
{
class request_serializer_base;
class interface_caller_base;
class request_processor;
class reference_validator_base;

struct operation_factory_base
{
    virtual const char * get_name() const = 0;

    // To json
    virtual void to_json(event::request* req, 
            std::string& str) const = 0;
    virtual void to_json(event::response* req, 
            std::string& str) const = 0;

    // Will be deprecated
    virtual event::request* from_json(const std::string& str) const = 0;
    
    // From json
    virtual event::request* request_from_json(
            const std::string& str) const = 0;
    virtual event::response* response_from_json(
            const std::string& str) const = 0;

    virtual ~operation_factory_base();
};

struct factory_base
{
    unsigned int operation_count() const;
    operation_factory_base * get_factory_by_index(unsigned int idx) const;
    operation_factory_base * get_factory_by_name(
            const std::string& name) const;
    operation_factory_base * get_factory_by_tag(tag_t tag) const;

    virtual core::interface_caller_base* create_caller() const = 0;

    virtual ~factory_base();
    virtual core::request_serializer_base * get_serializer() const = 0;

    void insert_factory(const std::string& name,
            tag_t tag, operation_factory_base * factory);

    virtual const char * get_name() const = 0;
    virtual const char * get_fqn() const = 0;

    virtual reference_validator_base * create_validator() const = 0;

    // Servant
    virtual PortableServer::ServantBase * create_servant(
            request_processor * proc) const = 0;

    // Data
    typedef std::vector< operation_factory_base * > factories_t;
    factories_t m_factories;

    typedef std::map< std::string, operation_factory_base * > 
        factories_by_name_t;
    factories_by_name_t m_factories_by_name;

    typedef std::map< tag_t, operation_factory_base * > 
        factories_by_tag_t;
    factories_by_tag_t m_factories_by_tag;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_FACTORY_FWD_HPP */


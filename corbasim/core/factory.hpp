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

#ifndef CORBASIM_CORE_FACTORY_HPP
#define CORBASIM_CORE_FACTORY_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/mpl.hpp>
#include <corbasim/core/inserter.hpp>
#include <corbasim/core/request_serializer.hpp>
#include <corbasim/core/reference_validator.hpp>
#include <corbasim/core/factory_fwd.hpp>
#include <corbasim/core/caller.hpp>
#include <corbasim/core/callable.hpp>

#include <sstream>
#include <memory>
#include <corbasim/json/writer.hpp>
#include <corbasim/json/parser.hpp>

namespace corbasim 
{
namespace core 
{

template< typename Value >
struct operation_factory : public operation_factory_base
{
    typedef dialogs::input< Value > input_t;
    typedef event::request_impl< Value > request_t;
    typedef event::response_impl< Value > response_t;

    const char * get_name() const
    {
        return adapted::name< Value >::call();
    }
    
    // To JSON
    void to_json(event::request* req, std::string& str) const
    {
        std::ostringstream oss;
        request_t* reqi = static_cast< request_t* >(req);

        json::write(oss, reqi->m_values);
        str = oss.str();
    }

    void to_json(event::response* req, std::string& str) const
    {
        std::ostringstream oss;
        response_t* reqi = static_cast< response_t* >(req);

        json::write(oss, reqi->m_values);
        str = oss.str();
    }

    // Will be deprecated
    event::request* from_json(const std::string& str) const
    {
        std::auto_ptr< request_t > reqi (new request_t);
        json::parse(reqi->m_values, str);
        return reqi.release();
    }

    // From JSON
    event::request* request_from_json(const std::string& str) const
    {
        std::auto_ptr< request_t > reqi (new request_t);
        json::parse(reqi->m_values, str);
        return reqi.release();
    }

    event::response* response_from_json(const std::string& str) const
    {
        std::auto_ptr< response_t > reqi (new response_t);
        json::parse(reqi->m_values, str);
        return reqi.release();
    }

    static inline operation_factory * get_instance()
    {
        static boost::shared_ptr< operation_factory > _instance(
                new operation_factory);
        return _instance.get();
    }
};

template< typename Interface >
struct factory : public factory_base
{
    typedef typename  adapted::interface< Interface >::_op_list 
        operations_t;

    factory()
    {
        typedef core::impl::inserter< factory > inserter_t;
        cs_mpl::for_each< operations_t >(inserter_t(this));
    }

    core::request_serializer_base * get_serializer() const
    {
        return core::request_serializer< Interface >::get_instance();
    }

    core::interface_caller_base* create_caller() const
    {
        return new core::interface_caller< Interface >();
    }

    reference_validator_base * create_validator() const
    {
        return new reference_validator_impl< Interface >();
    }

    // Servant
    PortableServer::ServantBase * create_servant(
            request_processor * proc) const
    {
        return new typename adapted::servant< Interface >::template 
            _type< callable >(callable(proc));
    }
   
    const char * get_name() const
    {
        return adapted::name< Interface >::call();
    }

    const char * get_fqn() const
    {
        return adapted::full_qualified_name< Interface >::call();
    }

    template< typename Value >
    void append()
    {
        typedef operation_factory< Value > factory_t;

        insert_factory(
                adapted::name< Value >::call(),
                tag< Value >::value(),
                factory_t::get_instance());
    }

    static inline factory * get_instance()
    {
        static boost::shared_ptr< factory > _instance(new factory);
        return _instance.get();
    }
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_FACTORY_HPP */


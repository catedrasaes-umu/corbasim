// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * caller.hpp
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

#ifndef CORBASIM_CORE_CALLER_HPP
#define CORBASIM_CORE_CALLER_HPP

#include <map>
#include <corbasim/adapted.hpp>
#include <corbasim/event.hpp>
#include <corbasim/impl.hpp>
#include <corbasim/core/inserter.hpp>

namespace corbasim 
{
namespace core 
{

template < typename Value >
struct oneway_caller
{
    typedef event::request_impl< Value > request_t;
    typedef adapted::call< Value > caller_t;

    template < typename Interface >
    static inline event::event* invoke(Interface * ref, 
            event::request * req)
    {
        request_t * reqi = static_cast< request_t * >(req);
        caller_t::invoke(ref, reqi->m_values);
        return NULL;
    }
};

template < typename Value >
struct default_caller
{
    typedef event::request_impl< Value > request_t;
    typedef event::response_impl< Value > response_t;
    typedef adapted::call< Value > caller_t;

    template < typename Interface >
    static inline event::event* invoke(Interface * ref, 
            event::request * req)
    {
        request_t * reqi = static_cast< request_t * >(req);
        response_t * resp = new response_t(reqi->m_values);

        caller_t::invoke(ref, resp->m_values);
        return resp;
    }
};

template< typename Value >
struct do_call : public cs_mpl::eval_if< adapted::is_oneway< Value >,
                        boost::mpl::identity< oneway_caller< Value > >,
                 // else
                        boost::mpl::identity< default_caller< Value > >
                >::type
{
};

template< typename Interface >
struct operation_caller_base
{
    virtual event::event* call(Interface *, event::request*) const = 0;

    virtual ~operation_caller_base() {}
};

template< typename Interface, typename Value >
struct operation_caller_impl : public operation_caller_base< Interface >
{
    event::event* call(Interface * _this, event::request* req) const
    {
        return do_call< Value >::invoke(_this, req);
    }
    
    static inline operation_caller_impl * get_instance()
    {
        typedef boost::shared_ptr< operation_caller_impl > ptr_t;
        static ptr_t ptr_(new operation_caller_impl);
        return ptr_.get();
    }
};

struct interface_caller_base
{
    virtual event::event * do_call(event::request * req) const = 0;
    virtual void set_reference(CORBA::Object_ptr ref) = 0;
    virtual bool is_nil() const = 0;

    virtual ~interface_caller_base();
};

typedef boost::shared_ptr< interface_caller_base > interface_caller_ptr;

template< typename Interface >
struct interface_caller : public interface_caller_base
{
    interface_caller(Interface * ref)
        : m_ref(Interface::_duplicate(ref))
    {
        cs_mpl::for_each< operations_t >(inserter_t(this));
    }

    interface_caller()
    {
        cs_mpl::for_each< operations_t >(inserter_t(this));
    }

    ~interface_caller()
    {
        CORBA::release(m_ref);
    }

    void set_reference(CORBA::Object_ptr ref)
    {
        CORBA::release(m_ref);
        m_ref = Interface::_narrow(ref);
    }

    template < typename Value >
    void append()
    {
        typedef operation_caller_impl< Interface, Value > caller_t;
        m_callers.insert(std::make_pair(tag< Value >::value(),
                caller_t::get_instance()));
    }

    typedef impl::inserter< interface_caller > inserter_t;
    typedef operation_caller_base< Interface > caller_base_t;
    typedef adapted::interface< Interface > adapted_t;
    typedef typename adapted_t::_op_list operations_t;
    typedef std::map< tag_t, caller_base_t* > callers_t;

    event::event * do_call(event::request * req) const
    {
        if (!m_ref)
            return NULL;

        typename callers_t::const_iterator it;
        
        it = m_callers.find(req->get_tag());

        if (it != m_callers.end())
        {
            try {
                return it->second->call(m_ref, req);
            } catch (...)
            {
                // TODO
                return new event::exception; 
            }
        }

        return NULL;
    }
    
    bool is_nil() const
    {
        return CORBA::is_nil(m_ref);
    }

    Interface * m_ref;
    callers_t m_callers;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_CALLER_HPP */


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
#include <corbasim/core/inserter.hpp>
#include <corbasim/core/caller_fwd.hpp>

namespace corbasim
{
namespace core
{

template < typename Value >
struct oneway_caller
{
    template < typename Interface >
        static inline event::event* invoke(typename Interface::_ptr_type ref,
            event::request * req)
    {
        typedef event::request_impl< Value > request_t;
        typedef adapted::call< Value > caller_t;

        request_t * reqi = static_cast< request_t * >(req);
        caller_t::invoke(ref, reqi->m_values);
        return NULL;
    }
};

template < typename Value >
struct default_caller
{
    template < typename Interface >
    static inline event::event* invoke(typename Interface::_ptr_type ref,
            event::request * req)
    {
        typedef event::request_impl< Value > request_t;
        typedef event::response_impl< Value > response_t;
        typedef adapted::call< Value > caller_t;

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
    virtual event::event* call(typename Interface::_ptr_type, event::request*) const = 0;

    virtual ~operation_caller_base() {}
};

template< typename Interface, typename Value >
struct operation_caller_impl : public operation_caller_base< Interface >
{
    event::event* call(typename Interface::_ptr_type _this, event::request* req) const
    {
        return do_call< Value >::template invoke< Interface >(_this, req);
    }

    static inline operation_caller_impl * get_instance()
    {
        static operation_caller_impl _instance;
        return &_instance;
    }
};

template< typename Interface >
struct interface_caller : public interface_caller_base
{
    interface_caller(typename Interface::_ptr_type ref)
        : m_ref(Interface::_duplicate(ref))
    {
        _init();
    }

    interface_caller()
        : m_ref(Interface::_nil())
    {
        _init();
    }

    ~interface_caller()
    {
        CORBA::release(m_ref);
    }

    void set_reference(CORBA::Object_ptr ref)
    {
        CORBA::release(m_ref);
        try
        {
            m_ref = Interface::_narrow(ref);
        }
        catch (...)
        {
            m_ref = Interface::_nil();
        }
    }

    CORBA::Object_ptr get_reference()
    {
        return CORBA::Object::_duplicate(m_ref);
    }

    template < typename Value >
    inline void append()
    {
        typedef operation_caller_impl< Interface, Value > caller_t;
        m_callers.insert(std::make_pair(tag< Value >::value(),
                caller_t::get_instance()));
    }

    typedef impl::inserter< interface_caller > inserter_t;
    typedef operation_caller_base< Interface > caller_base_t;
    typedef std::map< tag_t, caller_base_t* > callers_t;

    event::event * do_call(event::request * req) const
    {
        event::event * ev = NULL;

        try
        {
            ev = do_call_throw(req);
        }
        catch (const CORBA::Exception& ex)
        {
            ev = new event::exception(ex._name());
        }
        catch (...)
        {
            ev = new event::exception();
        }

        return ev;
    }

    event::event * do_call_throw(event::request * req) const
    {
        if (m_ref)
        {
            typename callers_t::const_iterator it =
                m_callers.find(req->get_tag());

            if (it != m_callers.end())
            {
                return it->second->call(m_ref, req);
            }
        }

        return NULL;
    }

    bool is_nil() const
    {
        return CORBA::is_nil(m_ref);
    }

    typename Interface::_ptr_type m_ref;
    callers_t m_callers;

private:

    void _init()
    {
        typedef adapted::interface< Interface > adapted_t;
        typedef typename adapted_t::_op_list operations_t;
        cs_mpl::for_each_list< operations_t >(inserter_t(this));
    }
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_CALLER_HPP */


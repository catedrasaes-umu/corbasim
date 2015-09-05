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
#include <corbasim/core/event.hpp>
#include <corbasim/core/inserter.hpp>
#include <corbasim/core/caller_fwd.hpp>
#include <boost/make_shared.hpp>

namespace corbasim
{
namespace core
{

template< typename Value >
struct do_call
{
    template < typename Interface >
    static inline event_ptr invoke(typename Interface::_ptr_type ref,
            request * req)
    {
        typedef request_impl< Value > request_t;
        typedef response_impl< Value > response_t;
        typedef adapted::call< Value > caller_t;

        request_t * reqi = static_cast< request_t * >(req);
        Value * values = &reqi->m_values;

        event_ptr res;

        if (!adapted::is_oneway< Value >::value)
        {
            boost::shared_ptr<response_t> resp =
                    boost::make_shared<response_t>(reqi->m_values);
            values = &resp->m_values;
            res = resp;
        }

        caller_t::invoke(ref, *values);
        return res;
    }
};

template< typename Interface >
struct operation_caller_base
{
    virtual event_ptr call(typename Interface::_ptr_type, request*) const = 0;

    virtual ~operation_caller_base() {}
};

template< typename Interface, typename Value >
struct operation_caller_impl : public operation_caller_base< Interface >
{
    event_ptr call(typename Interface::_ptr_type _this, request* req) const
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
    }

    interface_caller()
        : m_ref(Interface::_nil())
    {
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

    typedef operation_caller_base< Interface > caller_base_t;

    event_ptr do_call(request * req) const
    {
        event_ptr ev;

        try
        {
            ev = do_call_throw(req);
        }
        catch (const CORBA::Exception& ex)
        {
            ev = boost::make_shared<exception>(ex._name());
        }
        catch (...)
        {
            ev = boost::make_shared<exception>();
        }

        return ev;
    }

    event_ptr do_call_throw(request * req) const
    {
        event_ptr ev;

        if (m_ref)
        {
            const caller_base_t * caller =
                callers::get_instance()->get_caller(req->get_tag());

            if (caller)
            {
                ev = caller->call(m_ref, req);
            }
        }

        return ev;
    }

    bool is_nil() const
    {
        return CORBA::is_nil(m_ref);
    }

    typename Interface::_ptr_type m_ref;

    struct callers
    {
        static const callers * get_instance()
        {
            static callers _instance;
            return &_instance;
        }

        caller_base_t * get_caller(tag_t tag) const
        {
            typename callers_t::const_iterator it =
                m_callers.find(tag);

            return it != m_callers.end()? it->second : NULL;
        }

    protected:

        callers()
        {
            _init();
        }

        template < typename Value >
        inline void append()
        {
            typedef operation_caller_impl< Interface, Value > caller_t;
            m_callers.insert(std::make_pair(tag< Value >::value(),
                    caller_t::get_instance()));
        }

        typedef impl::inserter<callers> inserter_t;
        friend class impl::inserter<callers>;
        typedef std::map< tag_t, caller_base_t* > callers_t;

        callers_t m_callers;

        void _init()
        {
            typedef adapted::interface< Interface > adapted_t;
            typedef typename adapted_t::_op_list operations_t;
            cs_mpl::for_each_list< operations_t >(inserter_t(this));
        }
    };

};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_CALLER_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * callable.hpp
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

#ifndef CORBASIM_CORE_CALLABLE_HPP
#define CORBASIM_CORE_CALLABLE_HPP

#include <corbasim/adapted.hpp>
#include <corbasim/event.hpp>

namespace corbasim 
{
namespace core 
{

struct request_processor
{
    virtual event::event_ptr operator()(event::request_ptr,
            event::response_ptr) = 0;
    virtual ~request_processor() {}
};

struct callable
{
    callable(request_processor * proc) :
        m_proc (proc)
    {
    }

    template< typename Value >
    void operator()(Value& val)
    {
        using namespace ::corbasim::event;

        typedef request_impl< Value > request_t;
        typedef response_impl< Value > response_t;

        request_ptr _req (new request_t(val));

        // Proposed response
        response_ptr _resp (new response_t(val));

        // Call to the request processor
        event_ptr _ev ((*m_proc)(_req, _resp));

        if (_ev && _ev->get_type () == RESPONSE)
        {
            response_t * _resp = static_cast< response_t * > (_ev.get());

            val = _resp->m_values;
        }
    }

    request_processor * m_proc;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_CALLABLE_HPP */


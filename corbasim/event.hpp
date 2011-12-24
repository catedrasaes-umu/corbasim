// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * event.hpp
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

#ifndef CORBASIM_EVENT_HPP
#define CORBASIM_EVENT_HPP

#include <corbasim/event_fwd.hpp>
#include <corbasim/adapted.hpp>

namespace corbasim 
{
namespace event 
{

template< typename Value >
struct request_impl : public request
{
    Value m_values;

    request_impl()
    {
    }

    request_impl(const Value& val) :
        m_values(val)
    {
    }

    tag_t get_tag() const
    {
        return tag< Value >::value();
    }
    
    const char * get_name() const
    {
        return adapted::name< Value >::call();
    }
};

template< typename Value >
struct response_impl : public response
{
    Value m_values;

    response_impl()
    {
    }

    response_impl(const Value& values) :
        m_values(values)
    {
    }
    
    tag_t get_tag() const
    {
        return tag< Value >::value();
    }
};

} // namespace event
} // namespace corbasim

#endif /* CORBASIM_EVENT_HPP */


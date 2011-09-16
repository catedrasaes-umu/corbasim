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

#include <boost/shared_ptr.hpp>
#include <corbasim/mpl.hpp>
#include <corbasim/adapted.hpp>

namespace corbasim 
{
namespace event 
{

enum event_types { EXCEPTION, REQUEST, RESPONSE};

struct event
{
    // virtual void serialize(std::ostream& out) const = 0;
    virtual event_types get_type() const = 0;
    virtual tag_t get_tag() const = 0;

    virtual ~event() {}
};

typedef boost::shared_ptr< event > event_ptr;

struct exception : public event
{
    event_types get_type() const 
    {
        return EXCEPTION;
    }

    tag_t get_tag() const
    {
        return tag< exception >::value();
    }
};

struct request : public event
{
    event_types get_type() const 
    {
        return REQUEST;
    }
    
    virtual ~request() {}

    virtual const char * get_name() const = 0; 
};

typedef boost::shared_ptr< request > request_ptr;

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

struct response : public event
{
    event_types get_type() const 
    {
        return RESPONSE;
    }

    virtual ~response() {}
};

typedef boost::shared_ptr< response > response_ptr;

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


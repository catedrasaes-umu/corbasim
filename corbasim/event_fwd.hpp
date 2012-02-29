// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * event_fwd.hpp
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

#ifndef CORBASIM_EVENT_FWD_HPP
#define CORBASIM_EVENT_FWD_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include <corbasim/adapted.hpp>
#include <corbasim/core/export.hpp>

namespace corbasim 
{
namespace event 
{

enum event_types { EXCEPTION, REQUEST, RESPONSE, MESSAGE};

struct CORBASIM_CORE_DECLSPEC event
{
    // virtual void serialize(std::ostream& out) const = 0;
    virtual event_types get_type() const = 0;
    virtual tag_t get_tag() const = 0;

    virtual ~event();
};

typedef boost::shared_ptr< event > event_ptr;

struct CORBASIM_CORE_DECLSPEC exception : public event
{
    event_types get_type() const;

    tag_t get_tag() const;
};

typedef boost::shared_ptr< exception > exception_ptr;

struct CORBASIM_CORE_DECLSPEC message : public event
{
    message(const char * msg);

    event_types get_type() const;

    tag_t get_tag() const;

    const char * get_message() const;

    const std::string m_msg;
};

typedef boost::shared_ptr< message > message_ptr;

struct CORBASIM_CORE_DECLSPEC request : public event
{
    event_types get_type() const;
    
    virtual ~request();

    virtual const char * get_name() const = 0; 
};

typedef boost::shared_ptr< request > request_ptr;

struct CORBASIM_CORE_DECLSPEC response : public event
{
    event_types get_type() const;

    virtual ~response();
};

typedef boost::shared_ptr< response > response_ptr;


} // namespace event
} // namespace corbasim

#endif /* CORBASIM_EVENT_FWD_HPP */


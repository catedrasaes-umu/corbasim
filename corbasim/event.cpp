// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * event.cpp
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

#include "event.hpp"

using namespace corbasim::event;

event::~event() {}

// Exception
exception::exception(const char * msg) :
    m_msg(msg)
{
}

event_types exception::get_type() const 
{
    return EXCEPTION;
}

corbasim::tag_t exception::get_tag() const
{
    return tag< exception >::value();
}

const char * exception::get_message() const
{
    return m_msg.c_str();
}

// Message

message::message(const char * msg) :
    m_msg(msg)
{
}

event_types message::get_type() const 
{
    return MESSAGE;
}

corbasim::tag_t message::get_tag() const
{
    return tag< message >::value();
}

const char * message::get_message() const
{
    return m_msg.c_str();
}

// Request

event_types request::get_type() const 
{
    return REQUEST;
}

request::~request() {}

// Response

event_types response::get_type() const 
{
    return RESPONSE;
}

response::~response() {}


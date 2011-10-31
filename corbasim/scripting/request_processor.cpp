// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * request_processor.cpp
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

#include "request_processor.hpp"
#include <boost/bind.hpp>

using namespace corbasim;
using namespace corbasim::scripting;

request_processor::request_processor(interpreter_ptr interpreter_,
        core::factory_base * factory_) :
    m_interpreter(interpreter_), m_factory(factory_)
{
}

request_processor::~request_processor()
{
}

void request_processor::process_message(event::request_ptr req)
{
    tag_t tag = req->get_tag();

    config_t::const_iterator it = m_config.find(tag);

    if (it != m_config.end() && it->second->active)
    {
        context_ptr ctx = m_interpreter->new_context();

        m_interpreter->request_to_context(ctx, m_factory, "input", req);

        m_interpreter->exec_code(ctx, it->second->code);
    }
}

void request_processor::configure(configuration_ptr config)
{
    m_config[config->request_type] = config;
}


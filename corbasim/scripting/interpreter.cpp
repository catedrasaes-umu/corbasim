// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * interpreter.cpp
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

#include "interpreter.hpp"
#include <boost/bind.hpp>

namespace  
{

corbasim::scripting::interpreter_ptr& corbasim_impl_default_interpreter()
{
    static corbasim::scripting::interpreter_ptr _instance;
    return _instance;
}

} // namespace

namespace corbasim 
{
namespace scripting 
{

void set_default_interpreter(interpreter * interpreter_)
{

    interpreter_ptr i_(interpreter_);
    set_default_interpreter(i_);
}

void set_default_interpreter(interpreter_ptr interpreter_)
{
    interpreter_ptr worker_(new interpreter_worker(interpreter_));
    corbasim_impl_default_interpreter() = worker_;
}

interpreter_ptr get_default_interpreter()
{
    return corbasim_impl_default_interpreter();
}

} // namespace scripting
} // namespace corbasim

using namespace corbasim;
using namespace corbasim::scripting;

interpreter_worker::interpreter_worker(interpreter_ptr interpreter_) :
    m_interpreter(interpreter_), m_work(m_io_service)
{
    m_threads.create_thread(boost::bind(&boost::asio::io_service::run,
                &m_io_service));

    m_interpreter->request_signal.connect(boost::bind(
                &interpreter_worker::forward_request, this, _1));
    m_interpreter->output_signal.connect(boost::bind(
                &interpreter_worker::forward_output, this, _1));
}

interpreter_worker::~interpreter_worker()
{
    m_io_service.stop();
    m_threads.join_all();
}

context_ptr interpreter_worker::main_context()
{
    return m_interpreter->main_context();
}

context_ptr interpreter_worker::new_context()
{
    return m_interpreter->new_context();
}

void interpreter_worker::register_factory(core::factory_base * factory)
{
    m_io_service.post(boost::bind(&interpreter_worker::do_register_factory,
                this, factory));
}

void interpreter_worker::exec_code(context_ptr ctx, 
        const std::string& code)
{
    string_ptr code_(new std::string(code));

    m_io_service.post(boost::bind(&interpreter_worker::do_exec_code,
                this, ctx, code_));
}

void interpreter_worker::request_to_context(context_ptr ctx, 
        core::factory_base * factory,
        const char * name,
        event::request_ptr req)
{
    m_io_service.post(boost::bind(
                &interpreter_worker::do_request_to_context,
                this, ctx, factory, name, req));
}

void interpreter_worker::do_register_factory(core::factory_base * factory)
{
    m_interpreter->register_factory(factory);
}

void interpreter_worker::do_exec_code(context_ptr ctx, 
        string_ptr code)
{
    m_interpreter->exec_code(ctx, *code.get());
}

void interpreter_worker::do_request_to_context(context_ptr ctx, 
        core::factory_base * factory,
        const char * name,
        event::request_ptr req)
{
    m_interpreter->request_to_context(ctx, factory, name, req);
}

void interpreter_worker::forward_request(event::request_ptr req)
{
    request_signal(req);
}

void interpreter_worker::forward_output(const std::string& out)
{
    output_signal(out);
}


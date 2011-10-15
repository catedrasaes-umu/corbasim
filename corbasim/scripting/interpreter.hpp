// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * interpreter.hpp
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

#ifndef CORBASIM_SCRIPTING_INTERPRETER_HPP
#define CORBASIM_SCRIPTING_INTERPRETER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <string>

#include <corbasim/event.hpp>
#include <corbasim/core/factory_fwd.hpp>

namespace corbasim 
{
namespace scripting 
{

/**
 * @brief Abstract class for scripting interpreter contexts. 
 */
struct context {};

typedef boost::shared_ptr< context > context_ptr;

/**
 * @brief Abstract class for scripting interpreters.
 */
class interpreter
{
public:

    virtual void register_factory(core::factory_base * factory) = 0;

    /**
     * @brief Returns the main context of the interpreter.
     *
     * @return A context.
     */
    virtual context_ptr main_context() = 0;
    
    /**
     * @brief Creates a new context.
     *
     * @return A context.
     */
    virtual context_ptr new_context() = 0;

    /**
     * @brief Runs some code into a context.
     *
     * @param ctx A Context.
     * @param code The code.
     */
    virtual void exec_code(context_ptr ctx, 
            const std::string& code) = 0;

    /**
     * @brief Insert a request into a context as a symbol.
     *
     * @param ctx A context.
     * @param factory Factory associated to the request type.
     * @param name A name for the symbol.
     * @param req A request.
     */
    virtual void request_to_context(context_ptr ctx, 
            core::factory_base * factory,
            const char * name,
            event::request_ptr req) = 0;

    virtual ~interpreter() {}

    // Signals
    typedef boost::signals2::signal< void (event::request_ptr) > 
        request_signal_t;

    typedef boost::signals2::signal< void (const std::string&) > 
        output_signal_t;

    request_signal_t request_signal;

    output_signal_t output_signal;

};

typedef boost::shared_ptr< interpreter > interpreter_ptr;

void set_default_interpreter(interpreter * interpreter_);
void set_default_interpreter(interpreter_ptr interpreter_);
interpreter_ptr get_default_interpreter();

} // namespace scripting
} // namespace corbasim

#endif /* CORBASIM_SCRIPTING_INTERPRETER_HPP */


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

#ifndef CORBASIM_LUA_INTERPRETER_HPP
#define CORBASIM_LUA_INTERPRETER_HPP

#include <corbasim/scripting/interpreter.hpp>

namespace corbasim 
{
namespace lua 
{

class context;

class interpreter : public scripting::interpreter
{
public:

    interpreter();

    ~interpreter();
    
    scripting::context_ptr main_context();
    
    scripting::context_ptr new_context();

    void register_factory(core::factory_base * factory);

    void request_to_context(scripting::context_ptr ctx, 
            core::factory_base * factory,
            const char * name,
            event::request_ptr req);

    void exec_code(scripting::context_ptr ctx, 
            const std::string& code);

protected:

    scripting::context_ptr m_main_context;

};

} // namespace lua
} // namespace corbasim

#endif /* CORBASIM_LUA_INTERPRETER_HPP */


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
#include <sstream>
#include <iostream>
#include "lua.hpp"
#include <luabind/luabind.hpp>

using namespace corbasim::lua;

namespace corbasim 
{
namespace lua 
{

struct context : public corbasim::scripting::context
{
    lua_State* m_state;
};

} // namespace lua
} // namespace corbasim

interpreter::interpreter()
{
    context * ctx = new context;
    m_main_context.reset(ctx);

    ctx->m_state = lua_open();
    luaL_openlibs(ctx->m_state);
    luabind::open(ctx->m_state);
}

interpreter::~interpreter()
{
    context * ctx_ = static_cast< context* >(m_main_context.get());
    lua_close(ctx_->m_state);
}

void interpreter::register_factory(core::factory_base * factory)
{
    context * ctx_ = static_cast< context* >(m_main_context.get());

    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        core::operation_factory_base * op = 
            factory->get_factory_by_index(i);

        const char * name = op->get_name();

        // TODO
    }
}

void interpreter::request_to_context(scripting::context_ptr ctx, 
        core::factory_base * factory,
        const char * name,
        event::request_ptr req)
{
    context * ctx_ = static_cast< context* >(ctx.get());
    tag_t tag = req->get_tag();

    // TODO
}

corbasim::scripting::context_ptr interpreter::main_context()
{
    return m_main_context;
}

corbasim::scripting::context_ptr interpreter::new_context()
{
    // TODO
    return m_main_context;
}

void interpreter::exec_code(scripting::context_ptr ctx, 
        const std::string& code)
{
    context * ctx_ = static_cast< context* >(ctx.get());

    int res = luaL_dostring(ctx_->m_state, code.c_str());

    // TODO
}


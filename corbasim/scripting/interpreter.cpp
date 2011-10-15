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
    corbasim_impl_default_interpreter().reset(interpreter_);
}

void set_default_interpreter(interpreter_ptr interpreter_)
{
    corbasim_impl_default_interpreter() = interpreter_;
}

interpreter_ptr get_default_interpreter()
{
    return corbasim_impl_default_interpreter();
}

} // namespace scripting
} // namespace corbasim

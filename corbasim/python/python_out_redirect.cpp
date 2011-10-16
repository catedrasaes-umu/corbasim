// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * python_out_redirect.cpp
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

#include "python_out_redirect.hpp"
#include <corbasim/python/interpreter.hpp>

using namespace corbasim::python;

python_out_redirect::python_out_redirect() :
    m_interpreter(NULL)
{
}

python_out_redirect::python_out_redirect(interpreter* interpreter_) :
    m_interpreter(interpreter_)
{
}

python_out_redirect::~python_out_redirect()
{
}

void python_out_redirect::write(std::string const& str)
{
    if (m_interpreter)
        m_interpreter->output_signal(str);
}


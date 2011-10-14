// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * python_out_redirect.hpp
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

#ifndef CORBASIM_PYTHON_PYTHON_OUT_REDIRECT_HPP
#define CORBASIM_PYTHON_PYTHON_OUT_REDIRECT_HPP

#include <boost/signal2.hpp>

namespace corbasim 
{
namespace python 
{

class python_out_redirect 
{
public:
    python_out_redirect ();
    virtual ~python_out_redirect ();

protected:
};

} // namespace python
} // namespace corbasim

#endif /* CORBASIM_PYTHON_PYTHON_OUT_REDIRECT_HPP */


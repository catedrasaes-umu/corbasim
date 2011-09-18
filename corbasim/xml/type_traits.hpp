// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * type_traits.hpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
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

#ifndef CORBASIM_XML_TYPE_TRAITS_HPP
#define CORBASIM_XML_TYPE_TRAITS_HPP

#include <string>
#include <sstream>

namespace corbasim
{
namespace type_traits
{

#ifdef CORBASIM_USE_WSTRING
  typedef std::wstring string_t;
  typedef wchar_t      char_t;
  typedef std::wstringstream stringstream_t;
#define E_COUT std::cout
#else // CORBASIM_USE_STRING (default)
  typedef std::string  string_t;
  typedef char         char_t;
  typedef std::stringstream stringstream_t;
#define E_COUT std::cout
#endif

} // namespace type_traits
} // namespace corbasim

#endif // CORBASIM_XML_TYPE_TRAITS_HPP

// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parse.hpp
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

#ifndef CORBASIM_XML_PARSE_HPP
#define CORBASIM_XML_PARSE_HPP

#include <corbasim/xml/handler.hpp>
#include <corbasim/xml/parser.hpp>

namespace corbasim 
{
namespace xml 
{

template< typename T >
inline bool parse(T& t, const char * str, size_t size)
{
    json::helper::helper_base * initial_helper = 
        json::helper::create_helper(t);
    handler _h(initial_helper);

    typedef xml_parser::SemanticState< handler > SemanticState;
    SemanticState _ss(_h);

    parser::State< SemanticState > _st(_ss, str, size);

    return xml_parser::grammar::the_xml::match(_st);
}

template< typename T >
inline bool parse(T& t, const std::string& str)
{
    return parse(t, str.c_str(), str.length());
}

} // namespace xml
} // namespace corbasim

#endif /* CORBASIM_XML_PARSE_HPP */


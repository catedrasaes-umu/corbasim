// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * writer.hpp
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

#ifndef CORBASIM_JSON_WRITER_HPP
#define CORBASIM_JSON_WRITER_HPP

#include <corbasim/json/helper.hpp>
#include <corbasim/json/detail/json_writer.hpp>
#include <ostream>

namespace corbasim 
{
namespace json 
{

template< typename Ostream, typename T >
inline void write(Ostream& os, const T& t, bool indent = false);

template< typename Ostream, typename T >
inline void write(Ostream& os, const T& t, bool indent)
{
    typedef csu::corbasim::json::writer::json_writer< Ostream > writer_t;
    writer_t w(os);
    helper::helper_write(w, t);
}

typedef csu::corbasim::json::writer::json_writer< std::ostream > ostream_writer_t;

} // namespace json
} // namespace corbasim

#endif /* CORBASIM_JSON_WRITER_HPP */


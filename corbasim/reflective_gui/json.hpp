// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * json.hpp
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

#ifndef CORBASIM_REFLECTIVE_GUI_JSON_HPP
#define CORBASIM_REFLECTIVE_GUI_JSON_HPP

#include <QVariant>
#include <ostream>
#include <corbasim/json/writer.hpp>
#include <corbasim/json/parser.hpp>

namespace corbasim 
{
namespace reflective_gui 
{

void toJson(json::ostream_writer_t& os, const QVariant& var);
bool fromJson(QVariant& var, const char * str, size_t size);
bool fromJsonFile(const char * file, QVariant& var);

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_JSON_HPP */


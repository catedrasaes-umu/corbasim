// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * primitive.cpp
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

#include "primitive.ipp"

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

// Explicit instantiation
template class primitive_as_spinbox< CORBA::Boolean >;
template class primitive_as_spinbox< CORBA::Short >;
template class primitive_as_spinbox< CORBA::UShort >;
template class primitive_as_spinbox< CORBA::Char >;
template class primitive_as_spinbox< CORBA::Octet >;
template class primitive_as_spinbox< CORBA::Long >;
template class primitive_as_spinbox< CORBA::ULong >;
template class primitive_as_spinbox< CORBA::LongLong >;
template class primitive_as_spinbox< CORBA::ULongLong >;
template class primitive_as_spinbox< CORBA::Float >;
template class primitive_as_spinbox< CORBA::Double >;
// TODO template class primitive_as_spinbox< CORBA::LongDouble >;

template class bool_as_checkbox< CORBA::Boolean >;
template class bool_as_checkbox< CORBA::Short >;
template class bool_as_checkbox< CORBA::UShort >;
template class bool_as_checkbox< CORBA::Char >;
template class bool_as_checkbox< CORBA::Octet >;
template class bool_as_checkbox< CORBA::Long >;
template class bool_as_checkbox< CORBA::ULong >;
template class bool_as_checkbox< CORBA::LongLong >;
template class bool_as_checkbox< CORBA::ULongLong >;
template class bool_as_checkbox< CORBA::Float >;
template class bool_as_checkbox< CORBA::Double >;
// TODO template class bool_as_checkbox< CORBA::LongDouble >;

template class spinbox_with_autoincrement< CORBA::Short >;
template class spinbox_with_autoincrement< CORBA::UShort >;
template class spinbox_with_autoincrement< CORBA::Char >;
template class spinbox_with_autoincrement< CORBA::Octet >;
template class spinbox_with_autoincrement< CORBA::Long >;
template class spinbox_with_autoincrement< CORBA::ULong >;
template class spinbox_with_autoincrement< CORBA::LongLong >;
template class spinbox_with_autoincrement< CORBA::ULongLong >;
template class spinbox_with_autoincrement< CORBA::Float >;
template class spinbox_with_autoincrement< CORBA::Double >;
// TODO template class spinbox_with_autoincrement< CORBA::LongDouble >;

} // namespace detail
} // namespace widgets
} // namespace corbasim


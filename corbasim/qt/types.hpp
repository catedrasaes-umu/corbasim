// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * types.hpp
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

#ifndef CORBASIM_QT_TYPES_HPP
#define CORBASIM_QT_TYPES_HPP

#include <QMetaType>
#include <corbasim/impl.hpp>
#include <corbasim/core/event_fwd.hpp>

Q_DECLARE_METATYPE(CORBA::Object_var);
Q_DECLARE_METATYPE(corbasim::core::event_ptr)
Q_DECLARE_METATYPE(corbasim::core::request_ptr)

#endif /* CORBASIM_QT_TYPES_HPP */


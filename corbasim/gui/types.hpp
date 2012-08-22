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

#ifndef CORBASIM_GUI_TYPES_HPP
#define CORBASIM_GUI_TYPES_HPP

#include <QtCore>
#include <boost/shared_ptr.hpp>
#include <corbasim/impl.hpp>
#include <corbasim/event_fwd.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/core/caller_fwd.hpp>
#include <corbasim/qt/types.hpp>
#include <corbasim/gui/export.hpp>

namespace corbasim 
{
namespace gui
{

CORBASIM_GUI_DECLSPEC void initialize();

typedef ::corbasim::core::interface_reflective_base const * 
    InterfaceDescriptor_ptr;
typedef ::corbasim::core::operation_reflective_base const * 
    OperationDescriptor_ptr;
typedef ::corbasim::core::reflective_base const * 
    TypeDescriptor_ptr;

typedef const void * ObjectId;

typedef ::corbasim::event::event_ptr Event_ptr;
typedef ::corbasim::event::request_ptr Request_ptr;
typedef ::corbasim::core::holder Holder;

typedef ::corbasim::core::interface_caller_ptr Caller_ptr;

class Objref;
typedef boost::shared_ptr< Objref > Objref_ptr;

class Servant;
typedef boost::shared_ptr< Servant > Servant_ptr;

class ObjrefRepository;


struct ObjrefConfig
{
    std::string name;
    std::string fqn;
    std::string entry;
    CORBA::Object_var reference;
};

typedef ObjrefConfig ServantConfig;

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_TYPES_HPP */


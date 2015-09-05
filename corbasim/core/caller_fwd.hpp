// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * caller.hpp
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

#ifndef CORBASIM_CORE_CALLER_FWD_HPP
#define CORBASIM_CORE_CALLER_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/impl.hpp>
#include <corbasim/core/event_fwd.hpp>
#include <corbasim/core/export.hpp>

namespace corbasim
{
namespace core
{

struct CORBASIM_CORE_DECLSPEC reference_validator_base
{
    virtual void set_reference(CORBA::Object_ptr ref) = 0;
    virtual bool is_nil() const = 0;
    virtual CORBA::Object_ptr get_reference() = 0;
    virtual ~reference_validator_base();
};

typedef boost::shared_ptr< reference_validator_base >
    reference_validator_ptr;

struct CORBASIM_CORE_DECLSPEC interface_caller_base :
    public reference_validator_base
{
    virtual event_ptr do_call(request * req) const = 0;
    virtual event_ptr do_call_throw(request * req) const = 0;

    virtual ~interface_caller_base();
};

typedef boost::shared_ptr< interface_caller_base > interface_caller_ptr;

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_CALLER_FWD_HPP */


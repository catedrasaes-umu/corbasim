// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Objref.hpp
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

#ifndef CORBASIM_APP_MODEL_OBJREF_HPP
#define CORBASIM_APP_MODEL_OBJREF_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/core/caller.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/qt/types.hpp>
#include "../app_adapted.hpp"

namespace corbasim 
{
namespace app 
{
namespace model 
{

class Objref
{
public:
    Objref(const ObjrefConfig& cfg, 
            const core::interface_reflective_base * factory,
            gui::ObjectId objectId);
    virtual ~Objref();

    const ObjrefConfig& getConfig() const;

    corbasim::event::event* sendRequest(corbasim::event::request_ptr req);

    CORBA::Object_ptr updateReference(CORBA::Object_ptr ref); 

protected:
    ObjrefConfig m_cfg;
    const core::interface_reflective_base * m_factory;
    gui::ObjectId m_objectId;
    core::interface_caller_ptr m_caller;
};

typedef boost::shared_ptr< Objref > Objref_ptr;

} // namespace model
} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_MODEL_OBJREF_HPP */


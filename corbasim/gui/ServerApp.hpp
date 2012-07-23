// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ServerApp.hpp
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

#ifndef CORBASIM_GUI_SERVERAPP_HPP
#define CORBASIM_GUI_SERVERAPP_HPP

#include <corbasim/impl.hpp>
#include <corbasim/event_fwd.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/export.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC ServerApp
{
public:

    ServerApp(int argc, char ** argv);
    ~ServerApp();

    CORBA::Object_var setClient(
            const char * fqn, 
            const char * clientName,
            const CORBA::Object_var& ref);

    CORBA::Object_var setServant(
            ::corbasim::core::interface_reflective_base const * reflective,
            PortableServer::ServantBase * servant);

    /**
     * @brief Must be executed in application's main thread.
     *
     * @return 
     */
    int exec();

protected:

    struct ServerApp_i;

    ServerApp_i * m_impl;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SERVERAPP_HPP */


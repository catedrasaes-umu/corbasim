// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Servant.hpp
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

#ifndef CORBASIM_APP_SERVANT_HPP
#define CORBASIM_APP_SERVANT_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/core/callable.hpp>

#include "../appC.h"

namespace corbasim 
{
namespace app 
{

class AppController;

namespace model 
{

class Servant : public core::request_processor
{
public:
    Servant(const ServantConfig& cfg, gui::gui_factory_base * factory);
    virtual ~Servant();

    void setController(AppController * controller);

    const ServantConfig& getConfig() const;

    // Request processor interface
    event::event_ptr operator()(event::request_ptr,
            event::response_ptr);

    PortableServer::ServantBase * getServant() const;

protected:
    AppController * m_controller;

    ServantConfig m_cfg;
    gui::gui_factory_base * m_factory;
    PortableServer::ServantBase * m_servant;

};

typedef boost::shared_ptr< Servant > Servant_ptr;

} // namespace model
} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_SERVANT_HPP */


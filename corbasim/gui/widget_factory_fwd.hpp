// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * widget_factory_fwd.hpp
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

#ifndef CORBASIM_GUI_WIDGET_FACTORY_FWD_HPP
#define CORBASIM_GUI_WIDGET_FACTORY_FWD_HPP

#include <corbasim/gui/widgets_fwd.hpp>

namespace corbasim 
{
namespace gui 
{

struct widget_factory_base
{
    virtual widgets::widget_base * create_widget() const = 0;

    virtual ~widget_factory_base() {}
};

typedef boost::shared_ptr< widget_factory_base > widget_factory_ptr;

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_WIDGET_FACTORY_FWD_HPP */


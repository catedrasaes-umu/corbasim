// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * objrefvar.hpp
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

#ifndef CORBASIM_WIDGETS_OBJREFVAR_HPP
#define CORBASIM_WIDGETS_OBJREFVAR_HPP

#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/adapted.hpp>
#include <corbasim/core/reference_validator.hpp>
#include <corbasim/qt/ObjrefWidget.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

template< typename T >
struct objrefvar_widget : public widget_base, 
    public core::reference_validator_impl< 
           typename adapted::is_objrefvar< T >::interface >
{
    typedef objrefvar_widget< T > type;
    typedef qt::ObjrefWidget qwidget_t;

    typedef cs_mpl::false_ is_simple_widget;

    typedef typename adapted::is_objrefvar< T >::interface interface_t;
    typedef core::reference_validator_impl< interface_t > validator_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    objrefvar_widget()
    {
        m_qwidget = new qwidget_t(this);
    }

    inline void get_value(T& t)
    {
        t = interface_t::_duplicate(validator_t::m_ref);
    }

    inline void set_value(const T& t)
    {
        set_reference(t);
        m_qwidget->validatorHasChanged();
    }

    CORBASIM_QWIDGET()
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_OBJREFVAR_HPP */


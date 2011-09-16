// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * enum.hpp
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

#ifndef CORBASIM_WIDGETS_ENUM_HPP
#define CORBASIM_WIDGETS_ENUM_HPP

#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/adapted.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

template< typename T >
struct enum_as_combobox : public widget_base
{
    typedef enum_as_combobox< T > type;
    typedef QComboBox qwidget_t;

    typedef adapted::enumeration< T > adapted_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    enum_as_combobox()
    {
        m_qwidget = new qwidget_t;

        const char ** values = adapted_t::values();

        for(; *values; values++)
            m_qwidget->addItem(*values);
    }

    inline void get_value(T& t)
    {
        t = static_cast< T >(m_qwidget->currentIndex());
    }

    inline void set_value(const T& t)
    {
        m_qwidget->setCurrentIndex(static_cast< int >(t));
    }

    CORBASIM_QWIDGET()
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_ENUM_HPP */


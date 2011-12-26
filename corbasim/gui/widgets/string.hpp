// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * string.hpp
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

#ifndef CORBASIM_WIDGETS_STRING_HPP
#define CORBASIM_WIDGETS_STRING_HPP

#include <QLineEdit>

#include <corbasim/gui/widgets_fwd.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

template< typename T >
struct string_as_lineedit : public widget_base
{
    typedef string_as_lineedit< T > type;

    typedef QLineEdit qwidget_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    string_as_lineedit()
    {
        m_qwidget = new qwidget_t;
    }

    inline void get_value(orbimpl::string_for_seq t)
    {
        // Makes copy
        t = m_qwidget->text().toStdString().c_str();
    }

    template < typename Y >
    inline void get_value(Y& t)
    {
        // Makes copy
        t = m_qwidget->text().toStdString().c_str();
    }

    template < typename Y >
    inline void set_value(Y t)
    {
        m_qwidget->setText(t.in());
    }

    CORBASIM_QWIDGET()
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_STRING_HPP */


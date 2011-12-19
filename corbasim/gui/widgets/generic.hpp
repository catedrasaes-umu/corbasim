// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * generic.hpp
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

#ifndef CORBASIM_WIDGETS_GENERIC_HPP
#define CORBASIM_WIDGETS_GENERIC_HPP

#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/core/archives.hpp>
#include <sstream>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

template< typename T >
struct type_as_serialized : public widget_base
{
    typedef type_as_serialized< T > type;
    typedef QTextEdit qwidget_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    type_as_serialized()
    {
        m_qwidget = new qwidget_t;
    }

    inline void set_value(const T& val)
    {
        // TODO JSON format
        std::ostringstream os;
        core::text_oarchive toa(os);

        toa << val;

        m_qwidget->setPlainText(os.str().c_str());
    }

    inline void get_value(T& val)
    {
        // TODO JSON format
        const std::string str(m_qwidget->toPlainText().toStdString());
        std::istringstream is(str);
        core::text_iarchive tia(is);

        tia >> val;
    }

    CORBASIM_QWIDGET()
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_GENERIC_HPP */

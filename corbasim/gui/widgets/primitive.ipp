// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * primitive.ipp
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

#include "primitive.hpp"

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

// Primitive as spinbox

template< typename T >
typename primitive_as_spinbox< T >::type* 
primitive_as_spinbox< T >::create_widget()
{
    type * w = new type;
    return w;
}

template< typename T >
primitive_as_spinbox< T >::primitive_as_spinbox()
{
    m_qwidget = new qwidget_t(range_t::min(), range_t::max());
    // TODO permitirá especificar rango
    m_qwidget->setRange(range_t::min(), range_t::max());
}

template< typename T >
void primitive_as_spinbox< T >::get_value(T& t)
{
    t = m_qwidget->value();
}

template< typename T >
void primitive_as_spinbox< T >::set_value(const T& t)
{
    m_qwidget->setValue(t);
}

template< typename T >
typename primitive_as_spinbox< T >::qwidget_t * 
primitive_as_spinbox< T >::get_QWidget()
{
    return m_qwidget;
}

template< typename T >
QWidget * primitive_as_spinbox< T >::getWidget() const
{
    return m_qwidget;
}

// Bool as checkbox
template< typename T >
typename bool_as_checkbox< T >::type* 
bool_as_checkbox< T >::create_widget()
{
    type * w = new type;
    return w;
}

template< typename T >
bool_as_checkbox< T >::bool_as_checkbox()
{
    m_qwidget = new qwidget_t;
}

template< typename T >
void bool_as_checkbox< T >::get_value(T& t)
{
    t = (T) m_qwidget->isChecked();
}

template< typename T >
void bool_as_checkbox< T >::set_value(const T& t)
{
    m_qwidget->setChecked((bool) t);
}

template< typename T >
typename bool_as_checkbox< T >::qwidget_t * 
bool_as_checkbox< T >::get_QWidget()
{
    return m_qwidget;
}

template< typename T >
QWidget * bool_as_checkbox< T >::getWidget() const
{
    return m_qwidget;
}

// Spinbox with autoincrement

template< typename T >
typename spinbox_with_autoincrement< T >::type* 
spinbox_with_autoincrement< T >::create_widget()
{
    type * w = new type;
    return w;
}

template< typename T >
spinbox_with_autoincrement< T >::spinbox_with_autoincrement()
{
    m_qwidget = new qwidget_t;
    QHBoxLayout * layout = new QHBoxLayout;

    layout->addWidget(m_spinbox.get_QWidget());
    layout->addWidget(new QLabel("Increment"));
    layout->addWidget(m_increment.get_QWidget());

    m_qwidget->setLayout(layout);
}

template< typename T >
void spinbox_with_autoincrement< T >::get_value(T& t)
{
    m_spinbox.get_value(t);

    T inc;
    m_increment.get_value(inc);

    m_spinbox.set_value(t + inc);
}

template< typename T >
void spinbox_with_autoincrement< T >::set_value(const T& t)
{
    m_spinbox.set_value(t);
}

template< typename T >
typename spinbox_with_autoincrement< T >::qwidget_t * 
spinbox_with_autoincrement< T >::get_QWidget()
{
    return m_qwidget;
}

template< typename T >
QWidget * spinbox_with_autoincrement< T >::getWidget() const
{
    return m_qwidget;
}

} // namespace detail
} // namespace widgets
} // namespace corbasim


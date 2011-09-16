// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * primitive.hpp
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

#ifndef CORBASIM_WIDGETS_PRIMITIVE_HPP
#define CORBASIM_WIDGETS_PRIMITIVE_HPP

#include <corbasim/core/range.hpp>
#include <corbasim/gui/widgets_fwd.hpp>

// Widgets de QT
#include <corbasim/qt/RangedWidget.hpp>
#include <corbasim/qt/TemplatedSpinBox.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

/** Widget type **/
template< typename T >
struct spinbox_impl
{
    typedef qt::RangedWidget type;
};

template < typename T >
struct spinbox_impl_TSpinBox
{
    typedef qt::TemplatedSpinBox< T > type;
};

template < >
struct spinbox_impl < CORBA::ULong > : 
    public spinbox_impl_TSpinBox < CORBA::ULong >
{};

template < >
struct spinbox_impl < CORBA::LongLong > : 
    public spinbox_impl_TSpinBox < CORBA::LongLong >
{};

template < >
struct spinbox_impl < CORBA::ULongLong > : 
    public spinbox_impl_TSpinBox < CORBA::ULongLong >
{};

template< >
struct spinbox_impl< CORBA::Float >
{
    typedef qt::RangedDoubleWidget type;
};

template< >
struct spinbox_impl< CORBA::Double >
{
    typedef qt::RangedDoubleWidget type;
};

template< >
struct spinbox_impl< CORBA::LongDouble >
{
    typedef qt::RangedDoubleWidget type;
};

template< typename T >
struct primitive_as_spinbox : public widget_base
{
    typedef primitive_as_spinbox< T > type;
    typedef typename spinbox_impl< T >::type qwidget_t;
    typedef core::detail::range< T > range_t;

    CORBASIM_DEFAULTCREATEWIDGET();

    primitive_as_spinbox()
    {
        m_qwidget = new qwidget_t(range_t::min(), range_t::max());
        // TODO permitirá especificar rango
        m_qwidget->setRange(range_t::min(), range_t::max());
    }

    inline void get_value(T& t)
    {
        t = m_qwidget->value();
    }

    inline void set_value(const T& t)
    {
        m_qwidget->setValue(t);
    }

    CORBASIM_QWIDGET()
};

template< typename T >
struct bool_as_checkbox : public widget_base
{
    typedef bool_as_checkbox< T > type;
    typedef QCheckBox qwidget_t;

    CORBASIM_DEFAULTCREATEWIDGET();

    bool_as_checkbox()
    {
        m_qwidget = new qwidget_t;
    }

    inline void get_value(T& t)
    {
        t = m_qwidget->isChecked();
    }

    inline void set_value(const T& t)
    {
        m_qwidget->setChecked(t);
    }

    CORBASIM_QWIDGET()
};

template< typename T >
struct spinbox_with_autoincrement : public widget_base
{
    typedef spinbox_with_autoincrement< T > type;
    typedef QWidget qwidget_t;

    typedef primitive_as_spinbox< T > spinbox_t;

    spinbox_t m_spinbox;
    spinbox_t m_increment;

    CORBASIM_DEFAULTCREATEWIDGET();

    spinbox_with_autoincrement()
    {
        m_qwidget = new qwidget_t;
        QHBoxLayout * layout = new QHBoxLayout;

        layout->addWidget(m_spinbox.get_QWidget());
        layout->addWidget(new QLabel("Increment"));
        layout->addWidget(m_increment.get_QWidget());

        m_qwidget->setLayout(layout);
    }

    inline void get_value(T& t)
    {
        m_spinbox.get_value(t);

        T inc;
        m_increment.get_value(inc);

        m_spinbox.set_value(t + inc);
    }

    inline void set_value(const T& t)
    {
        m_spinbox.set_value(t);
    }

    CORBASIM_QWIDGET()

};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_PRIMITIVE_HPP */


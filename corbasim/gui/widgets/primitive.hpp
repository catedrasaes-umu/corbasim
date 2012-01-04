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

#include <QCheckBox>

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

// TODO
// template< >
// struct spinbox_impl< CORBA::LongDouble >
// {
//     typedef qt::RangedDoubleWidget type;
// };

template< typename T >
struct primitive_as_spinbox : public widget_base
{
    typedef primitive_as_spinbox< T > type;
    typedef typename spinbox_impl< T >::type qwidget_t;
    typedef core::detail::range< T > range_t;

    static type* create_widget();

    primitive_as_spinbox();

    void get_value(T& t);

    void set_value(const T& t);

    qwidget_t* get_QWidget();
    
    QWidget * getWidget() const;

    qwidget_t * m_qwidget;
};

template< typename T >
struct bool_as_checkbox : public widget_base
{
    typedef bool_as_checkbox< T > type;
    typedef QCheckBox qwidget_t;

    static type* create_widget();

    bool_as_checkbox();

    void get_value(T& t);

    void set_value(const T& t);

    qwidget_t* get_QWidget();
    
    QWidget * getWidget() const;

    qwidget_t * m_qwidget;
};

template< typename T >
struct spinbox_with_autoincrement : public widget_base
{
    typedef spinbox_with_autoincrement< T > type;
    typedef QWidget qwidget_t;

    typedef primitive_as_spinbox< T > spinbox_t;

    static type* create_widget();

    spinbox_with_autoincrement();

    void get_value(T& t);

    void set_value(const T& t);

    qwidget_t* get_QWidget();
    
    QWidget * getWidget() const;

    // Data
    spinbox_t m_spinbox;
    spinbox_t m_increment;
    qwidget_t * m_qwidget;
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_PRIMITIVE_HPP */


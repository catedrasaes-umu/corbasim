// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * widgets.hpp
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

#ifndef CORBASIM_WIDGETS_HPP
#define CORBASIM_WIDGETS_HPP

#include <corbasim/core/config.hpp>

#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/adapted.hpp>
#include <corbasim/gui/widgets/primitive.hpp>
#include <corbasim/gui/widgets/array.hpp>
#include <corbasim/gui/widgets/enum.hpp>
#include <corbasim/gui/widgets/generic.hpp>
#include <corbasim/gui/widgets/sequence.hpp>
#include <corbasim/gui/widgets/string.hpp>
#include <corbasim/gui/widgets/struct.hpp>
#include <corbasim/gui/widgets/objrefvar.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

template< typename T >
struct empty_widget : public widget_base
{
    typedef empty_widget< T > type;
    typedef QWidget qwidget_t;

    CORBASIM_CREATEWIDGET()
    CORBASIM_EMPTY_SETGET()
    CORBASIM_QWIDGET()
};

template< typename T >
struct unsupported_type : public widget_base
{
    typedef unsupported_type< T > type;
    typedef QLabel qwidget_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    unsupported_type()
    {
        m_qwidget = new qwidget_t("Unsupported type!");
    }

    CORBASIM_EMPTY_SETGET()
    CORBASIM_QWIDGET()
};

template< typename T >
struct default_primitive_widget : public primitive_as_spinbox< T >
{
};

template< typename T >
struct calculate_default_array_widget
{
    typedef typename boost::remove_bounds< T >::type slice_t;

    static const size_t size = sizeof(T) / sizeof(slice_t);
    typedef boost::mpl::bool_< (size > CORBASIM_ARRAY_RESUME_CONDITION) > size_condition;

    typedef typename 
        // if
        cs_mpl::eval_if< boost::mpl::not_< boost::is_arithmetic< slice_t > >, 
            array_as_tabs< T >,
        // else if
        cs_mpl::eval_if< size_condition, 
            type_as_serialized< T >,
        // else
            array_as_raw< T >
        > >::type type;
};

template< typename T >
struct default_array_widget : public calculate_default_array_widget< T >::type
{
};

template< typename T >
struct default_enum_widget : public enum_as_combobox< T >
{
};

template< typename T >
struct default_string_widget : public string_as_lineedit< T >
{
};

template< typename T >
struct default_sequence_widget : public sequence_as_stacked< T >
{
};

template< typename T >
struct default_struct_widget : public struct_as_grid< T >
{
};

template< typename T >
struct default_objrefvar_widget : public objrefvar_widget< T >
{
};

template< typename T >
struct calculate_default_widget
{
    typedef typename 
        // if
        cs_mpl::eval_if< cs_mpl::is_bool< T >, bool_as_checkbox< T >,
        // else if
        cs_mpl::eval_if< boost::is_arithmetic< T >, 
            default_primitive_widget< T >,
        // else if
        cs_mpl::eval_if< boost::is_array< T >, default_array_widget< T >,
        // else if
        cs_mpl::eval_if< boost::is_enum< T >, default_enum_widget< T >,
        // else if
        cs_mpl::eval_if< cs_mpl::is_string< T >, 
            default_string_widget< T >,
        // else if
        cs_mpl::eval_if< adapted::is_corbaseq< T >, 
            default_sequence_widget< T >,
        // else if
        cs_mpl::eval_if< cs_mpl::is_struct< T >, 
            default_struct_widget< T >,
        // else if
        cs_mpl::eval_if< adapted::is_objrefvar< T >, 
            default_objrefvar_widget< T >,
        // else
        unsupported_type< T >
        > > > > > > > >::type type;
};

} // namespace detail

/**
 * @brief Widget CORBASIM asociado a un tipo.
 *
 * Para cada tipo T widget< T > ha de cumplir los siguientes requisitos:
 *
 * @code
 * template < >
 * struct widget< T > : public widget_base // 1. Ha de heredar de widget_base,
 *                                         // directa o indirectamente
 * {
 *     typedef implementation-defined type; // 2. El tipo que contiene el 
 *                                          // método create_widget
 *
 *     typedef implementation-defined qwidget_t; // 3. Tipo del widget de Qt 
 *                                               // asociado a ese tipo
 *
 *     static inline type* create_widget()
 *     {
 *         // 4. Método create_widget
 *     }
 *
 *     // 5. Métodos set y get
 *     inline void get_value(T&) { ... }
 *     inline void set_value(const T&) { ... }
 *
 *     // 6. Método get_QWidget
 *     // Nota: no devuelve un QWidget, devuelve el subtipo concreto 
 *     // asociado al tipo T
 *     qwidget_t* get_QWidget() {...}
 * };
 * @endcode
 *
 * @tparam T El tipo.
 */
template< typename T >
struct widget : public detail::calculate_default_widget< T >::type
{
};

template < typename Member >
struct widget_member :
    public widget< typename cs_mpl::type_of_member< typename Member::type, 
        typename Member::index_type >::type >
{
};


} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_HPP */


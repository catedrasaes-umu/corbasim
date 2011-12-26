// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * widgets_fwd.hpp
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

#ifndef CORBASIM_WIDGETS_FWD_HPP
#define CORBASIM_WIDGETS_FWD_HPP

#include <QWidget>
#include <boost/shared_ptr.hpp>
#include <corbasim/mpl.hpp>
#include <corbasim/adapted.hpp>

/**
 * @brief Método que ha de tener todo widget.
 */
#define CORBASIM_QWIDGET() \
    inline qwidget_t* get_QWidget() \
    { \
        return m_qwidget; \
    } \
    \
    qwidget_t * m_qwidget; \
    \
    QWidget * getWidget() const \
    { \
        return m_qwidget; \
    } \
    /***/

#define CORBASIM_CREATEWIDGET() \
    static inline type* create_widget() \
    { \
        type * w = new type; \
        w->m_qwidget = new qwidget_t; \
        return w; \
    } \
    /***/

#define CORBASIM_DEFAULTCREATEWIDGET() \
    static inline type* create_widget() \
    { \
        type * w = new type; \
        return w; \
    } \
    /***/

#define CORBASIM_EMPTY_SETGET() \
    inline void get_value(T& t) {} \
    inline void set_value(const T& t) {} \
    /***/

namespace corbasim 
{
namespace widgets 
{

struct widget_base
{
    typedef cs_mpl::true_ is_simple_widget;

    virtual QWidget* getWidget() const = 0;

    virtual ~widget_base() {}
};

typedef boost::shared_ptr< widget_base > widget_ptr;

template< typename T >
struct widget;

template< typename Member >
struct widget_member;

} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_FWD_HPP */

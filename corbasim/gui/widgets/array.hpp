// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * array.hpp
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

#ifndef CORBASIM_WIDGETS_ARRAY_HPP
#define CORBASIM_WIDGETS_ARRAY_HPP

#include <vector>
#include <fstream>

#include <QTabWidget>
#include <QHBoxLayout>

#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/qt/MultiFileSelectionWidget.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

/**
 * @brief Base para la mayoría de widgets para arrays. Gestiona 
 *        la colección
 *        de widgets hijo e implementa los métodos get y set.
 *
 * @tparam T Un tipo array.
 */
template< typename T >
struct array_base_widget : public widget_base
{
    typedef typename boost::remove_bounds < T >::type slice_t;
    typedef typename widget< slice_t >::type slice_widget_t;

    static const size_t size = sizeof(T) / sizeof(slice_t);

    inline void set_value(const T& val)
    {
        for (size_t idx = 0; idx < size; idx++)
            m_children[idx]->set_value(val[idx]);
    }

    inline void get_value(T& val)
    {
        for (size_t idx = 0; idx < size; idx++)
            m_children[idx]->get_value(val[idx]);
    }

    /**
     * @brief Utilizado por las clases derivadas para añadir widgets 
     *        hijos.
     *
     * @param w El widget hijo.
     */
    inline void add_widget(slice_widget_t * w)
    {
        m_children.push_back(slice_widget_ptr(w));
    }

    typedef boost::shared_ptr< slice_widget_t > slice_widget_ptr;
    std::vector< slice_widget_ptr > m_children;
};


/**
 * @brief Muestra un array como una sucesión de widgets del tipo 
 *        asociado a su
 *        subtipo.
 *
 * @tparam T Un tipo array.
 */
template< typename T >
struct array_as_raw : public array_base_widget< T >
{
    typedef array_as_raw< T > type;
    typedef QWidget qwidget_t;

    typedef array_base_widget< T > base_t;
    typedef typename base_t::slice_widget_t slice_widget_t;

    // Insertado en la grid como widget complejo (con un QGroupBox)
    typedef cs_mpl::false_ is_simple_widget;

    CORBASIM_DEFAULTCREATEWIDGET()

    array_as_raw()
    {
        m_qwidget = new qwidget_t;
        QHBoxLayout * layout = new QHBoxLayout;

        for (size_t idx = 0; idx < base_t::size; idx++)
        {
            slice_widget_t * w = slice_widget_t::create_widget();

            layout->addWidget(w->get_QWidget());

            base_t::add_widget(w);
        }

        m_qwidget->setLayout(layout);
    }

    CORBASIM_QWIDGET()
};

/**
 * @brief Muestra un array como una sucesión de pestañas con el widget 
 *        asociado
 *        a su subtipo.
 *
 * @tparam T Un tipo array.
 */
template< typename T >
struct array_as_tabs : public array_base_widget< T >
{
    typedef array_as_tabs< T > type;
    typedef QTabWidget qwidget_t;

    typedef array_base_widget< T > base_t;
    typedef typename base_t::slice_widget_t slice_widget_t;

    // Insertado en la grid como widget complejo (con un QGroupBox)
    typedef cs_mpl::false_ is_simple_widget;

    CORBASIM_DEFAULTCREATEWIDGET()

    array_as_tabs()
    {
        m_qwidget = new qwidget_t;

        for (size_t idx = 0; idx < base_t::size; idx++)
        {
            slice_widget_t * w = slice_widget_t::create_widget();

            m_qwidget->addTab(w->get_QWidget(), QString::number(idx));

            base_t::add_widget(w);
        }
    }

    CORBASIM_QWIDGET()
};

template< typename T >
struct array_trait
{
    static const size_t size = 1;
    typedef T type;
};

template< typename T, unsigned int N >
struct array_trait< T[N] >
{
    static const size_t size = N * array_trait< T >::size;
    typedef typename array_trait< T >::type type;
};

template < typename T, typename SourceType >
struct array_from_files : public widget_base
{
    typedef array_from_files< T, SourceType > type;
    typedef qt::MultiFileSelectionWidget qwidget_t;

    typedef typename array_trait< T >::type slice_t;
    static const size_t size = array_trait< T >::size;

    typedef cs_mpl::false_ is_simple_widget;

    CORBASIM_DEFAULTCREATEWIDGET();

    array_from_files()
    {
        m_qwidget = new qwidget_t;
    }

    inline void set_value(const T& val)
    {
    }

    inline void get_value(T& val)
    {
        const QString * file = m_qwidget->getNext();

        slice_t * val_ = (slice_t *) val;
        std::memset(val_, '\0', size * sizeof(slice_t));

        if (!file) return;

        std::ifstream ifs(file->toStdString().c_str(), 
                std::ios::in | std::ios::binary);
        std::streambuf * pbuf = ifs.rdbuf();

        for (size_t i = 0; i < size && pbuf->in_avail(); i++) 
        {
            SourceType value;
            pbuf->sgetn(reinterpret_cast< char* >(&value), 
                    sizeof(SourceType));
            val_[i] = (slice_t) value;
        }
    }

    CORBASIM_QWIDGET()
};


} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_ARRAY_HPP */


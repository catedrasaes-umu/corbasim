// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * sequence.hpp
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

#ifndef CORBASIM_WIDGETS_SEQUENCE_HPP
#define CORBASIM_WIDGETS_SEQUENCE_HPP

#include <vector>
#include <fstream>
#include <corbasim/gui/widgets/sequence_fwd.hpp>
#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/gui/widget_factory.hpp>
#include <corbasim/qt/SequenceWidget.hpp>
#include <corbasim/qt/MultiFileSelectionWidget.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

/**
 * @brief Base para la mayoría de widgets asociados a secuencias. 
 *
 * @tparam T Un tipo secuencia.
 */
template< typename T >
struct sequence_base_widget : public widget_base
{
    typedef typename adapted::is_corbaseq< T >::slice_type slice_t;
    typedef typename widget< slice_t >::type slice_widget_t;

    inline void set_value(const T& val)
    {
        size_t length = val.length();

        for (int i = 0; i < length; i++) 
            m_children[i]->set_value(val[i]);
    }

    inline void get_value(T& val)
    {
        size_t length = m_children.size();
        val.length(length);

        for (int i = 0; i < length; i++) 
            m_children[i]->get_value(val[i]);
    }

    typedef boost::shared_ptr< slice_widget_t > slice_widget_ptr;
    std::vector< slice_widget_ptr > m_children;

};

template < typename T >
struct sequence_as_stacked : public widget_base
{
    typedef sequence_as_stacked< T > type;
    typedef qt::SequenceWidget qwidget_t;
    typedef typename qwidget_t::widgets_t widgets_t;

    typedef cs_mpl::false_ is_simple_widget;

    typedef typename adapted::is_corbaseq< T >::slice_type slice_t;
    typedef typename widget< slice_t >::type slice_widget_t;
    typedef gui::widget_factory_impl< slice_t > factory_t;

    CORBASIM_DEFAULTCREATEWIDGET();

    sequence_as_stacked()
    {
        m_qwidget = new qwidget_t(factory_t::get_instance());
    }

    inline void set_value(const T& val)
    {
        size_t length = val.length();
        m_qwidget->lengthChanged(length);
        widgets_t& children = m_qwidget->getWidgets();

        for (size_t i = 0; i < length; i++) 
            static_cast< slice_widget_t* >
                (children[i].get())->set_value(val[i]);
    }

    inline void get_value(T& val)
    {
        widgets_t& children = m_qwidget->getWidgets();

        size_t length = children.size();
        val.length(length);

        for (size_t i = 0; i < length; i++) 
            static_cast< slice_widget_t* >
                (children[i].get())->get_value(val[i]);
    }

    CORBASIM_QWIDGET()
};

template < typename T >
struct sequence_as_stacked2 : public widget_base, 
    public abstract_sequence_widget
{
    typedef sequence_as_stacked2< T > type;
    typedef qt::SequenceWidget2 qwidget_t;

    typedef cs_mpl::false_ is_simple_widget;

    typedef typename adapted::is_corbaseq< T >::slice_type slice_t;
    typedef typename widget< slice_t >::type slice_widget_t;

    CORBASIM_DEFAULTCREATEWIDGET();

    sequence_as_stacked2() :
        m_current_index(0)
    {
        m_qwidget = new qwidget_t(this);
    }

    inline void set_value(const T& val)
    {
        m_current_value = val;

        m_qwidget->notifyValueHasChanged(m_current_value.length());
    }

    inline void get_value(T& val)
    {
        // Guarda el el que está en edición actualmente
        m_child_widget.get_value(m_current_value[m_current_index]);

        val = m_current_value;
    }

    // abstract_sequence_widget
    QWidget * get_child_widget() const
    {
        return m_child_widget.getWidget();
    }

    void set_length(unsigned int length)
    {
        m_current_value.length(length);
    }

    void change_to(unsigned int index)
    {
        if (m_current_index < m_current_value.length())
            // Guarda el anterior
            m_child_widget.get_value(m_current_value[m_current_index]);

        // Restaura el nuevo
        m_current_index = index;
        m_child_widget.set_value(m_current_value[index]);
    }

    // Data
    slice_widget_t m_child_widget;
    T m_current_value;
    unsigned int m_current_index;

    CORBASIM_QWIDGET()
};


template < typename T, typename SourceType, typename DestType >
struct sequence_from_files : public widget_base
{
    typedef sequence_from_files< T, SourceType, DestType > type;
    typedef qt::MultiFileSelectionWidget qwidget_t;

    typedef cs_mpl::false_ is_simple_widget;

    CORBASIM_DEFAULTCREATEWIDGET();

    sequence_from_files()
    {
        m_qwidget = new qwidget_t;
    }

    inline void set_value(const T& val)
    {
    }

    inline void get_value(T& val)
    {
        const QString * file = m_qwidget->getNext();

        if (!file) return;

        std::ifstream ifs(file->toStdString().c_str(), 
                std::ios::in | std::ios::binary);

        if (!ifs) return;

        std::streambuf * pbuf = ifs.rdbuf();

        size_t length = pbuf->in_avail() / sizeof(SourceType);
        
        if (!length) return;

        // TODO comprobar que no sea demasiado grande

        val.length(length);

        for (size_t i = 0; i < length; i++) 
        {
            SourceType value;
            pbuf->sgetn(reinterpret_cast< char* >(&value), 
                    sizeof(SourceType));

            val[i] = (DestType) value;
        }
    }

    CORBASIM_QWIDGET()
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_SEQUENCE_HPP */


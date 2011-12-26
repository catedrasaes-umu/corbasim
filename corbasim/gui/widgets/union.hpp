// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * union.hpp
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

#ifndef CORBASIM_WIDGETS_UNION_HPP
#define CORBASIM_WIDGETS_UNION_HPP

#include <vector>

#include <QVBoxLayout>
#include <QStackedWidget>
#include <QGridLayout>
#include <QComboBox>

#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/gui/widgets/grid.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{
namespace iterator 
{

typedef std::vector< widget_ptr > UnionChildren;

// Iteracion sobre una estructura
template < typename S, typename N >
struct UnionImpl
{
    // Tipo del campo actual
    typedef typename cs_mpl::type_of_member< S, N >::type current_t;

    // Valor de N en la siguiente iteracion
    typedef typename boost::mpl::next < N >::type next_t;

    // Tipo que contiene el nombre del campo actual
    typedef cs_mpl::name_of_member< S, N > name_t;

    // Member
    typedef adapted::member< S, N::value > member_t;

    // Widget asociado al tipo del campo actual
    typedef typename widget_member< member_t >::type current_widget_t;
        
    struct create_impl
    {
        static inline void invoke(QGridLayout* layout, 
                UnionChildren& vector, int& pos)
        {
            current_widget_t * current_widget = 
                current_widget_t::create_widget();
            vector.push_back(widget_ptr(current_widget));

            current_widget->get_QWidget()->setObjectName(name_t::call());

            // Inserta el widget en la grid
            grid_inserter< current_widget_t > inserter;
            inserter.add_widget(layout, 
                    current_widget->get_QWidget(),
                    name_t::call());

            pos++;
        }
    };

    template < typename Layout >
    static inline void create(Layout* layout, UnionChildren& vector, 
            int pos = 0)
    {
        QWidget * w = new QWidget;
        QGridLayout * gridLayout = new QGridLayout;

        create_impl::invoke(gridLayout, vector, pos);

        w->setLayout(gridLayout);
        layout->addWidget(w);
    
        // Siguiente iteracion
        UnionImpl < S, next_t >::create(layout, vector, pos);
    }

    struct set_value_impl
    {
        static inline void invoke(const S& s,
                UnionChildren& vector, int& pos)
        {
            reinterpret_cast< current_widget_t* >(vector[pos].get())->
                set_value(boost::fusion::at < N >(s));
            pos++;
        }
    };

    static inline void set_value(const S& s, UnionChildren& vector, 
            int pos = 0)
    {
        if (pos == N::value - 1)
            set_value_impl::invoke(s, vector, pos);
        else
            UnionImpl < S, next_t >::set_value(s, vector, pos);
    }

    struct get_value_impl
    {
        static inline void invoke(S& s,
                UnionChildren& vector, int& pos)
        {
            current_t t;
            reinterpret_cast< current_widget_t* >(vector[pos].get())->
                get_value(t);
            boost::fusion::at < N >(s) = t;
            pos++;
        }
    };

    static inline void get_value(S& s, UnionChildren& vector, 
            int pos = 0)
    {
        if (pos == N::value - 1)
            get_value_impl::invoke(s, vector, pos);
        else
            UnionImpl < S, next_t >::get_value(s, vector, pos);
    }
};

// Fin de la iteracion sobre estructuras.
template < typename S >
struct UnionImpl < S, typename cs_mpl::number_of_members< S >::type >
{
    template < typename Layout >
    static inline void create(Layout* layout, UnionChildren& vector, 
            int pos = 0)
    {
        // Nada por hacer
    }

    static inline void set_value(const S& s, UnionChildren& vector, 
            int pos = 0)
    {
        // Nada por hacer
    }

    static inline void get_value(S& s, UnionChildren& vector, 
            int pos = 0)
    {
        // Nada por hacer
    }
};

// Iterador sobre una union. Template fachada. 
// El elemento 0 es el discriminante.
template < typename S >
struct Union: public UnionImpl < S, boost::mpl::int_ < 1 > >
{
};

} // namespace iterator

template< typename T >
struct union_base_widget : public widget_base
{
    std::vector< widget_ptr > m_children;
};

template< typename T >
struct union_as_stack : public union_base_widget< T >
{
    typedef union_as_stack< T > type;
    typedef QWidget qwidget_t;

    typedef cs_mpl::false_ is_simple_widget;

    typedef union_base_widget< T > base_t;

    typedef adapted::is_union< T > adapted_t;

    typedef typename cs_mpl::number_of_members< T >::type size_type; 

    typedef typename 
        cs_mpl::type_of_member< T, boost::mpl::int_< 0 > >::type 
        discriminator_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    union_as_stack()
    {
        m_qwidget = new qwidget_t;
        QVBoxLayout * layout = new QVBoxLayout;

        m_combo = new QComboBox;

        // add members
        const unsigned int count = size_type::value; 

        for (unsigned int i = 1; i < count; i++) 
        {
            std::ostringstream oss;
            oss << adapted_t::discriminators()[i - 1];

            // TODO more efficient but generic convertion to string
            m_combo->addItem(oss.str().c_str());
        }
        
        m_stack = new QStackedWidget;

        QObject::connect(m_combo, SIGNAL(currentIndexChanged(int)), 
                m_stack, SLOT(setCurrentIndex(int)));

        iterator::Union< T >::create(m_stack, base_t::m_children);

        layout->addWidget(m_combo);
        layout->addWidget(m_stack);

        m_qwidget->setLayout(layout);
    }

    CORBASIM_QWIDGET()

    QComboBox * m_combo;
    QStackedWidget * m_stack;

    static inline int disc_to_pos(discriminator_t d)
    {
        for (int i = 0; i < size_type::value - 1; i++) 
        {
            if (adapted_t::discriminators()[i] == d)
                return i;
        }

        // Invalid value
        return size_type::value;
    }

    inline void get_value(T& t)
    {
        const int pos = m_combo->currentIndex();

        if (pos > 0 && pos < size_type::value - 1)
            iterator::Union< T >::get_value(t, base_t::m_children, pos);
    }

    inline void set_value(const T& t)
    {
        const int pos = disc_to_pos(t._d());

        if (pos < size_type::value - 1)
            iterator::Union< T >::set_value(t, base_t::m_children, pos);
    }

};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_UNION_HPP */


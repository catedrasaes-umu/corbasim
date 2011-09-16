// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * struct.hpp
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

#ifndef CORBASIM_WIDGETS_STRUCT_HPP
#define CORBASIM_WIDGETS_STRUCT_HPP

#include <vector>
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

struct always_insert
{
    template< typename N >
    struct apply : public cs_mpl::true_ {};
};

typedef std::vector< widget_ptr > StructChildren;

// Iteracion sobre una estructura
template < typename S, typename N, typename Func >
struct StructImpl
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
        
    typedef typename Func::template apply< N > condition_t;

    struct null_impl
    {
        template< typename X, typename Y, typename Z>
        static inline void invoke(X x, Y y, Z z) { /* does nothing */}
    };

    struct create_impl
    {
        static inline void invoke(QGridLayout* layout, 
                StructChildren& vector, int& pos)
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
    static inline void create(Layout* layout, StructChildren& vector, 
            int pos = 0)
    {
        typedef typename cs_mpl::eval_if< 
                    condition_t,
                        boost::mpl::identity< create_impl >,
                    // else
                        boost::mpl::identity< null_impl >
                >::type typex;
        typex::invoke(layout, vector, pos);
    
        // Siguiente iteracion
        StructImpl < S, next_t, Func >::create(layout, vector, pos);
    }

    struct set_value_impl
    {
        static inline void invoke(const S& s,
                StructChildren& vector, int& pos)
        {
            reinterpret_cast< current_widget_t* >(vector[pos].get())->
                set_value(boost::fusion::at < N >(s));
            pos++;
        }
    };

    static inline void set_value(const S& s, StructChildren& vector, 
            int pos = 0)
    {
        typedef typename cs_mpl::eval_if< 
                    condition_t,
                        boost::mpl::identity< set_value_impl >,
                    // else
                        boost::mpl::identity< null_impl >
                >::type typex;
        typex::invoke(s, vector, pos);

        StructImpl < S, next_t, Func >::set_value(s, vector, pos);
    }

    struct get_value_impl
    {
        static inline void invoke(S& s,
                StructChildren& vector, int& pos)
        {
            reinterpret_cast< current_widget_t* >(vector[pos].get())->
                get_value(boost::fusion::at < N >(s));
            pos++;
        }
    };

    static inline void get_value(S& s, StructChildren& vector, int pos = 0)
    {
        typedef typename cs_mpl::eval_if< 
                    condition_t,
                        boost::mpl::identity< get_value_impl >,
                    // else
                        boost::mpl::identity< null_impl >
                >::type typex;
        typex::invoke(s, vector, pos);

        StructImpl < S, next_t, Func >::get_value(s, vector, pos);
    }
};

// Fin de la iteracion sobre estructuras.
template < typename S, typename Func >
struct StructImpl < S, typename cs_mpl::number_of_members< S >::type, Func >
{
    template < typename Layout >
    static inline void create(Layout* layout, StructChildren& vector, 
            int pos = 0)
    {
        // Nada por hacer
    }

    static inline void set_value(const S& s, StructChildren& vector, 
            int pos = 0)
    {
        // Nada por hacer
    }

    static inline void get_value(S& s, StructChildren& vector, int pos = 0)
    {
        // Nada por hacer
    }
};

// Iterador sobre una estructura. Template fachada.
template < typename S, typename Func >
struct Struct: public StructImpl < S, boost::mpl::int_ < 0 >, Func >
{
};

} // namespace iterator

template< typename T, typename Func = iterator::always_insert >
struct struct_base_widget : public widget_base
{
    inline void get_value(T& t)
    {
        iterator::Struct< T, Func >::get_value(t, m_children);
    }

    inline void set_value(const T& t)
    {
        iterator::Struct< T, Func >::set_value(t, m_children);
    }

    std::vector< widget_ptr > m_children;
};

template< typename T, typename Func = iterator::always_insert >
struct struct_as_grid : public struct_base_widget< T, Func >
{
    typedef struct_as_grid< T > type;
    typedef QWidget qwidget_t;

    typedef cs_mpl::false_ is_simple_widget;

    typedef struct_base_widget< T, Func > base_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    struct_as_grid()
    {
        m_qwidget = new qwidget_t;
        QGridLayout * layout = new QGridLayout;

        iterator::Struct< T, Func >::create(layout, base_t::m_children);

        m_qwidget->setLayout(layout);
    }

    CORBASIM_QWIDGET()
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_STRUCT_HPP */


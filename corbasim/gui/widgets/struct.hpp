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

#include <QGridLayout>

#include <corbasim/gui/widgets_fwd.hpp>
#include <corbasim/gui/widgets/grid.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

typedef std::vector< widget_ptr > StructChildren;

// Iteracion sobre una estructura
template < typename S >
struct create_iterator
{
    QGridLayout * layout_;
    std::vector< widget_ptr >& children_;

    create_iterator(QGridLayout * l,
            std::vector< widget_ptr >& c) : 
        layout_(l), children_(c)
    {}

    template < typename N >
    void operator()(N const& nn)
    {
        // Tipo del campo actual
        typedef typename cs_mpl::type_of_member< S, N >::type current_t;

        // Tipo que contiene el nombre del campo actual
        typedef cs_mpl::name_of_member< S, N > name_t;

        // Member
        typedef adapted::member< S, N::value > member_t;

        // Widget asociado al tipo del campo actual
        typedef typename widget_member< member_t >::type 
            current_widget_t;

        current_widget_t * current_widget = 
            current_widget_t::create_widget();
        children_[N::value] = widget_ptr(current_widget);

        current_widget->get_QWidget()->setObjectName(name_t::call());

        // Inserta el widget en la grid
        grid_inserter< current_widget_t > inserter;
        inserter.add_widget(layout_, 
                current_widget->get_QWidget(),
                name_t::call());
    }
};

template < typename S >
struct set_value_iterator
{
    const S& struct_;
    std::vector< widget_ptr >& children_;

    set_value_iterator(const S& s,
            std::vector< widget_ptr >& c) : 
        struct_(s), children_(c)
    {}

    template < typename N >
    void operator()(N const& nn)
    {
        // Member
        typedef adapted::member< S, N::value > member_t;

        // Widget asociado al tipo del campo actual
        typedef typename widget_member< member_t >::type 
            current_widget_t;

        if (!children_[N::value]) return;

        reinterpret_cast< current_widget_t* >(
                children_[N::value].get())->set_value(
                    boost::fusion::at < N >(struct_));
    }
};

template < typename S >
struct get_value_iterator
{
    S& struct_;
    std::vector< widget_ptr >& children_;

    get_value_iterator(S& s,
            std::vector< widget_ptr >& c) : 
        struct_(s), children_(c)
    {}

    template < typename N >
    void operator()(N const& nn)
    {
        // Member
        typedef adapted::member< S, N::value > member_t;

        // Widget asociado al tipo del campo actual
        typedef typename widget_member< member_t >::type 
            current_widget_t;

        if (!children_[N::value]) return;

        reinterpret_cast< current_widget_t* >(
                children_[N::value].get())->get_value(
                    boost::fusion::at < N >(struct_));
    }
};


template< typename T >
struct struct_base_widget : public widget_base
{
    static const std::size_t members_count = 
        boost::fusion::result_of::size< T >::value;
    typedef boost::mpl::range_c< size_t, 0, members_count > 
        members_range_t;

    struct_base_widget() : m_children(members_count) {}

    inline void get_value(T& t)
    {
        get_value_iterator< T > it(t, m_children);
        boost::mpl::for_each< members_range_t >(it);
    }

    inline void set_value(const T& t)
    {
        set_value_iterator< T > it(t, m_children);
        boost::mpl::for_each< members_range_t >(it);
    }

    std::vector< widget_ptr > m_children;
};

template< typename T >
struct struct_as_grid : public struct_base_widget< T >
{
    typedef struct_as_grid< T > type;
    typedef QWidget qwidget_t;

    typedef cs_mpl::false_ is_simple_widget;

    typedef struct_base_widget< T > base_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    struct_as_grid()
    {
        m_qwidget = new qwidget_t;
        QGridLayout * layout = new QGridLayout;

        create_iterator< T > it(layout, base_t::m_children);
        boost::mpl::for_each< typename base_t::members_range_t >(it);

        m_qwidget->setLayout(layout);
    }

    CORBASIM_QWIDGET()
};

template< typename T, typename View >
struct struct_as_filtred_grid : public struct_base_widget< T >
{
    typedef struct_as_grid< T > type;
    typedef QWidget qwidget_t;

    typedef cs_mpl::false_ is_simple_widget;

    typedef struct_base_widget< T > base_t;

    CORBASIM_DEFAULTCREATEWIDGET()

    struct_as_filtred_grid()
    {
        m_qwidget = new qwidget_t;
        QGridLayout * layout = new QGridLayout;

        create_iterator< T > it(layout, base_t::m_children);
        boost::mpl::for_each< View >(it);

        m_qwidget->setLayout(layout);
    }

    CORBASIM_QWIDGET()
};


} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_STRUCT_HPP */


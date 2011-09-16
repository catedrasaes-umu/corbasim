// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * grid.hpp
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

#ifndef CORBASIM_WIDGETS_GRID_HPP
#define CORBASIM_WIDGETS_GRID_HPP

#include <QtGui>
#include <corbasim/mpl.hpp>

namespace corbasim 
{
namespace widgets 
{
namespace detail 
{

template< typename T, typename Y >
struct grid_inserter_impl
{
    template< typename Grid, typename Widget >
    inline void add_widget(Grid* grid, Widget* widget, const char * name) 
    {
        int row = grid->rowCount();

        grid->addWidget(new QLabel(name), row, 0);
        grid->addWidget(widget, row, 1);
    }
};

template< typename T >
struct grid_inserter_impl< T, cs_mpl::false_ >
{
    template< typename Grid, typename Widget >
    inline void add_widget(Grid* grid, Widget* widget, const char * name) 
    {
        int row = grid->rowCount();

        QGroupBox * g = new QGroupBox(name);
        QVBoxLayout * l = new QVBoxLayout;
        l->addWidget(widget);
        g->setLayout(l);
                    
        grid->addWidget(g, row, 0, 1, 2);
    }
};


template< typename T >
struct grid_inserter : public grid_inserter_impl< T, 
    typename T::is_simple_widget >
{
};

} // namespace detail
} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_GRID_HPP */


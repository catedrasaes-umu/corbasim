// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * enum.hpp
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

#ifndef CORBASIM_TREES_ENUM_HPP
#define CORBASIM_TREES_ENUM_HPP

#include <corbasim/gui/trees_fwd.hpp>
#include <corbasim/adapted.hpp>

namespace corbasim
{
namespace trees
{
namespace detail
{

template < typename T >
struct enum_as_item
{
    typedef enum_as_item < T > type;
    typedef adapted::enumeration < T > adapted_t;

    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        const char ** values = adapted_t::values();
        std::ostringstream oss;
        
        oss << name << ": ";

        if (static_cast< unsigned int >(t) < adapted_t::size)
            oss << values[static_cast< unsigned int >(t)];
        else
            oss << "#Unknown value: " << t;
        return new QTreeWidgetItem(QStringList(oss.str().c_str()));
    }

    static inline QStandardItem* create_item(const T& t)
    {
        const char ** values = adapted_t::values();
        QStandardItem* item = new QStandardItem();

        if (static_cast< unsigned int >(t) < adapted_t::size)
            item->setText(values[static_cast< unsigned int >(t)]);
        else
            item->setText(QString("#Unknown value %1").arg(t));

        return item;
    }

};

} // detail
} // trees
} // corbasim

#endif // CORBASIM_TREES_ENUM_HPP

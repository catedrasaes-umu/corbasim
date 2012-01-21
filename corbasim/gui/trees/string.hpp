// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * string.hpp
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

#ifndef CORBASIM_TREES_STRING_HPP
#define CORBASIM_TREES_STRING_HPP

#include <corbasim/gui/trees_fwd.hpp>

namespace corbasim 
{
namespace trees 
{
namespace detail 
{

template< typename T >
struct string_as_item
{
    typedef string_as_item < T > type;

    template < typename Y >
    static inline QTreeWidgetItem* create_tree(Y t, 
            const char* name)
    {
        std::ostringstream oss;
        oss << name << ": " << t;
        std::string str = oss.str();
        return new QTreeWidgetItem(QStringList(str.c_str()));
    }

    template < typename Y >
    static inline QStandardItem* create_item(Y t)
    {
        std::ostringstream oss;
        oss << t;
        return new QStandardItem(oss.str().c_str());
    }
};

} // namespace detail
} // namespace trees
} // namespace corbasim

#endif /* CORBASIM_TREES_STRING_HPP */


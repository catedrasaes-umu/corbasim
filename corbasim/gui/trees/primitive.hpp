// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * primitive.hpp
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

#ifndef CORBASIM_TREES_PRIMITIVE_HPP
#define CORBASIM_TREES_PRIMITIVE_HPP

#include <corbasim/gui/trees_fwd.hpp>

namespace corbasim
{
namespace trees
{
namespace detail
{

template < typename T >
struct arithmetic_as_item
{
    typedef arithmetic_as_item < T > type;
    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        std::ostringstream oss;

	    oss << name << ": " /*<< std::setprecision(14)*/ << t;

        return new QTreeWidgetItem(QStringList(oss.str().c_str()));
    }
};

// represent CORBA::octet as a number
template < >
struct arithmetic_as_item < unsigned char > : 
    public arithmetic_as_item< unsigned int >
{
};

} // detail
} // trees
} // corbasim

#endif // CORBASIM_TREES_PRIMITIVE_HPP

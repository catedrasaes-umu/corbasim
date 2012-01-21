// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * objref.hpp
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

#ifndef CORBASIM_GUI_TREES_OBJREF_HPP
#define CORBASIM_GUI_TREES_OBJREF_HPP

#include <corbasim/gui/trees_fwd.hpp>
#include <corbasim/core/reference_repository.hpp>

namespace corbasim 
{
namespace trees 
{
namespace detail 
{

template< typename T >
struct objref_tree
{
    static inline QTreeWidgetItem* create_tree(const T& t,
            const char * name)
    {
        core::reference_repository * rr =
            core::reference_repository::get_instance();

        CORBA::String_var str;
        
        if (t.in())
            str = rr->object_to_string(t.in());
        else
            str = "NIL";

        return new QTreeWidgetItem(QStringList(
                    QString("%1: %2").arg(name).arg(str.in())));
    }

    static inline QStandardItem* create_item(const T& t)
    {
        QStandardItem* item = new QStandardItem();
        core::reference_repository * rr =
            core::reference_repository::get_instance();
        
        if (t.in())
        {
            CORBA::String_var str = rr->object_to_string(t.in());
            item->setText(str.in());
        }
        else
        {
            item->setText("NIL");
        }

        return item;
    }
};

} // namespace detail
} // namespace trees
} // namespace corbasim

#endif /* CORBASIM_GUI_TREES_OBJREF_HPP */


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

#ifndef CORBASIM_TREES_SEQUENCE_HPP
#define CORBASIM_TREES_SEQUENCE_HPP

#include <corbasim/gui/trees_fwd.hpp>
#include <corbasim/adapted.hpp>

namespace corbasim 
{
namespace trees 
{
namespace detail 
{

template< typename T >
struct sequence_as_tree
{
    typedef sequence_as_tree < T > type;
    typedef typename adapted::is_corbaseq < T >::slice_type slice_t;
    typedef tree < slice_t > slice_tree_t;

    static inline QTreeWidgetItem* create_tree(const T& t,
            const char * name)
    {
        size_t size = t.length();
        QString qname(name);
        qname += " (length: " + QString::number(size) +")";
        QTreeWidgetItem* parent = 
            new QTreeWidgetItem(QStringList(qname));

        for(size_t i=0; i<size; i++)
        {
            std::ostringstream oss;
            oss << name << "[" << i << "]";
            QTreeWidgetItem* child = slice_tree_t::create_tree(t[i], 
                    oss.str().c_str());
            parent->addChild(child);
        }

        return parent;
    }
};

template< typename T, 
    unsigned int MAX = CORBASIM_ARRAY_RESUME_CONDITION >
struct sequence_as_resume
{
    typedef sequence_as_resume < T > type;
    typedef typename adapted::is_corbaseq < T >::slice_type slice_t;

    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        const size_t size = t.length();

        std::ostringstream oss;
        oss << name << " (length: " << size << "):";

        size_t i = 0;
        for(; i < size && i < MAX; i++)
            oss << ' ' << t[i];

        if(MAX < size)
            oss << "...";

        return new QTreeWidgetItem(QStringList(oss.str().c_str()));
    }
};

} // namespace detail
} // namespace trees
} // namespace corbasim

#endif /* CORBASIM_TREES_SEQUENCE_HPP */


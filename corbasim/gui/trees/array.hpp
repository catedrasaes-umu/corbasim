// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * array.hpp
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

#ifndef CORBASIM_TREES_ARRAY_HPP
#define CORBASIM_TREES_ARRAY_HPP

#include <corbasim/gui/trees_fwd.hpp>
#include <corbasim/core/config.hpp>

namespace corbasim
{
namespace trees
{
namespace detail
{

template < typename T >
struct array_as_tree
{
    typedef array_as_tree < T > type;
    typedef typename boost::remove_bounds < T >::type slice_t;
    typedef tree < slice_t > slice_tree_t;

    static const size_t size = sizeof(T) / sizeof(slice_t);

    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        QTreeWidgetItem* parent = 
            new QTreeWidgetItem(QStringList(name));

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

    static inline QStandardItem* create_item(const T& t)
    {
        QStandardItem* parent = new QStandardItem();
        
        // parent->appendColumn(
        //         new QStandardItem(QString("length '%1'").arg(size)));

        for(size_t i=0; i<size; i++)
        {
            QStandardItem* child = slice_tree_t::create_item(t[i]);
            if (child->rowCount() > 0)
            {
                child->setText(QString("[%1]").arg(i));
                parent->appendRow(child);
            }
            else
            {
                QStandardItem* name = new QStandardItem(QString("[%1]").arg(i));
                QList< QStandardItem * > list;
                list << name;
                list << child;

                parent->appendRow(list);
            }
        }

        return parent;
    }
};

template < unsigned int N >
struct array_as_tree< char[N] >
{
    typedef array_as_tree < char[N] > type;
    typedef char T[N];

    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        const std::string value = std::string(name) + ": " + 
            std::string (t, N);
        QTreeWidgetItem* parent =
            new QTreeWidgetItem(QStringList(value.c_str()));
    	return parent;
    }

    static inline QStandardItem* create_item(const T& t)
    {
        const std::string str(t, N);
        return new QStandardItem(str.c_str());
    }
};

template< typename T, 
    unsigned int MAX = CORBASIM_ARRAY_RESUME_CONDITION >
struct array_as_resume
{
    typedef array_as_resume < T > type;
    typedef typename boost::remove_bounds < T >::type slice_t;
    typedef tree < slice_t > slice_tree_t;

    static const size_t size = sizeof(T) / sizeof(slice_t);

    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        std::ostringstream oss;
        oss << name << " (length: " << size << "):";

        size_t i = 0;
        for(; i < size && i < MAX; i++)
            oss << ' ' << t[i];

        if(MAX < size)
            oss << "...";

        return new QTreeWidgetItem(QStringList(oss.str().c_str()));
    }

    // TODO resume
    static inline QStandardItem* create_item(const T& t)
    {
        QStandardItem* parent = new QStandardItem();

        // parent->appendColumn(
        //         new QStandardItem(QString("length '%1'").arg(size)));

        for(size_t i=0; i<size; i++)
        {
            QStandardItem* child = slice_tree_t::create_item(t[i]);
            if (child->rowCount() > 0)
            {
                child->setText(QString("[%1]").arg(i));
                parent->appendRow(child);
            }
            else
            {
                QStandardItem* name = new QStandardItem(QString("[%1]").arg(i));
                QList< QStandardItem * > list;
                list << name;
                list << child;

                parent->appendRow(list);
            }
        }

        return parent;
    }
};

} // detail
} // trees
} // corbasim

#endif // CORBASIM_TREES_ARRAY_HPP

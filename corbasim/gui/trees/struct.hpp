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

#ifndef CORBASIM_TREES_STRUCT_HPP
#define CORBASIM_TREES_STRUCT_HPP

#include <corbasim/gui/trees_fwd.hpp>

namespace corbasim 
{
namespace trees 
{
namespace detail 
{

template< class Struct >
struct create_iterator
{
    const Struct& struct_;
    QTreeWidgetItem * parent_;

    create_iterator(const Struct& s, QTreeWidgetItem * parent) : 
        struct_(s), parent_(parent)
    {}

    template < typename N >
    void operator()(N const& nn)
    {
        // Tipo del campo actual
        typedef typename cs_mpl::type_of_member< Struct, N >::type 
            current_t;

        // Tipo que contiene el nombre del campo actual
        typedef cs_mpl::name_of_member< Struct, N > name_t;

        // Member
        typedef adapted::member< Struct, N::value > member_t;

        // Tree widget asociado al tipo del campo actual
        typedef tree_member < member_t > current_tree_t;

		QTreeWidgetItem* current = current_tree_t::create_tree(
                boost::fusion::at < N >(struct_), name_t::call());

		parent_->addChild(current);
    }
};

template< class Struct >
struct create_item_iterator
{
    const Struct& struct_;
    QStandardItem * parent_;

    create_item_iterator(const Struct& s, QStandardItem * parent) : 
        struct_(s), parent_(parent)
    {}

    template < typename N >
    void operator()(N const& nn)
    {
        // Tipo del campo actual
        typedef typename cs_mpl::type_of_member< Struct, N >::type 
            current_t;

        // Tipo que contiene el nombre del campo actual
        typedef cs_mpl::name_of_member< Struct, N > name_t;

        // Member
        typedef adapted::member< Struct, N::value > member_t;

        // Tree widget asociado al tipo del campo actual
        typedef tree_member < member_t > current_tree_t;

		QStandardItem* current = current_tree_t::create_item(
                boost::fusion::at < N >(struct_));

        if (current->rowCount() > 0)
        {
            current->setText(name_t::call());
            parent_->appendRow(current);
        }
        else
        {
            QStandardItem* name = new QStandardItem(name_t::call());
            QList< QStandardItem * > list;
            list << name;
            list << current;

            parent_->appendRow(list);
        }
    }
};


template < typename T >
struct struct_as_tree
{
    typedef struct_as_tree < T > type;

    static const std::size_t members_count = 
        boost::fusion::result_of::size< T >::value;
    typedef boost::mpl::range_c< size_t, 0, members_count > 
        members_range_t;

    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        QTreeWidgetItem* parent = 
            new QTreeWidgetItem(QStringList(name));

        create_iterator< T > it(t, parent);
        boost::mpl::for_each< members_range_t >(it);

        return parent;
    }

    static inline QStandardItem* create_item(const T& t)
    {
        QStandardItem* parent = new QStandardItem();

        create_item_iterator< T > it(t, parent);
        boost::mpl::for_each< members_range_t >(it);

        return parent;
    }
};

} // namespace detail
} // namespace trees
} // namespace corbasim

#endif /* CORBASIM_TREES_STRUCT_HPP */


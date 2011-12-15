// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * union.hpp
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

#ifndef CORBASIM_TREES_UNION_HPP
#define CORBASIM_TREES_UNION_HPP

#include <corbasim/gui/trees_fwd.hpp>

namespace corbasim 
{
namespace trees 
{
namespace detail 
{
namespace iterator
{

// Iteracion sobre una estructura
template < typename S, typename N >
struct UnionImpl
{
    // Tipo del campo actual
    typedef typename cs_mpl::type_of_member< S, N >::type current_t;

    // Valor de N en la siguiente iteracion
    typedef typename boost::mpl::next < N >::type next_t;

    // Tipo que contiene el nombre del campo actual
    typedef cs_mpl::name_of_member< S, N > name_t;

    // Member
    typedef adapted::member< S, N::value > member_t;

    // Tree widget asociado al tipo del campo actual
    typedef tree_member < member_t > current_tree_t;

	static inline void create_tree(QTreeWidgetItem* parent, const S& s,
            int pos = 0)
	{
        if (pos == N::value - 1)
        {
            QTreeWidgetItem* current = current_tree_t::create_tree(
                    boost::fusion::at < N >(s), name_t::call());

            parent->addChild(current);
        }
        else
        {
            // Siguiente iteración
    		UnionImpl< S, next_t >::create_tree(parent, s, pos++);
        }
	}
};

// Fin de la iteracion sobre estructuras.
template < typename S >
struct UnionImpl < S, typename cs_mpl::number_of_members < S >::type >
{
	static inline void create_tree(QTreeWidgetItem* parent, const S& s,
            int pos = 0)
	{
		// Nada que hacer
	}
};

// Iterador sobre una estructura. Template fachada.
template < typename S >
struct Union: UnionImpl < S, boost::mpl::int_ < 1 > >
{
};

} // iterator


template < typename T >
struct union_as_tree
{
    typedef union_as_tree < T > type;

    typedef adapted::is_union< T > adapted_t;

    typedef typename cs_mpl::number_of_members< T >::type size_type; 

    typedef typename 
        cs_mpl::type_of_member< T, boost::mpl::int_< 0 > >::type 
        discriminator_t;

    static inline int disc_to_pos(discriminator_t d)
    {
        for (int i = 0; i < size_type::value; i++) 
        {
            if (adapted_t::discriminators()[i] == d)
                return i;
        }

        // Invalid value
        return size_type::value;
    }

    typedef tree < discriminator_t > discriminator_tree_t;

    static inline QTreeWidgetItem* create_tree(const T& t, 
            const char* name)
    {
        QTreeWidgetItem* parent = new QTreeWidgetItem(QStringList(name));

        int pos = disc_to_pos(t._d());

        QTreeWidgetItem* current = discriminator_tree_t::create_tree(
                    t._d(), "discriminator");

        parent->addChild(current);
        
        if (pos < size_type::value)
            iterator::Union< T >::create_tree(parent, t, pos);

        return parent;
    }
};

} // namespace detail
} // namespace trees
} // namespace corbasim

#endif /* CORBASIM_TREES_UNION_HPP */


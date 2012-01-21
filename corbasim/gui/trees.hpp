// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * trees.hpp
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

#ifndef CORBASIM_TREES_HPP
#define CORBASIM_TREES_HPP

#include <corbasim/core/config.hpp>

#include <corbasim/gui/trees_fwd.hpp>
#include <corbasim/gui/trees/struct.hpp>
#include <corbasim/gui/trees/primitive.hpp>
#include <corbasim/gui/trees/array.hpp>
#include <corbasim/gui/trees/enum.hpp>
#include <corbasim/gui/trees/string.hpp>
#include <corbasim/gui/trees/sequence.hpp>
#include <corbasim/gui/trees/objref.hpp>
#include <corbasim/gui/trees/union.hpp>

namespace corbasim 
{
namespace trees 
{
namespace detail 
{

template< typename T >
struct unsupported_type
{
    static inline QTreeWidgetItem* create_tree(const T& t,
            const char * name)
    {
        return new QTreeWidgetItem(QStringList(
                    QString(name) + ": unsupported type!"));
    }

    static inline QStandardItem* create_item(const T& t)
    {
        return new QStandardItem("Unsupported type!");
    }
};

template< typename T >
struct default_primitive_tree : public arithmetic_as_item< T >
{
};

template< typename T >
struct calculate_default_array_tree
{
    typedef typename boost::remove_bounds< T >::type slice_t;

    typedef typename 
        // if
        cs_mpl::eval_if_identity< boost::is_arithmetic< slice_t >, 
            array_as_resume< T >,
        // else
            boost::mpl::identity< array_as_tree< T > >
        >::type type;
};

template< typename T >
struct default_array_tree : public calculate_default_array_tree< T >::type
{
};

template< typename T >
struct default_enum_tree : public enum_as_item< T >
{
};

template< typename T >
struct default_string_tree : public string_as_item< T >
{
};

template< typename T >
struct default_struct_tree : public struct_as_tree< T >
{
};

template< typename T >
struct default_union_tree : public union_as_tree< T >
{
};

template< typename T >
struct default_objrefvar_tree : public detail::objref_tree< T >
{
};

template< typename T >
struct calculate_default_sequence_tree
{
    typedef typename adapted::is_corbaseq < T >::slice_type slice_t;

    typedef typename 
        // if
        cs_mpl::eval_if_identity< boost::is_arithmetic< slice_t >, 
            sequence_as_resume< T >,
        // else
            boost::mpl::identity< sequence_as_tree< T > >
        >::type type;
};

template< typename T >
struct default_sequence_tree : 
    public calculate_default_sequence_tree< T >::type
{
};

template< typename T >
struct calculate_default_tree
{
    typedef typename 
        // if
        cs_mpl::eval_if_identity< boost::is_arithmetic< T >, 
            default_primitive_tree< T >,
        // else if
        cs_mpl::eval_if_identity< boost::is_array< T >, 
            default_array_tree< T >,
        // else if
        cs_mpl::eval_if_identity< boost::is_enum< T >, 
            default_enum_tree< T >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_string< T >, 
            default_string_tree< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_corbaseq< T >, 
            default_sequence_tree< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_union< T >, 
            default_union_tree< T >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_struct< T >, 
            default_struct_tree< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_objrefvar< T >, 
            default_objrefvar_tree< T >,
        // else
            boost::mpl::identity< unsupported_type< T > >
        > > > > > > > >::type type;
};

} // namespace detail

/**
 * @brief Helper para crear QTreeWidgetItem que representan es valor de
 *        un elemento de tipo T.
 *
 * Para cada tipo T tree< T > ha de cumplir los siguientes requisitos:
 *
 * @code
 * template < >
 * struct tree< T >
 * {
 *     static inline QTreeWidgetItem* create_tree(const T& t, 
 *         const char * name)
 *     {
 *         // 1. Método create_tree
 *     }
 * };
 * @endcode
 *
 * @tparam T El tipo.
 */
template < typename T >
struct tree: public detail::calculate_default_tree < T >::type
{
};

template < typename Member >
struct tree_member :
    public tree< typename cs_mpl::type_of_member< typename Member::type, 
        typename Member::index_type >::type >
{
};

} // namespace trees
} // namespace corbasim

#endif /* CORBASIM_TREES_HPP */


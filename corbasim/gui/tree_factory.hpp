// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * tree_factory.hpp
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

#ifndef CORBASIM_GUI_TREE_FACTORY_HPP
#define CORBASIM_GUI_TREE_FACTORY_HPP

#include <map>
#include <boost/shared_ptr.hpp>
#include <corbasim/event.hpp>
#include <corbasim/adapted.hpp>
#include <corbasim/gui/trees_fwd.hpp>
#include <corbasim/core/inserter.hpp>

namespace corbasim 
{
namespace gui 
{

struct tree_factory_base
{
    virtual QTreeWidgetItem * create_tree(event::event* ev) = 0;
    virtual QStandardItem * create_item(event::event* ev) = 0;
    
    virtual ~tree_factory_base();
};

typedef boost::shared_ptr< tree_factory_base > tree_factory_ptr;

template < typename Value >
struct operation_tree_factory : public tree_factory_base
{
    QTreeWidgetItem * create_tree(event::event* ev)
    {
        return create_tree_impl(ev);
    }

    QStandardItem * create_item(event::event* ev)
    {
        return create_item_impl(ev);
    }

    static inline QTreeWidgetItem * create_tree_impl(event::event* ev)
    {
        typedef event::request_impl< Value > request_t;
        typedef event::response_impl< Value > response_t;
        typedef trees::tree< Value > tree_t; 
        typedef adapted::name< Value > name_t;

        QTreeWidgetItem * item = NULL;

        switch (ev->get_type())
        {
        case event::REQUEST:
        {
            request_t * reqi = static_cast< request_t * >(ev);
            item = tree_t::create_tree(reqi->m_values, name_t::call());
            item->setText(0, QString("Request ") + item->text(0));
            break;
        }
        case event::RESPONSE:
        {
            response_t * reqi = static_cast< response_t * >(ev);
            item = tree_t::create_tree(reqi->m_values, name_t::call());
            item->setText(0, QString("Response ") + item->text(0));
            break;
        }
        default:
            break;
        }

        return item;
    }

    static inline QStandardItem * create_item_impl(event::event* ev)
    {
        typedef event::request_impl< Value > request_t;
        typedef event::response_impl< Value > response_t;
        typedef trees::tree< Value > tree_t; 
        typedef adapted::name< Value > name_t;

        QStandardItem * item = NULL;

        switch (ev->get_type())
        {
        case event::REQUEST:
        {
            request_t * reqi = static_cast< request_t * >(ev);
            item = tree_t::create_item(reqi->m_values);
            item->setText(name_t::call());
            break;
        }
        case event::RESPONSE:
        {
            response_t * reqi = static_cast< response_t * >(ev);
            item = tree_t::create_item(reqi->m_values);
            item->setText(name_t::call());
            break;
        }
        default:
            break;
        }

        return item;
    }
};

struct tree_factory_interface : public tree_factory_base
{
    QTreeWidgetItem * create_tree(event::event* ev);

    // Data
    typedef std::map< tag_t, tree_factory_ptr > factories_t;
    factories_t m_factories;
};

template < typename Interface >
struct tree_factory_impl : public tree_factory_interface
{
    tree_factory_impl()
    {
        typedef typename adapted::interface< Interface >::_op_list 
            operations_t;

        typedef core::impl::inserter< tree_factory_impl > inserter_t;
        cs_mpl::for_each_list< operations_t >(inserter_t(this));
    }

    template < typename Value >
    inline void append()
    {
        m_factories.insert(std::make_pair(
                    tag< Value >::value(),
                tree_factory_ptr(
                    new operation_tree_factory< Value >())));
    }
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_TREE_FACTORY_HPP */


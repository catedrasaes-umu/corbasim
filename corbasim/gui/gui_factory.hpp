// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * gui_factory.hpp
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

#ifndef CORBASIM_GUI_GUI_FACTORY_HPP
#define CORBASIM_GUI_GUI_FACTORY_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/mpl.hpp>
#include <corbasim/core/inserter.hpp>
#include <corbasim/core/request_serializer.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/gui/tree_factory.hpp>

namespace corbasim 
{
namespace gui 
{

template< typename Value >
struct operation_factory : public operation_factory_base
{
    typedef dialogs::input< Value > input_t;

    dialogs::input_base * create_input() const
    {
        return new input_t;
    }

    const char * get_name() const
    {
        return adapted::name< Value >::call();
    }

    static inline operation_factory * get_instance()
    {
        static boost::shared_ptr< operation_factory > _instance(
                new operation_factory);
        return _instance.get();
    }

    typedef operation_tree_factory< Value > tree_factory_t;

    QTreeWidgetItem * create_tree(event::event* ev) const
    {
        return tree_factory_t::create_tree_impl(ev);
    }
};

template< typename Interface >
struct gui_factory : public gui_factory_base
{
    typedef typename  adapted::interface< Interface >::_op_list 
        operations_t;

    gui_factory()
    {
        typedef core::impl::inserter< gui_factory > inserter_t;
        cs_mpl::for_each< operations_t >(inserter_t(this));
    }

    core::request_serializer_base * get_serializer() const
    {
        return core::request_serializer< Interface >::get_instance();
    }

    template< typename Value >
    void append()
    {
        typedef operation_factory< Value > factory_t;

        insert_factory(
                adapted::name< Value >::call(),
                tag< Value >::value(),
                factory_t::get_instance());
    }

    static inline gui_factory * get_instance()
    {
        static boost::shared_ptr< gui_factory > _instance(new gui_factory);
        return _instance.get();
    }
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_GUI_FACTORY_HPP */


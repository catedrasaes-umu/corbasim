// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ModelNode.hpp
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

#ifndef CORBASIM_REFLECTIVE_GUI_MODELNODE_HPP
#define CORBASIM_REFLECTIVE_GUI_MODELNODE_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/core/reflective_fwd.hpp>

namespace corbasim 
{
namespace reflective_gui 
{

struct Node;
typedef boost::shared_ptr< Node > Node_ptr;

struct Node
{
    core::reflective_base const * reflective;
    core::holder holder;

    bool initialized;
    std::vector< Node_ptr > children;

    inline Node(core::reflective_base const * r,
            core::holder h) :
        m_reflective(r), holder(h), initialized(false)
    {
    }

    inline void initialize()
    {
        if (reflective->is_repeated())
        {
            const unsigned int count = reflective->get_length(holder);
            children.reserve(count);

            core::reflective_base const * slice =
                reflective->get_slice();

            for (unsigned int i = 0; i < count; i++) 
            {
                Node_ptr child(slice, 
                        reflective->get_child_value(holder, i));

                children.push_back(child);
            }
        }
        else if(reflective->get_type() == core::TYPE_STRUCT)
        {
            const unsigned int count = reflective->get_children_count();
            children.reserve(count);

            for (unsigned int i = 0; i < count; i++) 
            {
                Node_ptr child(reflective->get_child(i), 
                        reflective->get_child_value(holder, i));

                children.push_back(child);
            }
        }

        initialized = true;
    }
};

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_MODELNODE_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ModelNode.cpp
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

#include "ModelNode.hpp"

using namespace corbasim::reflective_gui;

Node::Node(corbasim::core::reflective_base const * r,
        corbasim::core::holder h, Node const * p, unsigned int idx) :
    reflective(r), holder(h), parent(p), index(idx), initialized(false)
{
}

void Node::initialize()
{
    if (reflective->is_repeated())
    {
        const unsigned int count = reflective->get_length(holder);
        children.reserve(count);

        core::reflective_base const * slice =
            reflective->get_slice();

        for (unsigned int i = 0; i < count; i++) 
        {
            Node_ptr child(new Node(slice, 
                    reflective->get_child_value(holder, i), this, i));

            children.push_back(child);
        }
    }
    else if(reflective->get_type() == core::TYPE_STRUCT)
    {
        const unsigned int count = reflective->get_children_count();
        children.reserve(count);

        for (unsigned int i = 0; i < count; i++) 
        {
            Node_ptr child(new Node(reflective->get_child(i), 
                    reflective->get_child_value(holder, i), this, i));

            children.push_back(child);
        }
    }
    else if(reflective->get_type() == core::TYPE_UNION)
    {
        children.clear();

        // discriminator
        Node_ptr child(new Node(reflective->get_child(0), 
                reflective->get_child_value(holder, 0), this, 0));
        children.push_back(child);

        unsigned int idx = 0;
        if ((idx = reflective->get_length(holder)) > 0)
        {
            Node_ptr child(new Node(reflective->get_child(idx), 
                    reflective->get_child_value(holder, idx), this, idx));

            children.push_back(child);
        }
    }

    initialized = true;
}

void Node::check_for_initialized()
{
    if (!initialized)
        initialize();
}


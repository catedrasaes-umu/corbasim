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

#ifndef CORBASIM_GUI_MODELNODE_HPP
#define CORBASIM_GUI_MODELNODE_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/gui/types.hpp>


namespace corbasim 
{
namespace gui 
{

struct DescriptorNode;
typedef boost::shared_ptr< DescriptorNode > DescriptorNode_ptr;

struct Node;
typedef boost::shared_ptr< Node > Node_ptr;

struct MetaNode;
typedef boost::shared_ptr< MetaNode > MetaNode_ptr;

struct InstanceNode
{
    Objref_ptr instance;
    InterfaceDescriptor_ptr reflective;

    bool initialized;
    std::vector< DescriptorNode_ptr > children;

    InstanceNode(Objref_ptr o);

    void initialize();

    void check_for_initialized();

    void reset();
};

struct DescriptorNode
{
    TypeDescriptor_ptr reflective;

    InstanceNode * instance;

    DescriptorNode * parent;
    unsigned int index;

    bool initialized;
    std::vector< DescriptorNode_ptr > children;

    DescriptorNode(TypeDescriptor_ptr r,
            InstanceNode * i = 0,
            DescriptorNode * p = 0, 
            unsigned int idx = 0);

    void initialize();

    void check_for_initialized();

    void reset();
};

struct Node
{
    TypeDescriptor_ptr reflective;
    core::holder holder;

    Node * parent;
    unsigned int index;

    bool initialized;
    std::vector< Node_ptr > children;

    Node(TypeDescriptor_ptr r,
            core::holder h, Node * p = 0, 
            unsigned int idx = 0);

    void initialize();

    void check_for_initialized();

    void reset();
};

struct MetaNode
{
    TypeDescriptor_ptr reflective;

    MetaNode * parent;
    unsigned int index;

    bool initialized;
    std::vector< MetaNode_ptr > children;
    std::vector< Node_ptr > brothers;

    MetaNode(TypeDescriptor_ptr r,
            MetaNode * p = 0, 
            unsigned int idx = 0);

    void initialize();

    void check_for_initialized();

    void reset();
};


} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_MODELNODE_HPP */


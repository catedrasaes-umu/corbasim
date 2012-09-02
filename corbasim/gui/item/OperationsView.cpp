// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * OperationsView.cpp
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

#include "OperationsView.hpp"
#include <corbasim/gui/item/InstanceModel.hpp>

using namespace corbasim::gui;

// View
OperationsView::OperationsView(QWidget * parent) :
    QTreeView(parent)
{
    connect(this, SIGNAL(doubleClicked(const QModelIndex&)),
        this, SLOT(clicked(const QModelIndex&)));
}

OperationsView::~OperationsView()
{
}

void OperationsView::clicked(const QModelIndex& index)
{
    InstanceModel * src = dynamic_cast< InstanceModel * >(model());

    if (src)
    {
        Objref_ptr instance = src->getInstance(index);

        if (src->isInstanceNode(index))
        {
            emit selectedInstance(instance);
        }
        else if (src->isOperationNode(index))
        {
            QList< int > list;
            list << index.row();

            OperationDescriptor_ptr op = 
                instance->interface()->get_reflective_by_index(index.row());

            emit selectedItem(instance, op, list);

            emit selectedOperation(instance, op);
        }
        else
        {
            QList< int > list;

            QModelIndex current = index;
            while(current.parent().isValid())
            {
                list.push_front(current.row());
                current = current.parent();
            }

            OperationDescriptor_ptr op = 
                instance->interface()->get_reflective_by_index(list.front());

            emit selectedItem(instance, op, list);
        }
    }
}


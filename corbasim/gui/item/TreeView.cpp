// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TreeView.cpp
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

#include "TreeView.hpp"

using namespace corbasim::gui;

TreeView::TreeView(QWidget * parent) :
    QTreeView(parent), m_autoScrollToItem(true)
{
}

TreeView::~TreeView()
{
}

bool TreeView::autoScrollToItem() const
{
    return m_autoScrollToItem;
}

void TreeView::setAutoScrollToItem(bool value)
{
    m_autoScrollToItem = value;
}

void TreeView::setModel(QAbstractItemModel * model)
{
    QAbstractItemModel * oldModel = QTreeView::model();

    if (oldModel)
    {
        disconnect(oldModel, SIGNAL(rowsInserted(const QModelIndex&, int, int)),
            this, SLOT(scrollToItem(const QModelIndex&, int, int)));
    }

    QTreeView::setModel(model);

    if (model)
    {
        connect(model, SIGNAL(rowsInserted(const QModelIndex&, int, int)),
            this, SLOT(scrollToItem(const QModelIndex&, int, int)));
    }
}

void TreeView::scrollToItem(const QModelIndex& parent, int start, int end)
{
    if (model() && m_autoScrollToItem)
    {
        const QModelIndex item = model()->index(start, 0, parent);
        scrollTo(item);
    }
}



// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectivePlotTool.cpp
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

#include "ReflectivePlotTool.hpp"
#include <corbasim/qt/SortableGroup.hpp>
#include <QHBoxLayout>
#include <QTreeView>

using namespace corbasim::qwt;

ReflectivePlotTool::ReflectivePlotTool(QWidget * parent) :
    QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout(this);

    // TODO split

    // Model view
    QTreeView * view = new QTreeView(this);
    layout->addWidget(view);

    // Plots
    m_group = new qt::SortableGroup(this);
    layout->addWidget(m_group);

    setLayout(layout);
}

ReflectivePlotTool::~ReflectivePlotTool()
{
}


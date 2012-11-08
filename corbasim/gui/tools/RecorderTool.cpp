// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RecorderTool.cpp
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

#include "RecorderTool.hpp"
#include <corbasim/gui/utils.hpp>
#include <corbasim/json/reflective.hpp>
#include <QHBoxLayout>
#include <QTreeView>

using namespace corbasim::gui;

RecorderTool::RecorderTool(QWidget * parent) :
    AbstractTool(parent)
{
    QHBoxLayout * layout = new QHBoxLayout(this);

    // Model view
    QTreeView * view = new QTreeView(this);
    // TODO view->setModel(&m_model);
    layout->addWidget(view);
    view->setMaximumWidth(300);
    view->setColumnWidth(0, 210);

    setLayout(layout);

    setMinimumSize(650, 400);
}

RecorderTool::~RecorderTool()
{
}

void RecorderTool::registerInstance(Objref_ptr object)
{
}

void RecorderTool::unregisterInstance(ObjectId id)
{
}
void RecorderTool::save(QVariant& settings)
{
}

void RecorderTool::load(const QVariant& settings)
{
}


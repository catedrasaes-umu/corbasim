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

ReflectivePlot::ReflectivePlot(QWidget * parent) :
    SimplePlot("TODO", parent)
{
}

ReflectivePlot::~ReflectivePlot()
{
}

ReflectivePlotTool::ReflectivePlotTool(QWidget * parent) :
    QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout(this);

    // TODO splitter

    // Model view
    QTreeView * view = new QTreeView(this);
    view->setModel(&m_model);
    layout->addWidget(view);
    view->setMaximumWidth(300);

    // Plots
    m_group = new qt::SortableGroup(this);
    layout->addWidget(m_group);

    setLayout(layout);

    // connect model signals 
    QObject::connect(&m_model, 
            SIGNAL(createPlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)),
            this,
            SLOT(createPlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)));
    QObject::connect(&m_model, 
            SIGNAL(deletePlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)),
            this,
            SLOT(deletePlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)));
}

ReflectivePlotTool::~ReflectivePlotTool()
{
}

void ReflectivePlotTool::registerInstance(const QString& name,
        core::interface_reflective_base const * reflective)
{
    m_model.registerInstance(name, reflective);
}

void ReflectivePlotTool::unregisterInstance(const QString& name)
{
    m_model.unregisterInstance(name);
}

void ReflectivePlotTool::createPlot(const QString& id, 
        core::interface_reflective_base const * reflective,
        const QList< int >& path)
{
    m_group->appendWidget(new ReflectivePlot(this));
}

void ReflectivePlotTool::deletePlot(const QString& id, 
        core::interface_reflective_base const * reflective,
        const QList< int >& path)
{
    // TODO
}


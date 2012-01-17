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

ReflectivePlot::ReflectivePlot(
        core::operation_reflective_base const * reflective,
        const QList< int >& path, QWidget * parent) :
    SimplePlot("TODO", parent), m_reflective(reflective), m_path(path)
{
}

ReflectivePlot::~ReflectivePlot()
{
}

corbasim::core::operation_reflective_base const * 
ReflectivePlot::getReflective() const
{
    return m_reflective;
}

void ReflectivePlot::process(core::holder& value)
{
    core::reflective_base const * reflec = m_reflective;

    int size = m_path.size();

    core::holder tmp = value;

    for (int i = 1; i < size; i++) 
    {
        if (i == size - 2 && reflec->is_repeated())
            break;

        if (reflec->get_type() == core::TYPE_STRUCT)
        {
            tmp = reflec->get_child_value(tmp, m_path[i]);
            reflec = reflec->get_child(m_path[i]);
        }
        else if(reflec->is_repeated())
        {
            tmp = reflec->get_child_value(tmp, m_path[i]);
            reflec = reflec->get_slice();
        }
    }

    if (reflec->is_primitive())
    {
        append(reflec->to_double(tmp));
    }
    else if(reflec->is_repeated())
    {
        QVector< double > values;
        // TODO 
        append(values);
    }
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

void ReflectivePlotTool::processRequest(const QString& id, 
        corbasim::event::request_ptr req)
{
    QList< ReflectivePlot * >& list = 
        m_map[std::make_pair(id, req->get_tag())];

    int count = list.size();
    for (int i = 0; i < count; i++) 
    {
        core::holder value = list[i]->getReflective()->get_holder(req);
        list[i]->process(value);
    }
}

void ReflectivePlotTool::createPlot(const QString& id, 
        core::interface_reflective_base const * reflective,
        const QList< int >& path)
{
    core::operation_reflective_base const * op =
        reflective->get_reflective_by_index(path.front());

    ReflectivePlot * plot = new ReflectivePlot(op, path, this);

    m_map[std::make_pair(id, op->get_tag())].push_back(plot);

    m_group->appendWidget(plot);
}

void ReflectivePlotTool::deletePlot(const QString& id, 
        core::interface_reflective_base const * reflective,
        const QList< int >& path)
{
    // TODO
}


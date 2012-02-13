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
#include <corbasim/reflective_gui/utils.hpp>
#include <QHBoxLayout>
#include <QTreeView>

#include <iostream>

using namespace corbasim::qwt;

PlotProcessor::PlotProcessor(const QString& id,
        const reflective_gui::ReflectivePath_t path) :
    reflective_gui::RequestProcessor(id, path)
{

}

PlotProcessor::~PlotProcessor()
{
}

void PlotProcessor::process(event::request_ptr req, 
        core::reflective_base const * ref,
        core::holder hold)
{
    emit append(req, ref, hold);
}

// Reflective plot

ReflectivePlot::ReflectivePlot(const QString& id,
        core::operation_reflective_base const * reflective,
        const QList< int >& path, 
        QWidget * parent) :
    SimplePlot(parent), m_id(id), m_reflective(reflective), m_path(path)
{
    PlotProcessor * processor =
        new PlotProcessor(m_id, m_path);

    m_processor.reset(processor);

    // connect signal
    QObject::connect(processor,
            SIGNAL(append(corbasim::event::request_ptr,
                    const corbasim::core::reflective_base *,
                    corbasim::core::holder)),
            this,
            SLOT(appendValue(corbasim::event::request_ptr,
                    const corbasim::core::reflective_base *,
                    corbasim::core::holder)));
}

ReflectivePlot::~ReflectivePlot()
{
}

corbasim::core::operation_reflective_base const * 
ReflectivePlot::getReflective() const
{
    return m_reflective;
}

void ReflectivePlot::appendValue(corbasim::event::request_ptr req, 
        const corbasim::core::reflective_base * reflec,
        corbasim::core::holder hold)
{
    if (reflec->is_primitive())
    {
        append(reflec->to_double(hold));
    }
    else if(reflec->is_repeated() && 
            reflec->get_slice()->is_primitive())
    {
        QVector< double > values;
        
        const unsigned int length = reflec->get_length(hold);
        core::reflective_base const * slice = reflec->get_slice();

        for (unsigned int i = 0; i < length; i++) 
        {
            const core::holder h = reflec->get_child_value(hold, i);
            values.push_back(slice->to_double(h));
        }

        if (!values.isEmpty())
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
    view->setColumnWidth(0, 210);

    // Plots
    m_group = new qt::SortableGroup(this);
    m_group->setDelete(false);
    layout->addWidget(m_group);

    setLayout(layout);

    // widget signals
    QObject::connect(m_group, 
            SIGNAL(deleteRequested(corbasim::qt::SortableGroupItem *)),
            this, 
            SLOT(deleteRequested(corbasim::qt::SortableGroupItem *)));

    // connect model signals 
    QObject::connect(&m_model, 
            SIGNAL(createdPlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)),
            this,
            SLOT(createPlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)));
    QObject::connect(&m_model, 
            SIGNAL(deletedPlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)),
            this,
            SLOT(deletePlot(const QString&,
                    core::interface_reflective_base const *,
                    const QList< int >&)));
    
    // connect with the processor
    QObject::connect(this, 
            SIGNAL(addProcessor(
                    corbasim::reflective_gui::RequestProcessor_ptr)),
            reflective_gui::getDefaultInputRequestController(),
            SLOT(addProcessor(
                    corbasim::reflective_gui::RequestProcessor_ptr)));
    QObject::connect(this, 
            SIGNAL(removeProcessor(
                    corbasim::reflective_gui::RequestProcessor_ptr)),
            reflective_gui::getDefaultInputRequestController(),
            SLOT(removeProcessor(
                    corbasim::reflective_gui::RequestProcessor_ptr)));

    setMinimumSize(650, 400);
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

    // Maps
    map_t::iterator it = m_map.begin();
    for(; it != m_map.end(); it++)
    {
        if (name == it->first.first)
        {
            m_map.erase(it);

            for (int i = 0; i < it->second.size(); i++) 
            {
                m_inverse_map.erase(it->second[i]);
            }
        }
    }
}

void ReflectivePlotTool::createPlot(const QString& id, 
        core::interface_reflective_base const * reflective,
        const QList< int >& path)
{
    core::operation_reflective_base const * op =
        reflective->get_reflective_by_index(path.front());

    ReflectivePlot * plot = new ReflectivePlot(id, op, path);

    const key_t key(id, op->get_tag());
    m_map[key].push_back(plot);
    m_inverse_map[plot] = key;

    qt::SortableGroupItem * item = 
        new qt::SortableGroupItem(plot, m_group);

    const QString title(reflective_gui::getFieldName(op, path));
    item->setTitle(id + "." + title);

    m_group->appendItem(item);
    
    // Notify to the processor
    emit addProcessor(plot->getProcessor());
}

void ReflectivePlotTool::deletePlot(const QString& id, 
        core::interface_reflective_base const * reflective,
        const QList< int >& path)
{
    core::operation_reflective_base const * op =
        reflective->get_reflective_by_index(path.front());

    const key_t key(id, op->get_tag());
    QList< ReflectivePlot * >& list = m_map[key];

    for (int i = 0; i < list.size(); i++) 
    {
        ReflectivePlot * plot = list[i];
        if (plot->getPath() == path)
        {
            list.removeAt(i);
            m_inverse_map.erase(plot);
            m_group->deleteItem(
                    qobject_cast< qt::SortableGroupItem * >
                        (plot->parent()));

            // Notify to the processor
            emit removeProcessor(plot->getProcessor());
            break;
        }
    }
}

void ReflectivePlotTool::deleteRequested(qt::SortableGroupItem* item)
{
    ReflectivePlot * plot = qobject_cast< ReflectivePlot * >(item->getWidget());

    if (plot)
    {
        inverse_map_t::iterator it = m_inverse_map.find(plot);

        if (it != m_inverse_map.end())
        {
            const key_t key(it->second);
            m_map[key].removeAll(plot);

            // notify to model
            m_model.deletePlot(key.first, plot->getPath());

            m_inverse_map.erase(it);
        }
    }
    m_group->deleteItem(item);
}

extern "C" {

corbasim::qwt::ReflectivePlotTool * createReflectivePlotTool(
        QWidget * parent)
{
    return new corbasim::qwt::ReflectivePlotTool(parent);
}

void registerInstanceInPlotTool(QWidget * tool, 
        const QString& id, 
        corbasim::core::interface_reflective_base const * factory)
{
    static_cast< corbasim::qwt::ReflectivePlotTool * >(tool)->
        registerInstance(id, factory);
}

} // extern C


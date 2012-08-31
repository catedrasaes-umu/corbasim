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
#include <corbasim/gui/utils.hpp>
#include <QHBoxLayout>
#include <QTreeView>

#include <iostream>

using namespace corbasim::qwt;

PlotProcessor::PlotProcessor(Objref_ptr objref,
        const QList< int >& path) :
    RequestProcessor(objref, path)
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

ReflectivePlot::ReflectivePlot(Objref_ptr objref,
        OperationDescriptor_ptr reflective,
        const QList< int >& path, 
        QWidget * parent) :
    AbstractInputItem(objref, reflective, path, parent)
{
    PlotProcessor * processor =
        new PlotProcessor(objref, path);

    m_processor.reset(processor);

    // connect signal
    connect(processor,
            SIGNAL(append(Request_ptr,
                    TypeDescriptor_ptr,
                    Holder)),
            this,
            SLOT(appendValue(Request_ptr,
                    TypeDescriptor_ptr,
                    iHolder)));

    // widget
    QVBoxLayout * layout = new QVBoxLayout();
    m_plot = new SimplePlot(this);
    layout->addWidget(m_plot);
    layout->setMargin(0);

    // TODO start button

    setLayout(layout);
}

ReflectivePlot::~ReflectivePlot()
{
}

void ReflectivePlot::appendValue(Request_ptr req, 
        TypeDescriptor_ptr reflec,
        Holder hold)
{
    if (reflec->is_primitive())
    {
        m_plot->append(reflec->to_double(hold));
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
            m_plot->append(values);
    }
}

ReflectivePlotTool::ReflectivePlotTool(QWidget * parent) :
    AbstractInputTool(parent)
{
}

ReflectivePlotTool::~ReflectivePlotTool()
{
}

AbstractInputItem * ReflectivePlotTool::createItem(
        Objref_ptr objref, 
        OperationDescriptor_ptr reflective,
        const QList< int >& path)
{
    return new ReflectivePlot(objref, reflective, path); 
}

ParametersModel * ReflectivePlotTool::createModel() const
{
    new PlotModel();
}

extern "C" 
{

    corbasim::qwt::ReflectivePlotTool * createReflectivePlotTool(
            QWidget * parent)
    {
        return new corbasim::qwt::ReflectivePlotTool(parent);
    }

} // extern C



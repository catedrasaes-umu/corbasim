// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ValueViewerTool.cpp
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

#include "ValueViewerTool.hpp"
#include <corbasim/gui/proc/HolderEmitter.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/ReflectiveGUI.hpp>

using namespace corbasim::gui;

// ValueViewer

ValueViewer::ValueViewer(Objref_ptr objref,
        OperationDescriptor_ptr reflective,
        const QList< int >& path,
        QWidget * parent) :
    AbstractInputItem(objref, reflective, path, parent)
{
    TypeDescriptor_ptr descriptor =
        followPath(reflective, path);

    QGridLayout * grid = new QGridLayout();

    // Timestamp
    m_date = new QDateTimeEdit();
    m_date->setReadOnly(true);
    grid->addWidget(new QLabel("Timestamp"), 0, 0);
    grid->addWidget(m_date, 0, 1);

    // Value
    QGroupBox * box = new QGroupBox("Value");
    QVBoxLayout * boxLayout = new QVBoxLayout();

    m_widget = createSimpleWidget(descriptor, NULL);
    ReflectiveWidgetBase * refWidget =
        dynamic_cast< ReflectiveWidgetBase * >(m_widget);

    if (refWidget)
    {
        refWidget->_setReadOnly(true);
    }

    boxLayout->addWidget(m_widget);
    box->setLayout(boxLayout);
    grid->addWidget(box, 1, 0, 1, 2);

    setLayout(grid);

    // Processor
    HolderEmitter * processor =
        new HolderEmitter(objref, path);

    m_processor.reset(processor);

    // connect signal
    connect(processor,
            SIGNAL(append(Request_ptr,
                    TypeDescriptor_ptr,
                    Holder)),
            this,
            SLOT(appendValue(Request_ptr,
                    TypeDescriptor_ptr,
                    Holder)));
}

ValueViewer::~ValueViewer()
{
}

void ValueViewer::start()
{
    emit addProcessor(m_processor);
}

void ValueViewer::appendValue(Request_ptr req,
        TypeDescriptor_ptr reflec,
        Holder hold)
{
    m_date->setDateTime(QDateTime::currentDateTime());

    ReflectiveWidgetBase * w =
        dynamic_cast< ReflectiveWidgetBase * >(m_widget);

    if (w)
        w->fromHolder(hold);
}

//
//
// Dump Tool
//
//

ValueViewerTool::ValueViewerTool(QWidget * parent) :
    AbstractInputTool(parent)
{
}

ValueViewerTool::~ValueViewerTool()
{
}

AbstractInputItem * ValueViewerTool::createItem(
        Objref_ptr objref,
        OperationDescriptor_ptr reflective,
        const QList< int >& path)
{
    return new ValueViewer(objref, reflective, path);
}

// Save and load

void ValueViewer::save(QVariant& settings)
{
    QVariantMap map;

    settings = map;
}

void ValueViewer::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();
}


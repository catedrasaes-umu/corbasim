// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AbstractInputTool.cpp
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

#include "AbstractInputTool.hpp"
#include <corbasim/qt/SortableGroup.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/core/file_format_helper.hpp>
#include <QHBoxLayout>
#include <QTreeView>

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace corbasim::gui;

// Reflective plot

AbstractInputItem::AbstractInputItem(Objref_ptr objref,
        OperationDescriptor_ptr reflective,
        const QList< int >& path, 
        QWidget * parent) :
    QWidget(parent), m_objref(objref), 
    m_reflective(reflective), m_path(path)
{
}

AbstractInputItem::~AbstractInputItem()
{
}

OperationDescriptor_ptr AbstractInputItem::getReflective() const
{
    return m_reflective;
}

void AbstractInputItem::start()
{
}

void AbstractInputItem::reset()
{
}

//
//
// Abstract Input Tool
//
//

AbstractInputTool::AbstractInputTool(QWidget * parent) :
    QWidget(parent), m_model(NULL)
{
    QHBoxLayout * layout = new QHBoxLayout(this);

    // Model view
    m_view = new QTreeView(this);
    layout->addWidget(m_view);
    m_view->setMaximumWidth(300);
    m_view->setColumnWidth(0, 210);

    // Plots
    m_group = new qt::SortableGroup(this);
    m_group->setDelete(false);
    layout->addWidget(m_group);

    setLayout(layout);

    // widget signals
    connect(m_group, 
            SIGNAL(deleteRequested(corbasim::qt::SortableGroupItem *)),
            this, 
            SLOT(deleteRequested(corbasim::qt::SortableGroupItem *)));
    
    setMinimumSize(650, 400);

    setModel(createModel());
}

AbstractInputTool::~AbstractInputTool()
{
    delete m_model;
}

void AbstractInputTool::setModel(ParametersModel * model)
{
    if (m_model)
    {
        delete m_model;
    }

    m_model = model;

    if (model)
    {
        m_view->setModel(m_model);

        // connect model signals 
        connect(m_model, 
                SIGNAL(checked(const QString&,
                        InterfaceDescriptor_ptr,
                        const QList< int >&)),
                this,
                SLOT(createAbstractInputItem(const QString&,
                        InterfaceDescriptor_ptr,
                        const QList< int >&)));
        connect(m_model, 
                SIGNAL(unchecked(const QString&,
                        InterfaceDescriptor_ptr,
                        const QList< int >&)),
                this,
                SLOT(deleteAbstractInputItem(const QString&,
                        InterfaceDescriptor_ptr,
                        const QList< int >&)));
    }
}

ParametersModel * AbstractInputTool::createModel() 
{
    return new ParametersModel(this);
}

void AbstractInputTool::registerInstance(Objref_ptr objref)
{
    m_instances.add(objref);
    m_model->registerInstance(objref->name(), objref->interface());
}

void AbstractInputTool::unregisterInstance(ObjectId id)
{
    Objref_ptr objref = m_instances.find(id);

    if (!objref)
        return;

    // Maps
    map_t::iterator it = m_map.begin();
    for(; it != m_map.end(); it++)
    {
        if (objref->name() == it->first.first)
        {
            for (int i = 0; i < it->second.size(); i++) 
            {
                AbstractInputItem * plot = it->second[i];

                m_inverse_map.erase(plot);
                m_model->uncheck(objref->name(), plot->getPath());
            }

            m_map.erase(it);
        }
    }

    m_model->unregisterInstance(objref->name());
    m_instances.del(id);
}

AbstractInputItem * AbstractInputTool::createAbstractInputItem(const QString& id, 
        InterfaceDescriptor_ptr reflective,
        const QList< int >& path)
{
    Objref_ptr objref = m_instances.find(id);

    OperationDescriptor_ptr op =
        reflective->get_reflective_by_index(path.front());

    AbstractInputItem * item = NULL;

    if (op && objref)
    {
        item = createItem(objref, op, path);

        const key_t key(id, op->get_tag());
        m_map[key].push_back(item);
        m_inverse_map[item] = key;

        qt::SortableGroupItem * sitem = 
            new qt::SortableGroupItem(item, m_group);

        sitem->showDetails();

        const QString title(getFieldName(op, path));
        sitem->setTitle(id + "." + title);

        m_group->appendItem(sitem);

        // connect with the processor
        connect(item, 
                SIGNAL(addProcessor(RequestProcessor_ptr)),
                getDefaultInputRequestController(),
                SLOT(addProcessor(RequestProcessor_ptr)));
        connect(item, 
                SIGNAL(removeProcessor(RequestProcessor_ptr)),
                getDefaultInputRequestController(),
                SLOT(removeProcessor(RequestProcessor_ptr)));

        item->start();
    }

    return item;
}

void AbstractInputTool::deleteAbstractInputItem(const QString& id, 
        InterfaceDescriptor_ptr reflective,
        const QList< int >& path)
{
    OperationDescriptor_ptr op =
        reflective->get_reflective_by_index(path.front());

    const key_t key(id, op->get_tag());
    QList< AbstractInputItem * >& list = m_map[key];

    for (int i = 0; i < list.size(); i++) 
    {
        AbstractInputItem * item = list[i];
        if (item->getPath() == path)
        {
            list.removeAt(i);
            m_inverse_map.erase(item);
            m_group->deleteItem(
                    qobject_cast< qt::SortableGroupItem * >
                        (item->parent()));

            // Notify to the processor
            item->reset();
            break;
        }
    }
}

void AbstractInputTool::deleteRequested(qt::SortableGroupItem* item)
{
    AbstractInputItem * aItem = 
        qobject_cast< AbstractInputItem * >(item->getWidget());

    if (aItem)
    {
        inverse_map_t::iterator it = m_inverse_map.find(aItem);

        if (it != m_inverse_map.end())
        {
            const key_t key(it->second);

            m_map[key].removeAll(aItem);

            // notify to model
            m_model->uncheck(key.first, aItem->getPath());

            m_inverse_map.erase(it);
        }
    }

    m_group->deleteItem(item);
}

// 
//
// Load and Save
//
//

void AbstractInputItem::save(QVariant& settings)
{
    QVariantMap map;

    settings = map;
}

void AbstractInputItem::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();
}

void AbstractInputTool::save(QVariant& settings)
{
    QVariantList list;

    for (map_t::iterator it = m_map.begin(); 
            it != m_map.end(); ++it) 
    {
        for (int i = 0; i < it->second.size(); i++) 
        {
            QVariantMap map;
            QVariantList vpath;

            const QList< int >& path = it->second.at(i)->getPath();

            for (int j = 0; j < path.size(); j++) 
            {
                vpath << path.at(j);
            }

            map["instance"] = it->first.first;
            map["path"] = vpath;

            it->second.at(i)->save(map["config"]);

            list << map;
        }
    }

    settings = list;
}

void AbstractInputTool::load(const QVariant& settings)
{
    const QVariantList list = settings.toList();

    for (int i = 0; i < list.size(); i++) 
    {
        const QVariantMap map = list.at(i).toMap();

        const QString id = map["instance"].toString();

        const QVariantList vpath = map["path"].toList();
        QList< int > path;
        for (int j = 0; j < vpath.size(); j++) 
        {
            path << vpath.at(j).toInt();
        }

        InterfaceDescriptor_ptr ref =
            m_model->getReflective(id);

        if (ref)
        {
            AbstractInputItem * item = 
                createAbstractInputItem(id, ref, path);

            if (item)
            {
                item->load(map["config"]);

                m_model->check(id, path);
            }
        }
    }
}


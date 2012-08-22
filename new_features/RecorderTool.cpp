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


    setLayout(layout);

    setMinimumSize(650, 400);
}

RecorderTool::~RecorderTool()
{
}

void RecorderTool::registerInstance(const QString& name,
        core::interface_reflective_base const * reflective)
{
    m_model.registerInstance(name, reflective);
}

void RecorderTool::unregisterInstance(const QString& name)
{
    m_model.unregisterInstance(name);
}

void RecorderTool::save(QVariant& settings)
{
    /*
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
    */
}

void RecorderTool::load(const QVariant& settings)
{
    /*
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

        core::interface_reflective_base const * ref =
            m_model.getReflective(id);

        if (ref)
        {
            Dumper * dumper = createDumper(id, ref, path);

            if (dumper)
            {
                dumper->load(map["config"]);

                m_model.check(id, path);
            }
        }
    }
    */
}


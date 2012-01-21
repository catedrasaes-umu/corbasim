// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * LogModel.cpp
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

#include "LogModel.hpp"
#include <QStyle>
#include <QApplication>
#include <QDateTime>

using namespace corbasim::qt;

LogModel::LogModel(QObject * parent) :
    QStandardItemModel(parent), m_maxEntries(100)
{
    // setHeaderData(0, Qt::Horizontal, "ID");
    // setHeaderData(1, Qt::Horizontal, "Value");
    m_inputIcon = qApp->style()->standardIcon(QStyle::SP_ArrowRight);
    m_outputIcon = qApp->style()->standardIcon(QStyle::SP_ArrowLeft);

    setColumnCount(2);
}

LogModel::~LogModel()
{
}

int LogModel::maxEntries() const
{
    return m_maxEntries;
}

void LogModel::setMaxEntries(int max)
{
    // TODO update model
    m_maxEntries = max;
}

void LogModel::registerInstance(const QString& id,
    const corbasim::gui::gui_factory_base * factory)
{
    m_instances.insert(std::make_pair(id, factory));
}

void LogModel::unregisterInstance(const QString& id)
{
    m_instances.erase(id);
}

void LogModel::inputRequest(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    QStandardItem * item = append(id, req, resp);
    if (item)
    {
        const QString text (item->text());
        item->setText(QString("Incoming call ") + id + "." + text);

        item->setIcon(m_inputIcon);

        item->setBackground(Qt::green);
    }
}

void LogModel::outputRequest(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    QStandardItem * item = append(id, req, resp);
    if (item)
    {
        const QString text (item->text());
        item->setText(QString("Outgoing call ") + id + "." + text);

        item->setIcon(m_outputIcon);

        item->setBackground(Qt::yellow);
    }
}

QStandardItem* LogModel::append(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    instances_t::const_iterator it = m_instances.find(id);
    
    if (it != m_instances.end())
    {
        QDateTime dateTime = QDateTime::currentDateTime();
        QList< QStandardItem * > list;


        QStandardItem * item = it->second->create_item(req.get());

        // TODO process response
        
        list << item << new QStandardItem(dateTime.toString());
        appendRow(list);

        while (rowCount() > m_maxEntries)
        {
            // Elimina la primera
            removeRow(0);
        }

        return item;
    }

    return NULL;
}


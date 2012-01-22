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

QVariant LogModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::BackgroundRole)
        return QStandardItemModel::data(index, role);

    QModelIndex parent = index;
    while(parent.parent().isValid())
    {
        parent = parent.parent();
    }

    const LogEntry& entry = m_entries.at(parent.row());

    // Excepciones
    if (entry.resp && (entry.resp->get_type() == event::EXCEPTION || 
            entry.resp->get_type() == event::MESSAGE))
        return QColor(Qt::red);

    if (entry.is_in_entry)
        return QColor(Qt::green);

    return QColor(Qt::yellow);
}

int LogModel::maxEntries() const
{
    return m_maxEntries;
}

void LogModel::setMaxEntries(int max)
{
    m_maxEntries = max;

    while (rowCount() > m_maxEntries)
    {
        // Elimina la primera
        removeRow(0);
        m_entries.pop_front();
    }
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
    QStandardItem * item = append(id, req, resp, true);
    if (item)
    {
        const QString text (item->text());
        const QString prefix = QString("Incoming call ") + id + "." + text;
        
        if(resp && resp->get_type() == event::EXCEPTION)
        {
            item->setText(prefix + " (Exception!)");
        }
        else if(resp && resp->get_type() == event::MESSAGE)
        {
            event::message* msg = static_cast< event::message* >(resp.get());
            item->setText(prefix + " (" + msg->get_message() + ")");
        }
        else
        {
            item->setText(prefix);
        }

        item->setIcon(m_inputIcon);
    }
}

void LogModel::outputRequest(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    QStandardItem * item = append(id, req, resp, false);
    if (item)
    {
        const QString text (item->text());
        const QString prefix = QString("Outgoing call ") + id + "." + text;
        
        if(resp && resp->get_type() == event::EXCEPTION)
        {
            item->setText(prefix + " (Exception!)");
        }
        else if(resp && resp->get_type() == event::MESSAGE)
        {
            event::message* msg = static_cast< event::message* >(resp.get());
            item->setText(prefix + " (" + msg->get_message() + ")");
        }
        else
        {
            item->setText(prefix);
        }

        item->setIcon(m_outputIcon);
    }
}

QStandardItem* LogModel::append(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp,
        bool is_in)
{
    instances_t::const_iterator it = m_instances.find(id);
    
    if (it != m_instances.end())
    {
        QDateTime dateTime = QDateTime::currentDateTime();
        QList< QStandardItem * > list;

        // Deja espacio
        while (rowCount() > m_maxEntries - 1)
        {
            // Elimina la primera
            removeRow(0);
            m_entries.pop_front();
        }

        QStandardItem * item = it->second->create_item(req.get());

        // process response
        if (resp && resp->get_type() == event::RESPONSE)
        {
            QStandardItem * itemResp = it->second->create_item(resp.get());
            itemResp->setText("Response");
            item->appendRow(itemResp);
        }
        
        list << item << new QStandardItem(dateTime.toString());

        // List
        LogEntry entry;
        entry.is_in_entry = is_in;
        entry.id = id;
        entry.req = req;
        entry.resp = resp;
        m_entries.push_back(entry);

        appendRow(list);
        return item;
    }

    return NULL;
}


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

#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>

using namespace corbasim::reflective_gui;

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
    const corbasim::core::interface_reflective_base * factory)
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

QVariant toQVariant(
        corbasim::core::reflective_base const * reflective,
        corbasim::core::holder& hold)
{
    using namespace corbasim::core;

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            return QVariant(hold.to_value< bool >());
        case TYPE_OCTET:
            return QVariant(hold.to_value< unsigned char >());
        case TYPE_CHAR:
            return QVariant(hold.to_value< char >());
        case TYPE_SHORT:
            return QVariant(hold.to_value< short >());
        case TYPE_USHORT:
            return QVariant(hold.to_value< unsigned short >());
        case TYPE_LONG:
            return QVariant(hold.to_value< int32_t >());
        case TYPE_ULONG:
            return QVariant(hold.to_value< uint32_t >());
        case TYPE_LONGLONG:
            return QVariant(hold.to_value< int64_t >());
        case TYPE_ULONGLONG:
            return QVariant(hold.to_value< uint64_t >());

        case TYPE_STRING:
        case TYPE_WSTRING:
            {
                std::string str(reflective->to_string(hold));
                return QVariant(str.c_str());
            }
        case TYPE_OBJREF:
            break;

        case TYPE_ENUM:
            {
                // Maybe it works...
                int32_t value = hold.to_value< int32_t >();

                const char * str = "Unknown value"; 

                if (value >= 0 && value < reflective->get_children_count())
                    str = reflective->get_child_name((unsigned int) value);

                return QVariant(str);
            }

        case TYPE_DOUBLE:
            return QVariant(hold.to_value< double >());
        case TYPE_FLOAT:
            return QVariant(hold.to_value< float >());
        default:
            break;
    }
   
    return QVariant();
}

QStandardItem * createRecursive(
        corbasim::core::reflective_base const * reflective,
        corbasim::core::holder& hold)
{
    using namespace corbasim::core;

    if (!reflective)
        return new QStandardItem("Null reflective type!");

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
        case TYPE_OCTET:
        case TYPE_CHAR:
        case TYPE_SHORT:
        case TYPE_USHORT:
        case TYPE_LONG:
        case TYPE_ULONG:
        case TYPE_LONGLONG:
        case TYPE_ULONGLONG:
        case TYPE_STRING:
        case TYPE_WSTRING:
        case TYPE_OBJREF:
        case TYPE_ENUM:
        case TYPE_DOUBLE:
        case TYPE_FLOAT:
            {
                QStandardItem * item =  new QStandardItem();
                item->setData(toQVariant(reflective, hold), Qt::DisplayRole);
                return item;
            }

        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
            {
                QStandardItem * parent = new QStandardItem();

                const unsigned int count = reflective->get_length(hold);

                reflective_base const * slice = reflective->get_slice();

                for (unsigned int i = 0; i < count; i++) 
                {
                    const QString child_name = QString("[%1]").arg(i);

                    holder child_value = 
                        reflective->get_child_value(hold, i);

                    QStandardItem * current = 
                        createRecursive(slice, child_value);

                    if (current->rowCount() > 0)
                    {
                        current->setText(child_name);
                        parent->appendRow(current);
                    }
                    else
                    {
                        QStandardItem* name = new QStandardItem(child_name);
                        QList< QStandardItem * > list;
                        list << name;
                        list << current;

                        parent->appendRow(list);
                    }
                }

                return parent;
            }

        case TYPE_STRUCT:
            {
                QStandardItem * parent = new QStandardItem();

                const unsigned int count = reflective->get_children_count();

                for (unsigned int i = 0; i < count; i++) 
                {
                    reflective_base const * child = 
                        reflective->get_child(i);

                    holder child_value = 
                        reflective->get_child_value(hold, i);

                    QStandardItem * current = 
                        createRecursive(child, child_value);

                    const char * child_name = reflective->get_child_name(i);

                    if (current->rowCount() > 0)
                    {
                        current->setText(child_name);
                        parent->appendRow(current);
                    }
                    else
                    {
                        QStandardItem* name = new QStandardItem(child_name);
                        QList< QStandardItem * > list;
                        list << name;
                        list << current;

                        parent->appendRow(list);
                    }

                }

                return parent;
            }
        case TYPE_UNION:
        default:

            break;
    }

    return new QStandardItem("Unsupported item!");
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

        core::operation_reflective_base const * op =
            it->second->get_reflective_by_tag(req->get_tag());

        if (!op)
            return NULL;

        // Deja espacio
        while (rowCount() > m_maxEntries - 1)
        {
            // Elimina la primera
            removeRow(0);
            m_entries.pop_front();
        }

        core::holder hold = op->get_holder(req);

        QStandardItem * item = createRecursive(op, hold);
        item->setText(op->get_name());

        // process response
        if (resp && resp->get_type() == event::RESPONSE)
        {
#warning TODO
#if 0
            QStandardItem * itemResp = it->second->create_item(resp.get());
            itemResp->setText("Response");
            item->appendRow(itemResp);
#endif
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


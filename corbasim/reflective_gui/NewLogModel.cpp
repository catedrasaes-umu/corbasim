// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * NewLogModel.cpp
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

#include "NewLogModel.hpp"
#include <QStyle>
#include <QApplication>
#include <QDateTime>

#include <corbasim/core/reference_repository.hpp>

#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>

using namespace corbasim::reflective_gui;

extern QVariant toQVariant(
        corbasim::core::reflective_base const * reflective,
        corbasim::core::holder& hold);

NewLogModel::NewLogModel(QObject * parent) :
    QAbstractItemModel(parent), m_maxEntries(100)
{
    m_inputIcon = qApp->style()->standardIcon(QStyle::SP_ArrowRight);
    m_outputIcon = qApp->style()->standardIcon(QStyle::SP_ArrowLeft);
}

NewLogModel::~NewLogModel()
{
}

int NewLogModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant NewLogModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // Background
    if (role == Qt::BackgroundRole)
    {
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
    else if (role == Qt::DisplayRole)
    {
        // TODO
        return QVariant(QString("tmp"));
    }

    return QVariant();
}

Qt::ItemFlags NewLogModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant NewLogModel::headerData(int section, Qt::Orientation orientation,
                           int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Message");
        case 1:
            return QString("Value");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex NewLogModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Node * node = static_cast< Node * >(parent.internalPointer());
    node->check_for_initialized();

    if (row < node->children.size())
    {
        return createIndex(row, column, (void *) node->children[row].get());
    }

    return QModelIndex();
}

QModelIndex NewLogModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Node * node = static_cast< Node * >(index.internalPointer());

    if (!node->parent)
        return QModelIndex();

    return createIndex(node->index, 0, (void *) node->parent);
}

int NewLogModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return m_entries.size();

    Node * node = static_cast< Node * >(parent.internalPointer());
    node->check_for_initialized();

    return node->children.size();
}

void NewLogModel::clearLog()
{
    m_entries.clear();
    m_nodes.clear();
}

int NewLogModel::maxEntries() const
{
    return m_maxEntries;
}

void NewLogModel::setMaxEntries(int max)
{
    m_maxEntries = max;

    // TODO remove
}

void NewLogModel::registerInstance(const QString& id,
    const corbasim::core::interface_reflective_base * factory)
{
    m_instances.insert(std::make_pair(id, factory));
}

void NewLogModel::unregisterInstance(const QString& id)
{
    m_instances.erase(id);
}

void NewLogModel::inputRequest(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
     append(id, req, resp, true);
}

void NewLogModel::outputRequest(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    append(id, req, resp, false);
}

void NewLogModel::append(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp,
        bool is_in)
{
    instances_t::const_iterator it = m_instances.find(id);
    
    if (it != m_instances.end())
    {
        LogEntry entry;
        entry.dateTime = QDateTime::currentDateTime();

        core::operation_reflective_base const * op =
            it->second->get_reflective_by_tag(req->get_tag());

        if (!op)
            return;

        // Deja espacio
        int nRowsToBeRemoved = m_entries.size() - m_maxEntries + 1;
        if (nRowsToBeRemoved > 0)
        {
            beginRemoveRows(QModelIndex(), 0, nRowsToBeRemoved - 1);

            for (int i = 0; i < nRowsToBeRemoved; i++) 
            {
                // Elimina la primera
                m_entries.pop_front();
                m_nodes.pop_front();
            }

            endRemoveRows();
        }

        beginInsertRows(QModelIndex(), m_nodes.size(), m_nodes.size());

        core::holder hold = op->get_holder(req);
        Node_ptr node(new Node(op, hold));
        m_nodes.push_back(node);

        // List
        entry.is_in_entry = is_in;
        entry.id = id;
        entry.req = req;
        entry.resp = resp;
        m_entries.push_back(entry);
        
        endInsertRows();
    }
}


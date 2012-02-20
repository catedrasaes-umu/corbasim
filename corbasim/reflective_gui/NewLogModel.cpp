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
#include <corbasim/reflective_gui/qvariant.hpp>

#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>

#include <iostream>

using namespace corbasim::reflective_gui;

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

QString getNodeName(Node const * node)
{
    if (node->parent && node->parent->reflective->is_repeated())
    {
        return QString("[%1]").arg(node->index);
    }
    else if (node->parent && node->parent->reflective->get_type() ==
            corbasim::core::TYPE_STRUCT)
    {
        return node->parent->reflective->get_child_name(node->index);
    }

    return "Error!";
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

        // std::cout << parent.row() << std::endl;
        const LogEntry& entry = m_entries.at(parent.row());

        // return QVariant();
        return entry.color;
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        Node * node = static_cast< Node * >(index.internalPointer());
        node->check_for_initialized();

        // First level item
        if (!index.parent().isValid())
        {
            // Value
            if (index.column())
                return m_entries[index.row()].dateTime;

            return m_entries[index.row()].text;
        }
        else
        {
            // Value
            if (index.column())
                return toQVariant(node->reflective, node->holder);

            // Name
            return getNodeName(node);
        }
    }
    else if (!index.parent().isValid() && index.column() == 0
            && role == Qt::DecorationRole)
    {
        const LogEntry& entry = m_entries.at(index.row());
        return *(entry.icon);
    }

    return QVariant();
}

bool NewLogModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    Node * node = static_cast< Node * >(index.internalPointer());
    
    if (!node) return false;

    node->check_for_initialized();

    bool res = fromQVariant(node->reflective, node->holder, value);

    if (res)
    {
        emit dataChanged(index, index);
    }

    return res;
}

Qt::ItemFlags NewLogModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    // Value is editable by default
    if (index.column())
        return Qt::ItemIsEnabled 
            | Qt::ItemIsSelectable 
            | Qt::ItemIsEditable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant NewLogModel::headerData(int section, 
        Qt::Orientation orientation, int role) const
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

QModelIndex NewLogModel::index(int row, int column, 
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        return createIndex(row, column, (void *) m_nodes[row].get());
    }

    Node * node = static_cast< Node * >(parent.internalPointer());
    node->check_for_initialized();

    if (row < (int) node->children.size())
    {
        return createIndex(row, column, 
                (void *) node->children[row].get());
    }

    return QModelIndex();
}

QModelIndex NewLogModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Node * node = static_cast< Node * >(index.internalPointer());

    if (!node || !node->parent)
        return QModelIndex();

    // parent is first level item
    if (!node->parent->parent)
    {
        // index could be changed
        int row = 0;
        bool found = false;
        for (; row < m_nodes.size() && !found; row++) 
            if (m_nodes.at(row).get() == node->parent)
                return createIndex(row, 0, (void *) node->parent);

        return QModelIndex();
    }

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
    beginResetModel();
    reset();
    resetInternalData();
    endResetModel();
}

void NewLogModel::resetInternalData()
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

        entry.reflective = op;

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

        if (is_in)
        {
            entry.text = QString("Incoming call ") + id + "." 
                + op->get_name();
            entry.icon = &m_inputIcon;
            
            // Background color
            if (resp && (resp->get_type() == event::EXCEPTION || 
                    resp->get_type() == event::MESSAGE))
            {
                entry.text += " (Exception!)";
                entry.color = QColor(Qt::red);
            }
            else
                entry.color = QColor(Qt::green);
        }
        else
        {
            entry.text = QString("Outgoing call ") + id + "." 
                + op->get_name();
            entry.icon = &m_outputIcon;

            // Background Color
            if (resp && (resp->get_type() == event::EXCEPTION || 
                    resp->get_type() == event::MESSAGE))
            {
                entry.text += " (Exception!)";
                entry.color = QColor(Qt::red);
            }
            else
                entry.color = QColor(Qt::yellow);
        }

        m_entries.push_back(entry);

        endInsertRows();
    }
}


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

#include <corbasim/gui/qvariant.hpp>

#include <corbasim/gui/item/FilterModel.hpp>

#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>

#include <iostream>

using namespace corbasim::gui;

LogModel::LogModel(QObject * parent) :
    QAbstractItemModel(parent), m_instances(this), m_maxEntries(100)
{
    m_inputIcon = qApp->style()->standardIcon(QStyle::SP_ArrowRight);
    m_outputIcon = qApp->style()->standardIcon(QStyle::SP_ArrowLeft);

    m_entries.reserve(2 * m_maxEntries);
}

LogModel::~LogModel()
{
}

int LogModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}

const LogModel::LogEntry * LogModel::getEntry(const QModelIndex& index) const
{
    QModelIndex idx = index;

    while(idx.parent().isValid()) idx = idx.parent();

    if (idx.isValid() && idx.row() < m_entries.size())
    {
        return &(m_entries.at(idx.row()));
    }

    return NULL;
}

namespace 
{

QString getNodeName(MetaNode const * node)
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
    else if (node->parent && node->parent->reflective->get_type() ==
            corbasim::core::TYPE_UNION)
    {
        return node->parent->reflective->get_child_name(
                node->reflective->get_child_index());
    }

    return "Error!";
}

} // namespace 


QVariant LogModel::data(const QModelIndex& index, int role) const
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
        MetaNode * node = 
            static_cast< MetaNode * >(index.internalPointer());
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
            {
                int col = index.column() - 1;

                if (col < node->brothers.size() && node->brothers[col])
                    return toQVariant(node->reflective, node->brothers[col]->holder);

                return QVariant();
            }

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

bool LogModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    MetaNode * node = static_cast< MetaNode * >(index.internalPointer());
    
    if (!node) return false;

    node->check_for_initialized();

    const int col = index.column() - 1;

    if (col < 0 || col >= node->brothers.size() || !node->brothers[col])
        return false;

    bool res = fromQVariant(node->reflective, node->brothers[col]->holder, value);

    if (res)
    {
        // Temporal
        if (node->parent && 
                node->parent->reflective->get_type() == core::TYPE_UNION)
        {
            bool _d = (node->reflective->get_child_index() == 0);
            QModelIndex parent = createIndex(
                    node->parent->index, 0, (void *) node->parent);

            if (_d)
            {
                beginRemoveRows(parent, 0, node->parent->children.size());
            }

            // No es una referencia
            node->parent->reflective->set_child_value(node->parent->brothers[col]->holder, 
                    node->reflective->get_child_index(), node->brothers[col]->holder);

            if (_d)
            {
                node->parent->reset();
                endRemoveRows();

                node->parent->check_for_initialized();

                beginInsertRows(parent, 0, node->parent->children.size());
                endInsertRows();
                // emit dataChanged(parent, parent);
            }
            else
            {
                emit dataChanged(index, index);
            }
        }
        else
        {
            emit dataChanged(index, index);
        }
    }

    return res;
}

Qt::ItemFlags LogModel::flags(const QModelIndex &index) const
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

QVariant LogModel::headerData(int section, 
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Operation");
        case 1:
            return QString("Input value");
        case 2:
            return QString("Output value");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex LogModel::index(int row, int column, 
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        return createIndex(row, column, 
                (void *) m_nodes[row].get());
    }

    MetaNode * node = static_cast< MetaNode * >(
            parent.internalPointer());
    node->check_for_initialized();

    if (row < (int) node->children.size())
    {
        return createIndex(row, column, 
                (void *) node->children[row].get());
    }

    return QModelIndex();
}

QModelIndex LogModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    MetaNode * node = static_cast< MetaNode * >(
            index.internalPointer());

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

int LogModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return m_entries.size();

    MetaNode * node = static_cast< MetaNode * >(
            parent.internalPointer());
    node->check_for_initialized();

    return node->children.size();
}

void LogModel::clearLog()
{
    beginResetModel();
    reset();
    resetInternalData();
    endResetModel();
}

void LogModel::resetInternalData()
{
    m_entries.clear();
    m_nodes.clear();
}

int LogModel::maxEntries() const
{
    return m_maxEntries;
}

void LogModel::setMaxEntries(int max)
{
    m_maxEntries = max;
    m_entries.reserve(2 * m_maxEntries);
    // TODO remove
}

void LogModel::registerInstance(Objref_ptr objref)
{
    m_instances.add(objref);
}

void LogModel::unregisterInstance(ObjectId id)
{
    m_instances.del(id);
}

void LogModel::inputRequest(ObjectId id, 
        Request_ptr req,
        Event_ptr resp)
{
    append(id, req, resp, true);
}

void LogModel::outputRequest(ObjectId id, 
        Request_ptr req,
        Event_ptr resp)
{
    append(id, req, resp, false);
}

void LogModel::append(ObjectId id, 
        Request_ptr req,
        Event_ptr resp,
        bool is_in)
{
    Objref_ptr obj = m_instances.find(id);
    
    if (obj)
    {
        LogEntry entry;
        entry.dateTime = QDateTime::currentDateTime();

        OperationDescriptor_ptr op =
            obj->interface()->get_reflective_by_tag(req->get_tag());

        if (!op) return;

        entry.object = obj;
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

        MetaNode_ptr metaNode(new MetaNode(op));
        
        // Request
        core::holder hold = op->get_holder(req);
        Node_ptr node(new Node(op, hold));
        metaNode->brothers.push_back(node);
        
        // Response
        if (resp && (resp->get_type() == event::RESPONSE))
        {
            event::response_ptr response(
                    boost::static_pointer_cast< event::response >(resp));

            core::holder hold = op->get_holder(response);
            Node_ptr node(new Node(op, hold));
            metaNode->brothers.push_back(node);
        }
        else
        {
            // Null node
            metaNode->brothers.push_back(Node_ptr());
        }

        m_nodes.push_back(metaNode);

        // List
        entry.is_in_entry = is_in;
        entry.req = req;
        entry.resp = resp;

        if (is_in)
        {
            entry.text = QString("Incoming call ") + obj->name() + "." 
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
            entry.text = QString("Outgoing call ") + obj->name() + "." 
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

FilteredLogModel::FilteredLogModel(QObject * parent) : 
    QSortFilterProxyModel(parent), m_filter(NULL)
{
}

FilteredLogModel::~FilteredLogModel()
{
}

bool FilteredLogModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    if (sourceParent.isValid()) return true;

    if (!m_filter) return false;

    LogModel const * model = dynamic_cast< LogModel const * >(sourceModel());

    if (model)
    {
        const LogModel::LogEntry& entry(model->getLogEntry(sourceRow));

        return m_filter->visibleOperation(entry.object->id(), entry.reflective->get_tag());
    }

    return false;
}

void FilteredLogModel::setFilterModel(FilterModel * filter)
{
    if (m_filter)
    {
        QObject::disconnect(m_filter, SIGNAL(filterChanged()), this, SLOT(resetModel()));
    }

    m_filter = filter;

    if (m_filter)
    {
        QObject::connect(m_filter, SIGNAL(filterChanged()), this, SLOT(resetModel()));
    }
}

void FilteredLogModel::resetModel()
{
    invalidateFilter();
}


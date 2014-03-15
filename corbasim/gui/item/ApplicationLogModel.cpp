// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ApplicationLogModel.cpp
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

#include "ApplicationLogModel.hpp"
#include <QStyle>
#include <QApplication>

#include <iostream>

using namespace corbasim::gui;

ApplicationLogModel::ApplicationLogModel(QObject * parent) :
    QAbstractItemModel(parent), m_maxEntries(100)
{
    m_errorIcon = qApp->style()->standardIcon(QStyle::SP_MessageBoxCritical);
    m_messageIcon = qApp->style()->standardIcon(QStyle::SP_MessageBoxInformation);

    m_entries.reserve(2 * m_maxEntries);
}

ApplicationLogModel::~ApplicationLogModel()
{
}

int ApplicationLogModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

const ApplicationLogModel::LogEntry * ApplicationLogModel::getEntry(const QModelIndex& index) const
{
    QModelIndex idx = index;

    while(idx.parent().isValid()) idx = idx.parent();

    if (idx.isValid() && idx.row() < m_entries.size())
    {
        return &(m_entries.at(idx.row()));
    }

    return NULL;
}


QVariant ApplicationLogModel::data(const QModelIndex& index, int role) const
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
        // First level item
        if (!index.parent().isValid())
        {
            // Value
            if (!index.column())
                return m_entries[index.row()].dateTime;

            return m_entries[index.row()].text;
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

Qt::ItemFlags ApplicationLogModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ApplicationLogModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Time");
        case 1:
            return QString("Message");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex ApplicationLogModel::index(int row, int column,
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        return createIndex(row, column);
    }

    return QModelIndex();
}

QModelIndex ApplicationLogModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int ApplicationLogModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return m_entries.size();

    return 0;
}

void ApplicationLogModel::clearLog()
{
    beginResetModel();
    reset();
    resetInternalData();
    endResetModel();
}

void ApplicationLogModel::resetInternalData()
{
    m_entries.clear();
}

int ApplicationLogModel::maxEntries() const
{
    return m_maxEntries;
}

void ApplicationLogModel::setMaxEntries(int max)
{
    m_maxEntries = max;
    m_entries.reserve(2 * m_maxEntries);

    // TODO remove
}

void ApplicationLogModel::append(const QString& text, bool is_error)
{
    LogEntry entry;
    entry.dateTime = QDateTime::currentDateTime();

    // Deja espacio
    int nRowsToBeRemoved = m_entries.size() - m_maxEntries + 1;
    if (nRowsToBeRemoved > 0)
    {
        beginRemoveRows(QModelIndex(), 0, nRowsToBeRemoved - 1);

        for (int i = 0; i < nRowsToBeRemoved; i++)
        {
            // Elimina la primera
            m_entries.pop_front();
        }

        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), m_entries.size(), m_entries.size());

    // List
    entry.is_error = is_error;
    entry.text = text;

    if (entry.is_error)
    {
        entry.icon = &m_errorIcon;
        entry.color = QColor(Qt::red);
    }
    else
    {
        entry.icon = &m_messageIcon;
        entry.color = QColor(Qt::yellow);
    }

    m_entries.push_back(entry);

    endInsertRows();
}

void ApplicationLogModel::error(const QString& err)
{
    append(err, true);
}

void ApplicationLogModel::message(const QString& msg)
{
    append(msg, false);
}


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReferenceModel.cpp
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

#include "ReferenceModel.hpp"

using namespace corbasim::app::model;

ReferenceModel::ReferenceModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

ReferenceModel::~ReferenceModel()
{
}

int ReferenceModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

QVariant ReferenceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();

    if (row < 0 || row >= m_ids.count())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_ids[row];

    /*
    Q_DECLARE_METATYPE
    if (role == Qt::UserRole)
        return QVariant::fromValue(m_refs[row]);
    */

    return QVariant();
}

Qt::ItemFlags ReferenceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ReferenceModel::headerData(int section, Qt::Orientation orientation,
                           int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return QString("Value");
    }

    return QVariant();
}

QModelIndex ReferenceModel::index(int row, int column, 
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (row >= 0 && row < m_ids.count())
        return createIndex(row, column);

    return QModelIndex();
}

QModelIndex ReferenceModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int ReferenceModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return m_ids.count();

    return 0;
}

void ReferenceModel::appendItem(const QString& id, 
        const CORBA::Object_var& ref)
{
    int idx;
    if ((idx = m_ids.indexOf(id)) == -1)
    {
        m_ids.append(id);
        m_refs.append(ref);
    }
    else
    {
        // Updates the current reference
        m_refs[idx] = ref;
    }

    // TODO Notfiy model changed
    reset();
}

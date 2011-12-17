// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReferenceModel.hpp
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

#ifndef CORBASIM_APP_MODEL_REFERENCEMODEL_HPP
#define CORBASIM_APP_MODEL_REFERENCEMODEL_HPP

#include <QtGui>
#include <corbasim/impl.hpp>

namespace corbasim
{
namespace app
{
namespace model
{

class ReferenceModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ReferenceModel(QObject *parent = 0);
    ~ReferenceModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void appendItem(const QString& id, const CORBA::Object_var& ref);

protected:

    QList< QString > m_ids;
    QList< CORBA::Object_var > m_refs;
};

} // model
} // app
} // corbasim

#endif // CORBASIM_APP_MODEL_REFERENCEMODEL_HPP


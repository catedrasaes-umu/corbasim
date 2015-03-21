// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptModel.hpp
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

#ifndef CORBASIM_GUI_SCRIPTMODEL_HPP
#define CORBASIM_GUI_SCRIPTMODEL_HPP

#include <QAbstractItemModel>
#include <QDateTime>
#include <QIcon>

#include <corbasim/gui/types.hpp>
#include <corbasim/gui/item/ModelNode.hpp>
#include <corbasim/gui/export.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC ScriptModel :
    public QAbstractItemModel
{
    Q_OBJECT
public:
    ScriptModel(QObject * parent = 0);
    virtual ~ScriptModel();

    QVariant data(const QModelIndex& index,
            int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index,
            const QVariant& value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QMimeData *    mimeData(const QModelIndexList& indexes) const;

    corbasim::event::request_ptr getRequest(int pos);

    void initialize(InterfaceDescriptor_ptr instance);

    int indexToPosition(const QModelIndex& index) const;

    void deletePosition(int pos);

#if QT_VERSION < 0x50000
    Qt::DragActions supportedDragActions() const
    {
        return Qt::CopyAction;
    }
#endif

public slots:

    void clearLog();

    void addRequest(corbasim::event::request_ptr req,
            int pos = -1);

private slots:

    void resetInternalData();

protected:

    void append(corbasim::event::request_ptr req, int pos);

    InterfaceDescriptor_ptr m_instance;

    QIcon m_outputIcon;

    struct LogEntry
    {
        QString text;
        OperationDescriptor_ptr reflective;
        corbasim::event::request_ptr req;
        QDateTime dateTime;
        QIcon * icon;
        QColor color;
        bool exception;
    };

    QList< LogEntry > m_entries;
    QList< Node_ptr > m_nodes;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SCRIPTMODEL_HPP */


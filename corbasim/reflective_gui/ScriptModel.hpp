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

#ifndef CORBASIM_REFLECTIVE_GUI_SCRIPTMODEL_HPP
#define CORBASIM_REFLECTIVE_GUI_SCRIPTMODEL_HPP

#include <QAbstractItemModel>
#include <QDateTime>
#include <QIcon>

#include <corbasim/qt/types.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/reflective_gui/ModelNode.hpp>

namespace corbasim 
{
namespace reflective_gui
{

class ScriptModel : public QAbstractItemModel
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

    corbasim::event::request_ptr getRequest(int pos);

    void initialize(core::interface_reflective_base const * instance);

public slots:

    void clearLog();

    void addRequest(corbasim::event::request_ptr req,
            int pos = -1);

private slots:

    void resetInternalData();

protected:

    void append(corbasim::event::request_ptr req, int pos);

    core::interface_reflective_base const * m_instance;

    QIcon m_outputIcon;

    struct LogEntry
    {
        QString text;
        core::operation_reflective_base const * reflective;
        corbasim::event::request_ptr req;
        QDateTime dateTime;
        QIcon * icon;
        QColor color;
        bool exception;
    };

    QList< LogEntry > m_entries;
    QList< Node_ptr > m_nodes;
};

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_SCRIPTMODEL_HPP */


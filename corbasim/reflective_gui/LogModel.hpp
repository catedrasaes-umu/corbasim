// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * LogModel.hpp
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

#ifndef CORBASIM_REFLECTIVE_GUI_NEWLOGMODEL_HPP
#define CORBASIM_REFLECTIVE_GUI_NEWLOGMODEL_HPP

#include <map>

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QIcon>

#include <corbasim/reflective_gui/export.hpp>
#include <corbasim/qt/types.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/reflective_gui/ModelNode.hpp>

namespace corbasim 
{
namespace qt 
{
class FilterModel;
} // namespace qt

namespace reflective_gui
{

class FilteredLogModel;

class CORBASIM_REFLECTIVE_GUI_DECLSPEC LogModel : 
    public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(int maxEntries READ maxEntries WRITE setMaxEntries)
public:
    LogModel(QObject * parent = 0);
    virtual ~LogModel();

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

public slots:

    void clearLog();

    int maxEntries() const;
    void setMaxEntries(int max);

    void registerInstance(const QString& id,
        const corbasim::core::interface_reflective_base * factory);
    void unregisterInstance(const QString& id);

    void inputRequest(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);
    void outputRequest(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

private slots:

    void resetInternalData();

protected:

    void append(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp,
            bool is_in);

    int m_maxEntries;

    typedef std::map< QString, 
            core::interface_reflective_base const * > instances_t;
    instances_t m_instances;

    QIcon m_inputIcon;
    QIcon m_outputIcon;

    struct LogEntry
    {
        bool is_in_entry;
        QString id;
        QString text;
        core::operation_reflective_base const * reflective;
        corbasim::event::request_ptr req;
        corbasim::event::event_ptr resp;
        QDateTime dateTime;
        QIcon * icon;
        QColor color;
        bool exception;
    };

    const LogEntry& getLogEntry(int row) const { return m_entries.at(row); };

    QList< LogEntry > m_entries;
    QList< MetaNode_ptr > m_nodes;

    friend class FilteredLogModel;
};

class CORBASIM_REFLECTIVE_GUI_DECLSPEC FilteredLogModel : 
    public QSortFilterProxyModel
{
    Q_OBJECT
public:

    FilteredLogModel(QObject * parent = 0);
    virtual ~FilteredLogModel();

    void setFilterModel(qt::FilterModel * filter);

protected slots:

    void resetModel();

protected:

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;

    qt::FilterModel * m_filter;
};

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_NEWLOGMODEL_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ApplicationLogModel.hpp
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

#ifndef CORBASIM_GUI_APPLICATIONLOGMODEL_HPP
#define CORBASIM_GUI_APPLICATIONLOGMODEL_HPP

#include <QAbstractItemModel>
#include <QDateTime>
#include <QIcon>

#include <corbasim/gui/export.hpp>

namespace corbasim 
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC ApplicationLogModel : 
    public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(int maxEntries READ maxEntries WRITE setMaxEntries)
public:
    ApplicationLogModel(QObject * parent = 0);
    virtual ~ApplicationLogModel();

    QVariant data(const QModelIndex& index, 
            int role = Qt::DisplayRole) const; 

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    struct LogEntry
    {
        bool is_error;
        QString text;
        QDateTime dateTime;
        QColor color;
        QIcon * icon;
    };

    const LogEntry * getEntry(const QModelIndex& index) const;

public slots:

    void clearLog();

    int maxEntries() const;
    void setMaxEntries(int max);

    void message(const QString& msg);
    void error(const QString& err);

private slots:

    void resetInternalData();

    void append(const QString& text, bool is_error);

protected:

    int m_maxEntries;

    QIcon m_messageIcon;
    QIcon m_errorIcon;

    const LogEntry& getLogEntry(int row) const { return m_entries.at(row); };

    QList< LogEntry > m_entries;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_APPLICATIONLOGMODEL_HPP */


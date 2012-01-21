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

#ifndef CORBASIM_QT_LOGMODEL_HPP
#define CORBASIM_QT_LOGMODEL_HPP

#include <map>

#include <QStandardItemModel>
#include <corbasim/qt/types.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>

namespace corbasim 
{
namespace qt 
{

class LogModel : public QStandardItemModel
{
    Q_OBJECT
    Q_PROPERTY(int maxEntries READ maxEntries WRITE setMaxEntries)
public:
    LogModel(QObject * parent = 0);
    virtual ~LogModel();

public slots:

    int maxEntries() const;
    void setMaxEntries(int max);

    void registerInstance(const QString& id,
        const corbasim::gui::gui_factory_base * factory);
    void unregisterInstance(const QString& id);

    void inputRequest(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);
    void outputRequest(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

protected:

    QStandardItem * append(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    int m_maxEntries;

    typedef std::map< QString, 
            gui::gui_factory_base const * > instances_t;
    instances_t m_instances;

    QIcon m_inputIcon;
    QIcon m_outputIcon;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_LOGMODEL_HPP */


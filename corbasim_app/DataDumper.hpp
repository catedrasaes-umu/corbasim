// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DataDumper.hpp
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

#ifndef CORBASIM_APP_DATADUMPER_HPP
#define CORBASIM_APP_DATADUMPER_HPP

#include <QObject>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/qt/types.hpp>
#include <QMap>

namespace corbasim 
{
namespace app 
{

class AppController;

class DataDumper : public QObject
{
    Q_OBJECT
public:
    DataDumper(QObject * parent = 0);
    virtual ~DataDumper();

    void setController(AppController * m_controller);
    void setDirectory(const QString& directory);

public slots:

    void objrefCreated(const QString& id, 
            const corbasim::gui::gui_factory_base * factory);
    void objrefDeleted(const QString& id);

    void servantCreated(const QString& id, 
            const corbasim::gui::gui_factory_base * factory);
    void servantDeleted(const QString& id);

    void requestReceived(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

protected:
    QString m_directory;
    AppController * m_controller;

    typedef QMap< QString, 
                  corbasim::core::factory_base const * > 
            serializers_t;
    serializers_t m_serializers;
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_DATADUMPER_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppFileWatcher.hpp
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

#ifndef CORBASIM_APP_APPFILEWATCHER_HPP
#define CORBASIM_APP_APPFILEWATCHER_HPP

#include <QtCore>
#include <corbasim/gui/gui_factory_fwd.hpp>

namespace corbasim 
{
namespace app 
{

class AppController;

class AppFileWatcher : public QObject
{
    Q_OBJECT
public:
    AppFileWatcher(QObject * parent = 0);
    virtual ~AppFileWatcher();

    void setDirectory(const QString& directory);
    void setController(AppController * controller);

public slots:

    void objrefCreated(const QString& id,
        const corbasim::gui::gui_factory_base * factory);
    void objrefDeleted(const QString& id);

    void servantCreated(const QString& id,
        const corbasim::gui::gui_factory_base * factory);
    void servantDeleted(const QString& id);

    void readFile(const QString& path);
    void fileChanged(const QString& path);

signals:

    void updateReference(QString, CORBA::Object_var);

protected:
    QDir m_directory;
    QFileSystemWatcher m_watcher;

    AppController * m_controller;
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPFILEWATCHER_HPP */


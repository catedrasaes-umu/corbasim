// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppFileWatcher.cpp
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

#include "AppFileWatcher.hpp"
#include "AppController.hpp"
#include <corbasim/core/reference_repository.hpp>

using namespace corbasim::app;

AppFileWatcher::AppFileWatcher(QObject * parent) :
    QObject(parent), m_controller(NULL)
{
    QObject::connect(
            &m_watcher,
            SIGNAL(fileChanged(QString)),
            this,
            SLOT(fileChanged(const QString&)));
}

AppFileWatcher::~AppFileWatcher()
{
}

void AppFileWatcher::setDirectory(const QString& directory)
{
    m_directory = directory;

    if (!m_directory.exists())
    {
        // TODO try to create
    }
}

void AppFileWatcher::setController(AppController * controller)
{
    m_controller = controller;

    // Signals
    QObject::connect(
            m_controller,
            SIGNAL(objrefCreated(
                    QString, const corbasim::gui::gui_factory_base *)),
            this,
            SLOT(objrefCreated(
                    const QString&, const 
                    corbasim::gui::gui_factory_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(objrefDeleted(QString)),
            this,
            SLOT(objrefDeleted(const QString&)));

    QObject::connect(
            m_controller,
            SIGNAL(servantCreated(
                    QString, 
                    const corbasim::gui::gui_factory_base *)),
            this,
            SLOT(servantCreated(
                    const QString&, 
                    const corbasim::gui::gui_factory_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(servantDeleted(QString)),
            this,
            SLOT(servantDeleted(const QString&)));

    // Watcher to Controller
    QObject::connect(
            this,
            SIGNAL(updateReference(QString, CORBA::Object_var)),
            m_controller,
            SLOT(updateReference(const QString&, 
                    const CORBA::Object_var&)));
}

void AppFileWatcher::objrefCreated(const QString& id,
    const corbasim::gui::gui_factory_base * factory)
{
    QString path = m_directory.absoluteFilePath(id);

    if (!m_directory.exists(id))
    {
        QFile file(path);

        if (!file.open(QIODevice::WriteOnly))
            return;

        // File exits
        file.close();
    }

    m_watcher.addPath(path);
}

void AppFileWatcher::objrefDeleted(const QString& id)
{
    QString path = m_directory.absoluteFilePath(id);
    m_watcher.removePath(path);
}

void AppFileWatcher::servantCreated(const QString& id,
    const corbasim::gui::gui_factory_base * factory)
{
}

void AppFileWatcher::servantDeleted(const QString& id)
{
}

void AppFileWatcher::fileChanged(const QString& path)
{
    QFileInfo info(path);
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString content(file.readAll());

    int offset = 0;
    QRegExp rx("IOR:(\\w+)");

    int pos;
    QString ior;

    while((pos = rx.indexIn(content, offset)) != -1)
    {
        int length = rx.matchedLength();
        ior = rx.cap();
        offset = pos + length;
    }

    if (!ior.isEmpty())
    {
        try {
            const std::string iorStr(ior.toStdString());

            CORBA::Object_var ref = 
                corbasim::core::reference_repository::get_instance()->string_to_object(iorStr);

            // notify the detected reference
            emit updateReference(info.baseName(), ref);
        } catch(...) {
        }
    }
}


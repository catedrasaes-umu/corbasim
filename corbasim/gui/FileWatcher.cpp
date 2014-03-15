// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FileWatcher.cpp
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

#include "FileWatcher.hpp"

using namespace corbasim::gui;

FileWatcher::FileWatcher(QObject * parent) :
    QObject(parent), m_watcher(this)
{
#if 0
    connect(&m_watcher,
            SIGNAL(fileChanged(QString)),
            this,
            SLOT(fileChanged(const QString&)));
#endif
}

FileWatcher::~FileWatcher()
{
}

void FileWatcher::objrefCreated(Objref_ptr objref)
{
}

void FileWatcher::objrefDeleted(ObjectId id)
{
}

#if 0
void FileWatcher::fileChanged(const QString& path)
{
    readFile(path);
}

void FileWatcher::readFile(const QString& path)
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
        ior = rx.cap();
        offset = pos + rx.matchedLength();
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
#endif


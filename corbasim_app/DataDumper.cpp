// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DataDumper.cpp
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

#include "DataDumper.hpp"
#include "AppController.hpp"
#include <iostream>
#include <fstream>
#include <corbasim/core/reflective_fwd.hpp>

using namespace corbasim::app;

DataDumper::DataDumper(QObject * parent) :
    QObject(parent), m_directory("."), m_controller(NULL)
{
}

DataDumper::~DataDumper()
{
}

void DataDumper::setController(AppController * controller)
{
    m_controller = controller;

    if (!m_controller)
        return;

    // Signals
    QObject::connect(
            m_controller,
            SIGNAL(objrefCreated(
                    QString, 
                    const corbasim::core::interface_reflective_base *)),
            this,
            SLOT(objrefCreated(
                    const QString&, 
                    const corbasim::core::interface_reflective_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(objrefDeleted(QString)),
            this,
            SLOT(objrefDeleted(const QString&)));

    QObject::connect(
            m_controller,
            SIGNAL(servantCreated(
                    QString, 
                    const corbasim::core::interface_reflective_base *)),
            this,
            SLOT(servantCreated(
                    const QString&, 
                    const corbasim::core::interface_reflective_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(servantDeleted(QString)),
            this,
            SLOT(servantDeleted(const QString&)));

#define CORBASIM_APP_CON(ev)                                         \
    QObject::connect(m_controller,                                   \
    SIGNAL(ev(QString, corbasim::event::request_ptr,                 \
            corbasim::event::event_ptr)),                            \
    this,                                                            \
    SLOT(ev(const QString&, corbasim::event::request_ptr,            \
            corbasim::event::event_ptr)));                           \
    /***/

    CORBASIM_APP_CON(requestReceived);

#undef CORBASIM_APP_CON
}

void DataDumper::objrefCreated(const QString& id, 
        const corbasim::core::interface_reflective_base * factory)
{
}

void DataDumper::objrefDeleted(const QString& id)
{
}

void DataDumper::servantCreated(const QString& id, 
        const corbasim::core::interface_reflective_base * factory)
{
    m_serializers[id] = factory;
}

void DataDumper::servantDeleted(const QString& id)
{
    m_serializers.remove(id);
}

void DataDumper::requestReceived(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    serializers_t::const_iterator it = m_serializers.find(id);

    if (it != m_serializers.end())
    {
        // TODO dump directory
        std::ofstream ofs(id.toStdString().c_str(), 
                std::ios::out | std::ios::app);

        if (ofs.good())
        {
            // TODO max file size
            // it.value()->save(ofs, req.get());
            ofs.close();
        }
    }
}

void DataDumper::setDirectory(const QString& directory)
{
    m_directory = directory;
}


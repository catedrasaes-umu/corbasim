// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ClientApp.cpp
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

#include "ClientApp.hpp"
#include <corbasim/gui/Application.hpp>
#include <corbasim/gui/client/SimpleClient.hpp>

using namespace corbasim::gui;

struct ClientApp::ClientData
{
    Application m_application;
    QThread m_applicationThread;
    SimpleClient m_window;
};

ClientApp::ClientApp(const char * fqn) :
    m_data(new ClientData)
{
    QObject::connect(&(m_data->m_application),
            SIGNAL(objrefCreated(Objref_ptr)),
            &(m_data->m_window),
            SLOT(initialize(Objref_ptr)));

    // Create the object
    ObjrefConfig cfg;
    cfg.name = "Object reference";
    cfg.fqn = fqn;

    m_data->m_application.createObjref(cfg);

    // Dedicated threads
    m_data->m_application.moveToThread(
            &(m_data->m_applicationThread));
    m_data->m_applicationThread.start();

    m_data->m_window.setWindowTitle(fqn);
    m_data->m_window.show();
}

ClientApp::~ClientApp()
{
    m_data->m_applicationThread.quit();
    m_data->m_applicationThread.wait();

    delete m_data;
}

QWidget * ClientApp::window() const
{
    return &(m_data->m_window);
}


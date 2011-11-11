// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppModel.cpp
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

#include "AppModel.hpp"
#include "AppController.hpp"

#include <dlfcn.h>

using namespace corbasim::app;

AppModel::AppModel() : m_controller(NULL)
{
}

AppModel::~AppModel()
{
}

void AppModel::setController(AppController * controller)
{
    m_controller = controller;
}

void AppModel::createObjref(const corbasim::app::ObjrefConfig& cfg)
{
    corbasim::gui::gui_factory_base * factory = NULL;

    QString lib(cfg.fqn.in());
    lib.replace("::","_");
    lib.prepend("libcorbasim_lib_");
    lib.append(".so");

    std::string str(lib.toStdString());

    typedef corbasim::gui::gui_factory_base *(*get_factory_t)();

    void * handle = dlopen(str.c_str(), RTLD_NOW);

    if (!handle)
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Library %1 not found!").arg(lib));
        return;
    }

    lib.remove(0, 3); // lib
    lib.truncate(lib.length() - 3); // .so
    str = lib.toStdString();
   
    get_factory_t get_factory = (get_factory_t) dlsym(handle,
            str.c_str());

    if (!get_factory)
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Symbol %1 not found!").arg(lib));
        return;
    }

    factory = get_factory();

    if (m_controller)
        m_controller->notifyObjrefCreated(cfg.id.in(), factory);
}


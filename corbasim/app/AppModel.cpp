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
    // TODO close libraries
}

corbasim::gui::gui_factory_base * 
AppModel::getFactory(const QString& fqn)
{
    factories_t::iterator it = m_factories.find(fqn);

    if (it != m_factories.end())
        return it->second;

    QString lib (fqn);
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
        return NULL;
    }

    lib.remove(0, 3); // lib
    lib.truncate(lib.length() - 3); // .so
    str = lib.toStdString();
   
    get_factory_t get_factory = (get_factory_t) dlsym(handle,
            str.c_str());

    if (!get_factory)
    {
        dlclose (handle);

        if (m_controller)
            m_controller->notifyError(
                    QString("Symbol %1 not found!").arg(lib));
        return NULL;
    }

    corbasim::gui::gui_factory_base * factory = get_factory();

    if (factory)
    {
        m_libraries.insert(std::make_pair(fqn, handle));
        m_factories.insert(std::make_pair(fqn, factory));
    }
    else
    {
        // Impossible is nothing!
        if (m_controller)
            m_controller->notifyError(
                    QString("Erroneus library %1!").arg(lib));

        dlclose(handle);
    }

    return factory;
}

void AppModel::setController(AppController * controller)
{
    m_controller = controller;
}

void AppModel::createObjref(const corbasim::app::ObjrefConfig& cfg)
{
    QString id(cfg.id.in());

    if (m_objrefs.find(id) != m_objrefs.end())
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Object %1 already exists!").arg(id));
        return;
    }

    corbasim::gui::gui_factory_base * factory = 
        getFactory(cfg.fqn.in());

    if (factory)
    {
        model::Objref_ptr obj(new model::Objref(cfg, factory));
        m_objrefs.insert(std::make_pair(id, obj));

        if (m_controller)
            m_controller->notifyObjrefCreated(id, factory);
    }
}

void AppModel::createServant(const corbasim::app::ServantConfig& cfg)
{
    /*
    QString id(cfg.id.in());

    if (m_objrefs.find(id) != m_objrefs.end())
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Object %1 already exists!").arg(id));
        return;
    }

    factory = get_factory();

    model::Servant_ptr obj(new model::Servant(cfg, factory));
    m_objrefs.insert(std::make_pair(id, obj));

    if (m_controller)
        m_controller->notifyServantCreated(id, factory);
    */
}

void AppModel::sendRequest(const QString& id,
        corbasim::event::request_ptr req)
{
    objrefs_t::iterator it = m_objrefs.find(id);
    if (it == m_objrefs.end())
        m_controller->notifyError(
                QString("Object %1 not found!").arg(id));
    else
    {
        corbasim::event::event_ptr ev (it->second->sendRequest(req));

        if (m_controller)
            m_controller->notifyRequestSent(id, req, ev);
    }
}

void AppModel::deleteObjref(const QString& id)
{
    if (m_objrefs.erase(id) > 0)
    {
        if (m_controller)
            m_controller->notifyObjrefDeleted(id);
    }
    else if (m_controller)
        m_controller->notifyError(
                QString("Object %1 not found!").arg(id));
}

void AppModel::deleteServant(const QString& id)
{
    /*
    if (m_objrefs.erase(id) > 0)
    {
        if (m_controller)
            m_controller->notifyServantDeleted(id);
    }
    else if (m_controller)
        m_controller->notifyError(
                QString("Object %1 not found!").arg(id));
    */
}


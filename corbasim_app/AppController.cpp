// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppController.cpp
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

#include "AppController.hpp"
#include "AppModel.hpp"

using namespace corbasim::app;

AppController::AppController(QObject * parent) :
    QObject(parent), m_model(NULL)
{
}

AppController::~AppController()
{
}

void AppController::setModel(AppModel * model)
{
    m_model = model;
}

void AppController::loadFile(const QString& file)
{
    if (m_model)
        m_model->loadFile(file);
}

void AppController::saveFile(const QString& file)
{
    if (m_model)
        m_model->saveFile(file);
}

void AppController::loadDirectory(const QString& directory)
{
    if (m_model)
        m_model->loadDirectory(directory);
}

void AppController::createObjref(const ObjrefConfig& cfg)
{
    if (m_model)
        m_model->createObjref(cfg);
}

void AppController::deleteObjref(const QString& id)
{
    if (m_model)
        m_model->deleteObjref(id);
}

void AppController::createServant(const ServantConfig& cfg)
{
    if (m_model)
        m_model->createServant(cfg);
}

void AppController::deleteServant(const QString& id)
{
    if (m_model)
        m_model->deleteServant(id);
}

void AppController::sendRequest(const QString& id,
        corbasim::event::request_ptr req)
{
    if (m_model)
        m_model->sendRequest(id, req);
}

void AppController::updateReference(const QString& id,
        const CORBA::Object_var& ref)
{
    if (m_model)
        m_model->updateReference(id, ref);
}

// Usados por el modelo

void AppController::notifyObjrefCreated(const QString& id, 
        const corbasim::core::interface_reflective_base * factory)
{
    emit objrefCreated(id, factory);
}

void AppController::notifyObjrefDeleted(const QString& id)
{
    emit objrefDeleted(id);
}

void AppController::notifyServantCreated(const QString& id, 
        const corbasim::core::interface_reflective_base * factory)
{
    emit servantCreated(id, factory);
}

void AppController::notifyServantDeleted(const QString& id)
{
    emit servantDeleted(id);
}

void AppController::notifyError(const QString& msg)
{
    emit error(msg);
}

void AppController::notifyMessage(const QString& msg)
{
    emit message(msg);
}

void AppController::notifyRequestSent(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    emit requestSent(id, req, resp);
}

void AppController::notifyRequestReceived(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    emit requestReceived(id, req, resp);
}

void AppController::notifyUpdatedReference(const QString& id,
        const CORBA::Object_var& ref)
{
    emit updatedReference(id, ref);
}

QAbstractItemModel * AppController::getFQNModel()
{
    if (m_model) return m_model->getFQNModel();
    return NULL;
}

QAbstractItemModel * AppController::getReferenceModel()
{
    if (m_model) return m_model->getReferenceModel();
    return NULL;
}


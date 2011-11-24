// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TriggerEngine.cpp
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

#include "TriggerEngine.hpp"
#include "AppController.hpp"

using namespace corbasim::app;

TriggerEngine::TriggerEngine(QObject * parent) :
    QObject(parent), m_controller(NULL), m_engine(this)
{
    // TODO add createServant and createObjref methods
}

TriggerEngine::~TriggerEngine()
{
}

void TriggerEngine::setController(AppController * controller)
{
    m_controller = controller;

    if (!m_controller)
        return;

    // Signals
    QObject::connect(
            m_controller,
            SIGNAL(objrefCreated(
                    QString, corbasim::gui::gui_factory_base *)),
            this,
            SLOT(objrefCreated(
                    const QString&, corbasim::gui::gui_factory_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(objrefDeleted(QString)),
            this,
            SLOT(objrefDeleted(const QString&)));

    QObject::connect(
            m_controller,
            SIGNAL(servantCreated(
                    QString, corbasim::gui::gui_factory_base *)),
            this,
            SLOT(servantCreated(
                    const QString&, corbasim::gui::gui_factory_base *)));
    QObject::connect(
            m_controller,
            SIGNAL(servantDeleted(QString)),
            this,
            SLOT(servantDeleted(const QString&)));

}

void TriggerEngine::objrefCreated(const QString& id, 
        corbasim::gui::gui_factory_base * factory)
{
    QScriptValue obj = m_engine.newObject();

    // TODO add 'on' method like in node.js

    QScriptValue on = m_engine.evaluate(
            "function (id, func)"
            "{"
            "   this[id] = func;"
            "}");
    obj.setProperty("on", on);

    // TODO expose methods

    m_engine.globalObject().setProperty(id, obj);
}

void TriggerEngine::objrefDeleted(const QString& id)
{
    m_engine.globalObject().setProperty(id, QScriptValue());
}

void TriggerEngine::servantCreated(const QString& id, 
        corbasim::gui::gui_factory_base * factory)
{
    QScriptValue obj = m_engine.newObject();

    // TODO expose methods

    m_engine.globalObject().setProperty(id, obj);
}

void TriggerEngine::servantDeleted(const QString& id)
{
    m_engine.globalObject().setProperty(id, QScriptValue());
}

void TriggerEngine::requestReceived(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    QScriptValue obj = m_engine.globalObject().property(id);

    if (obj.isValid() && obj.isObject())
    {
        // TODO evaluate
        QScriptValue meth = obj.property(req->get_name());

        if (meth.isValid() && meth.isFunction())
        {
            // TODO request to script
            meth.call();
        }
    }
}

void TriggerEngine::runFile(const QString& file)
{}

void TriggerEngine::runCode(const QString& code)
{}


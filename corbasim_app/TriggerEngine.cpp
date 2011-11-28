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
#include <iostream>
#include <corbasim/core/factory_fwd.hpp>

using namespace corbasim::app;

ScriptEngine::ScriptEngine(QObject * parent) :
    QScriptEngine(parent)
{
}

ScriptEngine::~ScriptEngine()
{
}

QScriptValue ScriptEngine::_call(QScriptContext * ctx, 
        QScriptEngine * eng)
{
    ScriptEngine * _this = static_cast< ScriptEngine * >(eng);

    // QScriptContextInfo info(ctx);

    QScriptValue fun = ctx->callee();

    QString id = ctx->thisObject().prototype().property("id").toString();
    QString fn = fun.property("prototype").property("name").toString();

    std::cout << "ID: " << id.toStdString() << std::endl;
    std::cout << "Function name: " << fn.toStdString() << std::endl;

    factories_t::const_iterator it = _this->m_factories.find(id);

    if (it != _this->m_factories.end())
    {
        const core::factory_base * f = it->second->get_core_factory();
        const core::operation_factory_base * op =
            f->get_factory_by_name(fn.toStdString());

        // arguments in JSON
        std::string json_request("{}"); // empty request

        if (ctx->argumentCount() > 0)
        {
            QScriptValue val = ctx->argument(0);

            // JSON string
            if (val.isString())
                json_request = 
                    val.toString().toStdString();
        }

        std::cout << "Request: " << json_request << std::endl;

        corbasim::event::request_ptr request(
                op->request_from_json(json_request));

        // send request
        _this->doSendRequest(id, request);
    }

    return QScriptValue();
}
void ScriptEngine::doSendRequest(const QString& id,
        corbasim::event::request_ptr req)
{
    emit sendRequest(id, req);
}

void TriggerEngine::doSendRequest(const QString& id,
        corbasim::event::request_ptr req)
{
    emit sendRequest(id, req);
}

QScriptValue ScriptEngine::_createObject(QScriptContext * ctx, 
        QScriptEngine * eng)
{
    QScriptContextInfo info(ctx);
    return QScriptValue();
}

QScriptValue ScriptEngine::_createServant(QScriptContext * ctx, 
        QScriptEngine * eng)
{
    QScriptContextInfo info(ctx);
    return QScriptValue();
}

void ScriptEngine::addFactory(const QString& id, gui::gui_factory_base * f) 
{
    m_factories.insert(std::make_pair(id, f));
}

void ScriptEngine::removeFactory(const QString& id)
{
    m_factories.erase(id);
}

corbasim::gui::gui_factory_base * ScriptEngine::getFactory(
        const QString& id)
{
    factories_t::const_iterator it = m_factories.find(id);

    if (it != m_factories.end())
        return it->second;

    return NULL;
}

TriggerEngine::TriggerEngine(QObject * parent) :
    QObject(parent), m_controller(NULL), m_engine(this)
{
    // add createServant and createObjref methods

    m_engine.globalObject().setProperty("createObject", 
            m_engine.newFunction(ScriptEngine::_createObject));
    m_engine.globalObject().setProperty("createServant", 
            m_engine.newFunction(ScriptEngine::_createServant));

    // Envio desde el engine
    QObject::connect(&m_engine, SIGNAL(sendRequest(QString, 
                    corbasim::event::request_ptr)),
            this, SLOT(doSendRequest(const QString&,
                    corbasim::event::request_ptr)));
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

    // Envio asincrono
    QObject::connect(this, SIGNAL(sendRequest(QString, 
                    corbasim::event::request_ptr)),
            m_controller, SLOT(sendRequest(const QString&,
                    corbasim::event::request_ptr)));
}

void TriggerEngine::objrefCreated(const QString& id, 
        corbasim::gui::gui_factory_base * factory)
{
    m_engine.addFactory(id, factory);

    QScriptValue obj = m_engine.newObject();
    obj.prototype().setProperty("id", id);

    // expose methods

    m_engine.globalObject().setProperty(id, obj);

    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        gui::operation_factory_base * op =
            factory->get_factory_by_index(i);

        // Prototype
        QScriptValue fnProto = m_engine.newObject();
        fnProto.setProperty("name", op->get_name());

        QScriptValue fn = m_engine.newFunction(ScriptEngine::_call,
                fnProto);

        obj.setProperty(QString("_%1").arg(op->get_name()), fn);

        // Convert into JSON
        m_engine.evaluate(
                QString("%1.%2 = function(request) "
                    "{ this._%2(JSON.stringify(request)); }")
                .arg(id).arg(op->get_name()));
    }
}

void TriggerEngine::objrefDeleted(const QString& id)
{
    m_engine.removeFactory(id);

    m_engine.globalObject().setProperty(id, QScriptValue());
}

void TriggerEngine::servantCreated(const QString& id, 
        corbasim::gui::gui_factory_base * factory)
{
    m_engine.addFactory(id, factory);

    QScriptValue obj = m_engine.newObject();
    obj.prototype().setProperty("id", id);

    // add 'on' method like in node.js

    m_engine.globalObject().setProperty(id, obj);

    m_engine.evaluate(QString(
    //      "var %1 = new Object;"
            "%1.on = function (op, func)"
            "{"
            "   print('Registred method ' + op + ' in %1!');"
            "   this[op] = func;"
            "}").arg(id));

    // expose methods
    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        gui::operation_factory_base * op =
            factory->get_factory_by_index(i);

        // Prototype
        QScriptValue fnProto = m_engine.newObject();
        fnProto.setProperty("name", op->get_name());

        QScriptValue fn = m_engine.newFunction(ScriptEngine::_call,
                fnProto);

        obj.setProperty(QString("_%1").arg(op->get_name()), fn);

        // Convert into JSON
        m_engine.evaluate(
                QString("%1.%2 = function(request) "
                    "{ this._%2(JSON.stringify(request)); }")
                .arg(id).arg(op->get_name()));
    }
}

void TriggerEngine::servantDeleted(const QString& id)
{
    m_engine.removeFactory(id);

    m_engine.globalObject().setProperty(id, QScriptValue());
}

void TriggerEngine::requestReceived(const QString& id, 
        corbasim::event::request_ptr req,
        corbasim::event::event_ptr resp)
{
    QScriptValue obj = m_engine.globalObject().property(id);

    if (obj.isValid() && obj.isObject())
    {
        // evaluates the trigger
        QScriptValue meth = obj.property(req->get_name());

        if (meth.isValid() && meth.isFunction())
        {
            // request to script using JSON
            const gui::gui_factory_base * factory = 
                m_engine.getFactory(id);
            
            if (!factory)
            {
                // TODO notify error: no such factory
                return;
            }

            // gets the operation factory
            const core::factory_base * core_factory =
                factory->get_core_factory();

            const core::operation_factory_base * op =
                core_factory->get_factory_by_name(req->get_name());

            if (!op)
            {
                // TODO notify error: no such operation
                return;
            }

            try {
                // JSON request
                std::string json_str;
                op->to_json(req.get(), json_str);

                std::cout << json_str << std::endl;

                // Script object with the request
                QScriptValueList args;

                QString code = QString("(%1)")
                    .arg(json_str.c_str());

                QScriptValue val = m_engine.evaluate(code);

                // Adds the object to the arguments
                args << val;

                // Call the trigger
                meth.call(obj, args);

                // TODO check uncaught exceptions
            } catch(...) {
            }
        }
    }
}

void TriggerEngine::runFile(const QString& file)
{
    QFile scriptFile(file);

    if (!scriptFile.open(QIODevice::ReadOnly))
    {
        m_controller->notifyError(QString("Can not read file %1!").arg(file));
        return;
    }

    QTextStream stream(&scriptFile);
    QString code = stream.readAll();
    scriptFile.close();

    m_engine.evaluate(code, file);

    // notify evaluation error
    if (m_engine.hasUncaughtException())
    {
        QString error = QString("%1\n\n%2")
            .arg(m_engine.uncaughtException().toString())
            .arg(m_engine.uncaughtExceptionBacktrace().join("\n"));

        m_controller->notifyError(error);
    }
}

void TriggerEngine::runCode(const QString& code)
{
    m_engine.evaluate(code);

    // notify evaluation error
    if (m_engine.hasUncaughtException())
    {
        QString error = QString("%1\n\n%2")
            .arg(m_engine.uncaughtException().toString())
            .arg(m_engine.uncaughtExceptionBacktrace().join("\n"));

        m_controller->notifyError(error);
    }
}


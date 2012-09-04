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
#include <iostream>
#include <corbasim/gui/item/ModelNode.hpp>

using namespace corbasim::gui;

QScriptValue TriggerEngine::_call(QScriptContext * ctx, 
        QScriptEngine * eng)
{
    TriggerEngine * _this = static_cast< TriggerEngine * >(eng);

    // QScriptContextInfo info(ctx);

    QScriptValue fun = ctx->callee();

    const QString id = ctx->thisObject().prototype().property("id").toString();
    const std::string method = 
        fun.property("prototype").property("name").toString().toStdString();

    /*
    std::cout << "ID: " << id.toStdString() << std::endl;
    std::cout << "Function name: " << method << std::endl;
     */

    Objref_ptr object = _this->m_objrefs.find(id);

    if (object)
    {
        const OperationDescriptor_ptr op =
            object->interface()->get_reflective_by_name(method);

        if (op)
        {
            Request_ptr req = op->create_request();

            if (ctx->argumentCount() > 0)
            {
                const QScriptValue val = ctx->argument(0);

                Holder holder(op->get_holder(req));
                Node_ptr node(new Node(op, holder));

                _this->m_clazz.fromScriptValue(val, node);

                // Request
                /*
                QScriptValue reqObject = 
                    _this->newObject(&_this->m_clazz,
                        _this->newVariant(
                            qVariantFromValue(node)));
                 */
            }

            // Thread-safe
            Event_ptr ev = object->sendRequest(req);
        }
    }

    return QScriptValue();
}

TriggerEngine::TriggerEngine(QObject * parent) :
    QScriptEngine(parent), 
    m_objrefs(this), 
    m_servants(this),
    m_clazz(this)
{
    // add createServant and createObjref methods
/*
    globalObject().setProperty("createObject", 
            newFunction(ScriptEngine::_createObject));
    globalObject().setProperty("createServant", 
            newFunction(ScriptEngine::_createServant));
*/
}

TriggerEngine::~TriggerEngine()
{
}

void TriggerEngine::objrefCreated(Objref_ptr object)
{
    m_objrefs.add(object);

    QScriptValue obj = newObject();
    obj.prototype().setProperty("id", object->name());

    // expose methods

    globalObject().setProperty(object->name(), obj);

    const InterfaceDescriptor_ptr iface = 
        object->interface();

    unsigned int count = iface->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        const OperationDescriptor_ptr op =
            iface->get_reflective_by_index(i);

        // Prototype
        QScriptValue fnProto = newObject();
        fnProto.setProperty("name", op->get_name());

        const QScriptValue fn = newFunction(
                TriggerEngine::_call,
                fnProto);

        obj.setProperty(op->get_name(), fn);
    }
}

void TriggerEngine::objrefDeleted(ObjectId id)
{
    Objref_ptr object = m_objrefs.find(id);

    if (object)
    {
        globalObject().setProperty(
                object->name(), QScriptValue());
    }

    m_objrefs.del(id);
}

void TriggerEngine::servantCreated(Objref_ptr servant)
{
    objrefCreated(servant);

    evaluate(QString(
            "this[\"%1\"]._on = function (op, func)"
            "{"
            "   print('Registred method ' + op + ' in %1!');"
            "   this['_dispatch_' + op] = func;"
            "}").arg(servant->name()));


    connect(servant.get(), 
            SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
            this,
            SLOT(requestReceived(ObjectId, Request_ptr, Event_ptr)));
}

void TriggerEngine::servantDeleted(ObjectId id)
{
    Objref_ptr servant = m_objrefs.find(id);

    if (servant)
    {
        disconnect(servant.get(), 
                SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
                this,
                SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)));
    }

    objrefDeleted(id);
}

void TriggerEngine::requestReceived(ObjectId id, 
        Request_ptr req,
        Event_ptr resp)
{
    Objref_ptr servant = m_objrefs.find(id);

    if (servant)
    {
        const QScriptValue thisObject = 
            globalObject().property(servant->name());
        QScriptValue meth = thisObject.property(
                QString("_dispatch_%1").arg(req->get_name()));

        if (meth.isValid() && meth.isFunction())
        {
            const OperationDescriptor_ptr op =
                servant->interface()->get_reflective_by_tag(req->get_tag());

            QScriptValueList args;

            // first parameter
            Holder holder(op->get_holder(req));
            Node_ptr node(new Node(op, holder));
            args << m_clazz.toScriptValue(node);

            meth.call(thisObject, args);
        }
    }
}

void TriggerEngine::runFile(const QString& file)
{
    QFile scriptFile(file);

    if (!scriptFile.open(QIODevice::ReadOnly))
    {
        const QString err = 
            QString("Can not read file %1!").arg(file);

        emit error(err);
        return;
    }

    QTextStream stream(&scriptFile);
    const QString code = stream.readAll();
    scriptFile.close();

    evaluate(code, file);

    // notify evaluation error
    if (hasUncaughtException())
    {
        const QString err = QString("%1\n\n%2")
            .arg(uncaughtException().toString())
            .arg(uncaughtExceptionBacktrace().join("\n"));

        emit error(err);
    }
}

void TriggerEngine::runCode(const QString& code)
{
    evaluate(code);

    // notify evaluation error
    if (hasUncaughtException())
    {
        const QString err = QString("%1\n\n%2")
            .arg(uncaughtException().toString())
            .arg(uncaughtExceptionBacktrace().join("\n"));

        emit error(err);
    }
}


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TriggerEngine.hpp
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

#ifndef CORBASIM_APP_TRIGGERENGINE_HPP
#define CORBASIM_APP_TRIGGERENGINE_HPP

#include <QObject>
#include <QtScript>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/event.hpp>
#include <boost/function.hpp>

namespace corbasim 
{
namespace app 
{

class AppController;

class ScriptEngine : public QScriptEngine
{
    Q_OBJECT
public:
    ScriptEngine(QObject * parent = 0);
    virtual ~ScriptEngine();

    typedef boost::function< void() > method_type;
    typedef std::map< QString, gui::gui_factory_base * > factories_t;

    static QScriptValue _call(QScriptContext *, 
            QScriptEngine *);
    static QScriptValue _createObject(QScriptContext *, 
            QScriptEngine *);
    static QScriptValue _createServant(QScriptContext *, 
            QScriptEngine *);

    void addFactory(const QString& id, gui::gui_factory_base *);
    void removeFactory(const QString& id);

    gui::gui_factory_base * getFactory(const QString& id);

signals:

    void sendRequest(QString id,
            corbasim::event::request_ptr req);

protected:

    void doSendRequest(const QString& id,
            corbasim::event::request_ptr req);

    factories_t m_factories;

};

class TriggerEngine : public QObject
{
    Q_OBJECT
public:
    TriggerEngine(QObject * parent = 0);
    virtual ~TriggerEngine();

    void setController(AppController * m_controller);

public slots:

    void runFile(const QString& file);
    void runCode(const QString& code);

    void objrefCreated(const QString& id, 
            corbasim::gui::gui_factory_base * factory);
    void objrefDeleted(const QString& id);

    void servantCreated(const QString& id, 
            corbasim::gui::gui_factory_base * factory);
    void servantDeleted(const QString& id);

    void requestReceived(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

protected slots:

    void doSendRequest(const QString& id,
            corbasim::event::request_ptr req);

signals:

    void sendRequest(QString id,
            corbasim::event::request_ptr req);

protected:

    AppController * m_controller;
    ScriptEngine m_engine;

};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_TRIGGERENGINE_HPP */


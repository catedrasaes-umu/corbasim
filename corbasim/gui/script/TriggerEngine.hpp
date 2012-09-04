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

#ifndef CORBASIM_GUI_TRIGGERENGINE_HPP
#define CORBASIM_GUI_TRIGGERENGINE_HPP

#include <QtScript>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/script/ReflectiveScriptClass.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC TriggerEngine : 
    public QScriptEngine
{
    Q_OBJECT
public:
    TriggerEngine(QObject * parent = 0);
    virtual ~TriggerEngine();

protected:

    static QScriptValue _call(QScriptContext *, 
            QScriptEngine *);
    /*
    static QScriptValue _createObject(QScriptContext *, 
            QScriptEngine *);
    static QScriptValue _createServant(QScriptContext *, 
            QScriptEngine *);
            */

public slots:

    void runFile(const QString& file);
    void runCode(const QString& code);

    void objrefCreated(Objref_ptr object);
    void objrefDeleted(ObjectId id);

    void servantCreated(Objref_ptr object);
    void servantDeleted(ObjectId id);

    void requestReceived(ObjectId id, 
            Request_ptr req,
            Event_ptr resp);

signals:

    void error(const QString&);

protected:
    
    ObjrefRepository m_objrefs;
    ObjrefRepository m_servants;
    
    ReflectiveScriptClass m_clazz;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_TRIGGERENGINE_HPP */


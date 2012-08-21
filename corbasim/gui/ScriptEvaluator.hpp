// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptEvaluatorWidget.hpp
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

#ifndef CORBASIM_GUI_SCRIPTEVALUATOR_HPP
#define CORBASIM_GUI_SCRIPTEVALUATOR_HPP

#include <QtGui>
#include <QtScript>
#include <boost/shared_ptr.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/ReflectiveScriptClass.hpp>
#include <corbasim/gui/ReflectiveGUI.hpp>

namespace corbasim 
{
namespace gui 
{

class OperationSender;

class OperationEvaluator;

typedef boost::shared_ptr< OperationEvaluator > OperationEvaluator_ptr;

class CORBASIM_GUI_DECLSPEC OperationEvaluator : 
    public QObject
{
    Q_OBJECT
public:
    OperationEvaluator(
            OperationDescriptor_ptr,
            QObject * parent = 0);
    virtual ~OperationEvaluator();

public slots:

    void evaluate(const QString& code);
    void init(Request_ptr);
    void pre(Request_ptr);
    void post(Request_ptr);

protected:

    void call(QScriptValue& func, Request_ptr req);

    OperationDescriptor_ptr m_reflective;

    QScriptEngine m_engine;
    ReflectiveScriptClass m_clazz;
    QScriptValue m_initFunc;
    QScriptValue m_preFunc;
    QScriptValue m_postFunc;
};

//
//
// Deprecated
//
//

class CORBASIM_GUI_DECLSPEC OperationEvaluatorWidget : 
    public QWidget
{
    Q_OBJECT
public:
    OperationEvaluatorWidget(Objref_ptr object, QWidget * parent = 0);
    virtual ~OperationEvaluatorWidget();
    
    void initialize(OperationDescriptor_ptr);

public slots:

    void evaluate();
    void execute();
    void save();
    void load();
    void saveForm();
    void loadForm();

protected:

    OperationDescriptor_ptr m_reflective;

    OperationEvaluator_ptr m_evaluator;
    Request_ptr m_request;

    OperationSender * m_widget;
};

class ScriptEvaluatorWidget : public QWidget
{
    Q_OBJECT
public:
    ScriptEvaluatorWidget(QWidget * parent = 0);
    virtual ~ScriptEvaluatorWidget();
    
    void initialize(InterfaceDescriptor_ptr);
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SCRIPTEVALUATOR_HPP */


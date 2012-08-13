// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptEvaluator.hpp
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
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/ReflectiveScriptClass.hpp>
#include <corbasim/gui/ReflectiveGUI.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/OperationForm.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC OperationEvaluator : 
    public QWidget
{
    Q_OBJECT
public:
    OperationEvaluator(QWidget * parent = 0);
    virtual ~OperationEvaluator();
    
    void initialize(core::operation_reflective_base const *);

public slots:

    void evaluate();
    void execute();

protected:

    core::operation_reflective_base const * m_reflective;

    QScriptEngine m_engine;
    ReflectiveScriptClass m_clazz;
    QScriptValue m_thisObject;
    QScriptValue m_initFunc;
    QScriptValue m_preFunc;
    QScriptValue m_postFunc;
    ::corbasim::event::request_ptr m_request;

    OperationForm * m_widget;
};

class ScriptEvaluator : public QWidget
{
    Q_OBJECT
public:
    ScriptEvaluator(QWidget * parent = 0);
    virtual ~ScriptEvaluator();
    
    void initialize(core::interface_reflective_base const *);
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SCRIPTEVALUATOR_HPP */


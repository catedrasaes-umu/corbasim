// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Interpreter.hpp
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

#ifndef CORBASIM_QT_INTERPRETER_HPP
#define CORBASIM_QT_INTERPRETER_HPP

#include <QtGui>
#include <corbasim/scripting/interpreter.hpp>

namespace corbasim 
{
namespace qt 
{

class Interpreter : public QWidget
{
    Q_OBJECT
public:
    Interpreter(QWidget * parent = 0);
    virtual ~Interpreter();

    void initialize(scripting::interpreter_ptr interpreter_);

public slots:

    void runCode();

protected:

    QTextEdit * m_code;

    scripting::interpreter_ptr m_interpreter;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_INTERPRETER_HPP */


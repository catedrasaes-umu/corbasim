// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Interpreter.cpp
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

#include "Interpreter.hpp"

using namespace corbasim;
using namespace corbasim::qt;

Interpreter::Interpreter(QWidget * parent) :
    QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;

    m_code = new QTextEdit;

    layout->addWidget(m_code);

    QPushButton * runBtn = new QPushButton("&Run code");

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addItem(new QSpacerItem(40, 20, 
                QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout->addWidget(runBtn);
    layout->addLayout(hLayout);

    setLayout(layout);

    QObject::connect(runBtn, SIGNAL(clicked()),
            this, SLOT(runCode()));
}

Interpreter::~Interpreter()
{
}

void Interpreter::initialize(scripting::interpreter_ptr interpreter_)
{
    m_interpreter = interpreter_;
}

void Interpreter::runCode()
{
    if (m_interpreter)
    {
        std::string code = m_code->toPlainText().toStdString();
        scripting::context_ptr ctx = m_interpreter->main_context();
        m_interpreter->exec_code(ctx, code);
    }
}


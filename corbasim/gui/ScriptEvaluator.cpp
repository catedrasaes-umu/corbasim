// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptEvaluator.cpp
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

#include "ScriptEvaluator.hpp"
#include <corbasim/qt/private/ScriptEditor.hpp>
#include <corbasim/gui/ModelNode.hpp>
#include <corbasim/gui/json.hpp>
#include <corbasim/gui/ParametersFromFilesTool.hpp>
#include <corbasim/json/reflective.hpp>

// Debug
#include <iostream>
#include <fstream>

using namespace corbasim::gui;

OperationEvaluator::OperationEvaluator(QWidget * parent) :
    QWidget(parent), m_reflective(NULL), 
    m_clazz(&m_engine), m_widget(new OperationForm())
{
    QVBoxLayout * ly = new QVBoxLayout();
    QGridLayout * btnLy = new QGridLayout();

    // Buttons
    QPushButton * btnEv = new QPushButton("E&valuate");
    btnLy->addWidget(btnEv, 0, 0);
    QPushButton * btnEx = new QPushButton("E&xecute");
    btnLy->addWidget(btnEx, 0, 1);
    QPushButton * btnSave = new QPushButton("&Save");
    btnLy->addWidget(btnSave, 0, 2);
    QPushButton * btnLoad = new QPushButton("&Load");
    btnLy->addWidget(btnLoad, 0, 3);
    QPushButton * btnSaveForm = new QPushButton("S&ave form");
    btnLy->addWidget(btnSaveForm, 1, 0);
    QPushButton * btnLoadForm = new QPushButton("L&oad form");
    btnLy->addWidget(btnLoadForm, 1, 1);

    // Main layout
    ly->addLayout(btnLy);
    ly->addWidget(m_widget);

    // Signals
    QObject::connect(btnEv, SIGNAL(clicked()), 
            this, SLOT(evaluate()));
    QObject::connect(btnEx, SIGNAL(clicked()), 
            this, SLOT(execute()));
    QObject::connect(btnSave, SIGNAL(clicked()), 
            this, SLOT(save()));
    QObject::connect(btnLoad, SIGNAL(clicked()), 
            this, SLOT(load()));
    QObject::connect(btnSaveForm, SIGNAL(clicked()), 
            this, SLOT(saveForm()));
    QObject::connect(btnLoadForm, SIGNAL(clicked()), 
            this, SLOT(loadForm()));

    setLayout(ly);
}

OperationEvaluator::~OperationEvaluator()
{
}

void OperationEvaluator::initialize(
    ::corbasim::core::operation_reflective_base const * factory)
{
    m_reflective = factory;

    m_widget->initialize(m_reflective);
}

void OperationEvaluator::evaluate()
{
    const QString strProgram (m_widget->code());
    if (!m_engine.canEvaluate(strProgram))
    {
        std::cerr << "Could not evaluate program!" << std::endl;
        return;
    }

    m_engine.evaluate(strProgram, QString(
                m_reflective->get_name())+ ".js");

    if (m_engine.hasUncaughtException())
    {
        QString error = QString("%1\n\n%2")
            .arg(m_engine.uncaughtException().toString())
            .arg(m_engine.uncaughtExceptionBacktrace().join("\n"));

        QMessageBox::critical(this, "Error", error);
        return;
    }

    // Look for this functions
    m_initFunc = m_engine.evaluate("init");
    m_preFunc = m_engine.evaluate("pre");
    m_postFunc = m_engine.evaluate("post");
 
    // This object
    m_request = m_widget->createRequest();
    core::holder holder(m_reflective->get_holder(m_request));
    Node_ptr node(new Node(m_reflective, holder));
    m_thisObject = m_engine.newObject(&m_clazz,
            m_engine.newVariant(qVariantFromValue(node)));
   
    if (m_initFunc.isFunction())
        m_initFunc.call(m_thisObject);
}

void OperationEvaluator::execute()
{
    // TODO
}

void OperationEvaluator::save()
{
    QString file = QFileDialog::getSaveFileName( 0, tr(
                "Select a file"), ".");

    if (file.isEmpty())
        return;

    QVariant var;
    m_widget->save(var);

    std::ofstream ofs(file.toStdString().c_str());
    json::ostream_writer_t ow(ofs, true);
    gui::toJson(ow, var);

    ofs << std::endl;
}

void OperationEvaluator::load()
{
    QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select a file"), ".");

    if (file.isEmpty())
        return;

    QVariant var;

    // Try to Read a JSON file
    bool res = 
        gui::fromJsonFile(file.toStdString().c_str(), var);

    if (res)
    {
        m_widget->load(var);
    }
    else
    {
        // TODO display error
    }
}

void OperationEvaluator::saveForm()
{
    QString file = QFileDialog::getSaveFileName( 0, tr(
                "Select a file"), ".");

    if (file.isEmpty())
        return;

    event::request_ptr request = m_widget->createRequest();
    core::holder holder(m_reflective->get_holder(request));

    std::ofstream out(file.toStdString().c_str());

    json::write(out, m_reflective, holder, true);
}

void OperationEvaluator::loadForm()
{
    QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select a file"), ".");

    if (file.isEmpty())
        return;

    event::request_ptr request = m_reflective->create_request();
    core::holder holder(m_reflective->get_holder(request));

    std::ifstream in(file.toStdString().c_str());

    json::parse(m_reflective, holder, in);

    m_widget->getWidget()->setValue(request);
}

//
//
// Script evaluator
//
//

ScriptEvaluator::ScriptEvaluator(QWidget * parent) :
    QWidget(parent)
{
}

ScriptEvaluator::~ScriptEvaluator()
{
}

void ScriptEvaluator::initialize(
    ::corbasim::core::interface_reflective_base const * factory)
{
    // Each operation evaluator in a tab
    QVBoxLayout * ly = new QVBoxLayout();
    QTabWidget * tabs = new QTabWidget();

    const unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        const core::operation_reflective_base * op = 
            factory->get_reflective_by_index(i);
        const char * name = op->get_name();

        OperationEvaluator * ev = new OperationEvaluator();
        ev->initialize(op);

        tabs->addTab(ev, name);
    }

    ly->addWidget(tabs);
    setLayout(ly);
}



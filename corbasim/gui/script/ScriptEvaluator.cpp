// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptEvaluatorWidget.cpp
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

#include <corbasim/json/reflective.hpp>
#include <corbasim/qt/private/ScriptEditor.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/item/ModelNode.hpp>
#include <corbasim/gui/json.hpp>
#include <corbasim/gui/OperationForm.hpp>

#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

// Debug
#include <iostream>
#include <fstream>

using namespace corbasim::gui;

OperationEvaluator::OperationEvaluator(
        ::corbasim::core::operation_reflective_base const * reflective,
        QObject * parent) :
    QObject(parent), m_reflective(reflective),
    m_clazz(&m_engine)
{
}

OperationEvaluator::~OperationEvaluator()
{
}

void OperationEvaluator::evaluate(const QString& code)
{
    m_engine.evaluate(code, QString(m_reflective->get_name())+ ".js");

    if (m_engine.hasUncaughtException())
    {
        // TODO
    }
    else
    {
        // Look for this functions
        m_initFunc = m_engine.evaluate("init");
        m_preFunc = m_engine.evaluate("pre");
        m_postFunc = m_engine.evaluate("post");

        m_engine.clearExceptions();
    }
}

void OperationEvaluator::init(Request_ptr req)
{
    call(m_initFunc, req);
}

void OperationEvaluator::pre(Request_ptr req)
{
    call(m_preFunc, req);
}

void OperationEvaluator::post(Request_ptr req)
{
    call(m_postFunc, req);
}

void OperationEvaluator::call(QScriptValue& func,
        Request_ptr req)
{
    if (func.isFunction())
    {
        core::holder holder(m_reflective->get_holder(req));

        Node_ptr node(new Node(m_reflective, holder));

        QScriptValue thisObject = m_engine.newObject(&m_clazz,
                m_engine.newVariant(qVariantFromValue(node)));

        func.call(thisObject);
    }
}

bool OperationEvaluator::hasError() const
{
    return m_engine.hasUncaughtException();
}

QString OperationEvaluator::error() const
{
    return m_engine.uncaughtException().toString();
}

//
//
// Deprecated.
//
//

OperationEvaluatorWidget::OperationEvaluatorWidget(Objref_ptr object,
        OperationDescriptor_ptr op,
        QWidget * parent) :
    QWidget(parent), m_reflective(op),
    m_widget(new OperationSender(object, op))
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
    btnLy->addWidget(btnSaveForm, 0, 4);
    QPushButton * btnLoadForm = new QPushButton("L&oad form");
    btnLy->addWidget(btnLoadForm, 0, 5);

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

    m_evaluator.reset(new OperationEvaluator(op, this));
}

OperationEvaluatorWidget::~OperationEvaluatorWidget()
{
}

void OperationEvaluatorWidget::evaluate()
{
    if (!m_evaluator)
        return;

    const QString strProgram (m_widget->getForm()->code());

    m_evaluator->evaluate(strProgram);

    // This object
    m_request = m_widget->getForm()->createRequest();

    m_evaluator->init(m_request);
}

void OperationEvaluatorWidget::execute()
{
    m_evaluator->pre(m_request);

    // TODO

    m_evaluator->post(m_request);
}

void OperationEvaluatorWidget::save()
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

void OperationEvaluatorWidget::load()
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
        QMessageBox::critical(this, "Error",
                QString("Error parsing file: %1").arg(file));
    }
}

void OperationEvaluatorWidget::saveForm()
{
    QString file = QFileDialog::getSaveFileName( 0, tr(
                "Select a file"), ".");

    if (file.isEmpty())
        return;

    core::request_ptr request =
        m_widget->getForm()->createRequest();
    core::holder holder(m_reflective->get_holder(request));

    std::ofstream out(file.toStdString().c_str());

    json::write(out, m_reflective, holder, true);
}

void OperationEvaluatorWidget::loadForm()
{
    QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select a file"), ".");

    if (file.isEmpty())
        return;

    core::request_ptr request =
        m_reflective->create_request();
    core::holder holder(m_reflective->get_holder(request));

    std::ifstream in(file.toStdString().c_str());

    if (json::parse(m_reflective, holder, in))
    {
        m_widget->getForm()->getWidget()->setValue(request);
    }
    else
    {
         QMessageBox::critical(this, "Error",
                QString("Error parsing file: %1").arg(file));
    }
}

//
//
// Script evaluator
//
//

ScriptEvaluatorWidget::ScriptEvaluatorWidget(QWidget * parent) :
    QWidget(parent)
{
    corbasim::gui::initialize();
}

ScriptEvaluatorWidget::~ScriptEvaluatorWidget()
{
}

void ScriptEvaluatorWidget::initialize(
    InterfaceDescriptor_ptr factory)
{
    // Dummy object
    Objref_ptr object(new Objref("this", factory));

    // Each operation evaluator in a tab
    QVBoxLayout * ly = new QVBoxLayout();
    QTabWidget * tabs = new QTabWidget();

    const unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++)
    {
        const core::operation_reflective_base * op =
            factory->get_reflective_by_index(i);
        const char * name = op->get_name();

        OperationEvaluatorWidget * ev =
            new OperationEvaluatorWidget(object, op);

        tabs->addTab(ev, name);
    }

    ly->addWidget(tabs);
    setLayout(ly);
}



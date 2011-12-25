// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptEditor.Cpp
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

#include "ScriptEditor.hpp"
#include <fstream>
#include <iostream>
#include <corbasim/qt/MultiInputWidget.hpp>
#include <corbasim/gui/gui_factory.hpp>
#include <boost/next_prior.hpp>

using namespace corbasim;
using namespace corbasim::qt;

ScriptEditor::ScriptEditor(QWidget * parent) :
    QMainWindow(parent), m_factory(NULL)
{
    QWidget * central = new QWidget();
    setCentralWidget(central);

    m_code = new QTextEdit;
    m_selector = new QComboBox;

    m_how_many = new QSpinBox;
    m_how_many->setRange(1, 9999);
    m_how_many->setValue(1);

    m_multi = new MultiInputWidget;

    QHBoxLayout * mainLayout = new QHBoxLayout;
    QVBoxLayout * inputLayout = new QVBoxLayout;

    // Arriba
    QHBoxLayout * selLayout = new QHBoxLayout;
    selLayout->addWidget(new QLabel("Operation"));
    selLayout->addWidget(m_selector);
    selLayout->addWidget(new QLabel("Times"));
    selLayout->addWidget(m_how_many);
    inputLayout->addLayout(selLayout);

    inputLayout->addWidget(m_multi);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(m_code);

    central->setLayout(mainLayout);

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)), 
            m_multi, SLOT(changeInputForm(int)));

    setWindowTitle("Script editor");

    // Actions
    // Load
    QAction * loadAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogOpenButton),
            "&Load", this);
    loadAction->setShortcut(QKeySequence::Open);
    QObject::connect(loadAction, SIGNAL(triggered()), 
            this, SLOT(doLoad()));

    // Save
    QAction * saveAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogSaveButton),
            "&Save as...", this);
    saveAction->setShortcut(QKeySequence::SaveAs);
    QObject::connect(saveAction, SIGNAL(triggered()), 
            this, SLOT(doSave()));

    // Append
    QAction * appendAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogApplyButton),
            "&Append request", this);
    appendAction->setShortcut(QKeySequence::Redo);
    QObject::connect(appendAction, SIGNAL(triggered()), 
            this, SLOT(appendRequest()));

    QAction * appendOneAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogApplyButton),
            "Append &just a request", this);
    appendOneAction->setShortcut(QKeySequence::New);
    QObject::connect(appendOneAction, SIGNAL(triggered()), 
            this, SLOT(appendOneRequest()));

    // Clear script
    QAction * clearAction = new QAction(
            style()->standardIcon(QStyle::SP_TrashIcon),
            "&Clear script", this);
    clearAction->setShortcut(QKeySequence::Cut);
    QObject::connect(clearAction, SIGNAL(triggered()), 
            this, SLOT(clearClicked()));

    // Play
    QAction * playAction = new QAction(
            style()->standardIcon(QStyle::SP_MediaPlay),
            "&Play", this);
    playAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    QObject::connect(playAction, SIGNAL(triggered()), 
            this, SLOT(playClicked()));

    QAction * playSelectedAction = new QAction(
            style()->standardIcon(QStyle::SP_MediaPlay),
            "Play &from selected item", this);
    playSelectedAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Space));
    QObject::connect(playSelectedAction, SIGNAL(triggered()), 
            this, SLOT(playFromSelected()));

    // Stop
    QAction * stopAction = new QAction(
            style()->standardIcon(QStyle::SP_MediaStop),
            "&Stop", this);
    // stopAction->setShortcut(QKeySequence::Cut);
    QObject::connect(stopAction, SIGNAL(triggered()), 
            this, SLOT(stopClicked()));

    // Send current
    QAction * sendCurrentAction = new QAction(
            style()->standardIcon(QStyle::SP_MediaPlay),
            "Send &current value", this);
    sendCurrentAction->setShortcut(QKeySequence::Save);
    QObject::connect(sendCurrentAction, SIGNAL(triggered()), 
            this, SLOT(sendCurrent()));

    // Menu
    QMenu * fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    QAction * closeAction = 
        fileMenu->addAction("&Close", this, SLOT(hide()));

    closeAction->setShortcut(QKeySequence::Close);

    QMenu * scriptMenu = menuBar()->addMenu("&Script");
    scriptMenu->addAction(appendAction);
    scriptMenu->addAction(appendOneAction);
    scriptMenu->addAction(clearAction);
    
    QMenu * playerMenu = menuBar()->addMenu("&Player");
    playerMenu->addAction(playAction);
    playerMenu->addAction(playSelectedAction);
    playerMenu->addAction(stopAction);
    playerMenu->addSeparator();
    playerMenu->addAction(sendCurrentAction);

    // Tool bar
    QToolBar * toolBar = addToolBar("File");
    toolBar->addAction(loadAction);
    toolBar->addAction(saveAction);

    toolBar = addToolBar("Script");
    m_cbInsertAtEnd = new QCheckBox("Insert before selected");
    toolBar->addWidget(m_cbInsertAtEnd);
    toolBar->addAction(appendAction);
    toolBar->addAction(appendOneAction);
    toolBar->addAction(clearAction);

    toolBar = addToolBar("Player");
    toolBar->addAction(playAction);
    toolBar->addAction(playSelectedAction);
    toolBar->addAction(stopAction);
    toolBar->addSeparator();
    toolBar->addAction(sendCurrentAction);
    
    setWindowIcon(QIcon(":/resources/images/csu.png"));
}

ScriptEditor::~ScriptEditor()
{
}

void ScriptEditor::initialize(gui::gui_factory_base const * factory)
{
    unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
        m_selector->addItem(factory->get_factory_by_index(i)->get_name());

    m_multi->initialize(factory);
    m_factory = factory;
}

void ScriptEditor::playFromSelected()
{
    // TODO
}

void ScriptEditor::sendNextRequest()
{
    // TODO
}

void ScriptEditor::sendCurrent()
{
    // TODO
}

void ScriptEditor::appendRequest()
{
    // Obtiene el dialogo seleccionado
    dialogs::input_ptr dlg = m_multi->getCurrentDialog();

    for (int i = 0; i < m_how_many->value(); i++) 
    {
        // Crea una request del tipo seleccionado con los valores
        // del dialogo
        event::request_ptr req(dlg->create_request());

        doAppendRequest(req, m_cbInsertAtEnd->isChecked());
    }
}

void ScriptEditor::appendOneRequest()
{
    // Obtiene el dialogo seleccionado
    dialogs::input_ptr dlg = m_multi->getCurrentDialog();

    // Crea una request del tipo seleccionado con los valores
    // del dialogo
    event::request_ptr req(dlg->create_request());

    doAppendRequest(req, m_cbInsertAtEnd->isChecked());
}

void ScriptEditor::playClicked()
{   
    // TODO
}

void ScriptEditor::clearClicked()
{
    m_code->clear();
}

void ScriptEditor::stopClicked()
{
    // TODO
}

void ScriptEditor::doSave()
{
    // Seleccionar fichero
    QString log_file = QFileDialog::getSaveFileName( 0, tr(
                "Select a script file"), ".");

    // User cancels
    if (log_file.isEmpty())
        return;

    std::ofstream ofs(log_file.toStdString().c_str());

    ofs << m_code->toPlainText().toStdString();
}

void ScriptEditor::doLoad()
{
    QStringList log_file = QFileDialog::getOpenFileNames( 0, tr(
                "Select some script files"), ".");

    // User cancels
    if (log_file.isEmpty())
        return;

    // TODO load
}

void ScriptEditor::doAppendRequest(event::request_ptr _request, bool beforeSelected)
{
    QString line = _request->get_name();
    line += '(';
    
    // Parameters
    std::string params;
    m_factory->get_core_factory()->get_factory_by_tag(
            _request->get_tag())->to_json(_request.get(), params);
    line += params.c_str();

    line += ')';

    m_code->append(line);
}


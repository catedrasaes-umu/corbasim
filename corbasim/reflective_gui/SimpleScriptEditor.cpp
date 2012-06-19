// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SimpleScriptEditor.Cpp
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

#include "SimpleScriptEditor.hpp"
#include <fstream>
#include <iostream>
#include <boost/next_prior.hpp>
#include <corbasim/reflective_gui/ReflectiveGUI.hpp>
#include <corbasim/json/reflective.hpp>
#include <corbasim/json/parser.hpp> // for parse

using namespace corbasim;
using namespace corbasim::reflective_gui;

SimpleScriptEditor::SimpleScriptEditor(QWidget * parent) :
    QMainWindow(parent), m_timer(this), m_current_request(0), 
    m_factory(NULL)
{
    QWidget * central = new QWidget();
    setCentralWidget(central);

    m_tree = new QTreeView();
    m_tree->setModel(&m_model);
    m_tree->setDragDropMode(QAbstractItemView::DragOnly);
    m_tree->setDragEnabled(true);

    m_selector = new QComboBox();
    m_selector->setEditable(true);
    m_selector->setInsertPolicy(QComboBox::NoInsert);

    m_diff = new QSpinBox();
    m_diff->setRange(0, 9999);
    m_diff->setValue(200);
    m_diff->setSuffix(" ms");

    m_how_many = new QSpinBox();
    m_how_many->setRange(1, 9999);
    m_how_many->setValue(1);

    m_multi = new QStackedWidget();

    QHBoxLayout * mainLayout = new QHBoxLayout();
    QVBoxLayout * inputLayout = new QVBoxLayout();

    // Arriba
    QHBoxLayout * selLayout = new QHBoxLayout;
    selLayout->addWidget(new QLabel("Operation"));
    selLayout->addWidget(m_selector);
    selLayout->addWidget(new QLabel("Diff"));
    selLayout->addWidget(m_diff);
    selLayout->addWidget(new QLabel("Times"));
    selLayout->addWidget(m_how_many);
    inputLayout->addLayout(selLayout);

    inputLayout->addWidget(m_multi);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(m_tree);

    central->setLayout(mainLayout);

    QObject::connect(m_selector, SIGNAL(currentIndexChanged(int)), 
            m_multi, SLOT(setCurrentIndex(int)));

    QObject::connect(&m_timer, SIGNAL(timeout()), 
            this, SLOT(sendNextRequest()));

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

    // Copy selected item
    QAction * copyAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogApplyButton),
            "&Copy selected item", this);
    copyAction->setShortcut(QKeySequence::Copy);
    QObject::connect(copyAction, SIGNAL(triggered()), 
            this, SLOT(copySelected()));

    // Replace selected item
    QAction * replaceAction = new QAction(
            style()->standardIcon(QStyle::SP_FileDialogDetailedView),
            "&Replace selected item", this);
    replaceAction->setShortcut(QKeySequence::Paste);
    QObject::connect(replaceAction, SIGNAL(triggered()), 
            this, SLOT(replaceSelected()));

    // Delete selected item
    QAction * deleteAction = new QAction(
            style()->standardIcon(QStyle::SP_TrashIcon),
            "&Delete selected item", this);
    deleteAction->setShortcut(QKeySequence::Delete);
    QObject::connect(deleteAction, SIGNAL(triggered()), 
            this, SLOT(deleteSelected()));

    // Clear script
    QAction * clearAction = new QAction(
            style()->standardIcon(QStyle::SP_TrashIcon),
            "&Clear script", this);
    clearAction->setShortcut(QKeySequence::Cut);
    QObject::connect(clearAction, SIGNAL(triggered()), 
            this, SLOT(clearClicked()));

    // Move up
    QAction * moveUpAction = new QAction(
            style()->standardIcon(QStyle::SP_ArrowUp),
            "Move &up", this);
    moveUpAction->setShortcut(QKeySequence::MoveToPreviousPage);
    QObject::connect(moveUpAction, SIGNAL(triggered()), 
            this, SLOT(moveUp()));

    // Move down
    QAction * moveDownAction = new QAction(
            style()->standardIcon(QStyle::SP_ArrowDown),
            "Move &down", this);
    moveDownAction->setShortcut(QKeySequence::MoveToNextPage);
    QObject::connect(moveDownAction, SIGNAL(triggered()), 
            this, SLOT(moveDown()));

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
    playSelectedAction->setShortcut(
            QKeySequence(Qt::CTRL + Qt::Key_Space));
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
    scriptMenu->addAction(copyAction);
    scriptMenu->addAction(replaceAction);
    scriptMenu->addAction(deleteAction);
    scriptMenu->addAction(clearAction);
    scriptMenu->addSeparator();
    scriptMenu->addAction(moveUpAction);
    scriptMenu->addAction(moveDownAction);
    
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

    toolBar = addToolBar("Player");
    toolBar->addAction(playAction);
    toolBar->addAction(playSelectedAction);
    toolBar->addAction(stopAction);
    toolBar->addSeparator();
    toolBar->addAction(sendCurrentAction);

    toolBar = addToolBar("Script");
    m_cbInsertAtEnd = new QCheckBox("Insert before selected");
    toolBar->addWidget(m_cbInsertAtEnd);
    toolBar->addAction(appendAction);
    toolBar->addAction(appendOneAction);
    toolBar->addAction(copyAction);
    toolBar->addAction(replaceAction);
    toolBar->addAction(deleteAction);
    toolBar->addAction(clearAction);
    toolBar->addSeparator();
    toolBar->addAction(moveUpAction);
    toolBar->addAction(moveDownAction);
    
    setWindowIcon(QIcon(":/resources/images/csu.png"));
}

SimpleScriptEditor::~SimpleScriptEditor()
{
}

void SimpleScriptEditor::initialize(
        core::interface_reflective_base const * factory)
{
    unsigned int count = factory->operation_count();
    m_forms.reserve(count);

    m_model.initialize(factory);

    for (unsigned int i = 0; i < count; i++) 
    {
        core::operation_reflective_base const * op =
            factory->get_reflective_by_index(i);

        OperationInputForm * form = new OperationInputForm(op);

        // Scroll
        QScrollArea * scroll = new QScrollArea();
        scroll->setWidgetResizable(true);
        scroll->setWidget(form);
        m_multi->addWidget(scroll);

        m_forms.push_back(form);

        m_selector->addItem(op->get_name());
    }

    m_factory = factory;
}

void SimpleScriptEditor::moveUp()
{
}

void SimpleScriptEditor::moveDown()
{
}

void SimpleScriptEditor::playFromSelected()
{
    int pos = getSelected();

    if (pos >= 0)
    {
        m_current_request = pos;

        if (m_timer.isActive())
            m_timer.stop();

        m_timer.start(m_diff->value());
    }
}

void SimpleScriptEditor::deleteSelected()
{
    int pos = getSelected();

    m_model.deletePosition(pos);
}

void SimpleScriptEditor::replaceSelected()
{
    int pos = getSelected();

    int form = m_selector->currentIndex();

    if (form == -1) return;

    event::request_ptr req(m_forms[form]->createRequest());

    doAppendRequest(req, true);

    // Elimina el actual
    deleteSelected();
    
    m_tree->setCurrentIndex(m_model.index(pos, 0));
}

void SimpleScriptEditor::sendNextRequest()
{
    if (m_current_request < m_model.rowCount())
    {
        // Selecciona la siguiente request en el arbol
        m_tree->setCurrentIndex(m_model.index(m_current_request, 0));

        emit sendRequest(m_model.getRequest(m_current_request++));
    }
    else
        m_timer.stop();
}

void SimpleScriptEditor::sendCurrent()
{
    int idx = m_selector->currentIndex();

    if (idx == -1) return;

    event::request_ptr req = m_forms[idx]->createRequest();

    emit sendRequest(req);
}

void SimpleScriptEditor::appendRequest()
{
    int idx = m_selector->currentIndex();

    if (idx == -1) return;

    for (int i = 0; i < m_how_many->value(); i++) 
    {
        event::request_ptr req = m_forms[idx]->createRequest();

        doAppendRequest(req, m_cbInsertAtEnd->isChecked());
    }
}

void SimpleScriptEditor::appendOneRequest()
{
    int idx = m_selector->currentIndex();

    if (idx == -1) return;

    event::request_ptr req = m_forms[idx]->createRequest();

    doAppendRequest(req, m_cbInsertAtEnd->isChecked());
}

void SimpleScriptEditor::playClicked()
{   
    m_current_request = 0;

    if (m_timer.isActive())
        m_timer.stop();

    m_timer.start(m_diff->value());
}

void SimpleScriptEditor::clearClicked()
{
    m_model.clearLog();
}

void SimpleScriptEditor::stopClicked()
{
    m_timer.stop();
}

void SimpleScriptEditor::doSave()
{
    if (!m_factory)
        return;

    // Seleccionar fichero
    QString log_file = QFileDialog::getSaveFileName( 0, tr(
                "Select a script file"), ".");

    // User cancels
    if (log_file.isEmpty())
        return;

    std::ofstream ofs(log_file.toStdString().c_str());
    json::std_writer_t writer(ofs, true);

    typedef ::corbasim::event::request_ptr request_ptr;
    typedef ::corbasim::core::operation_reflective_base const * op_ptr;

    writer.array_start();

    for (int i = 0; i < m_model.rowCount(); i++) 
    {
        writer.object_start();

        request_ptr req (m_model.getRequest(i));

        if (!req) continue; // Not possible!

        op_ptr op (m_factory->get_reflective_by_tag(req->get_tag()));
        
        if (!op)  continue; // Not possible!

        writer.new_string(op->get_name());

        core::holder holder(op->get_holder(req));

        json::write(writer, op, holder);

        writer.object_end();
    }

    writer.array_end();
}

namespace 
{

typedef corbasim::reflective_gui::ScriptModel ScriptModel;
typedef ::corbasim::core::operation_reflective_base const * op_ptr;
typedef ::corbasim::core::interface_reflective_base const * interface_ptr;

using ::corbasim::event::request_ptr;
using ::corbasim::core::holder;

struct operation_helper : public corbasim::json::helper::helper_base
{

    ScriptModel& m_model;
    corbasim::json::helper::helper_base *  m_helper;
    request_ptr m_request;

    operation_helper(ScriptModel& model, op_ptr op) : 
        m_model(model)
    {
        m_request = op->create_request();
        holder h(op->get_holder(m_request));

        m_helper = new corbasim::json::reflective_helper(op, h);
    }

    virtual ~operation_helper()
    {
        m_model.addRequest(m_request);

        delete m_helper;
    }

    corbasim::json::helper::helper_base* new_child(const std::string& name)
    {
        return m_helper->new_child(name);
    }
};

struct script_helper : public corbasim::json::helper::helper_base
{
    ScriptModel& m_model;
    interface_ptr m_factory;

    script_helper(ScriptModel& model, interface_ptr factory) : 
        m_model(model), m_factory(factory)
    {}


    corbasim::json::helper::helper_base* new_child(const std::string& name)
    {
        op_ptr op (m_factory->get_reflective_by_name(name.c_str()));

        if (!op) throw "Error";

        return new operation_helper(m_model, op);
    }

    // For arrays
    corbasim::json::helper::helper_base* new_child()
    {
        return new script_helper(m_model, m_factory);
    }
};

} // namespace

void SimpleScriptEditor::doLoad()
{
    if (!m_factory)
        return;

    const QStringList script_files = QFileDialog::getOpenFileNames( 0, tr(
                "Select some script files"), ".");

    // User cancels
    if (script_files.isEmpty())
        return;

    typedef ::corbasim::event::request_ptr request_ptr;
    typedef ::corbasim::core::operation_reflective_base const * op_ptr;

    std::vector< char > buf;

    for (int i = 0; i < script_files.length(); i++) 
    {
        try {

            std::ifstream is(script_files.at(i).toStdString().c_str());
            
            if (!is.is_open()) continue;
   
            // get length of file:
            is.seekg (0, std::ios::end);
            std::size_t length = is.tellg();
            is.seekg (0, std::ios::beg);

            // allocate memory:
            buf.resize(length);

            // read data as a block:
            is.read (&(*buf.begin()), length);
            is.close();

            corbasim::json::parse(
                new script_helper(m_model, m_factory),
                &(*buf.begin()), length);

        } catch (...) 
        {
            std::cerr << "Error loading file!" << std::endl;

            QMessageBox::critical(this, "Error", 
                    QString("Error loading file %1").arg(script_files.at(i)));
        }
    }
}

int SimpleScriptEditor::getSelected()
{
    return m_model.indexToPosition(m_tree->currentIndex());
}

void SimpleScriptEditor::copySelected()
{
    int pos = getSelected();

    if (pos >= 0)
    {
        event::request_ptr selected = m_model.getRequest(pos);

        core::operation_reflective_base const * op =
            m_factory->get_reflective_by_tag(selected->get_tag());

        int cb_pos = m_selector->findText(
                QString(op->get_name()),
                Qt::MatchFixedString| Qt::MatchCaseSensitive);

        // copiar 'it' al editor correspondiente
        m_forms[cb_pos]->setValue(selected);

        // mostrar el editor correspondiente
        m_selector->setCurrentIndex(cb_pos);
    }
}

void SimpleScriptEditor::doAppendRequest(event::request_ptr _request, 
        bool beforeSelected)
{
    int pos = getSelected();

    if (pos >= 0 && beforeSelected)
        m_model.addRequest(_request, pos);
    else
        m_model.addRequest(_request, -1);
}

void SimpleScriptEditor::hideEvent(QHideEvent * event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}


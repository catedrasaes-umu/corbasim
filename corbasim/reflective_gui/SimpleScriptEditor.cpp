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

using namespace corbasim;
using namespace corbasim::reflective_gui;

SimpleScriptEditor::SimpleScriptEditor(QWidget * parent) :
    QMainWindow(parent), m_timer(this), m_current_request(0), 
    m_factory(NULL)
{
    QWidget * central = new QWidget();
    setCentralWidget(central);

    m_tree = new QTreeWidget;
    m_tree->setHeaderLabel("Script");
    m_selector = new QComboBox;
    m_selector->setEditable(true);
    m_selector->setInsertPolicy(QComboBox::NoInsert);
    m_diff = new QSpinBox;
    m_diff->setRange(0, 9999);
    m_diff->setValue(200);
    m_diff->setSuffix(" ms");

    m_how_many = new QSpinBox;
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

    for (unsigned int i = 0; i < count; i++) 
    {
        core::operation_reflective_base const * op =
            factory->get_reflective_by_index(i);

        OperationInputForm * form = new OperationInputForm(op);
        m_multi->addWidget(form);
        m_forms.push_back(form);

        m_selector->addItem(op->get_name());
    }

    m_factory = factory;
}

void SimpleScriptEditor::moveUp()
{
    int pos = getSelected();

    if (pos > 0)
    {
        // La elimina de la posición actual
        requests_t::iterator it = boost::next(m_requests.begin(), pos);
        event::request_ptr selected = *it;
        m_requests.erase(it);

        // La añade en la nueva
        it = boost::next(m_requests.begin(), pos - 1);
        m_requests.insert(it, selected);

        // Tree
        QTreeWidgetItem * item = m_tree->takeTopLevelItem(pos);
        m_tree->insertTopLevelItem(pos - 1, item);

        // Selecciona el elemento
        m_tree->setCurrentItem(item);
    }
}

void SimpleScriptEditor::moveDown()
{
    int pos = getSelected();

    if (pos >= 0 && pos < (int) m_requests.size() - 1)
    {
        // La elimina de la posición actual
        requests_t::iterator it = boost::next(m_requests.begin(), pos);
        event::request_ptr selected = *it;
        m_requests.erase(it);

        // La añade en la nueva
        it = boost::next(m_requests.begin(), pos + 1);
        m_requests.insert(it, selected);

        // Tree
        QTreeWidgetItem * item = m_tree->takeTopLevelItem(pos);
        m_tree->insertTopLevelItem(pos + 1, item);
       
        // Selecciona el elemento
        m_tree->setCurrentItem(item);
    }
}

void SimpleScriptEditor::playFromSelected()
{
    int pos = getSelected();

    if (pos >= 0)
    {
        m_current_request = pos;

        if (m_timer.isActive())
            m_timer.stop();

        m_current_iterator = boost::next(m_requests.begin(), pos);

        m_timer.start(m_diff->value());
    }
}

void SimpleScriptEditor::deleteSelected()
{
    int pos = getSelected();

    assert(m_tree->topLevelItemCount() == (int) m_requests.size());

    if (pos >= 0 && pos < m_tree->topLevelItemCount())
    {
        requests_t::iterator it = boost::next(m_requests.begin(), pos);
        m_requests.erase(it);
        delete m_tree->takeTopLevelItem(pos);
    }
}

void SimpleScriptEditor::replaceSelected()
{
    int pos = getSelected();

#if 0
    // Añade la nueva
    dialogs::input_ptr dlg = m_multi->getCurrentDialog();

    if (!dlg) return;

    event::request_ptr req(dlg->create_request());
    doAppendRequest(req, true);
#endif

    // Elimina el actual
    deleteSelected();
    
    // Selecciona la nueva entrada
    QTreeWidgetItem * item = m_tree->topLevelItem(pos);
    m_tree->setCurrentItem(item);
}

void SimpleScriptEditor::sendNextRequest()
{
    if (m_current_request < m_requests.size())
    {
        // Selecciona la siguiente request en el arbol
        m_tree->setCurrentItem(m_tree->topLevelItem(m_current_request++));
        emit sendRequest(*(m_current_iterator++));
    }
    else
        m_timer.stop();
}

void SimpleScriptEditor::sendCurrent()
{
#if 0
    // Obtiene el dialogo seleccionado
    dialogs::input_ptr dlg = m_multi->getCurrentDialog();

    if (!dlg) return;

    event::request_ptr req(dlg->create_request());

    emit sendRequest(req);
#endif
}

void SimpleScriptEditor::appendRequest()
{
#if 0
    // Obtiene el dialogo seleccionado
    dialogs::input_ptr dlg = m_multi->getCurrentDialog();
    
    if (!dlg) return;

    for (int i = 0; i < m_how_many->value(); i++) 
    {
        // Crea una request del tipo seleccionado con los valores
        // del dialogo
        event::request_ptr req(dlg->create_request());

        doAppendRequest(req, m_cbInsertAtEnd->isChecked());
    }
#endif
}

void SimpleScriptEditor::appendOneRequest()
{
#if 0
    // Obtiene el dialogo seleccionado
    dialogs::input_ptr dlg = m_multi->getCurrentDialog();
    
    if (!dlg) return;

    // Crea una request del tipo seleccionado con los valores
    // del dialogo
    event::request_ptr req(dlg->create_request());

    doAppendRequest(req, m_cbInsertAtEnd->isChecked());
#endif
}

void SimpleScriptEditor::playClicked()
{   
    m_current_request = 0;

    if (m_timer.isActive())
        m_timer.stop();

    m_current_iterator = m_requests.begin();

    m_timer.start(m_diff->value());
}

void SimpleScriptEditor::clearClicked()
{
    m_tree->clear();
    m_requests.clear();
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

#warning "TODO"
#if 0
    for (requests_t::const_iterator it = m_requests.begin(); 
            it != m_requests.end(); it++) 
        m_factory->get_core_factory()->save(ofs, (*it).get());
#endif
}

void SimpleScriptEditor::doLoad()
{
    if (!m_factory)
        return;

    const QStringList log_file = QFileDialog::getOpenFileNames( 0, tr(
                "Select some script files"), ".");

    // User cancels
    if (log_file.isEmpty())
        return;

#warning "TODO"
#if 0
    for (int i = 0; i < log_file.length(); i++) 
    {
        std::ifstream ifs(log_file.at(i).toStdString().c_str());

        try {
            while(ifs.good())
            {
                event::request_ptr _request(
                        m_factory->get_core_factory()->load(ifs));

                if (!_request)
                    continue;

                doAppendRequest(_request);
            }
        } catch (...) 
        {
            std::cerr << "Error loading file!" << std::endl;
        }
    }
#endif
}

int SimpleScriptEditor::getSelected()
{
    QTreeWidgetItem* current = m_tree->currentItem();
 
    // Obtiene el elemento de nivel superior 
    while(current && current->parent())
        current = current->parent();

    if (current)
        return m_tree->indexOfTopLevelItem(current);

    return -1;
}

void SimpleScriptEditor::copySelected()
{
    int pos = getSelected();

    if (pos >= 0)
    {
        event::request_ptr selected = 
            *boost::next(m_requests.begin(), pos);

        core::operation_reflective_base const * op =
            m_factory->get_reflective_by_tag(selected->get_tag());

        int cb_pos = m_selector->findText(
                QString(op->get_name()),
                Qt::MatchFixedString| Qt::MatchCaseSensitive);
#if 0
        // copiar 'it' al editor correspondiente
        m_multi->getDialog(cb_pos)->copy_from_request(selected.get());

        // mostrar el editor correspondiente
        m_selector->setCurrentIndex(cb_pos);
#endif
    }
}

void SimpleScriptEditor::doAppendRequest(event::request_ptr _request, 
        bool beforeSelected)
{
#if 0
    int pos = getSelected();

    // La inserta en el árbol
    QTreeWidgetItem * req_item = 
        m_factory->create_tree(_request.get());

    if (pos >= 0 && beforeSelected)
    {
        requests_t::iterator it = boost::next(m_requests.begin(), pos);
        m_requests.insert(it, _request);
        m_tree->insertTopLevelItem(pos, req_item);
    }
    else
    {
        m_requests.push_back(_request);
        m_tree->addTopLevelItem(req_item);
    }

    m_tree->scrollToItem(req_item);
#endif
}

void SimpleScriptEditor::hideEvent(QHideEvent * event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}


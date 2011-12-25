// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SimpleClient.hpp
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

#include "SimpleClient.hpp"
#include <iostream>
#include <string>
#include <corbasim/gui/gui_factory.hpp>
#include <corbasim/qt/RequestDialog.hpp>
#include <corbasim/qt/MultiInputWidget.hpp>
#include <corbasim/qt/SimpleScriptEditor.hpp>
#include <corbasim/qt/LogTreeWidget.hpp>
#include <corbasim/qt/initialize.hpp>

using namespace corbasim;
using namespace corbasim::qt::client;

SimpleClient::SimpleClient(QWidget * parent) :
    QMainWindow(parent), m_factory(NULL), m_actions(this),
    m_multi_sender(NULL), m_script_editor(NULL)
{
    corbasim::qt::initialize();

    QWidget * central = new QWidget;
    QVBoxLayout * layout = new QVBoxLayout;

    // Menu
    m_menu = new QMenuBar;
    setMenuBar(m_menu);
   
    // Menu File
    QMenu * menuFile = m_menu->addMenu("&File");
    QMenu * editMenu = m_menu->addMenu("&Edit");
    menuFile->addAction("&Multi-sender", this, SLOT(showMultiSender()));
    menuFile->addAction("&Script editor", this, SLOT(showScriptEditor()));
    menuFile->addSeparator();
    menuFile->addAction("&Close", this, SLOT(close()));

    // Menu Operations
    m_operations_menu = m_menu->addMenu("&Operations");

    // Menu window
    QMenu * menuWindow = m_menu->addMenu("&Window");

    m_mainSplitter = new QSplitter(Qt::Vertical);
    layout->addWidget(m_mainSplitter);

    // IOR
    QGroupBox * gb = new QGroupBox("Reference");
    QAction * act = menuWindow->addAction("&Reference");
    act->setCheckable(true);
    act->setChecked(true);
    QObject::connect(act, SIGNAL(toggled(bool)), gb,
        SLOT(setVisible(bool)));
    QHBoxLayout * gbLayout = new QHBoxLayout;
    m_ref = new ObjrefWidget;
    gbLayout->addWidget(m_ref);
    gb->setLayout(gbLayout);

    m_mainSplitter->addWidget(gb);

    // Operations
    gb = new QGroupBox("Operations");
    act = menuWindow->addAction("&Operations");
    act->setCheckable(true);
    act->setChecked(true);
    QObject::connect(act, SIGNAL(toggled(bool)), gb,
        SLOT(setVisible(bool)));
    QVBoxLayout * opsLayout = new QVBoxLayout;
    m_tab = new QTabWidget;
    opsLayout->addWidget(m_tab);
    gb->setLayout(opsLayout);
    m_mainSplitter->addWidget(gb);
    
    // Events
    gb = new QGroupBox("Events");
    act = menuWindow->addAction("&Events");
    act->setCheckable(true);
    act->setChecked(true);
    QObject::connect(act, SIGNAL(toggled(bool)), gb,
        SLOT(setVisible(bool)));

    gbLayout = new QHBoxLayout;
    m_tree = new LogTreeWidget(100);
    gbLayout->addWidget(m_tree);
    gb->setLayout(gbLayout);
    m_mainSplitter->addWidget(gb);

    // Actions
    QAction * pasteAction = new QAction("Paste &IOR from clipboard", 
            this);
    pasteAction->setShortcut(QKeySequence::Paste);
    QObject::connect(pasteAction, SIGNAL(triggered()), 
            this, SLOT(pasteIOR()));

    QAction * clearAction = new QAction("&Clear",
            this);
    clearAction->setShortcut(QKeySequence::Cut);
    QObject::connect(clearAction, SIGNAL(triggered()), 
            this, SLOT(clearAll()));

    QAction * stopAction = new QAction("&Stop all timers",
            this);
    // stopAction->setShortcut(QKeySequence::Cut);
    QObject::connect(stopAction, SIGNAL(triggered()), 
            this, SLOT(stopAllTimers()));

    editMenu->addAction(pasteAction);
    editMenu->addAction(clearAction);
    editMenu->addAction(stopAction);

#if 0
    // Buttons
    QHBoxLayout * btnsLayout = new QHBoxLayout;
    QPushButton * btn = new QPushButton("&Clear");
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(clearAll()));
    btnsLayout->addWidget(btn);

    btn = new QPushButton("Paste &IOR from clipboard");
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(pasteIOR()));
    btnsLayout->addWidget(btn);

    btn = new QPushButton("&Stop all timers");
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(stopAllTimers()));
    btnsLayout->addWidget(btn);
    layout->addLayout(btnsLayout);
#endif

    central->setLayout(layout);
    setCentralWidget(central);

    QObject::connect(&m_buttons, SIGNAL(buttonClicked(int)), 
            this, SLOT(showDialog(int)));

    QObject::connect(&m_actions, SIGNAL(triggered(QAction *)), 
            this, SLOT(showDialog(QAction *)));

}

SimpleClient::~SimpleClient()
{
    m_tree->clear();
}

void SimpleClient::pasteIOR()
{
    m_ref->pasteIOR();
}

void SimpleClient::stopAllTimers()
{
    for (size_t i = 0; i < m_dialogs.size(); i++) 
        if (m_dialogs[i])
            m_dialogs[i]->stopTimer();
}

void SimpleClient::clearAll()
{
    m_tree->clear();
    m_caller->set_reference(CORBA::Object::_nil());
    m_ref->validatorHasChanged();
}

void SimpleClient::sendRequest(corbasim::event::request_ptr req)
{
    if (m_caller && !m_caller->is_nil())
    {
        QTreeWidgetItem * req_item = m_factory->create_tree(req.get());

        if (req_item)
            m_tree->appendItem(req_item);

        event::event_ptr ev(m_caller->do_call(req.get()));
        if (ev)
        {
            QTreeWidgetItem * item = m_factory->create_tree(ev.get());

            if (item)
                m_tree->appendItem(item);
        }
    }
}

void SimpleClient::initialize(gui::gui_factory_base * factory)
{
    QGridLayout * grid = NULL;
    const unsigned int count = factory->operation_count();

    // Inicializa los dialogos a nulo
    m_dialogs.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        const unsigned int idx = i % _max_btns_per_page;

        const gui::operation_factory_base * op = 
            factory->get_factory_by_index(i);

        const char * name = op->get_name();

        if (!idx)
        {
            QWidget * w = new QWidget;
            grid = new QGridLayout;
            w->setLayout(grid);

            // TODO Page + number or from... to...
            QString page("From ");
            page += name; 
            m_tab->addTab(w, page);
        }

        // Button
        QPushButton * btn = new QPushButton(name);
        grid->addWidget(btn, idx / _max_btns_per_row,
            idx % _max_btns_per_row);

        m_buttons.addButton(btn, i);

        // Menu Operations
        QAction * act = m_operations_menu->addAction(name);
        m_actions.addAction(act);
        act->setData(i);
    }

    m_factory = factory;

    // Establece el llamador
    m_caller.reset(factory->get_core_factory()->create_caller());
    m_ref->setValidator(m_caller.get());
}

void SimpleClient::setReference(CORBA::Object_ptr ref)
{
    m_caller->set_reference(ref);
}

void SimpleClient::showDialog(int idx)
{
    getRequestDialog(idx)->show();
}

void SimpleClient::showDialog(QAction * action)
{
    getRequestDialog(action->data().toInt())->show();
}

corbasim::qt::RequestDialog * SimpleClient::getRequestDialog(int idx)
{
    RequestDialog * dlg = m_dialogs[idx];

    if (!dlg)
    {
        const gui::operation_factory_base * op = 
            m_factory->get_factory_by_index(idx);
        const char * name = op->get_name();

        dialogs::input_base * input = op->create_input();
        dlg = new RequestDialog(input, this);
        dlg->setWindowTitle(name);

        QObject::connect(dlg,
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            this, 
            SLOT(sendRequest(corbasim::event::request_ptr)));

        m_dialogs[idx] = dlg;
    }

    return dlg;
}

void SimpleClient::showScriptEditor()
{
    if (!m_script_editor)
    {
        m_script_editor = new SimpleScriptEditor(this);
        m_script_editor->initialize(m_factory);

        // Send Request
        QObject::connect(m_script_editor,
                SIGNAL(sendRequest(corbasim::event::request_ptr)),
                this, 
                SLOT(sendRequest(corbasim::event::request_ptr)));
    }
    m_script_editor->show();
}

void SimpleClient::showMultiSender()
{
    if (!m_multi_sender)
    {
        m_multi_sender = new MultiSenderDialog(this);
        m_multi_sender->initialize(m_factory);

        // Send Request
        QObject::connect(m_multi_sender,
                SIGNAL(sendRequest(corbasim::event::request_ptr)),
                this, 
                SLOT(sendRequest(corbasim::event::request_ptr)));
    }
    m_multi_sender->show();
}


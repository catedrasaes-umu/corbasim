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
#include <corbasim/reflective_gui/RequestDialog.hpp>
#include <corbasim/reflective_gui/SimpleScriptEditor.hpp>
#include <corbasim/qt/initialize.hpp>
#include <corbasim/reflective_gui/json.hpp>
#include <fstream>

using namespace corbasim;
using namespace corbasim::reflective_gui;

SimpleClient::SimpleClient(QWidget * parent) :
    QMainWindow(parent), m_factory(NULL), m_actions(this),
    m_script_editor(NULL)
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
    m_ref = new qt::ObjrefWidget;
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
    m_tree = new QTreeView();
    m_tree->setModel(&m_log_model);
    gbLayout->addWidget(m_tree);
    gb->setLayout(gbLayout);
    m_mainSplitter->addWidget(gb);

    // Filtered log
    QDialog * filteredLogDlg = new QDialog(this);
    QVBoxLayout * filteredLayout = new QVBoxLayout();
    m_filtered_log = new FilteredLogView();
    m_filtered_log->setLogModel(&m_log_model);
    filteredLayout->addWidget(m_filtered_log);
    filteredLogDlg->setLayout(filteredLayout);
    filteredLogDlg->hide();

    // Load
    QAction * loadAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogOpenButton),
            "&Load configuration", this);
    loadAction->setShortcut(QKeySequence::Open);
    QObject::connect(loadAction, SIGNAL(triggered()), 
            this, SLOT(doLoad()));

    // Save
    QAction * saveAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogSaveButton),
            "&Save configuration", this);
    saveAction->setShortcut(QKeySequence::SaveAs);
    QObject::connect(saveAction, SIGNAL(triggered()), 
            this, SLOT(doSave()));

    menuFile->addAction(loadAction);
    menuFile->addAction(saveAction);
    menuFile->addSeparator();
    menuFile->addAction("&Script editor", this, SLOT(showScriptEditor()));
    menuFile->addAction("&Filtered log", filteredLogDlg, SLOT(show()));
    menuFile->addSeparator();
    menuFile->addAction("&Close", this, SLOT(close()));

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

    central->setLayout(layout);
    setCentralWidget(central);

    QObject::connect(&m_buttons, SIGNAL(buttonClicked(int)), 
            this, SLOT(showDialog(int)));

    QObject::connect(&m_actions, SIGNAL(triggered(QAction *)), 
            this, SLOT(showDialog(QAction *)));

    QObject::connect(&m_finder, 
            SIGNAL(found(const CORBA::Object_var&)),
            this,
            SLOT(updateReference(const CORBA::Object_var&)));
}

SimpleClient::~SimpleClient()
{
    m_finder.terminate();
    m_finder.wait();
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
    m_caller->set_reference(CORBA::Object::_nil());
    m_ref->validatorHasChanged();
}

void SimpleClient::sendRequest(corbasim::event::request_ptr req)
{
    if (m_caller && !m_caller->is_nil())
    {
        event::event_ptr ev(m_caller->do_call(req.get()));

        m_log_model.outputRequest("Object", req, ev);
    }
}

void SimpleClient::initialize(core::interface_reflective_base const * factory)
{
    m_log_model.registerInstance("Object", factory);
    m_filtered_log->registerInstance("Referenced object", factory);

    QGridLayout * grid = NULL;
    const unsigned int count = factory->operation_count();

    // Inicializa los dialogos a nulo
    m_dialogs.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        const unsigned int idx = i % _max_btns_per_page;

        const core::operation_reflective_base * op = 
            factory->get_reflective_by_index(i);

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
    m_caller.reset(factory->create_caller());
    m_ref->setValidator(m_caller.get());

    m_finder.start();
}

void SimpleClient::setReference(CORBA::Object_ptr ref)
{
    m_caller->set_reference(ref);
    m_ref->validatorHasChanged();
}

void SimpleClient::showDialog(int idx)
{
    getRequestDialog(idx)->show();
}

void SimpleClient::showDialog(QAction * action)
{
    getRequestDialog(action->data().toInt())->show();
}

corbasim::reflective_gui::RequestDialog * SimpleClient::getRequestDialog(int idx)
{
    RequestDialog * dlg = m_dialogs[idx];

    if (!dlg)
    {
        const core::operation_reflective_base * op = 
            m_factory->get_reflective_by_index(idx);
        const char * name = op->get_name();

        dlg = new RequestDialog(op, this);
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

void SimpleClient::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    if (map.contains("dialogs"))
    {
        const QVariantList list = map.value("dialogs").toList();

        for (QVariantList::const_iterator it = list.begin(); 
                it != list.end(); ++it) 
        {
            const QVariantMap map = it->toMap();

            if (map.contains("operation") && map.contains("value"))
            {
                // find the index
                unsigned int i = 0;
                bool found = false;
                for (; !found && i < m_factory->operation_count(); 
                        i++) 
                {
                    found = (m_factory->get_reflective_by_index(i)->get_name() 
                            == map.value("operation").toString());
                }

                // load its saved value
                if (found)
                {
                    getRequestDialog(i)->load(map.value("value"));
                }
            }
        }
    }

    if (map.contains("filtered_log"))
    {
        m_filtered_log->load(map["filtered_log"]);
    }
}

void SimpleClient::save(QVariant& settings)
{
    QVariantMap map;
    QVariantList list;

    for (unsigned int i = 0; i < m_dialogs.size(); i++) 
    {
        if (m_dialogs[i])
        {
            QVariantMap op;
            op["operation"] = m_dialogs[i]->getReflective()->get_name();
            m_dialogs[i]->save(op["value"]);
            list << op;
        }
    }

    map["dialogs"] = list;

    // Filtered log
    QVariant filtered;
    m_filtered_log->save(filtered);
    map["filtered_log"] = filtered;

    settings = map;
}

// Settings
void SimpleClient::doLoad() 
{
    const QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select some files"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    QVariant var;

    // Try to Read a JSON file
    bool res = 
        reflective_gui::fromJsonFile(file.toStdString().c_str(), var);

    if (res)
    {
        load(var);
    }
    else
    {
        // TODO display error
    }
}

void SimpleClient::doSave() 
{
    QString file = QFileDialog::getSaveFileName( 0, tr(
                "Select a file"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    QVariant v;
    save(v);

    std::ofstream ofs(file.toStdString().c_str());
    json::ostream_writer_t ow(ofs, true);

    reflective_gui::toJson(ow, v);
}

void SimpleClient::resizeEvent(QResizeEvent * event)
{
    if (!event->oldSize().isValid() || event->oldSize().isNull())
        return;

    QList< int > sizes = m_mainSplitter->sizes();

    int available = event->size().height();

    for (int i = 0; i < sizes.size() - 1; i++)
        if (sizes.at(i))
        {
            int min = m_mainSplitter->widget(i)->sizeHint().height();
            // int min = m_mainSplitter->widget(i)->minimumHeight();
            available -= min; 
            sizes.replace(i, min);
        }

    sizes.last() = available;

    m_mainSplitter->setSizes(sizes);
}

void SimpleClient::updateReference(const CORBA::Object_var& ref)
{
    setReference(ref);
}


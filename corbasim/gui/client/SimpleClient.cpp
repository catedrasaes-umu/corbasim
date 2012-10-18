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
#include <corbasim/gui/RequestDialog.hpp>
#include <corbasim/gui/tools/FilteredLogView.hpp>
#include <corbasim/gui/tools/SimpleScriptEditor.hpp>
#include <corbasim/gui/tools/OperationSequence.hpp>
#include <corbasim/qt/initialize.hpp>
#include <corbasim/gui/json.hpp>
#include <corbasim/gui/item/TreeView.hpp>
#include <fstream>

using namespace corbasim;
using namespace corbasim::gui;

SimpleClient::SimpleClient(QWidget * parent) :
    QMainWindow(parent), m_actions(this),
    m_script_editor(NULL), m_dlgSeqTool(NULL),
    m_seqTool(NULL)
{
    corbasim::gui::initialize();

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
    connect(act, SIGNAL(toggled(bool)), gb,
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
    connect(act, SIGNAL(toggled(bool)), gb,
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
    connect(act, SIGNAL(toggled(bool)), gb,
        SLOT(setVisible(bool)));

    gbLayout = new QHBoxLayout;
    m_tree = new TreeView();
    m_tree->setModel(&m_log_model);
    gbLayout->addWidget(m_tree);
    gb->setLayout(gbLayout);
    m_mainSplitter->addWidget(gb);

    // Filtered log
    QDialog * filteredLogDlg = new QDialog(this);
    QVBoxLayout * filteredLayout = new QVBoxLayout();
    m_filteredLog = new FilteredLogView();
    m_filteredLog->setLogModel(&m_log_model);
    filteredLayout->setMargin(0);
    filteredLayout->addWidget(m_filteredLog);
    filteredLogDlg->setLayout(filteredLayout);
    filteredLogDlg->hide();

    // Load
    QAction * loadAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogOpenButton),
            "&Load configuration", this);
    loadAction->setShortcut(QKeySequence::Open);
    connect(loadAction, SIGNAL(triggered()), 
            this, SLOT(doLoad()));

    // Save
    QAction * saveAction = new QAction(
            style()->standardIcon(QStyle::SP_DialogSaveButton),
            "&Save configuration", this);
    saveAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAction, SIGNAL(triggered()), 
            this, SLOT(doSave()));

    menuFile->addAction(loadAction);
    menuFile->addAction(saveAction);
    menuFile->addSeparator();
    menuFile->addAction("&Script editor", this, SLOT(showScriptEditor()));
    menuFile->addAction("&Operation sequence", this, 
            SLOT(showOperationSequenceTool()));
    menuFile->addAction("&Filtered log", filteredLogDlg, SLOT(show()));
    menuFile->addSeparator();
    menuFile->addAction("&Close", this, SLOT(close()));

    // Actions
    QAction * pasteAction = new QAction("Paste &IOR from clipboard", 
            this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered()), 
            this, SLOT(pasteIOR()));

    QAction * clearAction = new QAction("&Clear",
            this);
    clearAction->setShortcut(QKeySequence::Cut);
    connect(clearAction, SIGNAL(triggered()), 
            this, SLOT(clearAll()));

    QAction * clearLogAction = new QAction("&Clear log",
            this);
    connect(clearLogAction, SIGNAL(triggered()), 
            &m_log_model, SLOT(clearLog()));

    QAction * stopAction = new QAction("&Stop all timers",
            this);
    // stopAction->setShortcut(QKeySequence::Cut);
    connect(stopAction, SIGNAL(triggered()), 
            this, SLOT(stopAllTimers()));

    editMenu->addAction(pasteAction);
    editMenu->addAction(clearAction);
    editMenu->addAction(clearLogAction);
    editMenu->addAction(stopAction);

    central->setLayout(layout);
    setCentralWidget(central);

    connect(&m_buttons, SIGNAL(buttonClicked(int)), 
            this, SLOT(showDialog(int)));

    connect(&m_actions, SIGNAL(triggered(QAction *)), 
            this, SLOT(showDialog(QAction *)));

    setWindowIcon(QIcon(":/resources/images/csu.png"));
}

SimpleClient::~SimpleClient()
{
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
    // TODO do this? m_objref->setReference(CORBA::Object::_nil());
}

void SimpleClient::initialize(Objref_ptr objref)
{
    m_objref = objref;

    // Signals
    connect(this, SIGNAL(sendRequest(Request_ptr)),
            m_objref.get(), SLOT(sendRequest(Request_ptr)));

    m_log_model.registerInstance(m_objref);

    connect(m_objref.get(), 
            SIGNAL(requestSent(ObjectId, const Request_ptr&, const Event_ptr&)),
            &m_log_model, 
            SLOT(outputRequest(ObjectId, Request_ptr, Event_ptr)));

    m_filteredLog->registerInstance(m_objref);

    if (m_seqTool)
        m_seqTool->objrefCreated(m_objref);

    QGridLayout * grid = NULL;
    InterfaceDescriptor_ptr factory = m_objref->interface();
    const unsigned int count = factory->operation_count();

    // Inicializa los dialogos a nulo
    m_dialogs.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        const unsigned int idx = i % _max_btns_per_page;

        OperationDescriptor_ptr op = 
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

    // Validator for reference updates
    m_ref->setObjref(m_objref);
}

void SimpleClient::showDialog(int idx)
{
    getRequestDialog(idx)->show();
}

void SimpleClient::showDialog(QAction * action)
{
    getRequestDialog(action->data().toInt())->show();
}

corbasim::gui::RequestDialog * SimpleClient::getRequestDialog(int idx)
{
    RequestDialog * dlg = m_dialogs[idx];

    if (!dlg)
    {
        OperationDescriptor_ptr op = 
            m_objref->interface()->get_reflective_by_index(idx);
        const char * name = op->get_name();

        dlg = new RequestDialog(op, this);
        dlg->setWindowTitle(name);

        connect(dlg,
            SIGNAL(sendRequest(Request_ptr)),
            this, 
            SIGNAL(sendRequest(Request_ptr)));

        m_dialogs[idx] = dlg;
    }

    return dlg;
}

void SimpleClient::showScriptEditor()
{
    if (!m_script_editor)
    {
        m_script_editor = new SimpleScriptEditor(this);
        m_script_editor->initialize(m_objref->interface());

        // Send Request
        connect(m_script_editor,
                SIGNAL(sendRequest(Request_ptr)),
                this, 
                SIGNAL(sendRequest(Request_ptr)));
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
                for (; !found && i < m_objref->interface()->operation_count(); 
                        i++) 
                {
                    found = (m_objref->interface()->get_reflective_by_index(i)->get_name() 
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
        m_filteredLog->load(map["filtered_log"]);
    }

    if (map.contains("operations"))
    {
        // ensure created
        showOperationSequenceTool();

        m_seqTool->load(map["operations"]);
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
    m_filteredLog->save(filtered);
    map["filtered_log"] = filtered;

    if (m_seqTool) m_seqTool->save(map["operations"]);

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
        gui::fromJsonFile(file.toStdString().c_str(), var);

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

    gui::toJson(ow, v);
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

void SimpleClient::showOperationSequenceTool()
{
    if (!m_seqTool)
    {
        QVBoxLayout * layout = new QVBoxLayout();
        layout->setMargin(0);
        m_dlgSeqTool = new QDialog(this);
        m_seqTool = new gui::OperationSequenceTool();
        
        layout->addWidget(m_seqTool);
        m_dlgSeqTool->setLayout(layout);

        // Initializes the tool
        if (m_objref->interface())
            m_seqTool->objrefCreated(m_objref);
    }

    m_dlgSeqTool->show();
}


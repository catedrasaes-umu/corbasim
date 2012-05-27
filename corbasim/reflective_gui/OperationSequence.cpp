// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * OperationSequence.cpp
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

#include "OperationSequence.hpp"
#include <corbasim/reflective_gui/ReflectiveGUI.hpp>
#include <corbasim/reflective_gui/json.hpp>
#include <boost/next_prior.hpp>

#include <fstream>
#include <iostream>

using namespace corbasim::reflective_gui;

OperationSequenceItem::OperationSequenceItem(const QString& id,
        OperationInputForm * dlg,
        QWidget * parent) : 
    QFrame(parent), m_id(id), m_dlg(dlg)
{
    core::operation_reflective_base const * reflective =
        dlg->getReflective();

    QVBoxLayout * layout = new QVBoxLayout();

    // Title bar
    QHBoxLayout * tLayout = new QHBoxLayout();
    QLabel * title = new QLabel(
        QString("<b>Object: '%1' Operation: '%2'</b>")
            .arg(id).arg(reflective->get_name()));
    tLayout->addWidget(title);
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    tLayout->addItem(spacer);

    layout->addLayout(tLayout);

    // Corner buttons
    {
        QToolButton * btShowInput = new QToolButton();
        btShowInput->setIcon(style()->standardIcon(
                    QStyle::SP_FileDialogDetailedView));
        btShowInput->setCheckable(true);
        QToolButton * btUp = new QToolButton();
        btUp->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
        QToolButton * btDown = new QToolButton();
        btDown->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
        QToolButton * btDelete = new QToolButton();
        btDelete->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
        tLayout->addWidget(btShowInput);
        tLayout->addWidget(btUp);
        tLayout->addWidget(btDown);
        tLayout->addWidget(btDelete);

        QObject::connect(btShowInput, SIGNAL(toggled(bool)),
                dlg, SLOT(setVisible(bool)));
        QObject::connect(btDelete, SIGNAL(clicked()),
                this, SLOT(deleteClicked()));
        QObject::connect(btUp, SIGNAL(clicked()),
                this, SLOT(upClicked()));
        QObject::connect(btDown, SIGNAL(clicked()),
                this, SLOT(downClicked()));

        // Tooltips
        btShowInput->setToolTip("Show/hide detailed input form");
        btDelete->setToolTip("Delete item");
        btUp->setToolTip("Move up");
        btDown->setToolTip("Move down");
    }

    // User-defined title
    {
        tLayout = new QHBoxLayout();
        title = new QLabel("title");
        m_title = new QLineEdit();

        tLayout->addWidget(title);
        tLayout->addWidget(m_title);
        layout->addLayout(tLayout);
    }

    // Editor
    m_layout = new QVBoxLayout();
    m_layout->addWidget(dlg);
    dlg->hide();
    layout->addLayout(m_layout);

    // Bottom buttons and options
    QHBoxLayout * bLayout = new QHBoxLayout();

    // Horizontal spacer
    spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    bLayout->addItem(spacer);

    // periodic
    bLayout->addWidget(new QLabel("Period (ms)"));
    m_sbPeriod = new QSpinBox;
    m_sbPeriod->setRange(0, 999999);
    m_sbPeriod->setValue(100);
    bLayout->addWidget(m_sbPeriod);

    bLayout->addWidget(new QLabel("Times"));
    m_sbTimes = new QSpinBox;
    m_sbTimes->setRange(-1, 999999);
    m_sbTimes->setValue(-1);
    bLayout->addWidget(m_sbTimes);

    bLayout->addWidget(new QLabel("Use stored value"));
    m_cbUseStored = new QCheckBox;
    m_cbUseStored->setChecked(true);
    bLayout->addWidget(m_cbUseStored);

    m_pbStartStop = new QPushButton("S&tart/Stop");
    m_pbStartStop->setCheckable(true);
    bLayout->addWidget(m_pbStartStop);

    m_pbUpdate = new QPushButton("&Update");
    bLayout->addWidget(m_pbUpdate);
    // end periodic

    QPushButton * btSend = new QPushButton("Send");
    // QPushButton * btSendNext = new QPushButton("Send and next");

    bLayout->addWidget(btSend);
    // bLayout->addWidget(btSendNext);
   
    QObject::connect(btSend, SIGNAL(clicked()),
            this, SLOT(sendClicked()));
    QObject::connect(m_pbUpdate, SIGNAL(clicked()), 
            this, SLOT(storeRequest()));
    QObject::connect(m_pbStartStop, SIGNAL(toggled(bool)), 
            this, SLOT(startStopChecked(bool)));
    QObject::connect(&m_timer, SIGNAL(timeout()), 
            this, SLOT(sendStored()));

    layout->addLayout(bLayout);
    // End buttons

    setLayout(layout);

    setLineWidth(1);
    setFrameStyle(QFrame::Box);
}

OperationSequenceItem::~OperationSequenceItem()
{
}

const QString& OperationSequenceItem::getObjrefId() const
{
    return m_id;
}

const char * OperationSequenceItem::getOperationName() const
{
    return "TODO";
}

void OperationSequenceItem::sendClicked()
{
     emit sendRequest(m_id, m_dlg->createRequest());
}

void OperationSequenceItem::startStopChecked(bool chk)
{
    if (chk)
    {
        storeRequest();
        m_currentPeriodicRequest = 0;
        m_timer.start(m_sbPeriod->value());
    }
    else
    {
        m_timer.stop();
    }
}

void OperationSequenceItem::storeRequest()
{
    m_storedRequest = m_dlg->createRequest();
}

void OperationSequenceItem::sendStored()
{
    if (m_cbUseStored->isChecked())
        emit sendRequest(m_id, m_storedRequest);
    else
        sendClicked();

    ++m_currentPeriodicRequest;
    if (m_sbTimes->value() >= 0 && 
            m_currentPeriodicRequest >= m_sbTimes->value())
        m_pbStartStop->setChecked(false);
}

void OperationSequenceItem::stopTimer()
{
    m_pbStartStop->setChecked(false);
}

void OperationSequenceItem::deleteClicked()
{
    emit doDelete();
}

void OperationSequenceItem::upClicked()
{
    emit up();
}

void OperationSequenceItem::downClicked()
{
    emit down();
}

OperationSequence::OperationSequence(const QString& name, QWidget * parent) :
    QWidget(parent), m_name(name)
{
    QVBoxLayout * layout = new QVBoxLayout();
    layout->setMargin(0);

    QWidget * scrollWidget = new QWidget();
    QVBoxLayout * scrollLayout = new QVBoxLayout();
    m_layout = new qt::CustomVLayout();
    scrollWidget->setLayout(scrollLayout);
    scrollLayout->addLayout(m_layout);

    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollLayout->addItem(spacer);

    // Scroll
    m_scroll = new QScrollArea();
    m_scroll->setObjectName("scroll");
    m_scroll->setWidgetResizable(true);
    m_scroll->setWidget(scrollWidget);

    m_scroll->setLineWidth(0);
    m_scroll->setFrameStyle(QFrame::NoFrame);

    layout->addWidget(m_scroll);
    setLayout(layout);
}

OperationSequence::~OperationSequence()
{
}

const QString& OperationSequence::getName() const
{
    return m_name;
}

void OperationSequence::appendItem(OperationSequenceItem * item)
{
    // Before spacer
    m_layout->addWidget(item);

    // Scroll to item
    // m_scroll->ensureWidgetVisible(item);

    QObject::connect(item, SIGNAL(doDelete()),
            this, SLOT(deleteItem()));
    QObject::connect(item, SIGNAL(up()),
            this, SLOT(moveUpItem()));
    QObject::connect(item, SIGNAL(down()),
            this, SLOT(moveDownItem()));

    m_items.push_back(item);

    emit modified();
}

void OperationSequence::deleteItem(OperationSequenceItem * item)
{
    m_items.removeAll(item);
    item->deleteLater();

    emit modified();
}

void OperationSequence::moveUpItem(OperationSequenceItem * item)
{
     int idx = m_items.indexOf(item);

     if (idx > 0)
     {
         // List
         m_items.takeAt(idx);
         m_items.insert(idx - 1, item);

         // Layout
         QLayoutItem * lItem = m_layout->takeAt(idx);
         m_layout->insertItem(idx - 1, lItem);

        emit modified();
     }
}

void OperationSequence::moveDownItem(OperationSequenceItem * item)
{
     int idx = m_items.indexOf(item);

     if (idx > -1 && idx < m_items.size() - 1)
     {
         // List
         m_items.takeAt(idx);
         m_items.insert(idx + 1, item);

         // Layout
         QLayoutItem * lItem = m_layout->takeAt(idx);
         m_layout->insertItem(idx + 1, lItem);

         emit modified();
     }
}

void OperationSequence::deleteItem()
{
    OperationSequenceItem * sndObj = 
        qobject_cast< OperationSequenceItem * >(sender());

    if (sndObj)
        deleteItem(sndObj);
}

void OperationSequence::moveUpItem()
{
    OperationSequenceItem * sndObj = 
        qobject_cast< OperationSequenceItem * >(sender());

    if (sndObj)
        moveUpItem(sndObj);
}

void OperationSequence::moveDownItem()
{
    OperationSequenceItem * sndObj = 
        qobject_cast< OperationSequenceItem * >(sender());

    if (sndObj)
        moveDownItem(sndObj);
}

// View
OperationsView::OperationsView(QWidget * parent) :
    QTreeView(parent)
{
}

OperationsView::~OperationsView()
{
}

// Tool
OperationSequenceTool::OperationSequenceTool(QWidget * parent) :
    QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout();

    m_view = new OperationsView();
    m_view->setMaximumWidth(200);
    layout->addWidget(m_view);

    m_view->setModel(&m_model);

    // Tabs
    m_tabs = new QTabWidget();
    m_tabs->setTabsClosable(true);

    QToolButton * btNewTab = new QToolButton();
    btNewTab->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    m_tabs->setCornerWidget(btNewTab);

    layout->addWidget(m_tabs);

    setLayout(layout);

    // Signals
    QObject::connect(m_view, 
            SIGNAL(doubleClicked(const QModelIndex&)),
            &m_model,
            SLOT(doubleClicked(const QModelIndex&)));

    QObject::connect(&m_model, 
            SIGNAL(selectedOperation(QString, 
                    const corbasim::core::operation_reflective_base *)),
            this,
            SLOT(appendOperation(const QString&, 
                    const corbasim::core::operation_reflective_base *)));

    QObject::connect(btNewTab, SIGNAL(clicked()),
            this, SLOT(createSequence()));

    QObject::connect(m_tabs, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeSequence(int)));

    // Context menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint&)));

    setMinimumHeight(400);
    setMinimumWidth(600);

    setWindowIcon(QIcon(":/resources/images/csu.png"));

    // Menu
    m_menu = new QMenu();
    m_menu->addAction("Save as...", this, SLOT(saveCurrentSequence()));
    m_menu->addSeparator();
    m_menu->addAction("New", this, SLOT(createSequence()));
    m_menu->addAction("Load", this, SLOT(loadSequence()));
}

OperationSequenceTool::~OperationSequenceTool()
{
}

void OperationSequenceTool::objrefCreated(const QString& id,
    const corbasim::core::interface_reflective_base * factory)
{
    m_model.registerInstance(id, factory);
}

void OperationSequenceTool::objrefDeleted(const QString& id)
{
    m_model.unregisterInstance(id);
}

OperationSequenceItem * 
OperationSequenceTool::appendOperation(const QString& id, 
		corbasim::core::operation_reflective_base const * op)
{
    OperationSequence * seq = NULL;
    if (m_sequences.isEmpty())
        seq = createSequence();
    else
        seq = m_sequences[m_tabs->currentIndex()];

    OperationSequenceItem * item = 
        new OperationSequenceItem(id, new OperationInputForm(op));

    seq->appendItem(item);

    QObject::connect(item, SIGNAL(sendRequest(QString,
                        corbasim::event::request_ptr)),
                this, SLOT(slotSendRequest(const QString&, 
                        corbasim::event::request_ptr)));

    return item;
}

OperationSequence* OperationSequenceTool::createSequence()
{
    OperationSequence * seq = new OperationSequence("no name");
    m_sequences.push_back(seq);
    m_tabs->addTab(seq, seq->getName());
    m_tabs->setCurrentIndex(m_tabs->count() - 1);

    QObject::connect(seq, SIGNAL(modified()),
            this, SLOT(sequenceModified()));

    return seq;
}

void OperationSequenceTool::showContextMenu(const QPoint& pos)
{
    if (m_sequences.size() > 0)
    {
        m_menu->exec(QCursor::pos());
    }
}

void OperationSequenceTool::saveCurrentSequence()
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

    toJson(ow, v);
}

void OperationSequenceTool::loadSequence()
{
    const QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select some file"), ".");

    // User cancels
    if (file.isEmpty())
        return;

    QVariant var;

    // Try to Read a JSON file
    bool res = fromJsonFile(file.toStdString().c_str(), var);

    if (res)
    {
        load(var);
    }
    else
    {
        // TODO display error
    }
}

void OperationSequenceTool::closeSequence(int idx)
{
    // QT Documentation
    // Removes the tab at position index from this stack of widgets. 
    // The page widget itself is not deleted.
    m_tabs->removeTab(idx);

    delete m_sequences.takeAt(idx);
}

void OperationSequenceTool::slotSendRequest(const QString& id, 
        corbasim::event::request_ptr req)
{
    emit sendRequest(id, req);
}

void OperationSequenceTool::sequenceModified()
{
    OperationSequence * sndObj = 
        qobject_cast< OperationSequence * >(sender());

    int idx = -1;
    if (sndObj && (idx = m_sequences.indexOf(sndObj)) != -1)
    {
        m_tabs->setTabText(idx, sndObj->getName() + " *");
    }
}

// Model
OperationModel::OperationModel(QObject *parent)
    : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "Operations";

    setHorizontalHeaderLabels(headers);
}

OperationModel::~OperationModel()
{
}

void OperationModel::registerInstance(const QString& name,
        corbasim::core::interface_reflective_base const * factory)
{
    FirstLevelItem item;
    item.name = name;
    item.factory = factory;
    m_items.push_back(item);

    QStandardItem * ifItem = new QStandardItem(name);
    ifItem->setEditable(false);

    const unsigned int count = factory->operation_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        core::operation_reflective_base const * op =
            factory->get_reflective_by_index(i);

        QStandardItem * opItem = new QStandardItem(op->get_name());
        opItem->setEditable(false);

        // opItem->setData(op);

        ifItem->appendRow(opItem);
    }

    appendRow(ifItem);
}

void OperationModel::unregisterInstance(const QString& name)
{
    int i = 0;
    for (FirstLevelItems_t::iterator it = m_items.begin(); 
            it != m_items.end(); ++it, ++i) 
    {
        if (name == it->name)
        {
            removeRows(i, 1);

            m_items.erase(it);
            break;
        }
    }
}

void OperationModel::doubleClicked(const QModelIndex& index)
{
    const QModelIndex parent = index.parent();

    if (parent.isValid())
    {
        FirstLevelItem& item = *boost::next(m_items.begin(), 
                parent.row());

        core::operation_reflective_base const * op =
            item.factory->get_reflective_by_name(
                    index.data().toString().toStdString());

        emit selectedOperation(item.name, op);
    }
}

corbasim::core::operation_reflective_base const * 
OperationModel::getOperation(
        const QString& obj, const QString& operation) const
{
    for (FirstLevelItems_t::const_iterator it = m_items.begin(); 
            it != m_items.end(); ++it) 
    {
        if (it->name == obj)
        {
            const std::string op (operation.toStdString());

            return it->factory->get_reflective_by_name(op.c_str());
        }
    }

    return NULL;
}    

// Settings

void OperationSequenceItem::save(QVariant& settings)
{
    QVariantMap map;

    map["object"] = m_id;
    map["operation"] = m_dlg->getReflective()->get_name();

    // User-defined title
    map["title"] = m_title->text();

    map["period"] = m_sbPeriod->value();
    map["times"] = m_sbTimes->value();
    map["use_stored"] = m_cbUseStored->isChecked();
    map["start_stop"] = m_pbStartStop->isChecked();

    m_dlg->save(map["form"]);

    settings = map;
}

void OperationSequenceItem::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    if (map.contains("form")) m_dlg->load(map.value("form"));

    // User-defined title
    if (map.contains("title"))
    {
        m_title->setText(map.value("title").toString());
    }

    // other things...
    if (map.contains("period") && 
            map.value("period").canConvert< int >())
    {
        m_sbPeriod->setValue(map.value("period").toInt());
    }

    if (map.contains("times") && 
            map.value("times").canConvert< int >())
    {
        m_sbTimes->setValue(map.value("times").toInt());
    }

    if (map.contains("use_stored") && 
            map.value("use_stored").canConvert< bool >())
    {
        m_cbUseStored->setChecked(map.value("use_stored").toBool());
    }

    if (map.contains("start_stop") && 
            map.value("start_stop").canConvert< bool >())
    {
        m_pbStartStop->setChecked(map.value("start_stop").toBool());
    }
}

void OperationSequence::save(QVariant& settings)
{
    QVariantList list;
    
    for (int i = 0; i < m_items.size(); i++) 
    {
        QVariant v;
        m_items.at(i)->save(v);
        list << v;
    }

    settings = list;
}

void OperationSequence::load(const QVariant& settings)
{
    // TODO currently impossible
}

void OperationSequenceTool::save(QVariant& settings)
{
    QVariantList list;
    
    for (int i = 0; i < m_sequences.size(); i++) 
    {
        QVariant v;
        m_sequences.at(i)->save(v);
        list << v;
    }

    settings = list;
}

void OperationSequenceTool::load(const QVariant& settings)
{
    // Clear its current configuration
    m_tabs->clear();
    for (int i = 0; i < m_sequences.size(); i++) 
    {
        delete m_sequences.at(i);
    }
    m_sequences.clear();

    const QVariantList list = settings.toList();

    for (int i = 0; i < list.size(); i++) 
    {
        OperationSequence * seq = createSequence();
        // It is not possible seq->load(list.at(i));

        const QVariantList seqList = list.at(i).toList();

        for (int j = 0; j < seqList.size(); j++) 
        {
            const QVariantMap map = seqList.at(j).toMap();

            if (map.contains("object") && map.contains("operation"))
            {
                // TODO display errors
                const QString obj = map.value("object").toString();
                const QString operation = 
                    map.value("operation").toString();

                core::operation_reflective_base const * op =
                    m_model.getOperation(obj, operation);

                // Create and load
                if (op) appendOperation(obj, op)->load(seqList.at(j));
            }
        }
    }
}



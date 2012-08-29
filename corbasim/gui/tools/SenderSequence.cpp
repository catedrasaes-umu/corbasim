// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SenderSequence.cpp
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

#include "SenderSequence.hpp"
#include <corbasim/gui/OperationForm.hpp>
#include <corbasim/gui/json.hpp>
#include <boost/next_prior.hpp>

#include <fstream>
#include <iostream>

using namespace corbasim::gui;

SenderSequenceItem::SenderSequenceItem(
        OperationSender * dlg,
        QWidget * parent) : 
    QFrame(parent), m_dlg(dlg)
{
    const QString& id = dlg->object()->name();

    OperationDescriptor_ptr reflective =
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

        connect(btShowInput, SIGNAL(toggled(bool)),
                dlg->getForm(), SLOT(setVisible(bool)));
        connect(btDelete, SIGNAL(clicked()),
                this, SIGNAL(doDelete()));
        connect(btUp, SIGNAL(clicked()),
                this, SIGNAL(up()));
        connect(btDown, SIGNAL(clicked()),
                this, SIGNAL(down()));

        // Tooltips
        btShowInput->setToolTip("Show/hide detailed input form");
        btDelete->setToolTip("Delete item");
        btUp->setToolTip("Move up");
        btDown->setToolTip("Move down");
    }

    // User-defined title
    {
        tLayout = new QHBoxLayout();
        title = new QLabel("Title");
        m_title = new QLineEdit();

        tLayout->addWidget(title);
        tLayout->addWidget(m_title);
        layout->addLayout(tLayout);
    }

    // Editor
    dlg->layout()->setMargin(0);
    dlg->getForm()->hide();
    layout->addWidget(dlg);

    setLayout(layout);

    setLineWidth(1);
    setFrameStyle(QFrame::Box);
}

SenderSequenceItem::~SenderSequenceItem()
{
}

ObjectId SenderSequenceItem::objectId() const
{
    return m_dlg->object()->id();
}

SenderSequence::SenderSequence(const QString& name, 
        QWidget * parent) :
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

    // Start/stop
    {
        QHBoxLayout * hLayout = new QHBoxLayout();
        hLayout->setMargin(5);

        // Spacer
        QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
        hLayout->addItem(spacer);

        // Button
        QPushButton * stBtn = new QPushButton("&Start/stop");
        stBtn->setCheckable(true);
        hLayout->addWidget(stBtn);

        connect(stBtn, SIGNAL(clicked(bool)), 
                this, SLOT(startOrStopAll(bool)));

        layout->addLayout(hLayout);
    }

    setLayout(layout);
}

SenderSequence::~SenderSequence()
{
}

void SenderSequence::startOrStopAll(bool checked)
{
    // TODO implementation
}

const QString& SenderSequence::getName() const
{
    return m_name;
}

void SenderSequence::removeItems(ObjectId id)
{
    const items_t old = m_items;

    for (items_t::const_iterator it = old.begin(); 
            it != old.end(); it++) 
    {
        SenderSequenceItem * ptr = *it;

        if (ptr->objectId() == id)
        {
            m_items.removeAll(ptr);
            ptr->deleteLater();

            emit modified();
        }
    }
}

void SenderSequence::appendItem(SenderSequenceItem * item)
{
    // Before spacer
    m_layout->addWidget(item);

    // Scroll to item
    // m_scroll->ensureWidgetVisible(item);

    connect(item, SIGNAL(doDelete()),
            this, SLOT(deleteItem()));
    connect(item, SIGNAL(up()),
            this, SLOT(moveUpItem()));
    connect(item, SIGNAL(down()),
            this, SLOT(moveDownItem()));

    m_items.push_back(item);

    emit modified();
}

void SenderSequence::deleteItem(SenderSequenceItem * item)
{
    m_items.removeAll(item);
    item->deleteLater();

    emit modified();
}

void SenderSequence::moveUpItem(SenderSequenceItem * item)
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

void SenderSequence::moveDownItem(SenderSequenceItem * item)
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

void SenderSequence::deleteItem()
{
    SenderSequenceItem * sndObj = 
        qobject_cast< SenderSequenceItem * >(sender());

    if (sndObj)
        deleteItem(sndObj);
}

void SenderSequence::moveUpItem()
{
    SenderSequenceItem * sndObj = 
        qobject_cast< SenderSequenceItem * >(sender());

    if (sndObj)
        moveUpItem(sndObj);
}

void SenderSequence::moveDownItem()
{
    SenderSequenceItem * sndObj = 
        qobject_cast< SenderSequenceItem * >(sender());

    if (sndObj)
        moveDownItem(sndObj);
}

// Tool
SenderSequenceTool::SenderSequenceTool(QWidget * parent) :
    QWidget(parent)
{
    m_model.setDisplayParameters(false);

    QHBoxLayout * layout = new QHBoxLayout();
    QSplitter * splitter = new QSplitter(Qt::Horizontal);

    m_view = new OperationsView();
    m_view->setMaximumWidth(200);
    splitter->addWidget(m_view);

    m_view->setModel(&m_model);

    // Tabs
    m_tabs = new QTabWidget();
    m_tabs->setTabsClosable(true);

    QToolButton * btNewTab = new QToolButton();
    btNewTab->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    m_tabs->setCornerWidget(btNewTab);

    splitter->addWidget(m_tabs);
    layout->addWidget(splitter);

    splitter->setStretchFactor(0, 30);
    splitter->setStretchFactor(1, 70);

    setLayout(layout);

    // Signals
    connect(m_view, 
            SIGNAL(selectedOperation(Objref_ptr, 
                    OperationDescriptor_ptr)),
            this,
            SLOT(appendOperation(Objref_ptr, 
                    OperationDescriptor_ptr)));

    connect(btNewTab, SIGNAL(clicked()),
            this, SLOT(createSequence()));

    connect(m_tabs, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeSequence(int)));

    // Context menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
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

SenderSequenceTool::~SenderSequenceTool()
{
}

void SenderSequenceTool::objrefCreated(Objref_ptr object)
{
    m_model.registerInstance(object);
}

void SenderSequenceTool::objrefDeleted(ObjectId id)
{
    m_model.unregisterInstance(id);

    // Remove all its associated senders
    for (sequences_t::iterator it = m_sequences.begin(); 
            it != m_sequences.end(); ++it) 
    {
        (*it)->removeItems(id);
    }
}

SenderSequenceItem * 
SenderSequenceTool::appendOperation(Objref_ptr object, 
		OperationDescriptor_ptr op)
{
    if (!object || !op)
        return NULL;

    SenderSequence * seq = NULL;
    if (m_sequences.isEmpty())
        seq = createSequence();
    else
        seq = m_sequences[m_tabs->currentIndex()];

    OperationSender * sender = new OperationSender(object);
    sender->initialize(op);
    SenderSequenceItem * item = 
        new SenderSequenceItem(sender);

    seq->appendItem(item);

    return item;
}

SenderSequence* SenderSequenceTool::createSequence()
{
    SenderSequence * seq = new SenderSequence("no name");
    m_sequences.push_back(seq);
    m_tabs->addTab(seq, seq->getName());
    m_tabs->setCurrentIndex(m_tabs->count() - 1);

    connect(seq, SIGNAL(modified()),
            this, SLOT(sequenceModified()));

    return seq;
}

void SenderSequenceTool::showContextMenu(const QPoint& pos)
{
    if (m_sequences.size() > 0)
    {
        m_menu->exec(QCursor::pos());
    }
}

void SenderSequenceTool::saveCurrentSequence()
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

void SenderSequenceTool::loadSequence()
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

void SenderSequenceTool::closeSequence(int idx)
{
    // QT Documentation
    // Removes the tab at position index from this stack of widgets. 
    // The page widget itself is not deleted.
    m_tabs->removeTab(idx);

    delete m_sequences.takeAt(idx);
}

void SenderSequenceTool::sequenceModified()
{
    SenderSequence * sndObj = 
        qobject_cast< SenderSequence * >(sender());

    int idx = -1;
    if (sndObj && (idx = m_sequences.indexOf(sndObj)) != -1)
    {
        m_tabs->setTabText(idx, sndObj->getName() + " *");
    }
}

// Settings

void SenderSequenceItem::save(QVariant& settings)
{
    QVariantMap map;

    map["object"] = m_dlg->object()->name();
    map["operation"] = m_dlg->getReflective()->get_name();

    // User-defined title
    map["title"] = m_title->text();

    m_dlg->save(map["form"]);

    settings = map;
}

void SenderSequenceItem::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    if (map.contains("form")) m_dlg->load(map.value("form"));

    // User-defined title
    if (map.contains("title"))
    {
        m_title->setText(map.value("title").toString());
    }
}

void SenderSequence::save(QVariant& settings)
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

void SenderSequence::load(const QVariant& settings)
{
    // TODO currently impossible
}

void SenderSequenceTool::save(QVariant& settings)
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

void SenderSequenceTool::load(const QVariant& settings)
{
    // Clear its current configuration
    m_tabs->clear();
    for (int i = 0; i < m_sequences.size(); i++) 
    {
        delete m_sequences.at(i);
    }
    m_sequences.clear();
    // En clear

    const QVariantList list = settings.toList();

    for (int i = 0; i < list.size(); i++) 
    {
        SenderSequence * seq = createSequence();
        // It is not possible seq->load(list.at(i));

        const QVariantList seqList = list.at(i).toList();

        for (int j = 0; j < seqList.size(); j++) 
        {
            const QVariantMap map = seqList.at(j).toMap();
            const QString obj = map.value("object").toString();
            const std::string operation = 
                map.value("operation").toString().toStdString();

            Objref_ptr object = m_model.getInstance(obj);
            OperationDescriptor_ptr op = NULL;

            if (object && 
                    (op = object->interface()->get_reflective_by_name(operation.c_str())))
            {
                appendOperation(object, op)->load(seqList.at(j));
            }
        }
    }
}



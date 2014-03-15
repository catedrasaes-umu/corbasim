// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AbstractSequence.cpp
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

#include "AbstractSequenceTool.hpp"
#include <corbasim/gui/json.hpp>
#include <corbasim/gui/item/OperationsView.hpp>
#include <corbasim/qt/StartStopButton.hpp>

#include <fstream>
#include <iostream>

using namespace corbasim::gui;

AbstractSequenceItem::AbstractSequenceItem(
        Objref_ptr object,
        OperationDescriptor_ptr operation,
        QWidget * parent) :
    qt::AbstractItemFrame(parent), m_object(object),
    m_operation(operation)
{
    const QString& id = object->name();

    QVBoxLayout * layout = new QVBoxLayout();

    // Title bar
    QHBoxLayout * tLayout = new QHBoxLayout();
    QLabel * title = new QLabel(
        QString("<b>Object: '%1' Operation: '%2'</b>")
            .arg(id).arg(operation->get_name()));
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

        btShowInput->setMaximumSize(20, 20);
        btUp->setMaximumSize(20, 20);
        btDown->setMaximumSize(20, 20);
        btDelete->setMaximumSize(20, 20);

        connect(btShowInput, SIGNAL(toggled(bool)),
                this, SLOT(showDetails(bool)));
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

    setLayout(layout);

    setLineWidth(1);
    setFrameStyle(QFrame::Box);
}

AbstractSequenceItem::~AbstractSequenceItem()
{
}

ObjectId AbstractSequenceItem::objectId() const
{
    return m_object->id();
}

Objref_ptr AbstractSequenceItem::object() const
{
    return m_object;
}

OperationDescriptor_ptr AbstractSequenceItem::operation() const
{
    return m_operation;
}

AbstractSequence::AbstractSequence(const QString& name,
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
        m_stBtn = new qt::StartStopButton();
        hLayout->addWidget(m_stBtn);

        connect(m_stBtn, SIGNAL(clicked(bool)),
                this, SLOT(startOrStopAll(bool)));
        connect(m_stBtn, SIGNAL(toggled(bool)),
                this, SLOT(startOrStopAll(bool)));

        layout->addLayout(hLayout);
    }

    setLayout(layout);
}

AbstractSequence::~AbstractSequence()
{
}

void AbstractSequence::startOrStopAll(bool checked)
{
    // TODO better implementation
    typedef QList< QPushButton * > list_t;

    const list_t list = findChildren< QPushButton * >("start-stop");

    list_t::const_iterator it = list.begin();
    list_t::const_iterator end = list.end();

    for (; it != end; it++)
    {
        (*it)->setChecked(checked);
    }
}

const QString& AbstractSequence::getName() const
{
    return m_name;
}

void AbstractSequence::setName(const QString& name)
{
    m_name = name;
}

void AbstractSequence::removeInstance(ObjectId id)
{
    const items_t old = m_items;

    for (items_t::const_iterator it = old.begin();
            it != old.end(); it++)
    {
        AbstractSequenceItem * ptr = *it;

        if (ptr->objectId() == id)
        {
            m_items.removeAll(ptr);
            ptr->deleteLater();

            emit modified();
        }
    }
}

void AbstractSequence::appendItem(AbstractSequenceItem * item)
{
    // Before spacer
    m_layout->addWidget(item);

    // Scroll to item
    m_scroll->widget()->resize(m_scroll->widget()->sizeHint());
    qApp->processEvents();
    m_scroll->ensureWidgetVisible(item);

    connect(item, SIGNAL(doDelete()),
            this, SLOT(deleteItem()));
    connect(item, SIGNAL(up()),
            this, SLOT(moveUpItem()));
    connect(item, SIGNAL(down()),
            this, SLOT(moveDownItem()));

    m_items.push_back(item);

    emit modified();
}

void AbstractSequence::forgetItem(AbstractSequenceItem * item)
{
    m_items.removeAll(item);
    emit modified();
}

void AbstractSequence::deleteItem(AbstractSequenceItem * item)
{
    m_items.removeAll(item);
    item->deleteLater();

    emit modified();
}

void AbstractSequence::moveUpItem(AbstractSequenceItem * item)
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

void AbstractSequence::moveDownItem(AbstractSequenceItem * item)
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

void AbstractSequence::deleteItem()
{
    AbstractSequenceItem * sndObj =
        qobject_cast< AbstractSequenceItem * >(sender());

    if (sndObj)
        deleteItem(sndObj);
}

void AbstractSequence::moveUpItem()
{
    AbstractSequenceItem * sndObj =
        qobject_cast< AbstractSequenceItem * >(sender());

    if (sndObj)
        moveUpItem(sndObj);
}

void AbstractSequence::moveDownItem()
{
    AbstractSequenceItem * sndObj =
        qobject_cast< AbstractSequenceItem * >(sender());

    if (sndObj)
        moveDownItem(sndObj);
}

// Tool
AbstractSequenceTool::AbstractSequenceTool(QWidget * parent) :
    AbstractTool(parent), m_moveToSignalMapper(NULL), m_currentItem(NULL)
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
            SLOT(appendAbstractItem(Objref_ptr,
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
    m_menu->addAction("Set name", this, SLOT(showSetName()));
    m_menu->addSeparator();
    m_menu->addAction("New tabs", this, SLOT(createSequence()));
    m_menu->addAction("Load tabs", this, SLOT(loadSequence()));
    m_menu->addAction("Save tabs as...", this, SLOT(saveCurrentSequence()));
    m_menu->addSeparator();
    // Current item actions
    m_menuCurrentItem = m_menu->addMenu("Current item");
    m_currentItemActions.push_back(
            m_menuCurrentItem->addAction("Duplicate",
                this, SLOT(duplicateCurrentItem())));
    m_currentItemActions.push_back(
            m_menuCurrentItem->addAction("Delete",
                this, SLOT(deleteCurrentItem())));
    m_menuCurrentItem->addSeparator();
    m_menuCurrentItemMoveTo = m_menuCurrentItem->addMenu("Move to tab");
    m_menuCurrentItem->addSeparator();
    m_currentItemActions.push_back(
            m_menuCurrentItem->addAction("Load configuration",
                this, SLOT(loadCurrentItem())));
    m_currentItemActions.push_back(
            m_menuCurrentItem->addAction("Save configuration",
                this, SLOT(saveCurrentItem())));

    createSequence();
}

AbstractSequenceTool::~AbstractSequenceTool()
{
    delete m_moveToSignalMapper;
}

void AbstractSequenceTool::registerInstance(Objref_ptr object)
{
    m_model.registerInstance(object);
}

void AbstractSequenceTool::unregisterInstance(ObjectId id)
{
    m_model.unregisterInstance(id);

    for (sequences_t::iterator it = m_sequences.begin();
            it != m_sequences.end(); ++it)
    {
        (*it)->removeInstance(id);
    }
}

AbstractSequenceItem *
AbstractSequenceTool::appendAbstractItem(
        Objref_ptr object,
		OperationDescriptor_ptr op)
{
    if (!object || !op)
        return NULL;

    AbstractSequence * seq = NULL;
    if (m_sequences.isEmpty())
        seq = createSequence();
    else
        seq = m_sequences[m_tabs->currentIndex()];

    AbstractSequenceItem * item =
        createAbstractItem(object, op);

    seq->appendItem(item);

    return item;
}

AbstractSequence* AbstractSequenceTool::createSequence()
{
    AbstractSequence * seq = new AbstractSequence("no name");
    m_sequences.push_back(seq);
    m_tabs->addTab(seq, seq->getName());
    m_tabs->setCurrentIndex(m_tabs->count() - 1);

    connect(seq, SIGNAL(modified()),
            this, SLOT(sequenceModified()));

    return seq;
}

void AbstractSequenceTool::showContextMenu(const QPoint& pos)
{
    if (m_sequences.size() > 0)
    {
        // Looking for current item
        QWidget * w = childAt(pos);
        m_currentItem = NULL;

        while (w && w != this &&
                !(m_currentItem = dynamic_cast< AbstractSequenceItem * >(w)))
            w = w->parentWidget();
        // End looking for current item

        // Actions enabled only when an item is under the cursor
        for (QList< QAction * >::iterator it = m_currentItemActions.begin();
                it != m_currentItemActions.end(); ++it)
        {
            (*it)->setEnabled(m_currentItem != NULL);
        }

        int currentTab = m_tabs->currentIndex();
        regenerateMoveTo(currentTab);

        m_menu->exec(QCursor::pos());
    }
}

void AbstractSequenceTool::regenerateMoveTo(int idx)
{
    delete m_moveToSignalMapper;

    m_menuCurrentItemMoveTo->clear();

    m_moveToSignalMapper = new QSignalMapper(this);

    connect(m_moveToSignalMapper, SIGNAL(mapped(int)),
            this, SLOT(moveCurrentItemTo(int)));

    for (int i = 0; i < m_sequences.size(); i++)
    {
        QAction * action =
            m_menuCurrentItemMoveTo->addAction(m_sequences[i]->getName());

        connect(action, SIGNAL(triggered()),
                m_moveToSignalMapper, SLOT(map()));

        // Only enabled if isn't the current sequence
        action->setEnabled(m_currentItem && (i != idx));

        m_moveToSignalMapper->setMapping(action, i);
    }
}

void AbstractSequenceTool::saveCurrentSequence()
{
    QString file = QFileDialog::getSaveFileName( 0, tr(
                "Select a file"), ".", m_filter);

    // User cancels
    if (file.isEmpty())
        return;

    if(!m_extension.isEmpty() && !file.endsWith(m_extension))
        file.append(m_extension);

    QVariant v;
    save(v);

    std::ofstream ofs(file.toStdString().c_str());
    json::ostream_writer_t ow(ofs, true);

    toJson(ow, v);
}

void AbstractSequenceTool::loadSequence()
{
    const QString file = QFileDialog::getOpenFileName( 0, tr(
                "Select some file"), ".", m_filter);

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

void AbstractSequenceTool::saveCurrentItem()
{
    if (m_currentItem)
    {
        QString file = QFileDialog::getSaveFileName(
                0, tr("Select a file"), ".");

        // User cancels
        if (file.isEmpty())
            return;

        QVariant v;
        m_currentItem->save(v);

        std::ofstream ofs(file.toStdString().c_str());
        json::ostream_writer_t ow(ofs, true);

        toJson(ow, v);
    }
}

void AbstractSequenceTool::loadCurrentItem()
{
    if (m_currentItem)
    {
        const QString file = QFileDialog::getOpenFileName(
                0, tr("Select a file"), ".");

        // User cancels
        if (file.isEmpty())
            return;

        QVariant var;

        // Try to Read a JSON file
        bool res = fromJsonFile(file.toStdString().c_str(), var);

        if (res)
        {
            m_currentItem->load(var);
        }
        else
        {
            // TODO display error
        }
    }
}

void AbstractSequenceTool::duplicateCurrentItem()
{
    int idx = m_tabs->currentIndex();

    if (m_currentItem && idx > -1 && idx < m_sequences.size())
    {
        AbstractSequence * seq = m_sequences[idx];

        // Creates the new item
        AbstractSequenceItem * item =
            createAbstractItem(m_currentItem->object(),
                    m_currentItem->operation());

        // Save its settings
        QVariant settings;
        m_currentItem->save(settings);

        // load this settings in the new item
        item->load(settings);

        // Appends it to the sequence
        seq->appendItem(item);
    }
}

void AbstractSequenceTool::deleteCurrentItem()
{
    int idx = m_tabs->currentIndex();

    if (m_currentItem && idx > -1 && idx < m_sequences.size())
    {
        m_sequences[idx]->deleteItem(m_currentItem);

        m_currentItem = NULL;
    }
}

void AbstractSequenceTool::moveCurrentItemTo(int idx)
{
    if (m_currentItem && idx > -1 && idx < m_sequences.size())
    {
        int currentTab = m_tabs->currentIndex();

        m_sequences[currentTab]->forgetItem(m_currentItem);

        // Appends the current item in the specified tab
        m_tabs->setCurrentIndex(idx);
        m_sequences[idx]->appendItem(m_currentItem);
    }
}

void AbstractSequenceTool::closeSequence(int idx)
{
    // QT Documentation
    // Removes the tab at position index from this stack of widgets.
    // The page widget itself is not deleted.
    m_tabs->removeTab(idx);

    delete m_sequences.takeAt(idx);
}

void AbstractSequenceTool::sequenceModified()
{
    AbstractSequence * sndObj =
        qobject_cast< AbstractSequence * >(sender());

    int idx = -1;
    if (sndObj && (idx = m_sequences.indexOf(sndObj)) != -1)
    {
        m_tabs->setTabText(idx, sndObj->getName() + " *");
    }
}

void AbstractSequenceTool::setTreeVisible(bool visible)
{
    m_view->setVisible(visible);
}

void AbstractSequenceTool::showSetName()
{
    bool ok = false;
    const QString name = QInputDialog::getText(this,
            "Sequence name", "Insert name for the sequence",
            QLineEdit::Normal, QString(), &ok);

    if (ok)
    {
        int currentIndex = m_tabs->currentIndex();

        m_sequences[currentIndex]->setName(name);
        m_tabs->setTabText(currentIndex, name);
    }
}

void AbstractSequence::stop()
{
    m_stBtn->setChecked(false);
}

void AbstractSequenceTool::stop()
{
    for (sequences_t::iterator it = m_sequences.begin();
            it != m_sequences.end(); ++it)
    {
        (*it)->stop();
    }
}

// Settings

void AbstractSequenceItem::save(QVariant& settings)
{
    QVariantMap map;

    map["object"] = m_object->name();
    map["operation"] = m_operation->get_name();

    // User-defined title
    map["title"] = m_title->text();

    doSave(map);

    settings = map;
}

void AbstractSequenceItem::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    // User-defined title
    m_title->setText(map.value("title").toString());

    doLoad(map);
}

void AbstractSequence::save(QVariant& settings)
{
    QVariantMap map;
    QVariantList list;

    for (int i = 0; i < m_items.size(); i++)
    {
        QVariant v;
        m_items.at(i)->save(v);
        list << v;
    }

    map["name"] = getName();
    map["items"] = list;

    settings = map;
}

void AbstractSequence::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();
    setName(map["name"].toString());
}

void AbstractSequenceTool::save(QVariant& settings)
{
    QVariantList list;

    for (sequences_t::iterator it = m_sequences.begin();
            it != m_sequences.end(); ++it)
    {
        QVariant v;
        (*it)->save(v);
        list << v;
    }

    settings = list;
}

void AbstractSequenceTool::load(const QVariant& settings)
{
    // Clear its current configuration
    m_tabs->clear();
    for (sequences_t::iterator it = m_sequences.begin();
            it != m_sequences.end(); ++it)
    {
        delete *it;
    }
    m_sequences.clear();

    const QVariantList list = settings.toList();

    int i = 0;
    for (QVariantList::const_iterator it = list.begin();
            it != list.end(); it++, i++)
    {
        AbstractSequence * seq = createSequence();

        const QVariantMap seqMap = it->toMap();
        const QVariantList seqList = seqMap["items"].toList();

        for (QVariantList::const_iterator lit = seqList.begin();
                lit != seqList.end(); lit++)
        {
            const QVariantMap map = lit->toMap();
            const QString obj = map.value("object").toString();
            const std::string operation =
                map.value("operation").toString().toStdString();

            Objref_ptr object = m_model.getInstance(obj);
            OperationDescriptor_ptr op = NULL;

            if (object &&
                    (op = object->interface()->get_reflective_by_name(operation.c_str())))
            {
                appendAbstractItem(object, op)->load(*lit);
            }
        }

        seq->load(*it);

        // Puts its name in its tab
        m_tabs->setTabText(i, seq->getName());
    }
}


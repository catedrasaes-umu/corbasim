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
#include <corbasim/gui/dialogs_fwd.hpp>
#include <boost/next_prior.hpp>

using namespace corbasim::qt;

OperationSequenceItem::OperationSequenceItem(const QString& id,
        dialogs::input_base* dlg,
        QWidget * parent) : 
    QFrame(parent), m_id(id), m_dlg(dlg)
{
    QVBoxLayout * layout = new QVBoxLayout();

    // Title bar
    QHBoxLayout * tLayout = new QHBoxLayout();
    QLabel * title = new QLabel(
        QString("<b>Object: '%1' Operation: '%2'</b>").arg(id).arg(
            dlg->get_name()));
    tLayout->addWidget(title);
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    tLayout->addItem(spacer);

    layout->addLayout(tLayout);

    // Editor
    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_dlg->get_qwidget());
    m_dlg->get_qwidget()->hide();
    layout->addLayout(m_layout);

    // Buttons
    QHBoxLayout * bLayout = new QHBoxLayout();
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

    // Horizontal spacer
    spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    bLayout->addItem(spacer);

    QPushButton * btSend = new QPushButton("Send");
    // QPushButton * btSendNext = new QPushButton("Send and next");

    bLayout->addWidget(btSend);
    // bLayout->addWidget(btSendNext);
    
    QObject::connect(btShowInput, SIGNAL(toggled(bool)),
            m_dlg->get_qwidget(), SLOT(setVisible(bool)));

    QObject::connect(btSend, SIGNAL(clicked()),
            this, SLOT(sendClicked()));

    QObject::connect(btDelete, SIGNAL(clicked()),
            this, SLOT(deleteClicked()));
    QObject::connect(btUp, SIGNAL(clicked()),
            this, SLOT(upClicked()));
    QObject::connect(btDown, SIGNAL(clicked()),
            this, SLOT(downClicked()));

    layout->addLayout(bLayout);
    // End buttons

    setLayout(layout);

    setLineWidth(1);
    setFrameStyle(QFrame::Box);

    // Tooltips
    btShowInput->setToolTip("Show/hide detailed input form");
    btDelete->setToolTip("Delete item");
    btUp->setToolTip("Move up");
    btDown->setToolTip("Move down");
}

OperationSequenceItem::~OperationSequenceItem()
{
}

void OperationSequenceItem::sendClicked()
{
    event::request_ptr req_(m_dlg->create_request());
    emit sendRequest(m_id, req_);
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

OperationSequence::OperationSequence(QWidget * parent) :
    QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QWidget * scrollWidget = new QWidget();
    QVBoxLayout * scrollLayout = new QVBoxLayout();
    m_layout = new CustomLayout();
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
}

void OperationSequence::deleteItem(OperationSequenceItem * item)
{
    m_items.removeAll(item);
    item->deleteLater();
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
                    const corbasim::gui::operation_factory_base *)),
            this,
            SLOT(appendOperation(const QString&, 
                    const corbasim::gui::operation_factory_base *)));

    QObject::connect(btNewTab, SIGNAL(clicked()),
            this, SLOT(createSequence()));

    QObject::connect(m_tabs, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeSequence(int)));

    setMinimumHeight(400);
    setMinimumWidth(600);
}

OperationSequenceTool::~OperationSequenceTool()
{
}

void OperationSequenceTool::objrefCreated(const QString& id,
    const corbasim::gui::gui_factory_base * factory)
{
    m_model.registerInstance(id, factory);
}

void OperationSequenceTool::objrefDeleted(const QString& id)
{
    m_model.unregisterInstance(id);
}

void OperationSequenceTool::appendOperation(const QString& id, 
        gui::operation_factory_base const * op)
{
    OperationSequence * seq = NULL;
    if (m_sequences.isEmpty())
        seq = createSequence();
    else
        seq = m_sequences[m_tabs->currentIndex()];

    OperationSequenceItem * item = 
        new OperationSequenceItem(id, op->create_input());

    seq->appendItem(item);

    QObject::connect(item, SIGNAL(sendRequest(QString,
                        corbasim::event::request_ptr)),
                this, SLOT(slotSendRequest(const QString&, 
                        corbasim::event::request_ptr)));
}

OperationSequence* OperationSequenceTool::createSequence()
{
    OperationSequence * seq = new OperationSequence();
    m_sequences.push_back(seq);
    m_tabs->addTab(seq, "unnamed");
    m_tabs->setCurrentIndex(m_tabs->count() - 1);
    return seq;
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
        gui::gui_factory_base const * factory)
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
        gui::operation_factory_base const * op =
            factory->get_factory_by_index(i);

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

        // QStandardItem * mItem = itemFromIndex(index);
        // gui::operation_factory_base const * op =
        //    qvariant_cast< gui::operation_factory_base const * >(mItem->data()); 

        gui::operation_factory_base const * op =
            item.factory->get_factory_by_name(index.data().toString().toStdString());

        emit selectedOperation(item.name, op);
    }
}



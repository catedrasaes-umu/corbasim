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
    m_id(id), m_dlg(dlg)
{
    QVBoxLayout * layout = new QVBoxLayout();

    // Title bar
    QHBoxLayout * tLayout = new QHBoxLayout();
    tLayout->addWidget(new QLabel(
                QString("Object: '%1' Operation: '%2'").arg(id).arg(dlg->get_name())));
    layout->addLayout(tLayout);

    // Editor
    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_dlg->get_qwidget());
    m_dlg->get_qwidget()->hide();
    layout->addLayout(m_layout);

    // Buttons
    QHBoxLayout * bLayout = new QHBoxLayout();
    QToolButton * btUp = new QToolButton();
    btUp->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    QToolButton * btDown = new QToolButton();
    btDown->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
    QToolButton * btDelete = new QToolButton();
    btDelete->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
    bLayout->addWidget(btUp);
    bLayout->addWidget(btDown);
    bLayout->addWidget(btDelete);

    // Horizontal spacer
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Minimum);
    bLayout->addItem(spacer);

    QPushButton * btShowInput = new QPushButton("Show input");
    btShowInput->setCheckable(true);
    QPushButton * btSend = new QPushButton("Send");
    QPushButton * btSendNext = new QPushButton("Send and next");

    bLayout->addWidget(btShowInput);
    bLayout->addWidget(btSend);
    bLayout->addWidget(btSendNext);
    
    QObject::connect(btShowInput, SIGNAL(toggled(bool)),
            m_dlg->get_qwidget(), SLOT(setVisible(bool)));

    QObject::connect(btDelete, SIGNAL(clicked()),
            this, SLOT(deleteClicked()));

    layout->addLayout(bLayout);
    // End buttons

    setLayout(layout);
}

OperationSequenceItem::~OperationSequenceItem()
{
}

void OperationSequenceItem::deleteClicked()
{
    emit doDelete();
}

OperationSequence::OperationSequence(QWidget * parent) :
    QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    QWidget * scrollWidget = new QWidget();
    m_layout = new QVBoxLayout();
    scrollWidget->setLayout(m_layout);

    // Scroll
    QScrollArea * scroll = new QScrollArea();
    scroll->setObjectName("scroll");
    scroll->setWidgetResizable(true);
    scroll->setWidget(scrollWidget);

    layout->addWidget(scroll);
    setLayout(layout);
}

OperationSequence::~OperationSequence()
{
}

void OperationSequence::appendItem(OperationSequenceItem * item)
{
    m_layout->addWidget(item);

    QObject::connect(item, SIGNAL(doDelete()),
            this, SLOT(deleteItem()));

    m_items.push_back(item);
}

void OperationSequence::deleteItem(OperationSequenceItem * item)
{
    m_items.removeAll(item);
    item->deleteLater();
}

void OperationSequence::deleteItem()
{
    OperationSequenceItem * sndObj = 
        qobject_cast< OperationSequenceItem * >(sender());

    if (sndObj)
        deleteItem(sndObj);
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

    m_tabs = new QTabWidget();
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
}

OperationSequence* OperationSequenceTool::createSequence()
{
    OperationSequence * seq = new OperationSequence();
    m_sequences.push_back(seq);
    m_tabs->addTab(seq, "unnamed");
    return seq;
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
        FirstLevelItem& item = *boost::next(m_items.begin(), parent.row());

        // QStandardItem * mItem = itemFromIndex(index);
        // gui::operation_factory_base const * op =
        //    qvariant_cast< gui::operation_factory_base const * >(mItem->data()); 

        gui::operation_factory_base const * op =
            item.factory->get_factory_by_name(index.data().toString().toStdString());

        emit selectedOperation(item.name, op);
    }
}



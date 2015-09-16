// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FilteredLogView.cpp
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

#include "FilteredLogView.hpp"
#include <QHBoxLayout>
#include <QTreeView>
#include <QSplitter>
#include <corbasim/gui/item/TreeView.hpp>
#include <corbasim/gui/ReflectiveGUI.hpp>

using namespace corbasim::gui;

FilteredLogView::FilteredLogView(QWidget * parent) :
    AbstractTool(parent),
    m_filterModel(this), m_model(this),
    m_sourceModel(NULL)
{
    QHBoxLayout * layout = new QHBoxLayout();

    QSplitter * splitter = new QSplitter(Qt::Horizontal);

    QTreeView * filterView = new QTreeView();
    QTreeView * logView = new TreeView();
    filterView->setObjectName("filterView");
    logView->setObjectName("logView");

    filterView->setModel(&m_filterModel);
    logView->setModel(&m_model);

    logView->setDragDropMode(QAbstractItemView::DragOnly);
    logView->setDragEnabled(true);

    // links between models
    m_model.setFilterModel(&m_filterModel);

    m_viewer = new EntryViewer();

    splitter->addWidget(filterView);
    splitter->addWidget(logView);
    splitter->addWidget(m_viewer);

    layout->addWidget(splitter);

    setLayout(layout);

    // Size
    setMinimumSize(650, 400);

    splitter->setStretchFactor(0, 20);
    splitter->setStretchFactor(1, 50);
    splitter->setStretchFactor(1, 30);

    /*
    connect(logView, SIGNAL(clicked(const QModelIndex&)),
            this, SLOT(selected(const QModelIndex&)));
    connect(logView, SIGNAL(entered(const QModelIndex&)),
            this, SLOT(selected(const QModelIndex&)));
    connect(logView, SIGNAL(activated(const QModelIndex&)),
            this, SLOT(selected(const QModelIndex&)));
    */

    connect(logView->selectionModel(),
            SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
            this, SLOT(currentChanged(const QModelIndex&, const QModelIndex&)));
}

FilteredLogView::~FilteredLogView()
{
}

void FilteredLogView::registerInstance(Objref_ptr object)
{
    m_filterModel.registerInstance(object);
}

void FilteredLogView::unregisterInstance(ObjectId id)
{
    m_filterModel.unregisterInstance(id);
}

void FilteredLogView::setLogModel(QAbstractItemModel * model)
{
    m_model.setSourceModel(model);

    QTreeView * logView = findChild< QTreeView * >("logView");

    logView->setColumnWidth(0, 150);
    logView->setColumnWidth(1, 200);
    logView->setColumnWidth(2, 200);

    m_sourceModel = dynamic_cast< LogModel * >(model);
}

void FilteredLogView::save(QVariant& settings)
{
    m_filterModel.save(settings);
}

void FilteredLogView::load(const QVariant& settings)
{
    m_filterModel.load(settings);
}

void FilteredLogView::currentChanged(const QModelIndex& current,
        const QModelIndex& previous)
{
    selected(current);
}

void FilteredLogView::selected(const QModelIndex& index)
{
    QModelIndex sourceIndex = m_model.mapToSource(index);

    if (m_sourceModel)
    {
        const LogModel::LogEntry * entry = m_sourceModel->getEntry(sourceIndex);

        if (entry)
        {
            m_viewer->show(entry->text, entry->reflective, entry->req);
        }
    }
}

EntryViewer::EntryViewer(QWidget * parent) :
    QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();

    // Label
    m_label = new QLabel();
    layout->addWidget(m_label);

    // Stack
    m_stack = new QStackedWidget(this);

    layout->addWidget(m_stack);
    layout->setMargin(0);
    setLayout(layout);
}

EntryViewer::~EntryViewer()
{
}

void EntryViewer::show(
        const QString& text,
        corbasim::core::operation_reflective_base const * op,
        corbasim::core::request_ptr req)
{
    m_label->setText(text);

    viewers_t::iterator it = m_viewers.find(op);

    QScrollArea * w = NULL;

    if (it != m_viewers.end())
    {
        w = it->second;
    }
    else
    {
        w = new QScrollArea();
        w->setWidget(createSimpleWidget(op, w));
        w->setWidgetResizable(true);
        m_stack->addWidget(w);
    }

    ReflectiveWidgetBase * r =
        dynamic_cast< ReflectiveWidgetBase * >(w->widget());

    if (r)
    {
        r->_setReadOnly(true);

        core::holder holder = op->get_holder(req);
        r->fromHolder(holder);

        m_stack->setCurrentWidget(w);
    }
}


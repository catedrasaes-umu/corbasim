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

using namespace corbasim::reflective_gui;

FilteredLogView::FilteredLogView(QWidget * parent) :
    QWidget(parent), m_filterModel(this), m_model(this)
{
    QHBoxLayout * layout = new QHBoxLayout();

    QSplitter * splitter = new QSplitter(Qt::Horizontal);

    QTreeView * filterView = new QTreeView();
    QTreeView * logView = new QTreeView();
    filterView->setObjectName("filterView");
    logView->setObjectName("logView");

    filterView->setModel(&m_filterModel);
    logView->setModel(&m_model);

    logView->setDragDropMode(QAbstractItemView::DragOnly);
    logView->setDragEnabled(true);

    // links between models
    m_model.setFilterModel(&m_filterModel);

    splitter->addWidget(filterView);
    splitter->addWidget(logView);

    layout->addWidget(splitter);
    
    setLayout(layout);

    // Size
    setMinimumSize(800, 600);

    splitter->setStretchFactor(0, 30);
    splitter->setStretchFactor(1, 70);
}

FilteredLogView::~FilteredLogView()
{
}

void FilteredLogView::registerInstance(const QString& name,
        core::interface_reflective_base const * reflective)
{
    m_filterModel.registerInstance(name, reflective);
}

void FilteredLogView::unregisterInstance(const QString& name)
{
    m_filterModel.unregisterInstance(name);
}


void FilteredLogView::setLogModel(QAbstractItemModel * model)
{
    m_model.setSourceModel(model);

    QTreeView * logView = findChild< QTreeView * >("logView");

    logView->setColumnWidth(0, 150);
    logView->setColumnWidth(1, 200);
    logView->setColumnWidth(2, 200);
}

void FilteredLogView::save(QVariant& settings)
{
    m_filterModel.save(settings);
}

void FilteredLogView::load(const QVariant& settings)
{
    m_filterModel.load(settings);
}



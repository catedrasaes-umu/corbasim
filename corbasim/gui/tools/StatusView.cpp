// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * StatusView.cpp
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

#include "StatusView.hpp"
#include <corbasim/qt/Status.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>

using namespace corbasim::gui;

const int MAX_WIDTH = 300;

StatusViewItem::StatusViewItem(Objref_ptr objref, QWidget * parent) :
    QWidget(parent), m_objref(objref)
{
    m_status = new qt::Status();

    const QString labelText = QString("<b>%1</b>").
        arg(objref->name());

    const QString labelFqn = QString("<i>%2</i>").
        arg(objref->interface()->get_fqn());

    QGridLayout * l = new QGridLayout();
    l->addWidget(new QLabel(labelText), 0, 0);
    l->addWidget(new QLabel(labelFqn), 1, 0);
    l->addWidget(m_status, 0, 1, 1, 1);

    setLayout(l);
    setMaximumSize(MAX_WIDTH, 80);

    connect(objref.get(),
            SIGNAL(updatedReference(const CORBA::Object_var&)),
            this,
            SLOT(update()));

    update();
}

StatusViewItem::~StatusViewItem()
{
}

void StatusViewItem::update()
{
    if(m_objref->isNil())
        m_status->setRedLight();
    else
        m_status->setGreenLight();
}

StatusView::StatusView(QWidget * parent) :
    QWidget(parent)
{
    QVBoxLayout * l = new QVBoxLayout();
    QScrollArea * scroll = new QScrollArea();
    QWidget * w = new QWidget();

    // Layout
    m_layout = new QGridLayout();

    w->setLayout(m_layout);
    scroll->setWidget(w);
    scroll->setWidgetResizable(true);

    l->setMargin(0);
    l->addWidget(scroll);
    setLayout(l);
}

StatusView::~StatusView()
{
}

void StatusView::registerInstance(Objref_ptr objref)
{
    int columns = width() / MAX_WIDTH;

    if (!columns) columns = 1;

    if (m_items.find(objref->id()) == m_items.end())
    {
        StatusViewItem * item = new StatusViewItem(objref, this);

        m_layout->addWidget(item,
                m_items.size() / columns, m_items.size() % columns);

        m_items.insert(objref->id(), item);
    }
}

void StatusView::unregisterInstance(ObjectId id)
{
    items_t::iterator it = m_items.find(id);

    if (it != m_items.end())
    {
        delete it.value();
        m_items.erase(it);

        reallocate(width());
    }
}

void StatusView::resizeEvent(QResizeEvent * event)
{
    if (event->size().width() / MAX_WIDTH !=
            event->oldSize().width() != MAX_WIDTH)
    {
        reallocate(event->size().width());
    }
}

void StatusView::reallocate(int width)
{
    int columns = width / MAX_WIDTH;
    if (!columns) columns = 1;

    QGridLayout * l = m_layout;

    for (int i = l->count() - 1; i >= 0; i--)
    {
        l->takeAt(i);
    }

    int i = 0;
    for (items_t::iterator it = m_items.begin();
            it != m_items.end(); ++it, ++i)
    {
        l->addWidget(it.value(), i / columns, i % columns);
    }
}


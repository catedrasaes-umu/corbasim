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

using namespace corbasim::gui;

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
    setMaximumSize(300, 100);

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
    // Layout
    QGridLayout * l = new QGridLayout();
    setLayout(l);
}

StatusView::~StatusView()
{
}

void StatusView::registerInstance(Objref_ptr objref)
{
    if (m_items.find(objref->id()) == m_items.end())
    {
        StatusViewItem * item = new StatusViewItem(objref, this);

        static_cast< QGridLayout * >(layout())->addWidget(item, 
                m_items.size() / 2, m_items.size() % 2);

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
    }
}


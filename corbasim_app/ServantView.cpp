// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ServantView.cpp
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

#include "ServantView.hpp"
#include <corbasim/core/reflective_fwd.hpp>

using namespace corbasim::app;

ServantView::ServantView(QMdiArea * area,
        Objref_ptr servant,
        QObject * parent) :
    QObject(parent), m_mdi_area(area), m_servant(servant),
    m_sub_script(NULL), m_script(NULL)
{
    const QString menu_entry = QString("%1 (%2)")
        .arg(servant->name())
        .arg(servant->interface()->get_fqn());

    m_menu = new QMenu(menu_entry);
    // TODO
    m_menu->addAction("Self-stimulator", this, SLOT(showSelfStimulator()));
    m_menu->addSeparator();
    m_menu->addAction("&Delete", this, SLOT(deleteServant()));
}

ServantView::~ServantView()
{
    delete m_menu;
    delete m_script;
    delete m_sub_script;
}

QMenu * ServantView::getMenu() const
{
    return m_menu;
}

InterfaceDescriptor_ptr ServantView::getFactory() const
{
    return m_servant->interface();
}

void ServantView::deleteServant()
{
    emit deleteServant(m_servant->id());
}

void ServantView::showSelfStimulator()
{
    if (!m_sub_script)
    {
        m_script = new SimpleScriptEditor();
        m_script->initialize(m_servant->interface());

        m_sub_script = new QMdiSubWindow();
        m_sub_script->setWidget(m_script);
        m_sub_script->setWindowTitle(QString("%1: Self-stimulator").arg(m_servant->name()));
        m_mdi_area->addSubWindow(m_sub_script);

        QObject::connect(m_script,
            SIGNAL(sendRequest(Request_ptr)),
            m_servant.get(), 
            SLOT(sendRequest(Request_ptr)));
    }
    m_sub_script->showNormal();
    m_script->show();
    m_mdi_area->setActiveSubWindow(m_sub_script);
}

// Settings
void ServantView::save(QVariant& settings) 
{
    QVariantMap map;

    map["fqn"] = m_servant->interface()->get_fqn();

    settings = map;
}

void ServantView::load(const QVariant& settings) 
{
}



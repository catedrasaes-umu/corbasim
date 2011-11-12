// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Objref.cpp
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

#include "Objref.hpp"

using namespace corbasim::app::view;

Objref::Objref(QMdiArea * area,
        const QString& id, gui::gui_factory_base* factory,
        QObject * parent) :
    QObject(parent), m_mdi_area(area), m_id(id), m_factory(factory)
{
    m_menu = new QMenu(m_id);
    QMenu * operation = m_menu->addMenu("Operations");

    unsigned int count = factory->operation_count();

    // Inicializa los dialogos a nulo
    m_dialogs.resize(count, NULL);
    m_subwindows.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        gui::operation_factory_base * op = 
            factory->get_factory_by_index(i);

        const char * name = op->get_name();

        operation->addAction(name)->setData(i);
    }

    QObject::connect(operation,
            SIGNAL(triggered(QAction*)),
            this,
            SLOT(showRequestDialog(QAction*)));

    m_menu->addSeparator();
    m_menu->addAction("Delete");
}

Objref::~Objref()
{
}

QMenu * Objref::getMenu() const
{
    return m_menu;
}

void Objref::sendRequest(corbasim::event::request_ptr req)
{
    emit sendRequest(m_id, req);
}

void Objref::showRequestDialog(int idx)
{
    QMdiSubWindow * w = getWindow(idx);
    w->showNormal();
    getRequestDialog(idx)->show();
    m_mdi_area->setActiveSubWindow(w);
}

void Objref::showRequestDialog(QAction * act)
{
    showRequestDialog(act->data().toInt());
}

QMdiSubWindow * Objref::getWindow(int idx)
{
    QMdiSubWindow * win = m_subwindows[idx];

    if (!win)
    {
        m_subwindows[idx] = new QMdiSubWindow;

        m_subwindows[idx]->setWidget(getRequestDialog(idx));
        m_mdi_area->addSubWindow(m_subwindows[idx]);
        
        m_subwindows[idx]->setWindowTitle("Title");
        win = m_subwindows[idx];
    }

    return win;
}

corbasim::qt::RequestDialog * Objref::getRequestDialog(int idx)
{
    qt::RequestDialog * dlg = m_dialogs[idx];

    if (!dlg)
    {
        gui::operation_factory_base * op = 
            m_factory->get_factory_by_index(idx);
        const char * name = op->get_name();

        dialogs::input_base * input = op->create_input();
        dlg = new qt::RequestDialog(input);
        dlg->setWindowTitle(name);

        QObject::connect(dlg,
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            this, 
            SLOT(sendRequest(corbasim::event::request_ptr)));

        m_dialogs[idx] = dlg;
    }

    return dlg;
}


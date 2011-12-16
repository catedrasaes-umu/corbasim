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
#include <iostream>
#include <corbasim/core/factory.hpp>

using namespace corbasim::app::view;

Objref::Objref(QMdiArea * area,
        const QString& id, const gui::gui_factory_base* factory,
        QObject * parent) :
    QObject(parent), m_mdi_area(area), m_id(id), m_factory(factory),
    m_sub_script(NULL), 
    m_sub_reference(NULL),
    m_script(NULL),
    m_reference(NULL)
{
    QString menu_entry = QString("%1 (%2)")
        .arg(m_id).arg(factory->get_core_factory()->get_fqn());

    m_menu = new QMenu(menu_entry);
    // Takes the ownership
    QMenu * operation = m_menu->addMenu("Operations");

    unsigned int count = factory->operation_count();

    // Inicializa los dialogos a nulo
    m_dialogs.resize(count, NULL);
    m_subwindows.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        const gui::operation_factory_base * op = 
            factory->get_factory_by_index(i);

        const char * name = op->get_name();

        operation->addAction(name)->setData(i);
    }

    QObject::connect(operation,
            SIGNAL(triggered(QAction*)),
            this,
            SLOT(showRequestDialog(QAction*)));

    m_menu->addAction("&Script editor", this, SLOT(showScriptEditor()));
    m_menu->addAction("Set &reference", this, SLOT(showSetReference()));
    m_menu->addSeparator();
    m_menu->addAction("&Delete", this, SLOT(deleteObjref()));

    // Set reference
    m_sub_reference = new QMdiSubWindow;
    ReferenceValidatedWidget * w = 
        new ReferenceValidatedWidget(
                factory->get_core_factory()->create_validator());
    m_reference = w;
    m_sub_reference->setWidget(m_reference);
    m_mdi_area->addSubWindow(m_sub_reference);
    m_sub_reference->hide();
    m_sub_reference->setWindowTitle(QString("%1: reference").arg(id));

    QObject::connect(w, SIGNAL(updatedReference(CORBA::Object_var)),
            this, SLOT(slotUpdateReference(const CORBA::Object_var&)));
}

Objref::~Objref()
{
    std::cout << "Deleting: " << m_id.toStdString() << std::endl;

    m_menu->deleteLater();

    for (unsigned int i = 0; i < m_dialogs.size(); i++) 
    {
        m_dialogs[i]->deleteLater();
        m_subwindows[i]->deleteLater();
    }

    m_script->deleteLater();
    m_sub_script->deleteLater();

    m_reference->deleteLater();
    m_sub_reference->deleteLater();

}

QMenu * Objref::getMenu() const
{
    return m_menu;
}

const corbasim::gui::gui_factory_base * Objref::getFactory() const
{
    return m_factory;
}

void Objref::sendRequest(corbasim::event::request_ptr req)
{
    emit sendRequest(m_id, req);
}

void Objref::deleteObjref()
{
    emit deleteObjref(m_id);
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
        m_mdi_area->addSubWindow(m_subwindows[idx], Qt::SubWindow);
        
        // Window title
        QString title = QString("%1: %2").arg(m_id).arg(
            m_factory->get_factory_by_index(idx)->get_name());

        m_subwindows[idx]->setWindowTitle(title);
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

void Objref::showScriptEditor()
{
    if (!m_sub_script)
    {
        m_script = new qt::SimpleScriptEditor;
        m_script->initialize(m_factory);

        m_sub_script = new QMdiSubWindow;
        m_sub_script->setWidget(m_script);
        m_sub_script->setWindowTitle(
                QString("%1: Script editor").arg(m_id));
        m_mdi_area->addSubWindow(m_sub_script, Qt::SubWindow);

        QObject::connect(m_script,
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            this, 
            SLOT(sendRequest(corbasim::event::request_ptr)));
    }
    m_sub_script->showNormal();
    m_script->show();
    m_mdi_area->setActiveSubWindow(m_sub_script);
}

void Objref::showSetReference()
{
    m_sub_reference->showNormal();
    m_reference->show();
    m_mdi_area->setActiveSubWindow(m_sub_reference);
}

void Objref::slotUpdateReference(const CORBA::Object_var& ref)
{
    emit updatedReference(m_id, ref);
}

void Objref::updateReference(const CORBA::Object_var& ref)
{
    // TODO
}


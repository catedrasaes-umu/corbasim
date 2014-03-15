// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ObjrefView.cpp
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

#include "ObjrefView.hpp"

using namespace corbasim::app;

ObjrefView::ObjrefView(QMdiArea * area,
        Objref_ptr objref,
        QObject * parent) :
    QObject(parent), m_mdi_area(area), m_objref(objref),
    m_sub_script(NULL),
    m_script(NULL),

    m_subUpdateReference(NULL),
    m_updateReference(NULL),
    m_client(NULL)
{
    InterfaceDescriptor_ptr factory = objref->interface();
    const QString& name = objref->name();

    const QString menu_entry = QString("%1 (%2)")
        .arg(name).arg(factory->get_fqn());

    m_menu = new QMenu(menu_entry);
    // Takes the ownership
    QMenu * operation = m_menu->addMenu("Operations");
    QMenu * sender = m_menu->addMenu("Senders");

    unsigned int count = factory->operation_count();

    // Inicializa los dialogos a nulo
    m_dialogs.resize(count, NULL);
    m_senders.resize(count, NULL);
    m_subwindows.resize(count, NULL);
    m_subwindows_senders.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++)
    {
        OperationDescriptor_ptr op =
            factory->get_reflective_by_index(i);

        const char * name = op->get_name();

        operation->addAction(name)->setData(i);
        sender->addAction(name)->setData(i);
    }

    connect(operation,
            SIGNAL(triggered(QAction*)),
            this,
            SLOT(showRequestDialog(QAction*)));

    connect(sender,
            SIGNAL(triggered(QAction*)),
            this,
            SLOT(showSenderDialog(QAction*)));

    m_menu->addAction("&Script editor", this, SLOT(showScriptEditor()));
    m_menu->addAction("&Client application", this, SLOT(showClient()));
    m_menu->addAction("Set &reference", this, SLOT(showSetReference()));
    m_menu->addSeparator();
    m_menu->addAction("&Delete", this, SLOT(deleteObjref()));
}

ObjrefView::~ObjrefView()
{
    m_menu->deleteLater();

    for (unsigned int i = 0; i < m_dialogs.size(); i++)
    {
        delete m_dialogs[i];
        delete m_subwindows[i];
    }

    for (unsigned int i = 0; i < m_senders.size(); i++)
    {
        delete m_senders[i];
        delete m_subwindows_senders[i];
    }

    delete m_script;
    delete m_sub_script;
}

Objref_ptr ObjrefView::objref() const
{
    return m_objref;
}

QMenu * ObjrefView::getMenu() const
{
    return m_menu;
}

InterfaceDescriptor_ptr ObjrefView::getFactory() const
{
    return m_objref->interface();
}

void ObjrefView::deleteObjref()
{
    emit deleteObjref(m_objref->id());
}

void ObjrefView::showRequestDialog(OperationDescriptor_ptr op)
{
    InterfaceDescriptor_ptr iface = m_objref->interface();

    for (int i = 0; i < (int) iface->operation_count(); i++)
    {
        if (op == iface->get_reflective_by_index(i))
        {
            showRequestDialog(i);
            break;
        }
    }
}

void ObjrefView::showRequestDialog(int idx)
{
    QMdiSubWindow * w = getRequestWindow(idx);
    w->showNormal();
    getRequestDialog(idx)->show();
    m_mdi_area->setActiveSubWindow(w);
}

void ObjrefView::showRequestDialog(QAction * act)
{
    showRequestDialog(act->data().toInt());
}

void ObjrefView::showSenderDialog(int idx)
{
    QMdiSubWindow * w = getSenderWindow(idx);
    w->showNormal();
    getSenderDialog(idx)->show();
    m_mdi_area->setActiveSubWindow(w);
}

void ObjrefView::showSenderDialog(QAction * act)
{
    showSenderDialog(act->data().toInt());
}

QMdiSubWindow * ObjrefView::getRequestWindow(int idx)
{
    QMdiSubWindow * win = m_subwindows[idx];

    if (!win)
    {
        QWidget * widget = getRequestDialog(idx);
        m_subwindows[idx] = new QMdiSubWindow();
        m_subwindows[idx]->setWidget(widget);
        m_mdi_area->addSubWindow(m_subwindows[idx]);

        // Window title
        const QString title = QString("%1: %2").arg(m_objref->name()).arg(
            m_objref->interface()->get_reflective_by_index(idx)->get_name());

        m_subwindows[idx]->setWindowTitle(title);
        win = m_subwindows[idx];
    }

    return win;
}

RequestDialog * ObjrefView::getRequestDialog(int idx)
{
    RequestDialog * dlg = m_dialogs[idx];

    if (!dlg)
    {
        OperationDescriptor_ptr op =
            m_objref->interface()->get_reflective_by_index(idx);

        const char * name = op->get_name();

        dlg = new RequestDialog(op);
        dlg->setWindowTitle(name);

        connect(dlg,
            SIGNAL(sendRequest(Request_ptr)),
            m_objref.get(),
            SLOT(sendRequest(Request_ptr)));

        m_dialogs[idx] = dlg;
    }

    return dlg;
}

QMdiSubWindow * ObjrefView::getSenderWindow(int idx)
{
    QMdiSubWindow * win = m_subwindows_senders[idx];

    if (!win)
    {
        QWidget * widget = getSenderDialog(idx);
        m_subwindows_senders[idx] = new QMdiSubWindow();
        m_subwindows_senders[idx]->setWidget(widget);
        m_mdi_area->addSubWindow(m_subwindows_senders[idx]);

        // Window title
        const QString title = QString("%1: %2").arg(m_objref->name()).arg(
            m_objref->interface()->get_reflective_by_index(idx)->get_name());

        m_subwindows_senders[idx]->setWindowTitle(title);
        win = m_subwindows_senders[idx];
    }

    return win;
}

OperationSender * ObjrefView::getSenderDialog(int idx)
{
    OperationSender * dlg = m_senders[idx];

    if (!dlg)
    {
        OperationDescriptor_ptr op =
            m_objref->interface()->get_reflective_by_index(idx);

        const char * name = op->get_name();

        dlg = new OperationSender(m_objref);
        dlg->initialize(op);
        dlg->setWindowTitle(name);

        m_senders[idx] = dlg;
    }

    return dlg;
}


void ObjrefView::showScriptEditor()
{
    if (!m_sub_script)
    {
        m_script = new SimpleScriptEditor();
        m_script->initialize(m_objref->interface());

        m_sub_script = new QMdiSubWindow();
        m_sub_script->setWidget(m_script);
        m_mdi_area->addSubWindow(m_sub_script);
        m_sub_script->setWindowTitle(
                QString("%1: Script editor").arg(m_objref->name()));

        connect(m_script,
            SIGNAL(sendRequest(Request_ptr)),
            m_objref.get(),
            SLOT(sendRequest(Request_ptr)));
    }

    m_sub_script->showNormal();
    m_script->show();
    m_mdi_area->setActiveSubWindow(m_sub_script);
}

void ObjrefView::showSetReference()
{
    QMdiSubWindow *& sub = m_subUpdateReference;

    if (!m_updateReference)
    {
        m_updateReference = new UpdateReferenceDialog();
        m_updateReference->setObjref(m_objref);

        sub = new QMdiSubWindow();
        sub->setWidget(m_updateReference);
        sub->setWindowTitle(m_objref->name() + ": set reference");
        sub->setWindowIcon(QIcon(":/resources/images/csu.png"));
        m_mdi_area->addSubWindow(sub);
    }

    sub->showNormal();
    sub->widget()->show();
    m_mdi_area->setActiveSubWindow(sub);
}

// Settings
void ObjrefView::save(QVariant& settings)
{
    QVariantMap map;

    map["fqn"] = m_objref->interface()->get_fqn();

    {
        QVariantList list;

        for (unsigned int i = 0; i < m_dialogs.size(); i++)
        {
            if (m_dialogs[i])
            {
                QVariantMap op;
                op["operation"] = m_dialogs[i]->getReflective()->get_name();
                m_dialogs[i]->save(op["value"]);
                list << op;
            }
        }

        map["dialogs"] = list;
    }
    {
        QVariantList list;

        for (unsigned int i = 0; i < m_senders.size(); i++)
        {
            if (m_senders[i])
            {
                QVariantMap op;
                op["operation"] = m_senders[i]->getReflective()->get_name();
                m_senders[i]->save(op["value"]);
                list << op;
            }
        }

        map["senders"] = list;
    }

    settings = map;
}

void ObjrefView::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    if (map.contains("dialogs"))
    {
        const QVariantList list = map.value("dialogs").toList();

        for (QVariantList::const_iterator it = list.begin();
                it != list.end(); ++it)
        {
            const QVariantMap map = it->toMap();
            const QString operation = map["operation"].toString();

            if (!operation.isEmpty() && map.contains("value"))
            {
                // find the index
                unsigned int i = 0;
                const unsigned int count =
                    m_objref->interface()->operation_count();

                for (; i < count; i++)
                {
                    const char * current =
                            m_objref->interface()->get_reflective_by_index(
                                    i)->get_name();

                    if (operation == current) break;
                }

                // load its saved value
                if (i < count)
                {
                    getRequestDialog(i)->load(map.value("value"));
                }
            }
        }
    }

    if (map.contains("senders"))
    {
        const QVariantList list = map.value("senders").toList();

        for (QVariantList::const_iterator it = list.begin();
                it != list.end(); ++it)
        {
            const QVariantMap map = it->toMap();
            const QString operation = map["operation"].toString();

            if (!operation.isEmpty() && map.contains("value"))
            {
                // find the index
                unsigned int i = 0;
                const unsigned int count =
                    m_objref->interface()->operation_count();

                for (; i < count; i++)
                {
                    const char * current =
                            m_objref->interface()->get_reflective_by_index(
                                    i)->get_name();

                    if (operation == current) break;
                }

                // load its saved value
                if (i < count)
                {
                    getSenderDialog(i - 1)->load(map.value("value"));
                }
            }
        }
    }
}

void ObjrefView::showClient()
{
    if (!m_client)
    {
        m_client = new SimpleClient(qobject_cast< QWidget *>(parent()));
        m_client->initialize(m_objref);
        m_client->setWindowTitle(m_objref->name());
    }

    m_client->show();
}

void ObjrefView::stopAll()
{
    for (dialogs_t::iterator it = m_dialogs.begin();
            it != m_dialogs.end(); ++it)
    {
        if (*it)
        {
            (*it)->stopTimer();
        }
    }

    for (senders_t::iterator it = m_senders.begin();
            it != m_senders.end(); ++it)
    {
        if (*it)
        {
            (*it)->stop();
        }
    }
}


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * NSBrowser.cpp
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

#include "NSBrowser.hpp"

using namespace corbasim::app;

NSModel::NSModel(QObject * parent) :
    QStandardItemModel(parent)
{
}

NSModel::~NSModel()
{
}

void NSModel::updateModel()
{
    clear();

    try {

        if (CORBA::is_nil(m_rootNC))
        {
            int argc = 0;
            m_orb = CORBA::ORB_init(argc, NULL);

            CORBA::Object_var obj = 
                m_orb->resolve_initial_references("NameService");

            m_rootNC = 
                CosNaming::NamingContext::_narrow(obj);
        }

        processNC(m_rootNC, invisibleRootItem());
    } catch(...) {
    }
}

void NSModel::start()
{
    QObject::connect(&m_timer, SIGNAL(timeout()),
            this, SLOT(updateModel()));

    m_timer.start(2000);
}

void NSModel::processNCIteration(const CosNaming::NamingContext_ptr nc,
        const CosNaming::BindingList& bl,
        QStandardItem * parent)
{
    for (CORBA::ULong i = 0; i < bl.length(); i++) 
    {
        CosNaming::Name Name;
        Name.length (1);
        Name[0].id = CORBA::string_dup (bl[i].binding_name[0].id);
        Name[0].kind = CORBA::string_dup (bl[i].binding_name[0].kind);

        CORBA::Object_var obj = nc->resolve (Name);

        QString entry;
        entry = Name[0].id;
        entry += QString(".") + Name[0].kind;

        entry = QString("%1.%2 (%3)")
            .arg(Name[0].id.in()).arg(Name[0].kind.in())
            .arg(obj->_interface_repository_id());

        QStandardItem * item = new QStandardItem(entry);
        parent->appendRow(item);

        if (bl[i].binding_type == CosNaming::ncontext) 
        {
            CosNaming::NamingContext_var ncc = 
                CosNaming::NamingContext::_narrow(obj);

            processNC(ncc, item);
        }
        else
        {
        }
    }
}

void NSModel::processNC(const CosNaming::NamingContext_ptr nc,
        QStandardItem * parent)
{
    if (CORBA::is_nil(nc))
        return;

    CosNaming::BindingIterator_var it;
    CosNaming::BindingList_var bl;
    CORBA::ULong const CHUNK = 100;

    nc->list(CHUNK, bl, it);

    processNCIteration(nc, bl, parent);

    if (!CORBA::is_nil(it))
    {
        CORBA::Boolean more;

        do
        {
            more = it->next_n(CHUNK, bl);
            processNCIteration(nc, bl, parent);
        } while (more);

        it->destroy();
    }
}

NSBrowser::NSBrowser(QWidget * parent) :
    QWidget(parent)
{
    m_model.start();

    QHBoxLayout * layout = new QHBoxLayout();

    m_view = new QTreeView();
    m_view->setModel(&m_model);

    layout->addWidget(m_view);


    setLayout(layout);
}

NSBrowser::~NSBrowser()
{
}


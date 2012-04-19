// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * NSWatcher.cpp
 * Copyright (C) Andrés Senac 2012 <andres@senac.es>
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

#include "NSWatcher.hpp"
#include <corbasim/core/reference_repository.hpp>
#include <iostream>
#include <cstring>

using namespace corbasim::app;

NSWatcher::NSWatcher(QObject * parent) :
    QObject(parent)
{
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(refreshNS())); 
}

NSWatcher::~NSWatcher()
{
}

void NSWatcher::start()
{
    m_timer.start(5000);
}

void NSWatcher::refreshNS()
{
    core::reference_repository * rr = 
        core::reference_repository::get_instance();

    entries_t::iterator it = m_entries.begin();
    entries_t::iterator end = m_entries.end();

    for (; it != end; it++)
    {
        CORBA::Object_var oldRef = it.value().ref;
        CORBA::Object_var newRef;
        bool is_equivalent = true;

        try {
            
            newRef = rr->resolve_str(it.value().entry);

            if (!CORBA::is_nil(oldRef))
            {
                is_equivalent = oldRef->_is_equivalent(newRef);
            }
            else if ((CORBA::is_nil(oldRef) && !CORBA::is_nil(newRef)))
            {
                is_equivalent = false;
            }

        } catch(...) {

            is_equivalent = CORBA::is_nil(newRef);
        }

        if (!is_equivalent)
        {
            it.value().ref = newRef;

            emit updateReference(it.key(), newRef);
        }
    }
}

void NSWatcher::objrefCreated(const QString& id, 
        const corbasim::core::interface_reflective_base * factory,
        const corbasim::app::ObjrefConfig& cfg)
{
    if (std::strlen(cfg.entry.in()) > 0)
    {
        entry_t t;
        t.entry = cfg.entry.in();
        t.ref = cfg.ref;

        m_entries.insert(id, t);
    }
}

void NSWatcher::objrefDeleted(const QString& id)
{
    m_entries.remove(id);
}



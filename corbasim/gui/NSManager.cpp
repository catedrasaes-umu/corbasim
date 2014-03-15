// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * NSManager.cpp
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

#include "NSManager.hpp"
#include <iostream>

using namespace corbasim::gui;

NSManager::NSManager(const CORBA::ORB_var& orb, QObject * parent) :
    QObject(parent), m_orb(orb)
{
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(refreshNS()));
    QObject::connect(this, SIGNAL(started()), this, SLOT(doStart()));
}

NSManager::~NSManager()
{
}

void NSManager::start()
{
    emit started();
}

void NSManager::doStart()
{
    try {

        const CORBA::Object_var obj =
            m_orb->resolve_initial_references("NameService");

        setNSReference(obj);

    } catch (...) {

        // emit error("Invalid name service!");
    }

    m_timer.start(5000);
}

void NSManager::resolve(Objref_ptr objref)
{
    // Invalid name service
    if (CORBA::is_nil(m_nameService))
        return;

    CORBA::Object_var oldRef = objref->reference();
    CORBA::Object_var newRef;
    bool is_equivalent = true;

    const std::string str = objref->nsEntry().toStdString();

    if (!str.empty())
    {
        try {

            newRef = m_nameService->resolve_str(str.c_str());

            if (!CORBA::is_nil(oldRef))
            {
                is_equivalent = oldRef->_is_equivalent(newRef);
            }
            else if ((CORBA::is_nil(oldRef) && !CORBA::is_nil(newRef)))
            {
                is_equivalent = false;
            }

        } catch(...) {

            is_equivalent = CORBA::is_nil(oldRef);
        }
    }

    if (!is_equivalent)
    {
        objref->setReference(newRef);

        emit message(
                QString("Updated reference for '%1'").
                    arg(objref->name()));
    }
}

void NSManager::refreshNS()
{
    // Invalid name service
    if (CORBA::is_nil(m_nameService))
        return;

    ObjrefRepository::iterator it = m_objrefs.begin();
    ObjrefRepository::iterator end = m_objrefs.end();

    for (; it != end; it++)
    {
        resolve(it.value());
    }
}

void NSManager::setNSReference(const CORBA::Object_var& ref)
{
    m_nameService = CosNaming::NamingContextExt::_narrow(ref);

    if (CORBA::is_nil(m_nameService))
        emit error("Invalid Naming Service reference!");

    // TODO check if equivalent references
    resetRegisters();
}

void NSManager::resetRegisters()
{
    m_registers.clear();

    if (!CORBA::is_nil(m_nameService))
    {
        ObjrefRepository::iterator it = m_servants.begin();
        ObjrefRepository::iterator end = m_servants.end();

        for (; it != end; it++)
        {
            registerServant(it.value());
        }
    }
}

void NSManager::objrefCreated(Objref_ptr objref)
{
    m_objrefs.add(objref);
}

void NSManager::objrefDeleted(ObjectId id)
{
    m_objrefs.del(id);
}

void NSManager::registerServant(Objref_ptr servant)
{
    const std::string str = servant->nsEntry().toStdString();
    const CORBA::Object_var ref = servant->reference();

    // TODO Have I to check if ref is nil?
    if (!str.empty())
    {
        bool err = false;

        if (!CORBA::is_nil(m_nameService))
        {
            register_ptr reg(
                    new core::ns_register(m_nameService, str, ref));

            if (!(err = reg->error()))
            {
                m_registers.insert(servant->id(), reg);
            }
        }
        else
        {
            err = true;
        }

        if (err)
        {
            emit error(QString("Unable to register '%1' as '%2'").
                    arg(servant->name()).arg(str.c_str()));
        }
        else
        {
            emit message(QString("Registered '%1' as '%2'").
                    arg(servant->name()).arg(str.c_str()));
        }
    }
}

void NSManager::servantCreated(Objref_ptr servant)
{
    m_servants.add(servant);

    const QString nsEntry = servant->nsEntry();

    registerServant(servant);
}

void NSManager::servantDeleted(ObjectId id)
{
    m_servants.del(id);
    m_registers.remove(id);
}


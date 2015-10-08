// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Model.cpp
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

#include "Model.hpp"
#include <cassert>
#include <corbasim/core/event.hpp>
#include <QLibrary>
#include <iostream>
#include <boost/thread/shared_mutex.hpp>

using namespace corbasim::gui;

typedef boost::shared_lock< boost::shared_mutex > shared_lock;
typedef boost::unique_lock< boost::shared_mutex > unique_lock;

struct Objref::Data
{
    boost::shared_mutex refMutex;
    boost::shared_mutex nsEntryMutex;
};

Objref::Objref(const QString& name,
       InterfaceDescriptor_ptr interfaceDescriptor,
       QObject * parent) :
    QObject(parent),
    m_name(name),
    m_interfaceDescriptor(interfaceDescriptor),
    m_data(new Data)
{
    if(m_interfaceDescriptor)
    {
        m_caller.reset(m_interfaceDescriptor->create_caller());

        m_validator = m_caller;
    }
}

Objref::Objref(const ObjrefConfig& cfg,
       InterfaceDescriptor_ptr interfaceDescriptor,
       QObject * parent) :
    QObject(parent),
    m_name(cfg.name.c_str()),
    m_nsEntry(cfg.entry.c_str()),
    m_interfaceDescriptor(interfaceDescriptor),
    m_data(new Data)
{
    if(m_interfaceDescriptor)
    {
        m_caller.reset(m_interfaceDescriptor->create_caller());

        m_validator = m_caller;
    }

    setReference(cfg.reference);
}

Objref::~Objref()
{
    delete m_data;
}

ObjectId Objref::id() const
{
    return this;
}

InterfaceDescriptor_ptr Objref::interface() const
{
    return m_interfaceDescriptor;
}

const QString& Objref::name() const
{
    return m_name;
}

CORBA::Object_var Objref::reference() const
{
    shared_lock lock(m_data->refMutex);
    return m_reference;
}

void Objref::setReference(const CORBA::Object_var& reference)
{
    bool doEmit = false;
    {
        unique_lock lock(m_data->refMutex);

        bool newNil = CORBA::is_nil(reference);
        bool oldNil = CORBA::is_nil(m_reference);

        if (newNil && oldNil)
            return;

        if (oldNil || !m_reference->_is_equivalent(reference))
        {
            m_reference = reference;

            if (m_validator)
            {
                // Validates the reference
                m_validator->set_reference(reference);
                m_reference = m_validator->get_reference();
            }

            doEmit = true;
        }
    }

    if (doEmit)
    {
        shared_lock lock(m_data->refMutex);

        emit updatedReference(m_reference);
    }
}

QString Objref::nsEntry() const
{
    shared_lock lock(m_data->nsEntryMutex);
    return m_nsEntry;
}

bool Objref::isNil() const
{
    shared_lock lock(m_data->refMutex);
    if (m_validator)
        return m_validator->is_nil();

    return CORBA::is_nil(m_reference);
}

void Objref::setNsEntry(const QString& nsEntry)
{
    // Protected region
    {
        unique_lock lock(m_data->nsEntryMutex);
        m_nsEntry = nsEntry;
    }

    emit updatedNsEntry(nsEntry);
}

Event_ptr Objref::sendRequest(const Request_ptr& request)
{
    shared_lock lock(m_data->refMutex);

    Event_ptr ev;

    if (!m_caller || m_caller->is_nil())
    {
        ev = boost::make_shared<corbasim::core::message>(
                "Invalid reference!");
    }
    else
    {
        ev = m_caller->do_call(request.get());
    }

    emit requestSent(id(), request, ev);

    return ev;
}

Event_ptr Objref::sendRequestThrow(const Request_ptr& request)
{
    shared_lock lock(m_data->refMutex);

    Event_ptr ev;

    if (!m_caller || m_caller->is_nil())
    {
        // TODO throw exception?
        ev = boost::make_shared<corbasim::core::message>(
                "Invalid reference!");
    }
    else
    {
        try
        {
            ev = m_caller->do_call_throw(request.get());
        }
        catch(const CORBA::Exception& ex)
        {
            // Exception forwarding
            ev = boost::make_shared<corbasim::core::exception>(ex._name());

            emit requestSent(id(), request, ev);

            ex._raise();
        }
    }

    emit requestSent(id(), request, ev);

    return ev;
}

void Objref::setValidator(core::reference_validator_ptr validator)
{
    m_validator = validator;
}

bool Objref::isServant() const { return false; }

//
//
// Servant
//
//

bool Servant::isServant() const { return true; }

struct Servant::ServantData :
    public ::corbasim::core::request_processor
{
    Servant& m_this;
    PortableServer::ServantBase * m_servant;

    ServantData(Servant& this_) :
        m_this(this_),
        m_servant(this_.interface()->create_servant(this))
    {
    }

    ~ServantData()
    {
        delete m_servant;
    }

    ::corbasim::core::event_ptr operator()(
            ::corbasim::core::request_ptr req,
            ::corbasim::core::response_ptr resp)
    {
        if (m_this.proxy())
        {
            // Proxy and servant must be in the same thread
            try
            {
                ::corbasim::core::event_ptr ev =
                    m_this.proxy()->sendRequestThrow(req);

                emit m_this.requestReceived(m_this.id(), req, ev);

                return ev;
            }
            catch (const CORBA::Exception& ex)
            {
                ::corbasim::core::event_ptr ev =
                    boost::make_shared<corbasim::core::exception>(ex._name());

                emit m_this.requestReceived(m_this.id(), req, ev);

                ex._raise();
            }
        }

        emit m_this.requestReceived(m_this.id(), req, resp);
        return resp;
    }
};

Servant::Servant(const QString& name,
       InterfaceDescriptor_ptr interfaceDescriptor,
       QObject * parent) :
    Objref(name, interfaceDescriptor, parent),
    m_data(new ServantData(*this))
{
}

Servant::Servant(const ServantConfig& cfg,
       InterfaceDescriptor_ptr interfaceDescriptor,
       QObject * parent) :
    Objref(cfg, interfaceDescriptor, parent),
    m_data(new ServantData(*this))
{
}

Servant::~Servant()
{
}

PortableServer::ServantBase * Servant::getServant() const
{
    return m_data->m_servant;
}

Objref_ptr Servant::proxy() const
{
    return m_proxy;
}

void Servant::setProxy(Objref_ptr proxy)
{
    m_proxy = proxy;
}

//
//
// ObjrefRepository
//
//

ObjrefRepository::ObjrefRepository(QObject * parent) :
    QObject(parent)
{
}

ObjrefRepository::~ObjrefRepository()
{
}

ObjrefRepository::iterator ObjrefRepository::begin()
{
    return m_objrefById.begin();
}

ObjrefRepository::iterator ObjrefRepository::end()
{
    return m_objrefById.end();
}

ObjrefRepository::const_iterator ObjrefRepository::begin() const
{
    return m_objrefById.begin();
}

ObjrefRepository::const_iterator ObjrefRepository::end() const
{
    return m_objrefById.end();
}

void ObjrefRepository::clear()
{
    ObjrefById_t::const_iterator it = m_objrefById.begin();
    ObjrefById_t::const_iterator end = m_objrefById.end();

    for (; it != end; it++)
    {
        emit deleted(it.key());
        emit deleted(it.value());
    }

    m_objrefById.clear();
    m_objrefByName.clear();
}

Objref_ptr ObjrefRepository::find(ObjectId id) const
{
    ObjrefById_t::const_iterator it = m_objrefById.find(id);

    if (it != m_objrefById.end())
    {
        return it.value();
    }

    return Objref_ptr();
}

Objref_ptr ObjrefRepository::find(const QString& name) const
{
    ObjrefByName_t::const_iterator it = m_objrefByName.find(name);

    if (it != m_objrefByName.end())
    {
        return it.value();
    }

    return Objref_ptr();
}

void ObjrefRepository::add(Objref_ptr objref)
{
    assert(objref);

    m_objrefById.insert(objref->id(), objref);
    m_objrefByName.insert(objref->name(), objref);

    emit added(objref);
}

void ObjrefRepository::del(ObjectId id)
{
    ObjrefById_t::iterator it = m_objrefById.find(id);

    if (it != m_objrefById.end())
    {
        Objref_ptr objref = it.value();

        m_objrefByName.remove(objref->name());
        m_objrefById.erase(it);

        emit deleted(objref);
        emit deleted(objref->id());
    }
}

void ObjrefRepository::del(const QString& name)
{
    ObjrefByName_t::iterator it = m_objrefByName.find(name);

    if (it != m_objrefByName.end())
    {
        Objref_ptr objref = it.value();

        m_objrefById.remove(objref->id());
        m_objrefByName.erase(it);

        emit deleted(objref);
        emit deleted(objref->id());
    }
}

//
//
// InterfaceRepository
//
//

InterfaceRepository::InterfaceRepository(QObject * parent) :
    QObject(parent)
{
}

InterfaceRepository::~InterfaceRepository()
{
}

InterfaceDescriptor_ptr InterfaceRepository::loadLibrary(const QString& file)
{
    QFileInfo info(file);
    QString symbol(info.baseName());

    symbol.remove(".so");
    symbol.remove(".dll");
    symbol.remove(".dylib");
    symbol.replace("libcorbasim_", "corbasim_");

    const std::string str(symbol.toStdString());

    typedef InterfaceDescriptor_ptr (*get_reflective_t)();

    QLibrary lib(file);

    if (!lib.load())
    {
        return NULL;
    }

    get_reflective_t get_reflective =
        (get_reflective_t) lib.resolve(str.c_str());

    if (!get_reflective)
    {
        lib.unload();
        return NULL;
    }

    InterfaceDescriptor_ptr factory = get_reflective();

    if (!factory)
    {
        lib.unload();
        return NULL;
    }

    if (m_interfaces.find(factory->get_fqn()) == m_interfaces.end())
    {
        addInterface(factory);
    }

    return factory;
}

InterfaceDescriptor_ptr InterfaceRepository::getInterface(const QString& fqn)
{
    interfaces_t::const_iterator it = m_interfaces.find(fqn);

    if (it != m_interfaces.end())
    {
        return it.value();
    }

    QString lib (fqn);
    lib.replace("::","_");
    lib.prepend("corbasim_reflective_");

    return loadLibrary(lib);
}

void InterfaceRepository::addInterface(
        InterfaceDescriptor_ptr factory)
{
    m_interfaces.insert(factory->get_fqn(), factory);

    emit loadedInterface(factory);
}

void InterfaceRepository::loadDirectory(const QString& path)
{
    const QDir d(path);
    QStringList filters;
    QStringList idlFilters;

#ifdef _MSC_VER
    filters << "corbasim_reflective_*.dll";
    idlFilters << "*_idl.dll";
#else
#ifdef Q_OS_DARWIN
    filters << "libcorbasim_reflective_*.dylib";
    idlFilters << "lib*_idl.dylib";
#else
    filters << "libcorbasim_reflective_*.so";
    idlFilters << "lib*_idl.so";
#endif
#endif

    // Required idl libraries
    {
        const QFileInfoList files = d.entryInfoList(idlFilters, QDir::Files);
        const int count = files.count();

        for (int i = 0; i < count; i++)
        {
            QLibrary lib(files[i].absoluteFilePath());
            lib.load();
        }
    }

    // Corbasim plug-ins
    {
        const QFileInfoList files = d.entryInfoList(filters, QDir::Files);
        const int count = files.count();

        for (int i = 0; i < count; i++)
        {
            loadLibrary(files[i].absoluteFilePath());
        }
    }
}


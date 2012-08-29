// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Model.hpp
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

#ifndef CORBASIM_GUI_MODEL_HPP
#define CORBASIM_GUI_MODEL_HPP

#include <QtCore>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC Objref : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ObjectId id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(InterfaceDescriptor_ptr interface READ interface)
    Q_PROPERTY(CORBA::Object_var reference 
            READ reference 
            WRITE setReference)
public:

    Objref(const QString& name,
           InterfaceDescriptor_ptr interfaceDescriptor,
           QObject * parent = 0);

    Objref(const ObjrefConfig& cfg,
           InterfaceDescriptor_ptr interfaceDescriptor,
           QObject * parent = 0);

    virtual ~Objref();

    // Properties
    
    ObjectId id() const;

    InterfaceDescriptor_ptr interface() const;

    const QString& name() const;

    CORBA::Object_var reference() const;

public slots:

    // Properties
    
    void setReference(const CORBA::Object_var& reference);

    Event_ptr sendRequest(const Request_ptr& request);

    // void updateConfig(const ObjrefConfig& cfg);

signals:
    
    void updatedConfig(const ObjrefConfig& cfg);

    void updatedReference(const CORBA::Object_var& reference);

    void requestSent(ObjectId id, 
            const Request_ptr& request,
            const Event_ptr& event);

protected:

    const QString m_name;

    InterfaceDescriptor_ptr m_interfaceDescriptor;

    CORBA::Object_var m_reference;

    Caller_ptr m_caller;
};

class CORBASIM_GUI_DECLSPEC Servant : public Objref
{
    Q_OBJECT
    Q_PROPERTY(Objref_ptr proxy READ proxy WRITE setProxy)
public:

    Servant(const QString& name,
           InterfaceDescriptor_ptr interfaceDescriptor,
           QObject * parent = 0);

    Servant(const ServantConfig& cfg,
           InterfaceDescriptor_ptr interfaceDescriptor,
           QObject * parent = 0);

    ~Servant();

    PortableServer::ServantBase * getServant() const;
    
    Objref_ptr proxy() const;

public slots:

    void setProxy(Objref_ptr proxy);
    
    // void updateConfig(const ServantConfig& cfg);

signals:
    
    void updatedConfig(const ServantConfig& cfg);

    void requestReceived(ObjectId id, 
            const Request_ptr& request,
            const Event_ptr& event);

protected:

    friend class ServantData;
    struct ServantData;
    ServantData * m_data;

    Objref_ptr m_proxy;
};

class CORBASIM_GUI_DECLSPEC ObjrefRepository : public QObject
{
    Q_OBJECT
public:

    ObjrefRepository(QObject * parent = 0);
    /*
    ObjrefRepository(const ObjrefRepository * other,
            QObject * parent = 0);
    */

    virtual ~ObjrefRepository();

    typedef QMap< ObjectId, Objref_ptr > ObjrefById_t;
    typedef QMap< QString, Objref_ptr > ObjrefByName_t;
    typedef ObjrefById_t::iterator iterator;
    typedef ObjrefById_t::const_iterator const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    Objref_ptr find(ObjectId id) const;
    Objref_ptr find(const QString& name) const;

    void clear();

public slots:

    void add(Objref_ptr objref);

    void del(ObjectId id);
    void del(const QString& name);

signals:

    void added(Objref_ptr objref);
    void deleted(Objref_ptr objref);
    void deleted(ObjectId id);

protected:

    ObjrefById_t m_objrefById;
    ObjrefByName_t m_objrefByName;
};

class CORBASIM_GUI_DECLSPEC InterfaceRepository : public QObject
{
    Q_OBJECT
public:

    InterfaceRepository(QObject * parent = 0);
    ~InterfaceRepository();

    InterfaceDescriptor_ptr getInterface(const QString& fqn);
    
    InterfaceDescriptor_ptr loadLibrary(const QString& file);

public slots:

    void addInterface(InterfaceDescriptor_ptr interface);

    void loadDirectory(const QString& directory);

signals:

    void loadedInterface(InterfaceDescriptor_ptr interface);

protected:

    typedef QMap< QString, InterfaceDescriptor_ptr > interfaces_t;
    interfaces_t m_interfaces;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_MODEL_HPP */


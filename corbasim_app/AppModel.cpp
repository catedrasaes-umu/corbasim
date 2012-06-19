// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppModel.cpp
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

#include "AppModel.hpp"
#include "AppController.hpp"

#include "app_adapted.hpp" // for json serializer

#include <corbasim/json/writer.hpp>
#include <corbasim/json/parser.hpp>

#include <corbasim/core/reflective_fwd.hpp>

#include <corbasim/qt/ReferenceModel.hpp>

#include <fstream>
#include <QLibrary>

#include <iostream>

#include <memory>
#include <cstring>

using namespace corbasim::app;

namespace corbasim 
{
namespace app 
{

class AppModelData 
{
public:
    AppModelData ()
    {
        int argc = 0;
        orb = CORBA::ORB_init (argc, NULL);

        CORBA::Object_var rootPOAObj = 
            orb->resolve_initial_references ("RootPOA");

        rootPOA = PortableServer::POA::_narrow(rootPOAObj.in());

        manager = rootPOA->the_POAManager();

        manager->activate();
    }
    
    ~AppModelData ()
    {
    }

    CORBA::ORB_var orb;
    PortableServer::POA_var rootPOA;
    PortableServer::POAManager_var manager; 
};

} // namespace app
} // namespace corbasim

AppModel::AppModel() : 
    m_ref_model(*qt::ReferenceModel::getDefaultModel()),
    m_data(new AppModelData), m_controller(NULL)
{
}

AppModel::~AppModel()
{
    // TODO close libraries
   
    // ORB already destroyed
    /*
    servants_t::iterator it = m_servants.begin();
    servants_t::iterator end = m_servants.end();

   
    for (; it != end; it++) 
    {
        // Temporal - Proof of concept
        PortableServer::ObjectId_var myObjID = 
            m_data->rootPOA->servant_to_id(it->second->getServant()); 

        m_data->rootPOA->deactivate_object (myObjID);
        // End temporal
    }
    */

    delete m_data;
}

const corbasim::core::interface_reflective_base * 
AppModel::getFactory(const QString& fqn)
{
    factories_t::iterator it = m_factories.find(fqn);

    if (it != m_factories.end())
        return it->second;

    QString lib (fqn);
    lib.replace("::","_");
    lib.prepend("corbasim_reflective_");

    return loadLibrary(lib);
}

void AppModel::setController(AppController * controller)
{
    m_controller = controller;
}

void AppModel::createObjref(const corbasim::app::ObjrefConfig& cfg)
{
    QString id(cfg.id.in());

    if (m_servants.find(id) != m_servants.end() ||
            m_objrefs.find(id) != m_objrefs.end())
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Object '%1' already exists!").arg(id));
        return;
    }

    const corbasim::core::interface_reflective_base * factory = 
        getFactory(cfg.fqn.in());

    if (factory)
    {
        model::Objref_ptr obj(new model::Objref(cfg, factory));
        m_objrefs.insert(std::make_pair(id, obj));

        m_ref_model.appendItem(id, cfg.ref, factory);

        if (m_controller)
        {
            m_controller->notifyObjrefCreated(id, factory, cfg);

            // Also notifies its reference
            m_controller->notifyUpdatedReference(id, cfg.ref);
        }
    }
}

void AppModel::createServant(const corbasim::app::ServantConfig& cfg)
{
    const QString id(cfg.id.in());

    if (m_servants.find(id) != m_servants.end() ||
            m_objrefs.find(id) != m_objrefs.end())
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Object '%1' already exists!").arg(id));
        return;
    }

    const corbasim::core::interface_reflective_base * factory = 
        getFactory(cfg.fqn.in());

    if (factory)
    {
        model::Servant_ptr obj(new model::Servant(cfg, factory));
        obj->setController(m_controller);
        m_servants.insert(std::make_pair(id, obj));

        // Temporal - Proof of concept

        PortableServer::ObjectId_var myObjID = 
            m_data->rootPOA->activate_object (obj->getServant());
    
        CORBA::Object_var objSrv = 
            m_data->rootPOA->servant_to_reference(obj->getServant());

        // Displaying reference
        CORBA::String_var ref = m_data->orb->object_to_string (objSrv);
        std::cout << cfg.id << ": " << ref << std::endl;

        // End temporal

        m_ref_model.appendItem(id, objSrv, factory);

        if (m_controller)
            m_controller->notifyServantCreated(id, factory);

        // Naming service registration
        if (std::strlen(cfg.entry.in()) > 0)
        {
            std::auto_ptr< core::ns_register > ptr_(
                    new core::ns_register(m_data->orb, 
                        cfg.entry.in(), objSrv));

            if (!ptr_->error())
            {
                // Assumes its ownership
                obj->set_ns_entry(ptr_.release());

                if (m_controller)
                {
                    m_controller->notifyMessage(
                            QString("'%1' registred as '%2'").arg(id).
                                arg(cfg.entry.in()));
                }
            }
            else
            {
                if (m_controller)
                {
                    m_controller->notifyError(
                            QString("Unable to register '%1' as '%2'").
                                arg(id).arg(cfg.entry.in()));
                }
            }
        }
    }
}

void AppModel::sendRequest(const QString& id,
        corbasim::event::request_ptr req)
{
    objrefs_t::iterator it = m_objrefs.find(id);
    if (it == m_objrefs.end())
    {
        servants_t::iterator it = m_servants.find(id);
        if (it == m_servants.end())
            m_controller->notifyError(
                    QString("Object '%1' not found!").arg(id));
        else
            corbasim::event::event_ptr ev (it->second->sendRequest(req));
    }
    else
    {
        corbasim::event::event_ptr ev (it->second->sendRequest(req));

        if (m_controller)
            m_controller->notifyRequestSent(id, req, ev);
    }
}

void AppModel::deleteObjref(const QString& id)
{
    if (m_objrefs.erase(id) > 0)
    {
        m_ref_model.removeItem(id);

        if (m_controller)
            m_controller->notifyObjrefDeleted(id);
    }
    else if (m_controller)
        m_controller->notifyError(
                QString("Object '%1' not found!").arg(id));
}

void AppModel::deleteServant(const QString& id)
{
    servants_t::iterator it = m_servants.find(id);

    if (it != m_servants.end())
    {
        // Temporal - Proof of concept
        PortableServer::ObjectId_var myObjID = 
            m_data->rootPOA->servant_to_id(it->second->getServant()); 

        m_data->rootPOA->deactivate_object (myObjID);
        // End temporal
    }

    if (m_servants.erase(id) > 0)
    {
        m_ref_model.removeItem(id);

        if (m_controller)
            m_controller->notifyServantDeleted(id);
    }
    else if (m_controller)
        m_controller->notifyError(
                QString("Object '%1' not found!").arg(id));
}

void AppModel::saveFile(const QString& file)
{
    Configuration cfg;

    // Objrefs
    {
        cfg.objects.length(m_objrefs.size());
        objrefs_t::const_iterator it = m_objrefs.begin();
        objrefs_t::const_iterator end = m_objrefs.end();

        for (int i = 0; it != end; ++it, i++)
            cfg.objects[i] = it->second->getConfig();
    }

    // Servants
    {
        cfg.servants.length(m_servants.size());
        servants_t::const_iterator it = m_servants.begin();
        servants_t::const_iterator end = m_servants.end();

        for (int i = 0; it != end; ++it, i++)
            cfg.servants[i] = it->second->getConfig();
    }

    const std::string file_ (file.toStdString());
    std::ofstream ofs (file_.c_str());

    // convert to JSON and save
    try {
        json::write(ofs, cfg, true);

        if (m_controller)
            m_controller->notifyMessage(
                    QString("Configuration saved into file '%1'").arg(file));

    } catch (...) {
        if (m_controller)
            m_controller->notifyError(
                    QString("Error saving file '%1'").arg(file));
    }
}

void AppModel::loadFile(const QString& file)
{
    // clear current config
    clearConfig();

    std::vector< char > buffer;
    size_t length = 0;

    Configuration cfg;

    try {
        std::string file_ (file.toStdString());
        std::ifstream ifs (file_.c_str());

        // get length of file:
        ifs.seekg (0, std::ios::end);
        length = ifs.tellg();
        ifs.seekg (0, std::ios::beg);

        // allocate memory:
        buffer.resize(length);

        // read data as a block:
        ifs.read (&(*buffer.begin()), length);
        ifs.close();

        // parse JSON
        json::parse(cfg, &(*buffer.begin()), length);

        if (m_controller)
            m_controller->notifyMessage(
                    QString("Configuration loaded from file '%1'").arg(file));

        // process cfg

        // Objects
        for (unsigned int i = 0; i < cfg.objects.length(); i++) 
            createObjref(cfg.objects[i]);

        // Servants
        for (unsigned int i = 0; i < cfg.servants.length(); i++) 
            createServant(cfg.servants[i]);

    } catch (...) {
        if (m_controller)
            m_controller->notifyError(
                    QString("Error parsing file '%1'").arg(file));
    }
}

void AppModel::loadDirectory(const QString& path)
{
    const QDir d(path);
    QStringList filters;

#ifdef _MSC_VER
    filters << "corbasim_reflective_*.dll";
#else
    filters << "libcorbasim_reflective_*.so";
#endif

    const QFileInfoList files = d.entryInfoList(filters, QDir::Files);
    const int count = files.count();

    for (int i = 0; i < count; i++) 
    {
        loadLibrary(files[i].absoluteFilePath());
    }
}

const corbasim::core::interface_reflective_base * 
AppModel::loadLibrary(const QString& file)
{
    QFileInfo info(file);
    QString symbol(info.baseName());

    symbol.remove(".so");
    symbol.remove(".dll");
    symbol.replace("libcorbasim_", "corbasim_");

    const std::string str(symbol.toStdString());

    std::cout << str << std::endl;
    

    typedef const corbasim::core::interface_reflective_base *
        (*get_reflective_t)();

    QLibrary lib(file);

    if (!lib.load())
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Library '%1' not found!").arg(file));
        return NULL;
    }

    get_reflective_t get_reflective = 
        (get_reflective_t) lib.resolve(str.c_str());

    if (!get_reflective)
    {
        lib.unload();

        if (m_controller)
            m_controller->notifyError(
                    QString("Symbol '%1' not found!").arg(file));
        return NULL;
    }

    const corbasim::core::interface_reflective_base * factory = 
        get_reflective();
    
    if (factory)
    {
        const QString fqn(factory->get_fqn());

        // m_libraries.insert(std::make_pair(fqn, handle));
        m_factories.insert(std::make_pair(fqn, factory));

        // I don't like this solution because I need to set the list
        // for each new fqn, but...
        m_fqns << fqn;
        m_fqns.removeDuplicates();
        m_fqns_model.setStringList(m_fqns);

        if (m_controller)
            m_controller->notifyMessage(
                    QString("New library loaded '%1' for '%2'")
                    .arg(info.baseName()).arg(fqn));
    }
    else
    {
        // Impossible is nothing!
        if (m_controller)
            m_controller->notifyError(
                    QString("Erroneus library '%1'!").arg(info.baseName()));

        lib.unload();
    }

    return factory;
}

void AppModel::clearConfig()
{
   // TODO
}

void AppModel::updateReference(const QString& id,
        const CORBA::Object_var& ref)
{
    objrefs_t::iterator it = m_objrefs.find(id);

    if (it == m_objrefs.end())
    {
        if (m_controller)
            m_controller->notifyError(
                    QString("Object '%1' not found!").arg(id));
    }
    else
    {
        // Returns the validated reference
        // Narrows the input reference to the specific interface
        CORBA::Object_var new_ref = 
            it->second->updateReference(ref.in());

        if (CORBA::is_nil(new_ref) && m_controller)
            m_controller->notifyError(
                    QString("Invalid reference for '%1'!").arg(id));

        // In this case, 'append' means 'update'
        // You can't update the factory for this object
        // Ignores 3er parameter
        m_ref_model.appendItem(id, new_ref, NULL);

        if (m_controller)
            m_controller->notifyUpdatedReference(id, new_ref);
    }
}

QAbstractItemModel * AppModel::getFQNModel()
{
    return &m_fqns_model;
}

QAbstractItemModel * AppModel::getReferenceModel()
{
    return &m_ref_model;
}


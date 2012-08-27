// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Application.hpp
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

#ifndef CORBASIM_GUI_APPLICATION_HPP
#define CORBASIM_GUI_APPLICATION_HPP

#include <QtCore>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC Application : public QObject
{
    Q_OBJECT
public:

    Application(QObject * parent = 0);
    ~Application();

    static Application * currentApplication();

public slots:

    void loadScenario(const QString& file);
    void saveScenario(const QString& file);
    
    void loadDirectory(const QString& directory);

    void loadInterface(const QString& fqn);

    void createObjref(const ObjrefConfig& cfg);
    void deleteObjref(ObjectId id);

    void createServant(const ServantConfig& cfg);
    void deleteServant(ObjectId id);

signals:

    void loadedInterface(InterfaceDescriptor_ptr interface);

    void objrefCreated(Objref_ptr objref);
    void objrefDeleted(ObjectId);

    void servantCreated(Objref_ptr servant);
    void servantDeleted(ObjectId);

    void error(const QString& msg);
    void message(const QString& msg);

    void requestSent(ObjectId id, 
            Request_ptr req, Event_ptr res);

    void requestReceived(ObjectId id, 
            Request_ptr req, Event_ptr res);

protected:

    InterfaceRepository m_interfaces;

    ObjrefRepository m_objrefs;
    ObjrefRepository m_servants;

    struct ApplicationData;
    friend class ApplicationData;
    ApplicationData * m_data;

};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_APPLICATION_HPP */


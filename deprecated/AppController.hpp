// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppController.hpp
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

#ifndef CORBASIM_APP_APPCONTROLLER_HPP
#define CORBASIM_APP_APPCONTROLLER_HPP

#include <corbasim/qt/types.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <QObject>

#include "app_adapted.hpp"

class QAbstractItemModel;

namespace corbasim 
{
namespace app 
{

class AppModel;

class AppController : public QObject
{
    Q_OBJECT
public:
    AppController(QObject * parent = 0);
    virtual ~AppController();

    void setModel(AppModel * model);

    QAbstractItemModel * getFQNModel();
    QAbstractItemModel * getReferenceModel();

public slots:

    // Usados por la vista
    //
    void loadFile(const QString& file);
    void saveFile(const QString& file);
    
    void loadDirectory(const QString& directory);

    void createObjref(const corbasim::app::ObjrefConfig& cfg);
    void deleteObjref(const QString& id);

    void createServant(const corbasim::app::ServantConfig& cfg);
    void deleteServant(const QString& id);

    void sendRequest(const QString& id,
            corbasim::event::request_ptr req);

    void updateReference(const QString& id,
            const CORBA::Object_var& ref);

    // Usados por el modelo

    void notifyObjrefCreated(const QString& id, 
            const corbasim::core::interface_reflective_base * factory,
            const corbasim::app::ObjrefConfig& cfg);
    void notifyObjrefDeleted(const QString& id);

    void notifyServantCreated(const QString& id, 
            const corbasim::core::interface_reflective_base * factory);
    void notifyServantDeleted(const QString& id);

    void notifyError(const QString& msg);
    void notifyMessage(const QString& msg);

    void notifyRequestSent(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    void notifyRequestReceived(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    void notifyUpdatedReference(const QString& id,
            const CORBA::Object_var& ref);

signals:

    // Usadas por la vista

    void objrefCreated(QString id, 
            const corbasim::core::interface_reflective_base * factory);
    void objrefCreated(const QString& id, 
            const corbasim::core::interface_reflective_base * factory,
            const corbasim::app::ObjrefConfig& cfg);
    void servantCreated(QString id, 
            const corbasim::core::interface_reflective_base * factory);
    void objrefDeleted(QString id);
    void servantDeleted(QString id);

    void requestSent(QString id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr res);

    void requestReceived(QString id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr res);
    
    void error(QString msg);
    void message(QString msg);

    void updatedReference(QString id,
            CORBA::Object_var ref);

protected:
    AppModel * m_model;
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPCONTROLLER_HPP */


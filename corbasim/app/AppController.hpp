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

#include <corbasim/event.hpp>

namespace corbasim 
{
namespace app 
{

class AppModel;

class AppController : public QObject
{
    Q_OBJECT
public:
    AppController(AppModel * model, QObject * parent = 0);
    virtual ~AppController();

public slots:

    void sendRequest(corbasim::event::request_ptr req);

    void createObjref(); 
    void createServant();

    void removeObjref(); 
    void removeServant(); 

    void saveConfig(const QString& file);
    void loadConfig(const QString& file);

    void resetBehaviour();
    void resetAllBehaviours();

signals:

    void notifyObjrefCreated();
    void notifyServantCreated();

    void notifyRequestSent(QString id, corbasim::event::request_ptr req);
    void notifyResponseReceived();

    void notifyRequestReceived(QString id, corbasim::event::request_ptr req);
    void notifyResponseSent();
    
    void notifyError(QString msg);

protected:
    AppModel * m_model;
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPCONTROLLER_HPP */


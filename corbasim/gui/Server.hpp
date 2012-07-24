// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Server.hpp
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

#ifndef CORBASIM_GUI_SERVER_HPP
#define CORBASIM_GUI_SERVER_HPP

#include <corbasim/gui/export.hpp>
#include <corbasim/core/caller_fwd.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/LogModel.hpp>

#include <QtGui>
#include <map>

namespace corbasim 
{
namespace gui 
{

class FilteredLogView;
class OperationSequenceTool;

class CORBASIM_GUI_DECLSPEC Server : public QMainWindow
{
    Q_OBJECT
public:
    Server(QWidget * parent = 0);
    virtual ~Server();

    void initialize( ::corbasim::core::interface_reflective_base const * reflective);

    void notifyRequestReceived(
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    void notifyRequestSent(
            const QString& id,
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    void notifyClientCreated(
            const QString& clientName,
            ::corbasim::core::interface_reflective_base const * reflective,
            const CORBA::Object_var& ref);

public slots:

    void sendRequest(const QString& id, corbasim::event::request_ptr);

    void setClient(
            const QString& clientName,
            corbasim::core::interface_reflective_base const * reflective,
            const CORBA::Object_var& ref);

signals:

    void requestReceived(
            corbasim::event::request_ptr,
            corbasim::event::event_ptr);

    void requestSent(
            const QString&,
            corbasim::event::request_ptr,
            corbasim::event::event_ptr);

    void clientCreated(
            const QString&,
            corbasim::core::interface_reflective_base const *,
            const CORBA::Object_var&);

protected slots:

    void appendRequestReceived(
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    void appendRequestSent(
            const QString& id,
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

protected:

    struct Client
    {
        ::corbasim::core::interface_reflective_base const * reflective;
        ::corbasim::core::interface_caller_ptr caller;
    };

    LogModel m_logModel;

    FilteredLogView * m_view;
    OperationSequenceTool * m_seqTool;

    typedef std::map< QString, Client > clients_t;

    clients_t m_clients;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SERVER_HPP */


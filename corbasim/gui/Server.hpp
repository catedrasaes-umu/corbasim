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
#include <corbasim/gui/LogModel.hpp>

#include <QtGui>

namespace corbasim 
{
namespace gui 
{

class CORBASIM_GUI_DECLSPEC Server : public QMainWindow
{
    Q_OBJECT
public:
    Server(QWidget * parent = 0);
    virtual ~Server();

    void initialize( ::corbasim::core::interface_reflective_base const *);

    void notifyRequestReceived(
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

signals:

    void requestReceived(
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

protected slots:

    void appendRequestReceived(
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

protected:

    LogModel m_logModel;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SERVER_HPP */


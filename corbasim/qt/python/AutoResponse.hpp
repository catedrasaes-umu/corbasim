// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AutoResponse.hpp
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

#ifndef CORBASIM_QT_PYTHONAUTORESPONSE_HPP
#define CORBASIM_QT_PYTHONAUTORESPONSE_HPP

#include <QtGui>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/python/auto_response.hpp>
#include <corbasim/event.hpp>

namespace corbasim 
{
namespace qt 
{
namespace python 
{

class AutoResponseWidget : public QWidget
{
    Q_OBJECT
public:

    AutoResponseWidget(QWidget * parent = 0);
    virtual ~AutoResponseWidget();

    void initialize(gui::gui_factory_base * input_factory,
            gui::gui_factory_base* output_factory);

public slots:

    void requestReceived(event::request_ptr);

signals:

    void sendRequest(event::request_ptr);

protected:

    boost::shared_ptr< ::corbasim::python::auto_response > 
        m_auto_response;
    
    void notifyRequest(event::request_ptr);
};

} // namespace python
} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_PYTHONAUTORESPONSE_HPP */


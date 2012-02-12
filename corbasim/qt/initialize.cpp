// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * initialize.cpp
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

#include <QMetaType>
#include <boost/shared_ptr.hpp>
#include <corbasim/event_fwd.hpp>
#include <corbasim/impl.hpp>
#include <corbasim/qt/ReferenceModel.hpp>
#include <corbasim/reflective_gui/InputRequestProcessor.hpp>

namespace  
{

class Initializer
{
public:
    Initializer()
    {
        // Q_INIT_RESOURCE(corbasim_qt);

        qRegisterMetaType< corbasim::event::request_ptr >
            ("corbasim::event::request_ptr");
        qRegisterMetaType< corbasim::event::response_ptr >
            ("corbasim::event::response_ptr");
        qRegisterMetaType< corbasim::event::event_ptr >
            ("corbasim::event::event_ptr");
        qRegisterMetaType< corbasim::event::exception_ptr >
            ("corbasim::event::exception_ptr");

        qRegisterMetaType< corbasim::reflective_gui::ReflectivePath_t >
            ("corbasim::reflective_gui::ReflectivePath_t");
        qRegisterMetaType< corbasim::reflective_gui::RequestProcessor_ptr >
            ("corbasim::reflective_gui::RequestProcessor_ptr");

        qRegisterMetaType< CORBA::Object_var >
            ("CORBA::Object_var");

        corbasim::qt::ReferenceModel::getDefaultModel();
    }
};

} // namespace

namespace corbasim 
{
namespace qt 
{

void initialize()
{
    static boost::shared_ptr< Initializer > instance(new Initializer);
}

} // namespace qt
} // namespace corbasim



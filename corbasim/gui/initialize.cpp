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

#include "types.hpp"

#include <QMetaType>
#include <corbasim/gui/InputRequestProcessor.hpp>
#include <corbasim/gui/Sender.hpp>
#include <corbasim/core/file_format_helper.hpp>

#include <corbasim/qt/initialize.hpp>

namespace
{

class Initializer
{
public:
    Initializer()
    {
        corbasim::qt::initialize();

        using namespace corbasim::gui;

        qRegisterMetaType< Request_ptr >
            ("Request_ptr");
        qRegisterMetaType< Event_ptr >
            ("Event_ptr");

        qRegisterMetaType< Holder >
            ("Holder");

        qRegisterMetaType< ReflectivePath_t >
            ("ReflectivePath_t");
        qRegisterMetaType< RequestProcessor_ptr >
            ("RequestProcessor_ptr");

        qRegisterMetaType< SenderConfig_ptr >
            ("SenderConfig_ptr");

        qRegisterMetaType< ObjectId >
            ("ObjectId");

        qRegisterMetaType< Objref_ptr >
            ("Objref_ptr");
        qRegisterMetaType< Servant_ptr >
            ("Servant_ptr");

        qRegisterMetaType< InterfaceDescriptor_ptr >
            ("InterfaceDescriptor_ptr");
        qRegisterMetaType< TypeDescriptor_ptr >
            ("TypeDescriptor_ptr");
        qRegisterMetaType< OperationDescriptor_ptr >
            ("OperationDescriptor_ptr");

        qRegisterMetaType< ObjrefConfig >
            ("ObjrefConfig");
        qRegisterMetaType< ServantConfig >
            ("ServantConfig");

        // Ensure created all file format helpers
        {
            using namespace ::corbasim::core;

            file_format_factory const * fff =
                file_format_factory::get_instance();

            for (int i = 0; i < FILE_FORMAT_MAX; ++i)
            {
                fff->get_helper(static_cast< file_format >(i));
            }
        }
    }
};

} // namespace

CORBASIM_GUI_DECLSPEC void corbasim::gui::initialize()
{
    static boost::shared_ptr< Initializer > instance(new Initializer);
}



// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ClientMain.cpp
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

#include <corbasim/impl.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/Application.hpp>
#include <corbasim/gui/client/SimpleClient.hpp>
#include <iostream>

using namespace corbasim::gui;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "You must specify an interface full qualified name" 
            << std::endl;
        return -1;
    }

    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
	QApplication app(argc, argv);
    QThread applicationThread;
    Application application;
	SimpleClient window;

    // Connect signals
    QObject::connect(&application, SIGNAL(objrefCreated(Objref_ptr)), 
            &window, SLOT(initialize(Objref_ptr)));

    // Create the object
    ObjrefConfig cfg;
    cfg.name = "Object reference";
    cfg.fqn = argv[1];

    application.createObjref(cfg);

    // Run
    application.moveToThread(&applicationThread);
    applicationThread.start();

	window.show();
	int res = app.exec();

    applicationThread.quit();
    applicationThread.wait();

    return res;
}


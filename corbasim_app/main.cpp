// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * main.cpp
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

#include <iostream>
#include "AppMainWindow.hpp"
#include "AppController.hpp"
#include "AppModel.hpp"
#include "TriggerEngine.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

int main(int argc, char **argv)
{
    // Default ORB
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    QApplication app(argc, argv); 

    QThread threadController;
    QThread threadEngine;

    corbasim::app::AppModel model;
    corbasim::app::AppController controller(&threadController);
    corbasim::app::TriggerEngine engine(&threadEngine);

    controller.setModel(&model);
    model.setController(&controller);
    engine.setController(&controller);

    corbasim::app::AppMainWindow window;
    window.setController(&controller);
    window.setEngine(&engine);
    window.show();

    boost::thread orbThread(boost::bind(&CORBA::ORB::run, orb.in()));

    int res = app.exec();
    
    orb->shutdown();
    orbThread.join();

    return res;
}


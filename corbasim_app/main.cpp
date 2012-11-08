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
#include "AppConfiguration.hpp"
#include "AppMainWindow.hpp"
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Application.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <cstdlib>
#include <iterator>
#include <algorithm>

typedef std::vector< std::string > strings_t;

int main(int argc, char **argv)
{
    // Default ORB
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    QApplication app(argc, argv); 

    int res = 0;
    boost::thread * orbThread = NULL; 

    // Application scope because it is a RAII
    {
        corbasim::gui::Application application;

        corbasim::app::AppConfiguration * config =
            corbasim::app::AppConfiguration::getInstance();

        // options
        config->processCmdLine(argc, argv);

        if (config->exit)
            return 0;

        QThread threadApplication;
        corbasim::app::AppMainWindow window;

        // Signals application -> window
        QObject::connect(&application, SIGNAL(loadedInterface(InterfaceDescriptor_ptr)), 
                &window, SLOT(loadedInterface(InterfaceDescriptor_ptr)));
        QObject::connect(&application, SIGNAL(objrefCreated(Objref_ptr)), 
                &window, SLOT(objrefCreated(Objref_ptr)));
        QObject::connect(&application, SIGNAL(servantCreated(Objref_ptr)), 
                &window, SLOT(servantCreated(Objref_ptr)));
        QObject::connect(&application, SIGNAL(objrefDeleted(ObjectId)), 
                &window, SLOT(objrefDeleted(ObjectId)));
        QObject::connect(&application, SIGNAL(servantDeleted(ObjectId)), 
                &window, SLOT(servantDeleted(ObjectId)));
        QObject::connect(&application, SIGNAL(error(const QString&)), 
                &window, SLOT(displayError(const QString&)));
        QObject::connect(&application, SIGNAL(message(const QString&)), 
                &window, SLOT(displayMessage(const QString&)));
        // End signals application -> window
        
        // Signals window -> application
        QObject::connect(&window, SIGNAL(createObjref(const ObjrefConfig&)), 
                &application, SLOT(createObjref(const ObjrefConfig&)));
        QObject::connect(&window, SIGNAL(createServant(const ServantConfig&)), 
                &application, SLOT(createServant(const ServantConfig&)));
        QObject::connect(&window, SIGNAL(deleteObjref(ObjectId)), 
                &application, SLOT(deleteObjref(ObjectId)));
        QObject::connect(&window, SIGNAL(deleteServant(ObjectId)), 
                &application, SLOT(deleteServant(ObjectId)));
        QObject::connect(&window, SIGNAL(loadDirectory(const QString&)),
                &application, SLOT(loadDirectory(const QString&)));
        QObject::connect(&window, SIGNAL(loadScenario(const QString&)),
                &application, SLOT(loadScenario(const QString&)));
        QObject::connect(&window, SIGNAL(saveScenario(const QString&)),
                &application, SLOT(saveScenario(const QString&)));
        QObject::connect(&window, SIGNAL(clearScenario()),
                &application, SLOT(clearScenario()));
        // End signals window -> application
     
        QObject::connect(&window, 
                SIGNAL(setNameService(const CORBA::Object_var&)), 
                application.nameServiceManager(), 
                SLOT(setNSReference(const CORBA::Object_var&)));  

        QObject::connect(&window, 
                SIGNAL(runCode(const QString&)),
                application.scriptEngine(), 
                SLOT(runCode(const QString&)));
        QObject::connect(&window, SIGNAL(runFile(const QString&)),
                application.scriptEngine(), 
                SLOT(runFile(const QString&)));

        window.show();

        // Directories with corbasim_app plugins
        strings_t::const_iterator end2 = config->plugin_directories.end();
        for (strings_t::const_iterator it = 
                config->plugin_directories.begin(); it != end2; ++it) 
        {
            std::cout << "loading: " << (*it) << std::endl;
            application.loadDirectory(it->c_str());
        }

        // Load configuration files
        strings_t::const_iterator end = config->load_files.end();
        for (strings_t::const_iterator it = 
                config->load_files.begin(); it != end; ++it) 
        {
            std::cout << "loading: " << (*it) << std::endl;
            application.loadScenario(it->c_str());
        }

        if (!config->load_configuration.empty())
        {
            // TODO...
        }

        application.moveToThread(&threadApplication);
        threadApplication.start();

        // ORB worker
        orbThread = new boost::thread(boost::bind(&CORBA::ORB::run, 
                    orb.in()));

        res = app.exec();
        
        // Wait for child threads
        threadApplication.quit();
        threadApplication.wait();
    }

    orb->shutdown(1);
    orbThread->join();
    delete orbThread;

    return res;
}


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
#include "AppController.hpp"
#include "AppModel.hpp"
#include "TriggerEngine.hpp"
#include "AppFileWatcher.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <corbasim/qt/initialize.hpp>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include <algorithm>

typedef std::vector< std::string > strings_t;

int main(int argc, char **argv)
{
    // Default ORB
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    corbasim::app::AppConfiguration * config =
        corbasim::app::AppConfiguration::getInstance();

    // options
    config->processCmdLine(argc, argv);

    if (config->exit)
        return 0;

    QApplication app(argc, argv); 

    // Force initialization
    corbasim::qt::initialize();

    QThread threadController;
    QThread threadEngine;
    QThread threadWatcher;

    corbasim::app::AppModel model;
    corbasim::app::AppController controller;
    corbasim::app::TriggerEngine engine;
    corbasim::app::AppFileWatcher watcher;
    corbasim::app::AppMainWindow window;

    // Executed in dedicated threads
    controller.moveToThread(&threadController);

    if (config->enable_scripting)
    {
        engine.moveToThread(&threadEngine);
        threadEngine.start();
        engine.setController(&controller);
        window.setEngine(&engine);
    }

    if (config->enable_watch_directory)
    {
        watcher.setDirectory(config->watch_directory.c_str());
        watcher.setController(&controller);

        watcher.moveToThread(&threadWatcher);
        threadWatcher.start();
    }

    threadController.start();

    controller.setModel(&model);
    model.setController(&controller);

    window.setController(&controller);
    window.show();

    // Directories with corbasim_app plugins
    strings_t::const_iterator end2 = config->plugin_directories.end();
    for (strings_t::const_iterator it = 
            config->plugin_directories.begin(); it != end2; ++it) 
    {
        std::cout << "loading: " << (*it) << std::endl;
        model.loadDirectory(it->c_str());
    }

    // Load configuration files
    strings_t::const_iterator end = config->load_files.end();
    for (strings_t::const_iterator it = 
            config->load_files.begin(); it != end; ++it) 
    {
        std::cout << "loading: " << (*it) << std::endl;
        controller.loadFile(it->c_str());
    }

    boost::thread orbThread(boost::bind(&CORBA::ORB::run, orb.in()));

    int res = app.exec();
    
    // Wait for child threads
    threadController.quit();
    threadEngine.quit();
    threadWatcher.quit();

    orb->shutdown(1);
    orbThread.join();

    return res;
}


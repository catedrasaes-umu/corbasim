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
//#include "NSBrowser.hpp"
#include "NSWatcher.hpp"
#include "IDLBuilder.hpp"
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/LogModel.hpp>
#include <corbasim/gui/InputRequestProcessor.hpp>
#include <corbasim/gui/Sender.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include <algorithm>

typedef std::vector< std::string > strings_t;

int main(int argc, char **argv)
{
    // Default ORB
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    QApplication app(argc, argv); 

    corbasim::app::AppConfiguration * config =
        corbasim::app::AppConfiguration::getInstance();

    // options
    config->processCmdLine(argc, argv);

    if (config->exit)
        return 0;

    // Force initialization
    corbasim::gui::initialize();

    QThread threadController;
    QThread threadEngine;
    QThread threadWatcher;
#ifdef CORBASIM_FUTURE_FEATURES
    QThread threadBuilder;
#endif
    QThread threadInputReqCntl;

    // Sender
    corbasim::gui::SenderController * senderController =
        corbasim::gui::SenderController::getInstance();

    QThread senderThread;
    senderController->moveToThread(&senderThread);

    senderController->start();
    senderThread.start();
    // End sender

    corbasim::gui::InputRequestController& inputReqCntl = 
        *corbasim::gui::getDefaultInputRequestController();

    corbasim::app::AppModel model;
    corbasim::app::AppController controller;
    corbasim::app::TriggerEngine engine;
    corbasim::app::AppFileWatcher watcher;
#ifdef CORBASIM_FUTURE_FEATURES
    corbasim::app::IDLBuilder builder;
#endif
    corbasim::app::AppMainWindow window;
    // corbasim::gui::LogModel logModel;
    corbasim::gui::LogModel newLogModel;
    corbasim::app::NSWatcher nsWatcher;

    // Signals between models
    QObject::connect(&controller,
            SIGNAL(objrefCreated(
                    QString, const corbasim::core::interface_reflective_base *,
                    const corbasim::app::ObjrefConfig&)),
            &nsWatcher,
            SLOT(objrefCreated(
                    const QString&, 
                    const corbasim::core::interface_reflective_base *,
                    const corbasim::app::ObjrefConfig&)));
    QObject::connect(&controller,
            SIGNAL(objrefDeleted(QString)),
            &nsWatcher,
            SLOT(objrefDeleted(const QString&)));
    QObject::connect(&nsWatcher,
            SIGNAL(updateReference(const QString&, const CORBA::Object_var&)),
            &controller, 
            SLOT(updateReference(const QString&,
                    const CORBA::Object_var&)));

    QObject::connect(&controller,
            SIGNAL(objrefCreated(
                    QString, const corbasim::core::interface_reflective_base *)),
            &newLogModel,
            SLOT(registerInstance(
                    const QString&, const 
                    corbasim::core::interface_reflective_base *)));
    QObject::connect(&controller,
            SIGNAL(objrefDeleted(QString)),
            &newLogModel,
            SLOT(unregisterInstance(const QString&)));

    QObject::connect(&controller,
            SIGNAL(servantCreated(
                    QString, 
                    const corbasim::core::interface_reflective_base *)),
            &newLogModel,
            SLOT(registerInstance(
                    const QString&, 
                    const corbasim::core::interface_reflective_base *)));

    QObject::connect(&controller,
            SIGNAL(servantDeleted(QString)),
            &newLogModel, SLOT(unregisterInstance(const QString&)));

    QObject::connect(&controller,
        SIGNAL(requestSent(QString, corbasim::event::request_ptr,
                corbasim::event::event_ptr)),
        &newLogModel,
        SLOT(outputRequest(const QString&, corbasim::event::request_ptr,
                corbasim::event::event_ptr)));

    QObject::connect(&controller,
        SIGNAL(requestReceived(QString, corbasim::event::request_ptr,
                corbasim::event::event_ptr)),
        &newLogModel,
        SLOT(inputRequest(const QString&, corbasim::event::request_ptr,
                corbasim::event::event_ptr)));
    // End signals

    // Input request controller
    QObject::connect(&controller,
            SIGNAL(servantCreated(
                    QString, 
                    const corbasim::core::interface_reflective_base *)),
            &inputReqCntl,
            SLOT(registerInstance(
                    const QString&, 
                    const corbasim::core::interface_reflective_base *)));

    QObject::connect(&controller,
            SIGNAL(servantDeleted(QString)),
            &inputReqCntl, SLOT(unregisterInstance(const QString&)));

    QObject::connect(&controller,
        SIGNAL(requestReceived(QString, corbasim::event::request_ptr,
                corbasim::event::event_ptr)),
        &inputReqCntl,
        SLOT(processRequest(const QString&, corbasim::event::request_ptr,
                corbasim::event::event_ptr)));
    // End input request controller
    
    // Sender
    QObject::connect(senderController,
            SIGNAL(sendRequest(const QString&, corbasim::event::request_ptr)),
            &controller,
            SLOT(sendRequest(const QString&, corbasim::event::request_ptr)));
    // End sender

    // Executed in dedicated threads
    controller.moveToThread(&threadController);
    inputReqCntl.moveToThread(&threadInputReqCntl);
    threadInputReqCntl.start();

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

#ifdef CORBASIM_FUTURE_FEATURES
    builder.moveToThread(&threadBuilder);
    threadBuilder.start();
#endif

    nsWatcher.moveToThread(&threadWatcher);
    threadWatcher.start();
    nsWatcher.start();

    threadController.start();

    controller.setModel(&model);
    model.setController(&controller);

    window.setLogModel(&newLogModel);

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

    if (!config->load_configuration.empty())
    {
        // TODO...
    }

    // borrar
    // QTreeView view;
    // view.setModel(&newLogModel);
    // view.show();

    // corbasim::app::NSBrowser bw;
    // bw.show();
    // fin borrar

    boost::thread orbThread(boost::bind(&CORBA::ORB::run, orb.in()));

    int res = app.exec();
    
    // Wait for child threads
    threadController.quit();
    threadEngine.quit();
    threadWatcher.quit();

#ifdef CORBASIM_FUTURE_FEATURES
    threadBuilder.quit();
#endif

    threadInputReqCntl.quit();

    // Sender
    senderController->stop();
    senderThread.quit();
    senderController->join();
    senderThread.wait();
    // End sender

    threadController.wait();
    threadEngine.wait();
    threadWatcher.wait();

#ifdef CORBASIM_FUTURE_FEATURES
    threadBuilder.wait();
#endif

    threadInputReqCntl.wait();

    orb->shutdown(1);
    orbThread.join();

    return res;
}


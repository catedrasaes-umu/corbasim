// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppConfiguration.cpp
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

#include "AppConfiguration.hpp"
#include <boost/program_options.hpp>
#include <iostream>

using namespace corbasim::app;

namespace po = boost::program_options;

AppConfiguration::AppConfiguration() :
    exit(false), enable_scripting(false),
    enable_watch_directory(false),
    watch_directory("/tmp/corbasim_app")
{
}

AppConfiguration * AppConfiguration::getInstance()
{
    static std::auto_ptr< AppConfiguration > _instance(new AppConfiguration);
    return _instance.get();
}

void AppConfiguration::processCmdLine(int argc, char** argv)
{
    po::options_description desc_("corbasim generic application options");

    po::options_description generic_("Generic options");
    generic_.add_options()
        ("help,h", "produce help message")
        ("plugin-directory,d",
            po::value< strings_t >(&plugin_directories)->composing(),
            "add a directory with corbasim plugins")
        ("load-scenario,l",
            po::value< strings_t >(&load_files)->composing(),
            "load a scenario configuration file")
        ("load-configuration,c",
            po::value< std::string >(&load_configuration),
            "load a configuration file");

    po::options_description scripting_("Scripting options");
    scripting_.add_options()
        ("enable-scripting,s", "enable scripting support");

    po::options_description watch_("Watch directory");
    watch_.add_options()
        ("enable-watch,w", "enable watch directory")
        ("watch-directory",
            po::value< std::string >(&watch_directory),
            "directory to watch");

    desc_.add(generic_);
    desc_.add(scripting_);
    desc_.add(watch_);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc_), vm);
    po::notify(vm);

    // boolean options
    if (vm.count("help"))
    {
        exit = true;
        std::cout << desc_ << std::endl;
    }

    enable_scripting = vm.count("enable-scripting");
    enable_watch_directory = vm.count("enable-watch");
}


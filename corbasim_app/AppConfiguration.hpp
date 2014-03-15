// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppConfiguration.hpp
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

#ifndef CORBASIM_APP_APPCONFIGURATION_HPP
#define CORBASIM_APP_APPCONFIGURATION_HPP

#include <memory>
#include <string>
#include <vector>

namespace corbasim
{
namespace app
{

class AppConfiguration
{
public:
    static AppConfiguration * getInstance();

    void processCmdLine(int argc, char** argv);

    // Data
    bool exit;
    bool enable_scripting;
    bool enable_watch_directory;

    typedef std::vector< std::string > strings_t;

    strings_t plugin_directories;
    strings_t load_files;

    std::string watch_directory;

    std::string load_configuration;

protected:
    AppConfiguration();
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPCONFIGURATION_HPP */


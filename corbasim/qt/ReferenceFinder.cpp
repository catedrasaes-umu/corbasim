// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReferenceFinder.cpp
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

#include "ReferenceFinder.hpp"
#include <iostream>
#include <string>

using namespace corbasim::qt;

ReferenceFinder::ReferenceFinder(QObject * parent) :
    QThread(parent)
{
}

ReferenceFinder::~ReferenceFinder()
{
}

void ReferenceFinder::run()
{
    int argc = 0;
    CORBA::ORB_var orb = CORBA::ORB_init(argc, NULL);

    std::istream& is = std::cin;

    while (is.good())
    {
        std::string tk;
        is >> tk;

        std::size_t beg = tk.find("IOR:");

        if (beg == std::string::npos || beg + 5 > tk.size()) 
            continue;

        std::size_t end = 
            tk.find_first_not_of("0123456789abcdef", beg + 4);

        // Size
        if (end != std::string::npos)
            end = end - beg;

        const std::string ior = tk.substr(beg, end);

        try 
        {
            CORBA::Object_var obj = 
                orb->string_to_object(ior.c_str());

            if (!CORBA::is_nil(obj))
            {
                emit found(obj);
            }
        } 
        catch(...)
        {
        }
    }
}


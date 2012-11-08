// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DumpProcessor.cpp
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

#include "DumpProcessor.hpp"
#include <corbasim/core/file_format_helper.hpp>

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace corbasim::gui;

DumpProcessor::DumpProcessor(Objref_ptr object,
        const ReflectivePath_t path, 
        const Config& config) :
    RequestProcessor(object, path), m_config(config),
    m_currentIndex(0)
{
    switch(m_config.format)
    {
    case FORMAT_JSON:
        m_extension = ".json";
        break;

    case FORMAT_TEXT:
        m_extension = ".txt";
        break;

    case FORMAT_BINARY:
        m_extension = ".bin";
        break;

    default:
        break;
    }
    
    nextFile();
}

DumpProcessor::~DumpProcessor()
{
}

void DumpProcessor::nextFile()
{
    std::ostringstream oss;

    oss << m_config.filePrefix 
        << std::setfill('0')
        << std::setw(m_config.suffixLength)
        << m_currentIndex
        << m_extension;

    m_nextFile = oss.str();
}

void DumpProcessor::process(Request_ptr req, 
        TypeDescriptor_ptr ref,
        Holder hold)
{
    using namespace ::corbasim::core;

    std::ios_base::openmode flags = std::ios_base::out;

    const file_format_factory * factory = 
        file_format_factory::get_instance();

    if (!m_config.multipleFiles)
    {
        flags = flags | std::ios_base::app;
    }

    try 
    {
        switch(m_config.format)
        {
        case FORMAT_JSON:
            {
                std::ofstream out(m_nextFile.c_str(), flags);

                factory->get_helper(FILE_FORMAT_JSON)->save(out, ref, hold);
                
                out.close();
            }
            break;

        case FORMAT_TEXT:
            {
                std::ofstream out(m_nextFile.c_str(), flags);

                factory->get_helper(FILE_FORMAT_TEXT)->save(out, ref, hold);

                out.close();
            }
            break;

        case FORMAT_BINARY:
            {
                flags = flags | std::ios::binary;

                std::ofstream out(m_nextFile.c_str(), flags);

                factory->get_helper(FILE_FORMAT_BINARY)->save(out, ref, hold);

                out.close();
            }
            break;

        default:
            break;
        }
    } 
    catch(...) 
    {
    }

    if (m_config.multipleFiles)
    {
        m_currentIndex++;
        nextFile();
    }
}



// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FileLoaderProcessor.cpp
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

#include "FileLoaderProcessor.hpp"
#include <corbasim/core/file_format_helper.hpp>
#include <corbasim/gui/utils.hpp>
#include <iostream>

using namespace corbasim::gui;

FileLoaderProcessor::FileLoaderProcessor(
        Objref_ptr object,
        const QList< int >& path,
        const QStringList& files,
        int currentFile,
        const int format,
        const bool repeat) :
    RequestProcessor(object, path),
    m_files(files), 
    m_currentFile(currentFile), 
    m_format(format), 
    m_repeat(repeat)
{
}

FileLoaderProcessor::~FileLoaderProcessor()
{
}

void FileLoaderProcessor::process( 
        Request_ptr request,
        TypeDescriptor_ptr reflective,
        Holder holder)
{
    using namespace ::corbasim::core;

    // std::cout << __FUNCTION__  << std::endl;

    if (m_files.size() == 0)
        return;

    file_format_factory const * factory = 
        file_format_factory::get_instance();

    file_format_helper const * helper = 
        factory->get_helper(static_cast< file_format >(m_format));

    if (helper)
    {
        if (!m_currentIStream || !m_currentIStream->good())
        {
            openFile();
        }

        bool end = false;
        int i = 0;
        while (m_currentIStream && !end 
                && i++ < m_files.size())
        {
            end = helper->load(
                    *m_currentIStream, 
                    reflective, 
                    holder);

            if (!end) openFile();
        }
    }
    else
    {
        std::cerr << "Invalid file helper!" << std::endl;
    }
}

void FileLoaderProcessor::openFile()
{
    m_currentIStream.reset();

    if (m_files.size() > 0 && 
            (m_currentFile < m_files.size() || m_repeat))
    {
        if (m_repeat && m_currentFile == m_files.size())
        {
            m_currentFile = 0;
        }
    
        if (m_currentFile < m_files.size())
        {
            // std::cout << __FUNCTION__ << " " << 
            //     m_files.at(m_currentFile).toStdString() << std::endl;

            m_currentIStream.reset(new std::ifstream(
                        m_files.at(m_currentFile).toStdString().c_str()));

            // open a new file
            emit nextFile(m_currentFile);

            m_currentFile++;
        }
    }
}


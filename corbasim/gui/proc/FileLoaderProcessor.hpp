// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FileLoaderProcessor.hpp
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

#ifndef CORBASIM_GUI_FILELOADERPROCESSOR_HPP
#define CORBASIM_GUI_FILELOADERPROCESSOR_HPP

#include <fstream>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/proc/RequestProcessor.hpp>

namespace corbasim
{
namespace gui
{

class FileLoaderProcessor;

typedef boost::shared_ptr< FileLoaderProcessor >
    FileLoaderProcessor_ptr;

class CORBASIM_GUI_DECLSPEC FileLoaderProcessor :
    public QObject, public RequestProcessor
{
    Q_OBJECT
public:

    FileLoaderProcessor(
        Objref_ptr object,
        const QList< int >& path,
        const QStringList& files,
        int currentFile,
        const int format,
        const bool repeat);

    virtual ~FileLoaderProcessor();

    void process(
            Request_ptr request,
            TypeDescriptor_ptr reflective,
            Holder holder);

signals:

    void nextFile(int index);

protected:

    void openFile();

    const QStringList m_files;
    int m_currentFile;
    const int m_format;
    const bool m_repeat;

    typedef boost::shared_ptr< std::ifstream > ifstream_ptr;
    ifstream_ptr m_currentIStream;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_FILELOADERPROCESSOR_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DumpProcessor.hpp
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

#ifndef CORBASIM_GUI_DUMPPROCESSOR_HPP
#define CORBASIM_GUI_DUMPPROCESSOR_HPP

#include <corbasim/gui/export.hpp>
#include <corbasim/gui/proc/RequestProcessor.hpp>

namespace corbasim
{
namespace gui
{

class CORBASIM_GUI_DECLSPEC DumpProcessor : public QObject,
    public RequestProcessor
{
    Q_OBJECT
public:

    enum Format
    {
        FORMAT_BINARY,
        FORMAT_TEXT,
        FORMAT_JSON,
        FORMAT_MAX
    };

    struct Config
    {
        bool multipleFiles;
        std::string filePrefix;
        Format format;
        unsigned int suffixLength;
    };

    DumpProcessor(Objref_ptr object,
            const ReflectivePath_t path,
            const Config& config);
    ~DumpProcessor();

    void process(Request_ptr req,
            TypeDescriptor_ptr ref,
            Holder hold);

protected:

    void nextFile();

    const Config m_config;
    unsigned int m_currentIndex;
    std::string m_nextFile;
    std::string m_extension;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_DUMPPROCESSOR_HPP */

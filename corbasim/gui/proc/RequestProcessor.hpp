// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestProcessor.hpp
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

#ifndef CORBASIM_GUI_REQUESTPROCESSOR_HPP
#define CORBASIM_GUI_REQUESTPROCESSOR_HPP

#include <corbasim/gui/types.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/export.hpp>
#include <corbasim/gui/Model.hpp>

namespace corbasim 
{
namespace gui 
{

class RequestProcessor;

typedef boost::shared_ptr< RequestProcessor > RequestProcessor_ptr;

class CORBASIM_GUI_DECLSPEC RequestProcessor
{
public:

    virtual ~RequestProcessor();

    virtual void process(Request_ptr req, 
            TypeDescriptor_ptr ref,
            Holder hold) = 0;

    ObjectId id() const;

    Objref_ptr object() const;

    const ReflectivePath_t& path() const;

    OperationDescriptor_ptr operation() const;

    TypeDescriptor_ptr descriptor() const;

protected:

    RequestProcessor(Objref_ptr object,
            const ReflectivePath_t& path);

    Objref_ptr m_object;
    const ReflectivePath_t m_path;
    OperationDescriptor_ptr m_operation;
    TypeDescriptor_ptr m_descriptor;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_REQUESTPROCESSOR_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.cpp
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

#include "reflective.hpp"
#include <corbasim/json/parser.hpp>
#include <corbasim/json/writer.hpp>

#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>

#include <corbasim/core/reference_repository.hpp>

using namespace corbasim::json;
using namespace corbasim::core;

reflective_helper::reflective_helper(
        core::reflective_base const * reflective,
        core::holder holder) :
    m_reflective(reflective), m_holder(holder), m_currentIndex(0)
{
}

reflective_helper::~reflective_helper()
{
}

void reflective_helper::new_double(double value_)
{
    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_DOUBLE:
            m_holder.to_value< double >() = (double) value_;
            break;
        case TYPE_FLOAT:
            m_holder.to_value< float >() = (float) value_;
            break;
        case TYPE_OCTET:
            m_holder.to_value< unsigned char >() = (unsigned char) value_;
            break;
        case TYPE_CHAR:
            m_holder.to_value< char >() = (char) value_;
            break;
        case TYPE_SHORT:
            m_holder.to_value< short >() = (short) value_;
            break;
        case TYPE_USHORT:
            m_holder.to_value< unsigned short >() = (unsigned short) value_;
            break;
        case TYPE_LONG:
            m_holder.to_value< int32_t >() = (int32_t) value_;
            break;
        case TYPE_ULONG:
            m_holder.to_value< uint32_t >() = (uint32_t) value_;
            break;
        case TYPE_LONGLONG:
            m_holder.to_value< int64_t >() = (int64_t) value_;
            break;
        case TYPE_ULONGLONG:
            m_holder.to_value< uint64_t >() = (uint64_t) value_;
            break;
        default:
            throw "Error!";
    }
}

void reflective_helper::new_string(const std::string& d)
{
    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_STRING:
            m_reflective->from_string(m_holder, d);
            break;

        case TYPE_OBJREF:
            // TODO
            break;

        default:
            throw "Error!";
    }
}

void reflective_helper::new_bool(bool d)
{
    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            m_holder.to_value< bool >() = d;
            break;
        default:
            throw "Error!";
    }
}

void reflective_helper::new_null()
{
    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_OBJREF:
            // TODO
            break;
        default:
            throw "Error!";
    }
}

// For structs
helper::helper_base* reflective_helper::new_child(const std::string& name)
{
    if (m_reflective->get_type() == TYPE_STRUCT)
    {
        const unsigned int count = m_reflective->get_children_count();
        for (unsigned int i = 0; i < count; i++) 
            if (name == m_reflective->get_child_name(i))
            {
                return new reflective_helper(m_reflective->get_child(i),
                        m_reflective->get_child_value(m_holder, i));
            }
    }

    throw "Error!";
}

// For arrays
helper::helper_base* reflective_helper::new_child()
{
    if (m_reflective->is_repeated())
    {
        // Increments its length
        if (m_reflective->is_variable_length())
        {
            m_reflective->set_length(m_holder, m_currentIndex + 1);
        }

        return new reflective_helper(m_reflective->get_slice(),
                m_reflective->get_child_value(m_holder, m_currentIndex++));
    }

    throw "Error!";
}

// Parse
bool corbasim::json::parse(core::reflective_base const * reflective, 
        core::holder& holder, const char * str, size_t size)
{
    helper::helper_base * initial_helper = 
        new reflective_helper(reflective, holder);

    semantic_state _ss(initial_helper);
    state _st(_ss, str, size);

    return csu::corbasim::json::parser::grammar::gram::match(_st);
}

namespace  
{
    typedef csu::corbasim::json::writer::json_writer< 
        std::ostream > writer_t;

    void do_write(writer_t& w, 
            corbasim::core::reflective_base const * reflective, 
            corbasim::core::holder holder)
    {
        using namespace corbasim::core;

        const reflective_type type = reflective->get_type();

        switch(type)
        {
            case TYPE_OBJREF:
                {
                    objrefvar_reflective_base const * objref = 
                        static_cast< objrefvar_reflective_base const * >(
                                reflective);

                    CORBA::Object_var obj = objref->to_object(holder);

                    if (CORBA::is_nil(obj))
                    {
                        w.new_null();
                        break;
                    }
                    
                    try {
                        reference_repository * rr =
                            reference_repository::get_instance();

                        CORBA::String_var str = 
                            rr->object_to_string(obj);

                        w.new_string(str.in());

                    } catch (...) {
                        w.new_null();
                    }

                }

                break;

            case TYPE_DOUBLE:
                w.new_double((double) holder.to_value< double >());
                break;
            case TYPE_FLOAT:
                w.new_double((double) holder.to_value< float >());
                break;
            case TYPE_OCTET:
                w.new_double((double) holder.to_value< unsigned char >());
                break;
            case TYPE_CHAR:
                w.new_double((double) holder.to_value< char >());
                break;
            case TYPE_SHORT:
                w.new_double((double) holder.to_value< short >());
                break;
            case TYPE_USHORT:
                w.new_double((double) holder.to_value< unsigned short >());
                break;
            case TYPE_LONG:
                w.new_double((double) holder.to_value< int32_t >());
                break;
            case TYPE_ULONG:
                w.new_double((double) holder.to_value< uint32_t >());
                break;
            case TYPE_LONGLONG:
                w.new_double((double) holder.to_value< int64_t >());
                break;
            case TYPE_ULONGLONG:
                w.new_double((double) holder.to_value< uint64_t >());
                break;

            case TYPE_ARRAY:
            case TYPE_SEQUENCE:
                {
                    const unsigned int count = 
                        reflective->get_length(holder);

                    w.array_start();

                    for (unsigned int i = 0; i < count; i++) 
                    {
                        // Value
                        do_write(w, reflective->get_child(i),
                                reflective->get_child_value(holder, i));
                    }

                    w.array_end();
                }
                break;

            case TYPE_STRUCT:
                {
                    const unsigned int count = 
                        reflective->get_children_count();

                    w.object_start();

                    for (unsigned int i = 0; i < count; i++) 
                    {
                        // Name
                        w.new_string(reflective->get_child_name(i));

                        // Value
                        do_write(w, reflective->get_child(i),
                                reflective->get_child_value(holder, i));
                    }

                    w.object_end();
                }
                break;

            default:
                break;
        }
    }

} // namespace 

// Write
void corbasim::json::write(std::ostream& os, 
        core::reflective_base const * reflective, 
        core::holder& holder, bool indent)
{
    writer_t w(os);

    do_write(w, reflective, holder);
}



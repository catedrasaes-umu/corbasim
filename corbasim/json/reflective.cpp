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
        corbasim::core::reflective_base const * reflective,
        corbasim::core::holder holder) :
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
            m_holder.to_value< unsigned short >() =
                (unsigned short) value_;
            break;
        case TYPE_LONG:
            m_holder.to_value< CORBA::Long >() = (CORBA::Long) value_;
            break;
        case TYPE_ULONG:
            m_holder.to_value< CORBA::ULong >() = (CORBA::ULong) value_;
            break;
        case TYPE_LONGLONG:
            m_holder.to_value< CORBA::LongLong >() = (CORBA::LongLong) value_;
            break;
        case TYPE_ULONGLONG:
            m_holder.to_value< CORBA::ULongLong >() = (CORBA::ULongLong) value_;
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

        case TYPE_ENUM:
            {
                const unsigned int count =
                    m_reflective->get_children_count();

                for (int i = 0; i < (int) count; i++)
                {
                    if (d == m_reflective->get_child_name(i))
                    {
                        m_holder.to_value< CORBA::Long >() = i;
                        break;
                    }
                }
            }
            break;

        case TYPE_OBJREF:
            {
                core::reference_repository * rr =
                    core::reference_repository::get_instance();

                objrefvar_reflective_base const * objref =
                    static_cast< objrefvar_reflective_base const * >(
                            m_reflective);

                CORBA::Object_var obj;

                try
                {
                    obj = rr->string_to_object(d.c_str());
                }
                catch (...)
                {}

                objref->from_object(m_holder, obj);
            }
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
            {
                objrefvar_reflective_base const * objref =
                    static_cast< objrefvar_reflective_base const * >(
                            m_reflective);

                CORBA::Object_var obj;

                objref->from_object(m_holder, obj);
            }
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
    if (!m_reflective->is_repeated())
        throw "Error!";

    // Increments its length
    if (m_reflective->is_variable_length())
    {
        m_reflective->set_length(m_holder, m_currentIndex + 1);
    }
    else
    {
        unsigned int length = m_reflective->get_length(m_holder);

        if (m_currentIndex >= length)
            throw "Error!";
    }

    return new reflective_helper(m_reflective->get_slice(),
            m_reflective->get_child_value(m_holder, m_currentIndex++));
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

bool corbasim::json::parse(core::reflective_base const * reflective,
        core::holder& holder, std::istream& in)
{
    helper::helper_base * initial_helper =
        new reflective_helper(reflective, holder);

    semantic_state _ss(initial_helper);
    istream_state _st(_ss, in);

    return csu::corbasim::json::parser::grammar::gram::match(_st);
}

void corbasim::json::write(std_writer_t& w,
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

                try
                {
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

        case TYPE_ENUM:
            {
                const int count = (int) reflective->get_children_count();

                CORBA::Long idx = holder.to_value< CORBA::Long >();

                if (idx >= 0 && idx < count)
                {
                    w.new_string(reflective->get_child_name(idx));
                }
                else
                {
                    w.new_string("Invalid value!");
                }
            }
            break;

        case TYPE_BOOL:
            w.new_bool(holder.to_value< bool >());
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
            w.new_double((double) holder.to_value< CORBA::Long >());
            break;
        case TYPE_ULONG:
            w.new_double((double) holder.to_value< CORBA::ULong >());
            break;
        case TYPE_LONGLONG:
            w.new_double((double) holder.to_value< CORBA::LongLong >());
            break;
        case TYPE_ULONGLONG:
            w.new_double((double) holder.to_value< CORBA::ULongLong >());
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
                    write(w, reflective->get_slice(),
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
                    write(w, reflective->get_child(i),
                            reflective->get_child_value(holder, i));
                }

                w.object_end();
            }
            break;

        case TYPE_UNION:
            {
                w.object_start();

                unsigned int idx =  reflective->get_length(holder);

                w.new_string(reflective->get_child_name(0));

                write(w, reflective->get_child(0),
                        reflective->get_child_value(holder, 0));

                if (idx > 0)
                {
                    w.new_string(reflective->get_child_name(idx));

                    write(w, reflective->get_child(idx),
                            reflective->get_child_value(holder, idx));
                }

                w.object_end();
            }
            break;

        case TYPE_STRING:
            {
                std::string str = reflective->to_string(holder);
                w.new_string(str.c_str());
            }
            break;
        default:
            break;
    }
}

// Write
void corbasim::json::write(std::ostream& os,
        core::reflective_base const * reflective,
        core::holder& holder, bool indent)
{
    std_writer_t w(os, indent);

    write(w, reflective, holder);
}



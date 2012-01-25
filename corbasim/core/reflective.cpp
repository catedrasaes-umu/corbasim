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
#include "reflective.ipp"

namespace corbasim 
{
namespace core 
{
namespace detail 
{

template class bool_reflective< CORBA::Boolean >;
template class primitive_reflective< CORBA::Short >;
template class primitive_reflective< CORBA::UShort >;
template class primitive_reflective< CORBA::Char >;
template class primitive_reflective< CORBA::Octet >;
template class primitive_reflective< CORBA::Long >;
template class primitive_reflective< CORBA::ULong >;
template class primitive_reflective< CORBA::LongLong >;
template class primitive_reflective< CORBA::ULongLong >;
template class primitive_reflective< CORBA::Float >;
template class primitive_reflective< CORBA::Double >;

} // namespace detail
} // namespace core
} // namespace corbasim

using namespace corbasim::core;

// Holder
holder::holder()
{
}

holder::holder(holder_impl_base * impl) :
    m_impl(holder_impl_ptr(impl))
{
}

holder::holder(const holder& o) :
    m_impl(o.m_impl)
{
}

holder& holder::operator=(const holder& o)
{
    m_impl = o.m_impl;

    return *this;
}


// Reflective base

reflective_base::reflective_base(reflective_base const * parent,
        unsigned int child_index) : 
    m_parent(parent), m_child_index(child_index)
{
}

reflective_base::~reflective_base()
{
}

reflective_base const * reflective_base::get_parent() const 
{ 
    return m_parent; 
}

unsigned int reflective_base::get_child_index() const 
{ 
    return m_child_index; 
}

unsigned int reflective_base::get_children_count() const 
{ 
    return 0; 
}

const char * reflective_base::get_child_name(unsigned int idx) const 
{ 
    return 0;
}

reflective_base const * reflective_base::get_child(unsigned int idx) const
{
    return 0;
}

bool reflective_base::is_repeated() const        { return false; }
bool reflective_base::is_variable_length() const { return false; }
bool reflective_base::is_primitive() const       { return false; }
bool reflective_base::is_enum() const            { return false; }

reflective_type reflective_base::get_type() const
{
    return TYPE_INVALID;
}

reflective_base const * reflective_base::get_slice() const
{
    return 0;
}

// Dynamic information

holder reflective_base::create_holder() const
{
    return holder();
}

unsigned int reflective_base::get_length(holder const& value) const
{
    return 0;
}

holder reflective_base::get_child_value(holder& value, 
    unsigned int idx) const
{
    return holder();
}

double reflective_base::to_double(holder const& value) const
{
    return 0.0;
}

// Interface Reflective Base

void interface_reflective_base::insert_reflective(
        const std::string& name,
        tag_t tag, operation_reflective_base const * reflective)
{
    m_reflectives.push_back(reflective);

    // Maps
    m_reflectives_by_name.insert(std::make_pair(name, reflective));
    m_reflectives_by_tag.insert(std::make_pair(tag, reflective));
}

interface_reflective_base::~interface_reflective_base()
{
}

unsigned int interface_reflective_base::operation_count() const
{
    return m_reflectives.size();
}

operation_reflective_base const * 
interface_reflective_base::get_reflective_by_index(
        unsigned int idx) const
{
    return m_reflectives[idx];
}

operation_reflective_base const * 
interface_reflective_base::get_reflective_by_name(
        const std::string& name) const
{
    reflectives_by_name_t::const_iterator it;
    it = m_reflectives_by_name.find(name);

    if (it != m_reflectives_by_name.end())
        return it->second;

    return NULL;
}

operation_reflective_base const * 
interface_reflective_base::get_reflective_by_tag(
        tag_t tag) const
{
    reflectives_by_tag_t::const_iterator it;
    it = m_reflectives_by_tag.find(tag);

    if (it != m_reflectives_by_tag.end())
        return it->second;

    return NULL;
}

// Operation reflective base
operation_reflective_base::~operation_reflective_base()
{
}


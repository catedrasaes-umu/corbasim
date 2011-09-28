// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reference_validator.hpp
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

#ifndef CORBASIM_CORE_REFERENCE_VALIDATOR_HPP
#define CORBASIM_CORE_REFERENCE_VALIDATOR_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/impl.hpp>

namespace corbasim 
{
namespace core 
{

struct reference_validator_base
{
    virtual void set_reference(CORBA::Object_ptr ref) = 0;
    virtual bool is_nil() const = 0;
    virtual CORBA::Object_ptr get_reference() = 0;
    virtual ~reference_validator_base();
};

typedef boost::shared_ptr< reference_validator_base > reference_validator_ptr;

namespace detail 
{

template < typename Interface >
struct narrow
{
    static inline Interface* invoke(CORBA::Object_ptr ref)
    {
        return Interface::_narrow(ref);
    }
};

template < >
struct narrow< CORBA::Object >
{
    static inline CORBA::Object_ptr invoke(CORBA::Object_ptr ref)
    {
        return CORBA::Object::_duplicate(ref);
    }
};

} // namespace detail

template < typename Interface >
struct reference_validator_impl : public reference_validator_base
{
    reference_validator_impl() :
        m_ref(Interface::_nil())
    {
    }

    ~reference_validator_impl()
    {
        CORBA::release(m_ref);
    }

    void set_reference(CORBA::Object_ptr ref)
    {
        CORBA::release(m_ref);
        m_ref = Interface::_narrow(ref);
    }

    CORBA::Object_ptr get_reference()
    {
        return CORBA::Object::_duplicate(m_ref);
    }

    bool is_nil() const
    {
        return CORBA::is_nil(m_ref);
    }

    Interface * m_ref;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_REFERENCE_VALIDATOR_HPP */


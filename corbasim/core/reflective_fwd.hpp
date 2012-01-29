// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective_fwd.hpp
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

#ifndef CORBASIM_CORE_REFLECTIVE_FWD_HPP
#define CORBASIM_CORE_REFLECTIVE_FWD_HPP

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_same.hpp>
#include <corbasim/impl.hpp>
#include <corbasim/adapted.hpp>
#include <corbasim/event.hpp>
#include <corbasim/core/inserter.hpp>
#include <corbasim/core/caller.hpp>
#include <corbasim/core/callable.hpp>
#include <corbasim/core/reference_validator.hpp>

namespace corbasim 
{
namespace core 
{

struct holder;

struct holder_impl_base {};

typedef boost::shared_ptr< holder_impl_base > holder_impl_ptr;

template< typename T >
struct holder_ref_impl;

struct holder
{
    holder();

    /**
     * @brief Assumes its shared ownership.
     *
     * @param impl
     */
    holder(holder_impl_base * impl);

    holder(const holder& o);

    holder& operator=(const holder& o);

    template< typename Value >
    Value& to_value();
    
    holder_impl_ptr m_impl;
};


// And some other special cases for holders...
enum reflective_type
{
    TYPE_INVALID,
    TYPE_CHAR,
    TYPE_OCTET,
    TYPE_BOOL,
    TYPE_ENUM,
    TYPE_SHORT,
    TYPE_USHORT,
    TYPE_LONG,
    TYPE_ULONG,
    TYPE_LONGLONG,
    TYPE_ULONGLONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_WSTRING,
    TYPE_OBJREF,
    TYPE_STRUCT,
    TYPE_ARRAY,
    TYPE_UNION,
    TYPE_SEQUENCE
};

enum direction_type
{
    DIRECTION_IN,
    DIRECTION_OUT,
    DIRECTION_INOUT
};

struct reflective_base;
struct objrefvar_reflective_base;
struct operation_reflective_base;
struct interface_reflective_base;

struct reflective_base
{
    virtual ~reflective_base();

    // static information
    // virtual tag_t get_tag() const = 0;

    virtual const char * get_type_name() const;

    reflective_base const * get_parent() const;
    unsigned int get_child_index() const;

    virtual unsigned int get_children_count() const;
    virtual const char * get_child_name(unsigned int idx) const;
    virtual reflective_base const * get_child(unsigned int idx) const;

    virtual bool is_repeated() const;
    virtual bool is_variable_length() const;
    virtual bool is_primitive() const;
    virtual bool is_enum() const;

    virtual reflective_type get_type() const;

    // Requires is_repeated
    virtual reflective_base const * get_slice() const;

    virtual holder create_holder() const;

    // dynamic information
    virtual unsigned int get_length(holder const& value) const;
    virtual void set_length(holder& value, unsigned int length) const;

    virtual holder get_child_value(holder& value, 
        unsigned int idx) const;
    
    virtual double to_double(holder const& value) const;
    virtual std::string to_string(holder const& h) const;
    virtual void from_string(holder& h, const std::string& str) const;
    virtual void copy(holder const& src, holder& dst) const;

protected:
    reflective_base(reflective_base const * parent = NULL, 
            unsigned int child_index = 0);

    reflective_base const * m_parent;
    unsigned int m_child_index;
};

struct objrefvar_reflective_base : public reflective_base
{
    virtual CORBA::Object_ptr to_object(holder const& h) const = 0;
    virtual void from_object(holder& h, CORBA::Object_ptr obj) const = 0;

    // virtual interface_reflective_base const * get_interface() const = 0;
    virtual reference_validator_base * create_validator() const = 0;
    
    virtual ~objrefvar_reflective_base();

protected:
    objrefvar_reflective_base(reflective_base const * parent = NULL, 
            unsigned int child_index = 0);
};

typedef boost::shared_ptr< reflective_base > reflective_ptr;

template< typename T >
struct reflective;

struct operation_reflective_base : 
    public virtual reflective_base
{
    virtual const char * get_name() const = 0;
    virtual tag_t get_tag() const = 0;

    virtual event::request_ptr create_request() const = 0;

    virtual holder get_holder(event::request_ptr req) const = 0;

    virtual direction_type get_parameter_direction(
            unsigned int idx) const = 0;

    virtual ~operation_reflective_base();
};

struct interface_reflective_base
{
    unsigned int operation_count() const;
    operation_reflective_base const * get_reflective_by_index(
            unsigned int idx) const;
    operation_reflective_base const * get_reflective_by_name(
            const std::string& name) const;
    operation_reflective_base const * get_reflective_by_tag(tag_t tag) const;

    virtual ~interface_reflective_base();

    virtual const char * get_name() const = 0;
    virtual const char * get_fqn() const = 0;

    virtual interface_caller_base * create_caller() const = 0;
    virtual reference_validator_base * create_validator() const = 0;

    // Servant
    virtual PortableServer::ServantBase * create_servant(
            request_processor * proc) const = 0;

protected:

    void insert_reflective(const std::string& name,
        tag_t tag, operation_reflective_base const * reflective);

    // Data
    typedef std::vector< operation_reflective_base const * > 
        reflectives_t;
    reflectives_t m_reflectives;

    typedef std::map< std::string, operation_reflective_base const * > 
        reflectives_by_name_t;
    reflectives_by_name_t m_reflectives_by_name;

    typedef std::map< tag_t, operation_reflective_base const * > 
        reflectives_by_tag_t;
    reflectives_by_tag_t m_reflectives_by_tag;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_REFLECTIVE_FWD_HPP */


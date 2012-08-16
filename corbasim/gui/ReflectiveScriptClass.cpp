// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectiveScriptClass.cpp
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

#include "ReflectiveScriptClass.hpp"
#include <limits>
#include <corbasim/gui/qvariant.hpp>
#include <iostream>
#include <corbasim/core/reference_repository.hpp>

#include <boost/cstdint.hpp>
#ifdef _MSC_VER
using boost::uint32_t;
using boost::int32_t;
using boost::uint64_t;
using boost::int64_t;
#endif

using namespace corbasim::gui;

ReflectiveScriptClass::ReflectiveScriptClass(QScriptEngine * engine) :
    QScriptClass(engine)
{
}

ReflectiveScriptClass::~ReflectiveScriptClass()
{
}

QString ReflectiveScriptClass::name() const
{
    return "ReflectiveScriptClass";
}

QScriptClassPropertyIterator *  ReflectiveScriptClass::newIterator(
    const QScriptValue & object)
{
    return new ReflectivePropertyIterator(object);
}

QScriptValue ReflectiveScriptClass::property(
        const QScriptValue& object,
        const QScriptString& name, 
        uint id)
{
    std::cout << __FUNCTION__ << std::endl;

    Node_ptr node = qscriptvalue_cast< Node_ptr >(object.data());

    if (node)
    {
        node->check_for_initialized();

        ::corbasim::core::reflective_type type = 
            node->reflective->get_type();

        if (type == ::corbasim::core::TYPE_STRUCT)
        {
            if (id < node->children.size())
            {
                return toScriptValue(node->children[id]);
            }
        }
        else if (node->reflective->is_repeated())
        {
            if (id < node->children.size())
            {
                return toScriptValue(node->children[id]);
            }
            else if (QString(name) == "length")
            {
                // length property
                return QScriptValue(node->children.size());
            }
        }
    }

    // Invalid value
    return QScriptValue();
}

QScriptValue ReflectiveScriptClass::toScriptValue(Node_ptr node)
{
    std::cout << __FUNCTION__ << std::endl;

    using namespace corbasim::core;

    const reflective_type type =
        node->reflective->get_type();

    holder& hold = node->holder;
    reflective_base const * reflective = node->reflective;

    // Once again the same switch statement...
    switch(type)
    {
        case TYPE_STRUCT:
        case TYPE_UNION:
        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
            return engine()->newObject(this,
                    engine()->newVariant(qVariantFromValue(node)));

        case TYPE_BOOL:
            return QScriptValue(hold.to_value< bool >());
        case TYPE_OCTET:
            return QScriptValue(hold.to_value< unsigned char >());
        case TYPE_CHAR:
            return QScriptValue(hold.to_value< char >());
        case TYPE_SHORT:
            return QScriptValue(hold.to_value< short >());
        case TYPE_USHORT:
            return QScriptValue(hold.to_value< unsigned short >());
        case TYPE_LONG:
            return QScriptValue(hold.to_value< int32_t >());
        case TYPE_ULONG:
            return QScriptValue(hold.to_value< uint32_t >());
        case TYPE_LONGLONG:
            return QScriptValue((qsreal) hold.to_value< int64_t >());
        case TYPE_ULONGLONG:
            return QScriptValue((qsreal) hold.to_value< uint64_t >());

        case TYPE_STRING:
        case TYPE_WSTRING:
            {
                std::string str(reflective->to_string(hold));
                return QScriptValue(str.c_str());
            }
        case TYPE_OBJREF:
            {
                objrefvar_reflective_base const * objref = 
                    static_cast< objrefvar_reflective_base const * >(
                            reflective);

                CORBA::Object_var obj = objref->to_object(hold);

                if (CORBA::is_nil(obj))
                    return QScriptValue("NIL");
                
                try {
                    reference_repository * rr =
                        reference_repository::get_instance();

                    CORBA::String_var str = 
                        rr->object_to_string(obj);

                    return QScriptValue(str.in());

                } catch (...) {
                    return QScriptValue("NIL");
                }

            }
            break;

        case TYPE_ENUM:
            {
                // Maybe it works...
                int32_t value = hold.to_value< int32_t >();

                const char * str = "Unknown value"; 

                if (value >= 0 && 
                        value < reflective->get_children_count())
                {
                    str = reflective->get_child_name(
                            (unsigned int) value);
                }

                return QScriptValue(str);
            }

        case TYPE_DOUBLE:
            return QScriptValue(hold.to_value< double >());
        case TYPE_FLOAT:
            return QScriptValue(hold.to_value< float >());
        default:
            break;
    }

    return "ERROR!";
}

void ReflectiveScriptClass::fromScriptValue(
        const QScriptValue& value, Node_ptr node)
{
    std::cout << __FUNCTION__ << std::endl;

    using namespace corbasim::core;

    const reflective_type type =
        node->reflective->get_type();

    node->check_for_initialized();

    holder& hold = node->holder;
    reflective_base const * reflective = node->reflective;

    switch(type)
    {

        case TYPE_STRUCT:
            {
                if (value.isObject())
                {
                    unsigned int count = 
                        node->reflective->get_children_count();

                    // Search by name
                    for (unsigned int i = 0; i < count; i++) 
                    {
                        const char *childName = reflective->get_child_name(i);
                        QScriptValue childValue = value.property(childName);

                        if (childValue.isValid())
                            fromScriptValue(childValue, node->children[i]);
                    }
                }
                else
                {
                    std::cerr << "Must be an object!" << std::endl;
                }
            }
            break;

        /*
        TODO case TYPE_UNION:
        */
        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
            {
                unsigned int length = reflective->get_length(hold);
                unsigned int newLength = value.property("length").toUInt32();

                if (reflective->is_variable_length() &&
                        length != newLength)
                {
                    unsigned int length = value.property("length").toUInt32();

                    reflective->set_length(hold, newLength);

                    node->reset();
                    node->check_for_initialized();
                }

                for (unsigned int i = 0; i < newLength && i < length; i++) 
                {
                    fromScriptValue(value.property(i),
                            node->children[i]);
                }
            }
            break;

        case TYPE_BOOL:
            hold.to_value< bool >() = value.toBool();
            break;
        case TYPE_OCTET:
            hold.to_value< unsigned char >() = value.toInteger();
            break;
        case TYPE_CHAR:
            hold.to_value< char >();
            break;
        case TYPE_SHORT:
            hold.to_value< short >() = value.toInteger();
            break;
        case TYPE_USHORT:
            hold.to_value< unsigned short >() = value.toUInt16();
            break;
        case TYPE_LONG:
            hold.to_value< int32_t >() = value.toInteger();
            break;
        case TYPE_ULONG:
            hold.to_value< uint32_t >() = value.toUInt32();
            break;
        case TYPE_LONGLONG:
            hold.to_value< int64_t >() = value.toInteger();
            break;
        case TYPE_ULONGLONG:
            hold.to_value< uint64_t >() = value.toInteger();
            break;

        case TYPE_STRING:
        case TYPE_WSTRING:
            {
                const std::string str(value.toString().toStdString());
                reflective->from_string(hold, str);
            }
            break;

        /*
        TODO
        case TYPE_OBJREF:
            {
                objrefvar_reflective_base const * objref = 
                    static_cast< objrefvar_reflective_base const * >(
                            reflective);

                CORBA::Object_var obj = objref->to_object(hold);

                if (CORBA::is_nil(obj))
                    return QScriptValue("NIL");
                
                try {
                    reference_repository * rr =
                        reference_repository::get_instance();

                    CORBA::String_var str = 
                        rr->object_to_string(obj);

                    return QScriptValue(str.in());

                } catch (...) {
                    return QScriptValue("NIL");
                }

            }
            break;
        */

        case TYPE_ENUM:
            {
                const unsigned int count = reflective->get_children_count();

                const QString str (value.toString());

                for (unsigned int i = 0; i < count; i++) 
                {
                    if (str == reflective->get_child_name(i))
                    {
                        hold.to_value< int32_t >() = (int32_t) i;
                        break;
                    }
                }
            }
            break;

        case TYPE_DOUBLE:
            hold.to_value< double >() = value.toNumber();
        case TYPE_FLOAT:
            hold.to_value< float >() = value.toNumber();
        default:
            break;
    }

}

QScriptClass::QueryFlags ReflectiveScriptClass::queryProperty(
        const QScriptValue& object, 
        const QScriptString& name, 
        QScriptClass::QueryFlags flags, 
        uint * id)
{
    std::cout << __FUNCTION__ << " " << 
        name.toString().toStdString() << std::endl;

    // Invalid property identifier
    *id = std::numeric_limits< uint >::max();

    // Seen in Qt examples
    Node_ptr node = qscriptvalue_cast< Node_ptr >(object.data());

    if (node)
    {
        // Conversion from interned to normal string
        // for comparision
        const QString sName = name;

        node->check_for_initialized();

        ::corbasim::core::reflective_type type = 
            node->reflective->get_type();

        if (type == ::corbasim::core::TYPE_STRUCT)
        {
            unsigned int count = node->reflective->get_children_count();

            // Search by name
            for (unsigned int i = 0; i < count; i++) 
            {
                // Maybe better with interned strings
                if (sName == node->reflective->get_child_name(i))
                {
                    // Its identifier is its position
                    *id = i;

                    return QScriptClass::HandlesReadAccess |
                        QScriptClass::HandlesWriteAccess;
                }
            }
        }
        else if (node->reflective->is_repeated())
        {
            unsigned int count = node->reflective->get_length(node->holder);

            bool ok = false;
            *id = sName.toUInt(&ok);

            if (ok && *id < count)
            {
                return QScriptClass::HandlesReadAccess |
                    QScriptClass::HandlesWriteAccess;
            }
            else if (!ok && sName == "length")
            {
                *id = std::numeric_limits< uint >::max();

                if (node->reflective->is_variable_length())
                    return QScriptClass::HandlesReadAccess |
                        QScriptClass::HandlesWriteAccess;

                return QScriptClass::HandlesReadAccess;
            }
        }
    }
    else
    {
        std::cerr << "Invalid node!" << std::endl;
    }

    return 0;
}

void ReflectiveScriptClass::setProperty(
        QScriptValue& object, 
        const QScriptString & name, 
        uint id, 
        const QScriptValue& value)
{
    std::cout << __FUNCTION__ << " " << 
        name.toString().toStdString() << std::endl;

    Node_ptr node = qscriptvalue_cast< Node_ptr >(object.data());

    if (node)
    {
        // Ensure it is initialized
        node->check_for_initialized();

        ::corbasim::core::reflective_type type = 
            node->reflective->get_type();

        if (type == ::corbasim::core::TYPE_STRUCT)
        {
            // because I am sure it is initialized
            if (id < node->children.size())
            {
                fromScriptValue(value, node->children[id]);
            }
        }
        else if (node->reflective->is_repeated())
        {
            if (id < node->children.size())
            {
                fromScriptValue(value, node->children[id]);
            }
            else if (node->reflective->is_variable_length() &&
                    QString(name) == "length")
            {
                // length property
                unsigned int length = value.toUInt32();

                node->reflective->set_length(node->holder, length);

                // re-initialized in next access
                node->reset();
            }
        }
    }
}

//
//
//
// Property Iterator
//
//

ReflectivePropertyIterator::ReflectivePropertyIterator(
    const QScriptValue& object) : 
    QScriptClassPropertyIterator(object),
    m_idx(-1)
{
    m_node = qscriptvalue_cast< Node_ptr >(object.data());
}

ReflectivePropertyIterator::~ReflectivePropertyIterator()
{
}

/*
QScriptValue::PropertyFlags ReflectivePropertyIterator::flags() const 
{
}
*/

bool ReflectivePropertyIterator::hasNext() const 
{
    using namespace corbasim::core;
    reflective_base const * reflective = m_node->reflective;
    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_STRUCT:
            return (m_idx + 1 < reflective->get_children_count());

        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
            return (m_idx + 1 < reflective->get_length(m_node->holder));

        default:
            break;
    }

    return false;
}

bool ReflectivePropertyIterator::hasPrevious() const 
{
    using namespace corbasim::core;
    reflective_base const * reflective = m_node->reflective;
    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_STRUCT:
            return (m_idx - 1 >= 0);

        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
            return (reflective->get_length(m_node->holder) > 0 && 
                    m_idx - 1 >= 0);

        default:
            break;
    }

    return false;
}

uint ReflectivePropertyIterator::id() const 
{
    return m_idx;
}

QScriptString ReflectivePropertyIterator::name() const 
{
    using namespace corbasim::core;
    reflective_base const * reflective = m_node->reflective;
    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_STRUCT:
            return object().engine()->toStringHandle(
                reflective->get_child_name(m_idx));

        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
            return object().engine()->toStringHandle(QString("%1").arg(m_idx));

        default:
            break;
    }

     return QScriptString();
}

void ReflectivePropertyIterator::next() 
{
    using namespace corbasim::core;
    reflective_base const * reflective = m_node->reflective;
    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
        case TYPE_STRUCT:
            ++m_idx;
            break;

        default:
            break;
    }
}

void ReflectivePropertyIterator::previous() 
{
    using namespace corbasim::core;
    reflective_base const * reflective = m_node->reflective;
    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
        case TYPE_STRUCT:
            --m_idx;
            break;

        default:
            break;
    }
}

void ReflectivePropertyIterator::toBack() 
{
    using namespace corbasim::core;
    reflective_base const * reflective = m_node->reflective;
    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_STRUCT:
            m_idx = reflective->get_children_count();
            m_idx = (m_idx)? m_idx - 1: 0;
            break;

        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
            m_idx = reflective->get_length(m_node->holder);
            m_idx = (m_idx)? m_idx - 1: 0;
            break;

        default:
            break;
    }
}

void ReflectivePropertyIterator::toFront() 
{
    using namespace corbasim::core;
    reflective_base const * reflective = m_node->reflective;
    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_ARRAY:
        case TYPE_SEQUENCE:
        case TYPE_STRUCT:
            m_idx = -1;
            break;

        default:
            break;
    }
}



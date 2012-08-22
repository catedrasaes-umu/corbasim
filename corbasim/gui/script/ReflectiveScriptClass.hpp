// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectiveScriptClass.hpp
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

#ifndef CORBASIM_GUI_REFLECTIVESCRIPTCLASS_HPP
#define CORBASIM_GUI_REFLECTIVESCRIPTCLASS_HPP

#include <QtScript>
#include <corbasim/gui/item/ModelNode.hpp>

Q_DECLARE_METATYPE(corbasim::gui::Node_ptr)

namespace corbasim 
{
namespace gui 
{

class ReflectiveScriptClass : public QScriptClass
{
public:

    ReflectiveScriptClass ( QScriptEngine * engine );
    virtual ~ReflectiveScriptClass ();

    /*
    QVariant    extension ( Extension extension, const QVariant & argument = QVariant() );
    */

    QString name() const;

    QScriptClassPropertyIterator *  newIterator(const QScriptValue & object);

    QScriptValue property(
            const QScriptValue& object,
            const QScriptString& name, 
            uint id);

    /*
    QScriptValue::PropertyFlags propertyFlags ( const QScriptValue & object, const QScriptString & name, uint id );
    QScriptValue    prototype () const
    */

    QScriptClass::QueryFlags queryProperty(
            const QScriptValue& object, 
            const QScriptString& name, 
            QScriptClass::QueryFlags flags, 
            uint * id);

    void setProperty(
            QScriptValue& object, 
            const QScriptString & name, 
            uint id, 
            const QScriptValue& value);

    /*
    bool    supportsExtension ( Extension extension ) const;
    */

protected:

    QScriptValue toScriptValue(Node_ptr node);

    void fromScriptValue(
            const QScriptValue& value, 
            Node_ptr node);
};

class ReflectivePropertyIterator : 
    public QScriptClassPropertyIterator
{
public:

    ReflectivePropertyIterator(const QScriptValue& object);
    virtual ~ReflectivePropertyIterator();

    // QScriptValue::PropertyFlags flags() const;
    
    bool hasNext() const;
    bool hasPrevious() const;
    uint id() const;
    QScriptString name() const;
    void next();
    void previous();
    void toBack();
    void toFront();

protected:

    Node_ptr m_node;

    int m_idx;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_REFLECTIVESCRIPTCLASS_HPP */


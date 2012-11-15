// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectiveGUI.cpp
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

#include "ReflectiveGUI.hpp"
#include <cassert>
#include <limits>
#define CORBASIM_NO_IMPL
#include <corbasim/core/reflective.hpp>

#ifdef CORBASIM_USE_QTSCRIPT
#include <corbasim/qt/private/ScriptEditor.hpp>
#include <corbasim/gui/qvariant.hpp>
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <corbasim/json/reflective.hpp>
#include <corbasim/core/file_format_helper.hpp>

using namespace corbasim::gui;

#include <boost/cstdint.hpp>
#ifdef _MSC_VER
using boost::uint32_t;
using boost::int32_t;
using boost::uint64_t;
using boost::int64_t;
#endif

// should be a singleton instance of a factory
QWidget * ::corbasim::gui::createWidget(
        TypeDescriptor_ptr reflective,
        QWidget * parent)
{
    using namespace corbasim::core;

    WidgetFactory_t factory = createWidget;

    if (!reflective)
        return new QLabel("Null reflective type!", parent);

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            return new BoolWidget(reflective, parent);

            // Integer types
        case TYPE_OCTET:
        case TYPE_CHAR:
        case TYPE_SHORT:
        case TYPE_USHORT:
        case TYPE_LONG:
        case TYPE_ULONG:
        case TYPE_LONGLONG:
        case TYPE_ULONGLONG:
            return new IntegerWidget(reflective, parent);
        
        case TYPE_STRING:
        case TYPE_WSTRING:
            return new StringWidget(reflective, parent);

        case TYPE_OBJREF:
            return new ObjrefvarWidget(reflective, parent);

        case TYPE_UNION:
            return new UnionWidget(reflective, factory, parent);

        case TYPE_ARRAY:
        case TYPE_SEQUENCE:

            if (reflective->get_slice()->is_primitive())
            {
                AlternativesWidget * alt = 
                    new AlternativesWidget(reflective, parent);

                alt->addAlternative("W", "", 
                        new SequenceWidget(reflective, parent));

                alt->addAlternative("F", "", 
                        new FilesWidget(reflective, parent));

                return alt;
            }

            return new ComplexSequenceWidget(reflective, factory, parent);

        case TYPE_DOUBLE:
        case TYPE_FLOAT:
            return new FloatWidget(reflective, parent);
        case TYPE_STRUCT:
            return new StructWidget(reflective, factory, parent);
        case TYPE_ENUM:
            return new EnumWidget(reflective, parent);
        default:
            break;
    }

    return new QLabel("Unsupported item!", parent);
}

QWidget * ::corbasim::gui::createSimpleWidget(
        TypeDescriptor_ptr reflective,
        QWidget * parent)
{
    using namespace corbasim::core;

    WidgetFactory_t factory = createSimpleWidget;

    if (!reflective)
        return new QLabel("Null reflective type!", parent);

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            return new BoolWidget(reflective, parent);

            // Integer types
        case TYPE_OCTET:
        case TYPE_CHAR:
        case TYPE_SHORT:
        case TYPE_USHORT:
        case TYPE_LONG:
        case TYPE_ULONG:
        case TYPE_LONGLONG:
        case TYPE_ULONGLONG:
            return new IntegerWidget(reflective, parent);
        
        case TYPE_STRING:
        case TYPE_WSTRING:
            return new StringWidget(reflective, parent);

        case TYPE_OBJREF:
            return new ObjrefvarWidget(reflective, parent);

        case TYPE_UNION:
            return new UnionWidget(reflective, factory, parent);

        case TYPE_ARRAY:
        case TYPE_SEQUENCE:

            if (reflective->get_slice()->is_primitive())
            {
                return new SequenceWidget(reflective, parent);
            }

            return new ComplexSequenceWidget(reflective, factory, parent);

        case TYPE_DOUBLE:
        case TYPE_FLOAT:
            return new FloatWidget(reflective, parent);
        case TYPE_STRUCT:
            return new StructWidget(reflective, factory, parent);
        case TYPE_ENUM:
            return new EnumWidget(reflective, parent);
        default:
            break;
    }

    return new QLabel("Unsupported item!", parent);
}

// Widget base

ReflectiveWidgetBase::ReflectiveWidgetBase(
	TypeDescriptor_ptr reflective) :
    m_reflective(reflective)
{
}

ReflectiveWidgetBase::~ReflectiveWidgetBase()
{
}

TypeDescriptor_ptr 
ReflectiveWidgetBase::getReflective() const
{
    return m_reflective;
}

// Alternatives widget
    
AlternativesWidget::AlternativesWidget(
        TypeDescriptor_ptr reflective,
        QWidget * parent) :
    QWidget(parent), ReflectiveWidgetBase(reflective), m_group(this)
{
    m_group.setExclusive(true);

    QHBoxLayout * layout = new QHBoxLayout();

    m_stack = new QStackedWidget();
    layout->addWidget(m_stack);

    m_btnLayout = new QVBoxLayout();
    QSpacerItem * spacer = new QSpacerItem(20, 20, 
            QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_btnLayout->addSpacerItem(spacer);
    layout->addLayout(m_btnLayout);

    layout->setMargin(0);
    setLayout(layout);

    connect(&m_group, SIGNAL(buttonClicked(int)), 
            this, SLOT(changeWidget(int)));
}

AlternativesWidget::~AlternativesWidget()
{
}

void AlternativesWidget::setSelectionIndex(int index)
{
    m_stack->setCurrentIndex(index);
}

int AlternativesWidget::selectionIndex() const
{
    return m_stack->currentIndex();
}

void AlternativesWidget::toHolder(Holder& holder) 
{
    if (!m_widgets.empty())
        m_widgets[m_stack->currentIndex()]->toHolder(holder);
}

void AlternativesWidget::fromHolder(Holder& holder)
{
    for (unsigned int i = 0; i < m_widgets.size(); i++) 
    {
        m_widgets[i]->fromHolder(holder);
    }    
}

void AlternativesWidget::addAlternative(const QString& id,
        const QString& toolTip,
        ReflectiveWidgetBase * widget)
{
    QPushButton * btn = new QPushButton(id);

    btn->setToolTip(toolTip);
    btn->setCheckable(true);
    btn->setMaximumSize(20, 20);
    btn->setFlat(true);
    // before the spacer
    m_btnLayout->insertWidget(m_btnLayout->count() - 1, btn);

    if (m_widgets.empty()) btn->setChecked(true);

    m_group.addButton(btn, m_widgets.size());

    m_stack->addWidget(dynamic_cast< QWidget * >(widget));
    m_widgets.push_back(widget);
}

void AlternativesWidget::changeWidget(int idx)
{
    m_stack->setCurrentIndex(idx);
}

// Float widget

FloatWidget::FloatWidget(TypeDescriptor_ptr reflective,
        QWidget * parent) :
    QDoubleSpinBox(parent), ReflectiveWidgetBase(reflective)
{
    using namespace corbasim::core;

    setDecimals(10);

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_DOUBLE:
            setRange(-std::numeric_limits< double >::max(),
                    std::numeric_limits< double >::max());
            break;
        case TYPE_FLOAT:
            setRange(-std::numeric_limits< float >::max(),
                    std::numeric_limits< float >::max());
            break;
        default:
            break;
    }
}

FloatWidget::~FloatWidget()
{
}

void FloatWidget::toHolder(Holder& holder) 
{
    using namespace corbasim::core;

    const reflective_type type = m_reflective->get_type();

    double value_ = value();

    switch(type)
    {
        case TYPE_DOUBLE:
            holder.to_value< double >() = (double) value_;
            break;
        case TYPE_FLOAT:
            holder.to_value< float >() = (float) value_;
            break;
        default:
            break;
    }
}

void FloatWidget::fromHolder(Holder& holder)
{
    using namespace corbasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_DOUBLE:
            setValue(holder.to_value< double >());
            break;
        case TYPE_FLOAT:
            setValue(holder.to_value< float >());
            break;
        default:
            break;
    }
}

// Integer widget

IntegerWidget::IntegerWidget(TypeDescriptor_ptr reflective,
        QWidget * parent) :
    QSpinBox(parent), ReflectiveWidgetBase(reflective)
{
    using namespace corbasim::core;

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_OCTET:
            setRange(std::numeric_limits< unsigned char >::min(),
                    std::numeric_limits< unsigned char >::max());
            break;
        case TYPE_CHAR:
            setRange(std::numeric_limits< char >::min(),
                    std::numeric_limits< char >::max());
            break;
        case TYPE_SHORT:
            setRange(std::numeric_limits< short >::min(),
                    std::numeric_limits< short >::max());
            break;
        case TYPE_USHORT:
            setRange(std::numeric_limits< unsigned short >::min(),
                    std::numeric_limits< unsigned short >::max());
            break;
        case TYPE_LONG:
            setRange(std::numeric_limits< int32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
            // TODO custom widget
        case TYPE_ULONG:
            setRange(std::numeric_limits< uint32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
        case TYPE_LONGLONG:
            setRange(std::numeric_limits< int32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
        case TYPE_ULONGLONG:
            setRange(std::numeric_limits< uint32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
        default:
            break;
    }
}

IntegerWidget::~IntegerWidget()
{
}

void IntegerWidget::toHolder(Holder& holder) 
{
    using namespace corbasim::core;

    const reflective_type type = m_reflective->get_type();

    int value_ = value();

    switch(type)
    {
        case TYPE_OCTET:
            holder.to_value< unsigned char >() = (unsigned char) value_;
            break;
        case TYPE_CHAR:
            holder.to_value< char >() = (char) value_;
            break;
        case TYPE_SHORT:
            holder.to_value< short >() = (short) value_;
            break;
        case TYPE_USHORT:
            holder.to_value< unsigned short >() = (unsigned short) value_;
            break;
        case TYPE_LONG:
            holder.to_value< int32_t >() = (int32_t) value_;
            break;
        case TYPE_ULONG:
            holder.to_value< uint32_t >() = (uint32_t) value_;
            break;
        case TYPE_LONGLONG:
            holder.to_value< int64_t >() = (int64_t) value_;
            break;
        case TYPE_ULONGLONG:
            holder.to_value< uint64_t >() = (uint64_t) value_;
            break;
        default:
            break;
    }
}

void IntegerWidget::fromHolder(Holder& holder)
{
    using namespace corbasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_OCTET:
            setValue(holder.to_value< unsigned char >());
            break;
        case TYPE_CHAR:
            setValue(holder.to_value< char >());
            break;
        case TYPE_SHORT:
            setValue(holder.to_value< short >());
            break;
        case TYPE_USHORT:
            setValue(holder.to_value< unsigned short >());
            break;
        case TYPE_LONG:
            setValue(holder.to_value< int32_t >());
            break;
        case TYPE_ULONG:
            setValue(holder.to_value< uint32_t >());
            break;
        case TYPE_LONGLONG:
            setValue(holder.to_value< int64_t >());
            break;
        case TYPE_ULONGLONG:
            setValue(holder.to_value< uint64_t >());
            break;
        default:
            break;
    }
}

// String Widget

StringWidget::StringWidget(TypeDescriptor_ptr reflective,
        QWidget * parent) :
    QLineEdit(parent), ReflectiveWidgetBase(reflective)
{
}

StringWidget::~StringWidget()
{
}

void StringWidget::toHolder(Holder& holder)
{
    m_reflective->from_string(holder, text().toStdString());
}

void StringWidget::fromHolder(Holder& holder)
{
    const std::string str(m_reflective->to_string(holder));
    setText(str.c_str());
}

QString StringWidget::value() const 
{
    return text();
}

void StringWidget::setValue(const QString& value) 
{
    setText(value);
}

// Enum Widget

EnumWidget::EnumWidget(TypeDescriptor_ptr reflective,
        QWidget * parent) :
    QComboBox(parent), ReflectiveWidgetBase(reflective)
{
    assert(reflective->is_enum());

    unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        addItem(reflective->get_child_name(i));
    }
}

EnumWidget::~EnumWidget()
{
}

void EnumWidget::toHolder(Holder& holder) 
{
    holder.to_value< int32_t >() = currentIndex();
}

void EnumWidget::fromHolder(Holder& holder)
{
    int idx = holder.to_value< int32_t >();

    if (idx > -1 && idx < count())
    {
        setCurrentIndex(idx);
    }
}

BoolWidget::BoolWidget(TypeDescriptor_ptr reflective,
        QWidget * parent) :
    QCheckBox(parent), ReflectiveWidgetBase(reflective)
{
}

BoolWidget::~BoolWidget()
{
}

void BoolWidget::toHolder(Holder& holder) 
{
    using namespace corbasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            holder.to_value< bool >() = isChecked();
            break;
        default:
            break;
    }
}

void BoolWidget::fromHolder(Holder& holder)
{
    using namespace corbasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            setChecked(holder.to_value< bool >());
            break;
        default:
            break;
    }
}

StructWidget::StructWidget(
        TypeDescriptor_ptr reflective,
        WidgetFactory_t factory,
        QWidget * parent) :
    qt::FormWidget(parent), ReflectiveWidgetBase(reflective)
{
    assert(reflective->get_type() == core::TYPE_STRUCT);

    unsigned int count = reflective->get_children_count();

    m_widgets.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        core::reflective_base const * child = 
            reflective->get_child(i);

        const char * child_name = reflective->get_child_name(i);

        QWidget * child_widget = factory(child, this);

        m_widgets[i] = dynamic_cast< ReflectiveWidgetBase* >(
                child_widget);

        child_widget->setObjectName(child_name);

        if (child->is_primitive() || child->is_enum())
        {
            addField(child_name, child_widget);
        }
        else
        {
            addBigField(child_name, child_widget);
        }
    }
}

StructWidget::~StructWidget()
{
}

void StructWidget::toHolder(Holder& holder) 
{
    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            Holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->toHolder(child_holder);
        }
    }
}

void StructWidget::fromHolder(Holder& holder)
{
    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            Holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->fromHolder(child_holder);
        }
    }
}

void StructWidget::setValue(const QVariant& var)
{
    Holder h = m_reflective->create_holder();

    if (fromQVariant(m_reflective, h, var))
    {
        fromHolder(h);
    }
}

QVariant StructWidget::value() 
{
    Holder h = m_reflective->create_holder();
    toHolder(h);
    return toQVariant(m_reflective, h);
}

UnionWidget::UnionWidget(
        TypeDescriptor_ptr reflective,
        WidgetFactory_t factory,
        QWidget * parent) :
    QWidget(parent), ReflectiveWidgetBase(reflective)
{
    assert(reflective->get_type() == core::TYPE_UNION);

    QGridLayout * layout = new QGridLayout(this);

    unsigned int count = reflective->get_children_count();

    m_widgets.resize(count, NULL);

    // discriminator
    {
        const char * child_name = reflective->get_child_name(0);

        core::reflective_base const * child = reflective->get_child(0);

        QWidget * child_widget = factory(child, this);
        
        child_widget->setObjectName(child_name);

        m_widgets[0] = 
            dynamic_cast< ReflectiveWidgetBase* >(child_widget);

        child_widget->setObjectName(child_name);

        layout->addWidget(new QLabel(child_name), 0, 0);
        layout->addWidget(child_widget, 0, 1);

        if (qobject_cast< QComboBox * >(child_widget))
        {
            connect(child_widget, 
                    SIGNAL(currentIndexChanged(int)),
                    this,
                    SLOT(discriminatorChanged()));
        }
        else if (qobject_cast< QSpinBox * >(child_widget))
        {
            connect(child_widget, 
                    SIGNAL(valueChanged(int)),
                    this,
                    SLOT(discriminatorChanged()));
        }
        else if (qobject_cast< QDoubleSpinBox * >(child_widget))
        {
            connect(child_widget, 
                    SIGNAL(valueChanged(double)),
                    this,
                    SLOT(discriminatorChanged()));
        }
        else if (qobject_cast< QCheckBox * >(child_widget))
        {
            connect(child_widget, 
                    SIGNAL(stateChanged(int)),
                    this,
                    SLOT(discriminatorChanged()));
        }
    }

    m_stack = new QStackedWidget();
    layout->addWidget(m_stack, 1, 0, 1, 2);

    m_stack->addWidget(new QWidget()); // empty widget

    for (unsigned int i = 1; i < count; i++) 
    {
        core::reflective_base const * child = 
            reflective->get_child(i);

        const char * child_name = reflective->get_child_name(i);

        QWidget * child_widget = factory(child, this);

        m_widgets[i] = dynamic_cast< ReflectiveWidgetBase* >(
                child_widget);

        child_widget->setObjectName(child_name);

        qt::FormWidget * form = new qt::FormWidget(this);

        if (child->is_primitive() || child->is_enum())
        {
            form->addField(child_name, child_widget);
        }
        else
        {
            form->addBigField(child_name, child_widget);
        }

        m_stack->addWidget(form);
    }

    setLayout(layout);

    discriminatorChanged();
}

UnionWidget::~UnionWidget()
{
}

void UnionWidget::discriminatorChanged()
{
    core::reflective_base const * _dr = m_widgets[0]->getReflective();

    Holder _d = _dr->create_holder();
    Holder _this = m_reflective->create_holder();

    m_widgets[0]->toHolder(_d);

    m_reflective->set_child_value(_this, 0, _d);

    // 0 for invalid widget/value
    unsigned int page = m_reflective->get_length(_this);
    m_stack->setCurrentIndex(page);
}

void UnionWidget::toHolder(Holder& holder) 
{
    core::reflective_base const * _dr = m_widgets[0]->getReflective();

    Holder _d = _dr->create_holder();
    m_widgets[0]->toHolder(_d);

    m_reflective->set_child_value(holder, 0, _d);

    // 0 for invalid widget/value
    unsigned int idx = m_reflective->get_length(holder);
    // int idx = m_stack->currentIndex();

    if (idx > 0)
    {
        core::reflective_base const * _chr = m_widgets[idx]->getReflective();

        Holder _ch = _chr->create_holder();
        m_widgets[idx]->toHolder(_ch);
       
        m_reflective->set_child_value(holder, idx, _ch);
    }

    m_reflective->set_child_value(holder, 0, _d);
}

void UnionWidget::fromHolder(Holder& holder)
{
    Holder _d = m_reflective->get_child_value(holder, 0);

    m_widgets[0]->fromHolder(_d);

    unsigned int idx = m_reflective->get_length(holder);
    m_stack->setCurrentIndex(idx);

    if (idx > 0)
    {
        Holder ch = m_reflective->get_child_value(holder, idx);

        m_widgets[idx]->fromHolder(ch);
    }
}

SequenceWidget::SequenceWidget(
        TypeDescriptor_ptr reflective,
        QWidget * parent) :
    QWidget(parent), ReflectiveWidgetBase(reflective), 
    m_sbLength(NULL), m_sbCurrentIndex(NULL)
{
    QVBoxLayout * layout = new QVBoxLayout;
 
    QHBoxLayout * headerLayout = new QHBoxLayout;

    m_sbLength = new QSpinBox();
    headerLayout->addWidget(new QLabel("Length"));
    headerLayout->addWidget(m_sbLength);
    m_sbLength->setObjectName("length");

    m_sbCurrentIndex = new QSpinBox();
    headerLayout->addWidget(new QLabel("Index"));
    headerLayout->addWidget(m_sbCurrentIndex);
    m_sbCurrentIndex->setObjectName("index");

    layout->addLayout(headerLayout);

    m_holder = reflective->create_holder();

    m_slice_widget = createWidget(reflective->get_slice(), this);
    
    layout->addWidget(m_slice_widget);

    m_slice = dynamic_cast< ReflectiveWidgetBase * >(m_slice_widget);

    // Spacer
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addItem(spacer);

    setLayout(layout);

    if (reflective->is_variable_length())
    {
        connect(m_sbLength, SIGNAL(valueChanged(int)),
                this, SLOT(lengthChanged(int)));

        // TODO maximo razonable
        m_sbLength->setRange(0, 9999999);
        m_sbLength->setValue(0);
        m_sbCurrentIndex->setReadOnly(true);
        m_slice_widget->setEnabled(false);
    }
    else
    {
        Holder holder = m_reflective->create_holder();
        unsigned int length = m_reflective->get_length(holder);

        // Fixed length
        m_sbLength->setRange(0, length);
        m_sbLength->setValue(length);
        m_sbLength->setReadOnly(true);

        m_sbCurrentIndex->setRange(0, length - 1);
        indexChanged(0);
    }

    connect(m_sbCurrentIndex, SIGNAL(valueChanged(int)),
            this, SLOT(indexChanged(int)));

    if (dynamic_cast< QComboBox * >(m_slice_widget))
    {
        connect(m_slice_widget, SIGNAL(currentIndexChanged(int)),
                this, SLOT(saveCurrent()));
    }
    else if (dynamic_cast< QCheckBox * >(m_slice_widget))
    {
        connect(m_slice_widget, SIGNAL(stateChanged(int)),
                this, SLOT(saveCurrent()));
    }
    else
    {
        connect(m_slice_widget, SIGNAL(editingFinished()),
                this, SLOT(saveCurrent()));
    }

    saveCurrent();
}

SequenceWidget::~SequenceWidget()
{
}

void SequenceWidget::setValue(const QVariant& var)
{
    Holder h = m_reflective->create_holder();

    if (fromQVariant(m_reflective, h, var))
    {
        fromHolder(h);
    }
}

QVariant SequenceWidget::value() const
{
    Holder h = m_reflective->create_holder();
    m_reflective->copy(m_holder, h);

    return toQVariant(m_reflective, h);
}

void SequenceWidget::toHolder(Holder& holder)
{
    m_reflective->copy(m_holder, holder);
}

void SequenceWidget::fromHolder(Holder& holder)
{
    m_reflective->copy(holder, m_holder);

    if (m_reflective->is_variable_length())
    {
        // show current value
        m_sbLength->setValue(m_reflective->get_length(m_holder));
    }

    // Reload current value
    indexChanged(m_sbCurrentIndex->value());
}

void SequenceWidget::lengthChanged(int len)
{
    if (!m_reflective->is_variable_length())
        return;

    unsigned int oldLength = m_reflective->get_length(m_holder);

    if (len != 0)
    {
        m_sbCurrentIndex->setRange(0, len-1);
    }

    m_reflective->set_length(m_holder, len);

    m_sbCurrentIndex->setReadOnly(len == 0);
    m_slice_widget->setEnabled(len != 0);

    // Reload current value
    if (!oldLength && len)
    {
        indexChanged(m_sbCurrentIndex->value());
    }
}

void SequenceWidget::indexChanged(int idx)
{
    unsigned int length = m_reflective->get_length(m_holder);

    if (length && idx < (int) length)
    {
        core::holder child_value = 
            m_reflective->get_child_value(m_holder, (unsigned int) idx);

        m_slice->fromHolder(child_value);
    }
}

void SequenceWidget::saveCurrent()
{
    unsigned int length = m_reflective->get_length(m_holder);
    int index = m_sbCurrentIndex->value();

    if (length && index < (int) length)
    {
        core::holder child_value = m_reflective->get_child_value(
                m_holder, index);
        m_slice->toHolder(child_value);
    }
}

// Complex Sequence Widget

ComplexSequenceWidget::ComplexSequenceWidget(
        TypeDescriptor_ptr reflective,
        WidgetFactory_t factory,
        QWidget * parent) :
    QWidget(parent), ReflectiveWidgetBase(reflective), 
    m_factory(factory),
    m_sbLength(NULL), m_sbCurrentIndex(NULL)
{
    QVBoxLayout * layout = new QVBoxLayout;
 
    QHBoxLayout * headerLayout = new QHBoxLayout;

    // Read only for fixed length types
    m_sbLength = new QSpinBox();
    headerLayout->addWidget(new QLabel("Length"));
    headerLayout->addWidget(m_sbLength);
    m_sbLength->setObjectName("length");

    m_sbCurrentIndex = new QSpinBox();
    headerLayout->addWidget(new QLabel("Index"));
    headerLayout->addWidget(m_sbCurrentIndex);
    m_sbCurrentIndex->setObjectName("index");

    layout->addLayout(headerLayout);

    m_stack = new QStackedWidget();
    layout->addWidget(m_stack);

    // Spacer
    /*
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addItem(spacer);
    */

    setLayout(layout);

    if (reflective->is_variable_length())
    {
        connect(m_sbLength, SIGNAL(valueChanged(int)),
                this, SLOT(lengthChanged(int)));

        // TODO maximo razonable
        m_sbLength->setRange(0, 99999);
        m_sbLength->setValue(0);
    }
    else
    {
        Holder holder = m_reflective->create_holder();
        unsigned int length = m_reflective->get_length(holder);

        // Fixed length
        m_sbLength->setRange(0, length);
        m_sbLength->setValue(length);
        m_sbLength->setReadOnly(true);

        for (unsigned int i = 0; i < length; i++) 
        {
            m_stack->addWidget(factory(reflective->get_slice(), this));
        }

        m_sbCurrentIndex->setRange(0, length - 1);

        indexChanged(0);
    }

    connect(m_sbCurrentIndex, SIGNAL(valueChanged(int)),
            this, SLOT(indexChanged(int)));
}

ComplexSequenceWidget::~ComplexSequenceWidget()
{
}

void ComplexSequenceWidget::toHolder(Holder& holder)
{
    unsigned int len = 0;

    if (m_reflective->is_variable_length())
    {
        len = (unsigned int) m_sbLength->value();

        m_reflective->set_length(holder, len);
    }
    else
    {
        len = m_reflective->get_length(holder);
    }

    for (unsigned int i = 0; i < len; i++) 
    {
        Holder child_value = m_reflective->get_child_value(holder, i);

        ReflectiveWidgetBase * w = 
            dynamic_cast< ReflectiveWidgetBase * >(m_stack->widget(i));

        if (w) w->toHolder(child_value);
    }
}

void ComplexSequenceWidget::fromHolder(Holder& holder)
{
    unsigned int len = m_reflective->get_length(holder);

    if (m_reflective->is_variable_length())
    {
        m_sbLength->setValue(len);
    }

    for (unsigned int i = 0; i < len; i++) 
    {
        Holder child_value = m_reflective->get_child_value(holder, i);

        ReflectiveWidgetBase * w = 
            dynamic_cast< ReflectiveWidgetBase * >(m_stack->widget(i));

        if (w) w->fromHolder(child_value);
    }
}

void ComplexSequenceWidget::lengthChanged(int len)
{
    if (!m_reflective->is_variable_length())
        return;

    if (len == 0)
        m_stack->hide();
    else
        m_stack->show();

    int diff = len - m_stack->count();

    for (int i = 0; i < diff; i++) 
    {
        m_stack->addWidget(m_factory(m_reflective->get_slice(), this));
    }

    m_sbCurrentIndex->setRange(0, len-1);
}

void ComplexSequenceWidget::indexChanged(int idx)
{
    m_stack->setCurrentIndex(idx);
}

ObjrefvarWidget::ObjrefvarWidget(
        TypeDescriptor_ptr reflective,
        QWidget * parent) :
    ObjrefWidget(0, parent), ReflectiveWidgetBase(reflective)
{
    // set validator
    core::objrefvar_reflective_base const * ref = 
        static_cast< core::objrefvar_reflective_base const * >(m_reflective);

    setValidator(core::reference_validator_ptr(ref->create_validator()));
}

ObjrefvarWidget::~ObjrefvarWidget()
{
}

void ObjrefvarWidget::toHolder(Holder& holder) 
{
    core::objrefvar_reflective_base const * ref = 
        static_cast< core::objrefvar_reflective_base const * >(m_reflective);

    ref->from_object(holder, reference());
}

void ObjrefvarWidget::fromHolder(Holder& holder)
{
    core::objrefvar_reflective_base const * ref = 
        static_cast< core::objrefvar_reflective_base const * >(m_reflective);

    CORBA::Object_var obj = ref->to_object(holder);

    setReference(obj);
}

// Files

FilesWidget::FilesWidget(TypeDescriptor_ptr reflective,
        QWidget * parent) :
    corbasim::qt::MultiFileSelectionWidget(parent), 
    ReflectiveWidgetBase(reflective)
{
}

FilesWidget::~FilesWidget()
{
}

namespace  
{

void fromFile(const std::string& file, 
        TypeDescriptor_ptr seq,
        Holder& h)
{
    using namespace corbasim::core;

    std::ifstream ifs(file.c_str(), 
            std::ios::in | std::ios::binary);

    const file_format_factory * factory = 
        file_format_factory::get_instance();

    const file_format_helper * helper =
        factory->get_helper(FILE_FORMAT_BINARY);

    helper->load(ifs, seq, h);
}

} // namespace 

void FilesWidget::toHolder(Holder& holder) 
{
    const QString * nextFile = getNext();

    if (nextFile)
    {
        ::fromFile(nextFile->toStdString(), m_reflective, holder);
    }
}

void FilesWidget::fromHolder(Holder& holder)
{
    // does nothing...
}

OperationInputForm::OperationInputForm(
        OperationDescriptor_ptr reflective,
        QWidget * parent) :
    QWidget(parent), m_reflective(reflective)
{
    QVBoxLayout * mlayout = new QVBoxLayout();

    const unsigned int count = reflective->get_children_count();

    qt::FormWidget * form = new qt::FormWidget(this);

    m_widgets.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        const core::direction_type type = 
            reflective->get_parameter_direction(i);

        if (type == core::DIRECTION_IN || type == core::DIRECTION_INOUT)
        {
            core::reflective_base const * child = 
                reflective->get_child(i);

            const char * child_name = reflective->get_child_name(i);

            QWidget * child_widget = createWidget(child, this);

            m_widgets[i] = dynamic_cast< ReflectiveWidgetBase* >(
                    child_widget);

            child_widget->setObjectName(child_name);

            if (child->is_primitive() || child->is_enum())
            {
                form->addField(child_name, child_widget);
            }
            else
            {
                form->addBigField(child_name, child_widget);
            }
        }
    }

    mlayout->addWidget(form);

#ifdef CORBASIM_USE_QTSCRIPT
    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    m_tabs = new qt::TabWidget();
    QWidget * w = new QWidget();
    w->setLayout(mlayout);
    m_tabs->addTab(w, "Form");

    m_code = new qt::priv::ScriptEditor();
    m_tabs->addTab(m_code, "Script");

    mainLayout->addWidget(m_tabs);
    mlayout = mainLayout;

    m_thisObject = m_engine.newQObject(this);
    reloadScript();

    // reload button
    QTabBar * tabBar = m_tabs->tabBar();
    QPushButton* button = new QPushButton();
    button->setIcon(
            style()->standardIcon(QStyle::SP_DialogApplyButton)); 
    button->setIconSize(QSize(16, 16));
    button->resize(20, 20);
    tabBar->setTabButton(1, QTabBar::LeftSide, button);

    connect(button, SIGNAL(clicked()),
            this, SLOT(reloadScript()));

#endif

    setLayout(mlayout);

    setAcceptDrops(true);
}

OperationInputForm::~OperationInputForm()
{
}

void OperationInputForm::setValue(const QVariant& var)
{
    Request_ptr req = m_reflective->create_request();
    Holder h = m_reflective->get_holder(req);

    if (fromQVariant(m_reflective, h, var))
    {
        setValue(req);
    }
}

QVariant OperationInputForm::value()
{
    Request_ptr req (m_reflective->create_request());
    Holder holder(m_reflective->get_holder(req));

    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            Holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->toHolder(child_holder);
        }
    }

    return toQVariant(m_reflective, holder);
}

OperationDescriptor_ptr 
OperationInputForm::getReflective() const
{
    return m_reflective;
}

Request_ptr OperationInputForm::createRequest()
{
#ifdef CORBASIM_USE_QTSCRIPT
    if (m_preFunc.isFunction())
    {
        m_preFunc.call(m_thisObject);
    }
#endif /* CORBASIM_USE_QTSCRIPT*/

    Request_ptr req (m_reflective->create_request());
    Holder holder(m_reflective->get_holder(req));

    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            Holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->toHolder(child_holder);
        }
    }

#ifdef CORBASIM_USE_QTSCRIPT
    if (m_postFunc.isFunction())
    {
        m_postFunc.call(m_thisObject);
    }
#endif /* CORBASIM_USE_QTSCRIPT*/

    return req;
}

void OperationInputForm::setValue(Request_ptr req)
{
    Holder holder(m_reflective->get_holder(req));

    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            Holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->fromHolder(child_holder);
        }
    }
}
#ifdef CORBASIM_USE_QTSCRIPT
void OperationInputForm::reloadScript()
{
    const QString strProgram (m_code->toPlainText());
    if (!m_engine.canEvaluate(strProgram))
    {
        std::cerr << "Could not evaluate program!" << std::endl;
        return;
    }

    m_engine.evaluate(strProgram, QString(
                m_reflective->get_name())+ ".js");

    if (m_engine.hasUncaughtException())
    {
        QString error = QString("%1\n\n%2")
            .arg(m_engine.uncaughtException().toString())
            .arg(m_engine.uncaughtExceptionBacktrace().join("\n"));

        QMessageBox::critical(this, "Error", error);
        return;
    }

    m_initFunc = m_engine.evaluate("init");
    m_preFunc = m_engine.evaluate("pre");
    m_postFunc = m_engine.evaluate("post");
    
    if (m_initFunc.isFunction())
        m_initFunc.call(m_thisObject);

}
#endif /* CORBASIM_USE_QTSCRIPT*/

void OperationInputForm::dragLeaveEvent(QDragLeaveEvent *event)
{
}

void OperationInputForm::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
        event->acceptProposedAction();
    }
}

void OperationInputForm::dropEvent(QDropEvent *event)
{
    const std::string str = event->mimeData()->text().toStdString();

    try 
    {
        Request_ptr req = m_reflective->create_request();
        Holder holder = m_reflective->get_holder(req);

        bool res = json::parse(m_reflective, holder, 
                str.c_str(), str.size());

        if (res)
        {
            setValue(req);
            event->acceptProposedAction();
        }
    } 
    catch(...) 
    {
    }
}

void OperationInputForm::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_dragStartPosition = event->pos();
}

void OperationInputForm::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - m_dragStartPosition).manhattanLength()
            < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    std::ostringstream oss;
    Request_ptr req = createRequest();
    
    Holder holder = m_reflective->get_holder(req);

    json::write(oss, m_reflective, holder);

    mimeData->setText(oss.str().c_str());
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
}

// Settings

void AlternativesWidget::save(QVariant& settings)
{
    QVariantMap map;
    QVariantList list;

    map["index"] = m_stack->currentIndex();

    for (unsigned int i = 0; i < m_widgets.size(); i++) 
    {
        if (m_widgets[i]) 
        {
            QVariant ch;
            m_widgets[i]->save(ch);
            list << ch;
        }
    }

    map["alternatives"] = list;
    settings = map;
}

void AlternativesWidget::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    if (map.contains("index"))
    {
        int idx = map.value("index").toInt();

        if (idx < m_stack->count())
        {
            m_group.button(idx)->setChecked(true);
            m_stack->setCurrentIndex(idx);
        }
    }

    if (map.contains("alternatives"))
    {
        const QVariantList list = map.value("alternatives").toList();

        int j = 0;
        for (unsigned int i = 0; i < m_widgets.size() && 
                j < list.size(); i++) 
        {
            if (m_widgets[i]) 
            {
                m_widgets[i]->load(list.at(j++));
            }
        }
    }
}

void FloatWidget::save(QVariant& settings)
{
    settings = value();
}

void FloatWidget::load(const QVariant& settings)
{
    if (settings.canConvert< double >())
    {
        setValue(settings.toDouble());
    }
}

void IntegerWidget::save(QVariant& settings)
{
    settings = value();
}

void IntegerWidget::load(const QVariant& settings)
{
    if (settings.canConvert< int >())
    {
        setValue(settings.toInt());
    }
}

void StringWidget::save(QVariant& settings)
{
    settings = text();
}

void StringWidget::load(const QVariant& settings)
{
    if (settings.canConvert< QString >())
    {
        setText(settings.toString());
    }
}

void EnumWidget::save(QVariant& settings)
{
    settings = currentText();
}

void EnumWidget::load(const QVariant& settings)
{
    if (settings.canConvert< QString >())
    {
        const QString text(settings.toString());

        // find corresponding index to convert text
        
        int idx = findText(text);

        if (idx != -1) setCurrentIndex(idx);
    }
}

void BoolWidget::save(QVariant& settings)
{
    settings = isChecked();
}

void BoolWidget::load(const QVariant& settings)
{
    if (settings.canConvert< bool >())
    {
        setChecked(settings.toBool());
    }
}

void StructWidget::save(QVariant& settings)
{
    unsigned int count = m_reflective->get_children_count();

    QVariantMap value;
    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            QVariant child;

            m_widgets[i]->save(child);

            value[m_reflective->get_child_name(i)] = child;
        }
    }

    settings = value;
}

void StructWidget::load(const QVariant& settings)
{
    const QVariantMap value = settings.toMap();

    unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            m_widgets[i]->load(
                    value[m_reflective->get_child_name(i)]);
        }
    }
}

void UnionWidget::save(QVariant& settings)
{
    unsigned int count = m_reflective->get_children_count();

    QVariantMap value;
    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            QVariant child;

            m_widgets[i]->save(child);

            value[m_reflective->get_child_name(i)] = child;
        }
    }

    settings = value;
}

void UnionWidget::load(const QVariant& settings)
{
    const QVariantMap value = settings.toMap();

    unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            m_widgets[i]->load(
                    value[m_reflective->get_child_name(i)]);
        }
    }
}

void SequenceWidget::save(QVariant& settings)
{
    QVariantMap map;

    if (m_reflective->is_variable_length())
    {
        map["length"] = m_sbLength->value();
    }

    map["index"] = m_sbCurrentIndex->value();

    map["value"] = value();

    settings = map;
}

void SequenceWidget::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    if (m_reflective->is_variable_length())
    {
        m_sbLength->setValue(map["length"].toInt());
    }

    setValue(map["value"]);

    m_sbCurrentIndex->setValue(map["index"].toInt());
}

void ComplexSequenceWidget::save(QVariant& settings)
{
    QVariantMap map;

    int length = 0;

    if (m_reflective->is_variable_length())
    {
        length = m_sbLength->value();
        map["length"] = length;
    }
    else
    {
        Holder h;
        length = (int) m_reflective->get_length(h);
    }

    map["index"] = m_sbCurrentIndex->value();

    QVariantList list;

    for(int i = 0; i < length; i++)
    {
        ReflectiveWidgetBase * w = 
            dynamic_cast< ReflectiveWidgetBase * >(m_stack->widget(i));

        if (w)
        {
            QVariant v;
            w->save(v);
            list << v;
        }
    }

    map["sequence"] = list;

    settings = map;
}

void ComplexSequenceWidget::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

    int length = 0;

    if (m_reflective->is_variable_length())
    {
        length = map["length"].toInt();
        m_sbLength->setValue(length);
    }
    else
    {
        Holder h;
        length = (int) m_reflective->get_length(h);
    }

    m_sbCurrentIndex->setValue(map["index"].toInt());

    const QVariantList list = map["sequence"].toList();

    for(int i = 0; i < list.size() && i < length; i++)
    {
        ReflectiveWidgetBase * w = 
            dynamic_cast< ReflectiveWidgetBase * >(m_stack->widget(i));

        if (w) w->load(list.at(i));
    }
}

void ObjrefvarWidget::save(QVariant& settings)
{
    ObjrefWidget::save(settings);
}

void ObjrefvarWidget::load(const QVariant& settings)
{
    ObjrefWidget::load(settings);
}

void FilesWidget::save(QVariant& settings)
{
    MultiFileSelectionWidget::save(settings);
}

void FilesWidget::load(const QVariant& settings)
{
    MultiFileSelectionWidget::load(settings);
}

void OperationInputForm::save(QVariant& settings)
{
    QVariantMap map; 
    unsigned int count = m_reflective->get_children_count();

#ifdef CORBASIM_USE_QTSCRIPT
    map["script"] = m_code->toPlainText();
#endif /* CORBASIM_USE_QTSCRIPT*/

    QVariantMap value;
    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            QVariant child;

            m_widgets[i]->save(child);

            value[m_reflective->get_child_name(i)] = child;
        }
    }

    map["value"] = value;

    settings = map;
}

void OperationInputForm::load(const QVariant& settings)
{
    const QVariantMap map = settings.toMap();

#ifdef CORBASIM_USE_QTSCRIPT
    if (map.contains("script"))
    {
        m_code->setPlainText(map.value("script").toString());
        reloadScript();
    }
#endif /* CORBASIM_USE_QTSCRIPT*/

    if (map.contains("value"))
    {
        unsigned int count = m_reflective->get_children_count();

        const QVariantMap value = map.value("value").toMap();

        for (unsigned int i = 0; i < count; i++) 
        {
            if (m_widgets[i])
            {
                m_widgets[i]->load(
                        value[m_reflective->get_child_name(i)]);
            }
        }
    }
}

// Read only
void ReflectiveWidgetBase::_setReadOnly(bool readOnly)
{
}

void FloatWidget::_setReadOnly(bool readOnly)
{
    setReadOnly(readOnly);
}

void IntegerWidget::_setReadOnly(bool readOnly)
{
    setReadOnly(readOnly);
}

void StringWidget::_setReadOnly(bool readOnly)
{
    setReadOnly(readOnly);
}

void EnumWidget::_setReadOnly(bool readOnly)
{
    setEnabled(!readOnly);
}

void BoolWidget::_setReadOnly(bool readOnly)
{
    setEnabled(!readOnly);
}

void StructWidget::_setReadOnly(bool readOnly)
{
    unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            m_widgets[i]->_setReadOnly(readOnly);
        }
    }
}

void ComplexSequenceWidget::_setReadOnly(bool readOnly)
{
    for (unsigned int i = 0; i < m_stack->count(); i++) 
    {
        ReflectiveWidgetBase * w = 
            dynamic_cast< ReflectiveWidgetBase * >(m_stack->widget(i));

        if (w) w->_setReadOnly(readOnly);
    }
}

void SequenceWidget::_setReadOnly(bool readOnly)
{
    m_slice->_setReadOnly(readOnly);

    if (m_reflective->is_variable_length())
    {
        m_sbLength->setReadOnly(readOnly);
    }
}

void UnionWidget::_setReadOnly(bool readOnly)
{
    // Widgets
    unsigned int count = m_widgets.size();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            m_widgets[i]->_setReadOnly(readOnly);
        }
    }
}

void ObjrefvarWidget::_setReadOnly(bool readOnly)
{
    setEnabled(!readOnly);
}

void AlternativesWidget::_setReadOnly(bool readOnly)
{
    // Widgets
    unsigned int count = m_widgets.size();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            m_widgets[i]->_setReadOnly(readOnly);
        }
    }

    // Buttons
    const QList< QAbstractButton * > buttons = m_group.buttons();

    for (int i = 0; i < buttons.size(); i++) 
    {
        buttons.at(i)->setEnabled(!readOnly);
    }
}

void OperationInputForm::_setReadOnly(bool readOnly)
{
    for (unsigned int i = 0; i < m_widgets.size(); i++) 
    {
        if (m_widgets[i])
        {
            m_widgets[i]->_setReadOnly(readOnly);
        }
    }
}


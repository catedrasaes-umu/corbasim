// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectiveGUI.hpp
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

#ifndef CORBASIM_GUI_REFLECTIVEGUI_HPP
#define CORBASIM_GUI_REFLECTIVEGUI_HPP

#include <QtGui>
#include <corbasim/core/reflective_fwd.hpp>

namespace corbasim 
{
namespace reflective_gui 
{

class FloatWidget : public QDoubleSpinBox
{
    Q_OBJECT
public:
    FloatWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~FloatWidget();

protected:
    core::reflective_base const * m_reflective;
    
};

class IntegerWidget : public QSpinBox
{
    Q_OBJECT
public:
    IntegerWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~IntegerWidget();

protected:
    core::reflective_base const * m_reflective;
    
};

class StringWidget : public QLineEdit
{
    Q_OBJECT
public:
    StringWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~StringWidget();

protected:
    core::reflective_base const * m_reflective;
    
};

class EnumWidget : public QComboBox
{
    Q_OBJECT
public:
    EnumWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~EnumWidget();

protected:
    core::reflective_base const * m_reflective;
    
};

class BoolWidget : public QCheckBox
{
    Q_OBJECT
public:
    BoolWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~BoolWidget();

protected:
    core::reflective_base const * m_reflective;
    
};

class StructWidget : public QWidget
{
    Q_OBJECT
public:
    StructWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~StructWidget();

protected:
    core::reflective_base const * m_reflective;
    
};

class SequenceWidget : public QWidget
{
    Q_OBJECT
public:
    SequenceWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~SequenceWidget();

protected slots:

    void lengthChanged(int);
    void indexChanged(int);

protected:

    typedef std::vector< QWidget* > widgets_t;

    core::reflective_base const * m_reflective;
    
    QSpinBox * m_sbLength;
    QSpinBox * m_sbCurrentIndex;

    QStackedWidget * m_stack;

    widgets_t m_widgets;
};

class ArrayWidget : public QWidget
{
    Q_OBJECT
public:
    ArrayWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~ArrayWidget();

protected slots:

    void indexChanged(int);

protected:

    typedef std::vector< QWidget* > widgets_t;

    core::reflective_base const * m_reflective;
    
    QSpinBox * m_sbCurrentIndex;

    QStackedWidget * m_stack;

    widgets_t m_widgets;
};


} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_GUI_REFLECTIVEGUI_HPP */


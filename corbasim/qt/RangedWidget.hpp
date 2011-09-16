// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RangedWidget.hpp
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

#ifndef CORBASIM_QT_RANGEDWIDGET_HPP
#define CORBASIM_QT_RANGEDWIDGET_HPP

#include <QtGui>

namespace corbasim
{
namespace qt
{

const QString OutOfRangeStyleSheet = "background-color: red";

template < typename T, typename Widget >
class RangedValueBase
{
public:
    RangedValueBase(const T min, const T max, Widget* widget) :
        m_min(min), m_max(max), m_widget(widget),
        is_in_range(is_widget_in_range()),
        m_widget_dflt_ss(m_widget->styleSheet())
    {
        if(!is_in_range)
            change_status();
    }

    //change background color
    inline void change_status()
    {
        m_widget->setStyleSheet(is_in_range? m_widget_dflt_ss : OutOfRangeStyleSheet);
    }

    inline void check_value_in_range()
    {
        const bool was_in_range = is_in_range;
        is_in_range = is_widget_in_range();

        if(was_in_range != is_in_range) // change color only if necessary
            change_status();
    }

    inline void set_valid_range(const T min, const T max)
    {
        m_min = min;
        m_max = max;
        check_value_in_range();
    }

protected:
    T m_min;
    T m_max;
    Widget* m_widget;
    bool is_in_range;
    const QString m_widget_dflt_ss;

private:
    inline bool is_widget_in_range() const
    {
        const T value = m_widget->value();
        return (m_min <= value && value <= m_max);
    }
}; // class RangedValueBase

class RangedWidget : public QSpinBox, public RangedValueBase<int, QSpinBox>
{
    Q_OBJECT

public:
    RangedWidget(const int min, const int max, QWidget * parent = 0) :
        QSpinBox(parent),
        RangedValueBase<int, QSpinBox>(min, max, this)
    {
        QObject::connect( this, SIGNAL( valueChanged ( int ) ), this, SLOT(check_widget_value_in_range()));
    }

public slots:
    void check_widget_value_in_range()
    {
        check_value_in_range();
    }

}; // class RangedWidget

class EnumRangedWidget : public QSpinBox, 
    public RangedValueBase< int, QSpinBox >
{
    Q_OBJECT

public:
    EnumRangedWidget(const int min, const int max, QWidget * parent = 0) :
        QSpinBox(parent),
        RangedValueBase< int, QSpinBox >(min, max, this)
    {
        QObject::connect(this, SIGNAL(valueChanged(int)), this, 
                SLOT(check_widget_value_in_range(int)));
    }

public slots:
    void check_widget_value_in_range(int val)
    {
        check_value_in_range();

        if (val >= 0 && val < m_values.size())
            setSuffix(m_values[val]);
        else
            setSuffix(" (invalid)");
    }

    void setValue(int val)
    {
        QSpinBox::setValue(val);

        check_widget_value_in_range(val);
    }

    void addItem(const QString& item)
    {
        m_values << QString(" (") + item + ")";
    }

protected:
    QStringList m_values;

}; // class EnumRangedWidget

class RangedDoubleWidget : public QDoubleSpinBox, public RangedValueBase<double, QDoubleSpinBox>
{
    Q_OBJECT

public:
    RangedDoubleWidget(const double min, const double max, QWidget * parent = 0) :
        QDoubleSpinBox(parent),
        RangedValueBase<double, QDoubleSpinBox>(min, max, this)
    {
        setDecimals(13); // max decimals value
        QObject::connect( this, SIGNAL( valueChanged ( double ) ), this, SLOT(check_widget_value_in_range()));
    }

public slots:
    void check_widget_value_in_range()
    {
        check_value_in_range();
    }

}; // class RangedDoubleWidget

} // qt
} // corbasim

#endif // CORBASIM_QT_RANGEDWIDGET_HPP


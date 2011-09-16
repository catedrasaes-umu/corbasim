// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TemplatedSpinBox.hpp
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

#ifndef CORBASIM_QT_TEMPLATEDSPINBOX_HPP
#define CORBASIM_QT_TEMPLATEDSPINBOX_HPP

#include <QtGui>

namespace corbasim
{
namespace qt
{

namespace traits
{
    template < typename T >
    struct value_to_QString
    {
        static inline void set(QString& qstr, T value)
        {
            qstr.setNum(value);
        }
    };

    template < typename >
    struct value_from_QString;

    // Specialization of value_from_QString with 'get' method for each type (for types whose range is out of the range of the int type)
    template < >
    struct value_from_QString < unsigned long >
    {
        typedef unsigned long type;
        static inline type get(QString value, bool * ok = 0, int base = 10)
        {
            return value.toUInt(ok, base);
        }
    };

    template < >
    struct value_from_QString < unsigned int >
    {
        typedef unsigned int type;
        static inline type get(QString value, bool * ok = 0, int base = 10)
        {
            return value.toUInt(ok, base);
        }
    };

    template < >
    struct value_from_QString < long long >
    {
        typedef long long type;
        static inline type get(QString value, bool * ok = 0, int base = 10)
        {
            return value.toLongLong(ok, base);
        }
    };

    template < >
    struct value_from_QString < unsigned long long >
    {
        typedef unsigned long long type;
        static inline type get(QString value, bool * ok = 0, int base = 10)
        {
            return value.toULongLong(ok, base);
        }
    };

    template < >
    struct value_from_QString < long >
    {
        typedef long type;
        static inline type get(QString value, bool * ok = 0, int base = 10)
        {
            return value.toInt(ok, base);
        }
    };

} // traits


template < typename T >
class TemplatedSpinBox : public QAbstractSpinBox
{
public:
    TemplatedSpinBox(const T min, const T max, QWidget * parent = 0) :
        QAbstractSpinBox(parent),
        m_min_valid(min), m_max_valid(max),
        is_in_range(true),
        m_default_ss(styleSheet()),
        m_suffix(""), m_prefix("")
    {
        setValue(0);
    }

    //change background color
    inline void change_status()
    {
        setStyleSheet(is_in_range? m_default_ss : OutOfRangeStyleSheet);
    }

    inline void check_value_in_range() // in valid range
    {
        const bool was_in_range = is_in_range;
        is_in_range = is_widget_in_range(m_min_valid, m_max_valid);

        if(was_in_range != is_in_range) // change color only if necessary
            change_status();
    }

    inline void set_valid_range(const T min, const T max)
    {
        m_min_valid = min;
        m_max_valid = max;
        check_value_in_range();
    }

    // inherited methods from QAbstractSpinBox
    virtual QValidator::State validate ( QString & input, int & pos ) const
    {
        QValidator::State state;
        validateAndInterpret(input, pos, state);

        if(state == QValidator::Acceptable) {
            const_cast<TemplatedSpinBox< T > * >(this)->check_value_in_range();
            state = is_widget_in_range(m_min, m_max)? QValidator::Acceptable : QValidator::Invalid;
        }
        return state;
    }

    void stepBy(int steps)
    {
        const T old = value();
        QString tmp = this->lineEdit()->displayText();
        int cursorPos = this->lineEdit()->cursorPosition();
        bool dontstep = false;
        dontstep = validate(tmp, cursorPos) != QValidator::Acceptable;
        if (!dontstep)
            setValue(old + steps);
        selectAll();
    }

    StepEnabled stepEnabled() const
    {
        return (QAbstractSpinBox::StepUpEnabled
                | QAbstractSpinBox::StepDownEnabled);
    }

    // common methods of QSpinBox and QDoubleSpinBox, not defined in QAbstracSpinBox
    inline T value() const
    {
        int pos = 0;
        return traits::value_from_QString< T >::get(stripped(text(), &pos));
    }

    inline void setValue(T val)
    {
        QString val_str;
        traits::value_to_QString< T >::set(val_str, val);
        lineEdit()->setText(m_prefix+val_str+m_suffix);
        check_value_in_range();
    }

    inline void setRange(T min, T max)
    {
        m_min = min;
        m_max = max;
    }

    QString suffix () const
    {
        return m_suffix;
    }
    void setSuffix ( const QString & suffix )
    {
        // update text with new suffix
        QString str = lineEdit()->text();
        QString regExp_str = m_suffix+"$";
        QRegExp regExp(regExp_str);
        str.replace(regExp_str, suffix);
        lineEdit()->setText(str);
        m_suffix = suffix;

        updateGeometry();
    }

    QString prefix() const
    {
        return m_prefix;
    }

    void setPrefix(const QString &prefix)
    {
        // update text with new prefix
        QString str = lineEdit()->text();
        QString regExp_str = m_prefix + "$";
        QRegExp regExp(regExp_str);
        str.replace(regExp_str, prefix);
        m_prefix = prefix;
        lineEdit()->setText(str);

        updateGeometry();
    }

protected:
    // valid value range
    T m_min_valid;
    T m_max_valid;
    // value range (widget input range)
    T m_min;
    T m_max;
    bool is_in_range;
    const QString m_default_ss;

    QString m_suffix;
    QString m_prefix;

private:
    inline bool is_widget_in_range(T min, T max) const
    {
        bool ok = true;
        const T value = traits::value_from_QString< T >::get(text(), &ok);
        return !ok || (min <= value && value <= max);
    }

    /*!
        \internal
        Strips any prefix/suffix from \a text.
    */
    QString stripped(const QString &t, int *pos) const
    {
        QString text = t;
        if (specialValueText().size() == 0 || text != specialValueText()) {
            int from = 0;
            int size = text.size();
            bool changed = false;
            if (m_prefix.size() && text.startsWith(m_prefix)) {
                from += m_prefix.size();
                size -= from;
                changed = true;
            }
            if (m_suffix.size() && text.endsWith(m_suffix)) {
                size -= m_suffix.size();
                changed = true;
            }
            if (changed)
                text = text.mid(from, size);
        }

        const int s = text.size();
        text = text.trimmed();
        if (pos)
            (*pos) -= (s - text.size());
        return text;

    }

    /*!
        \internal Multi purpose function that parses input, sets state to
        the appropriate state and returns the value it will be interpreted
        as.
    */
    void validateAndInterpret(QString &input, int &pos,
            QValidator::State &state) const
    {
//        if (cachedText == input && !input.isEmpty()) {
//            state = cachedState;
//
//            return cachedValue;
//        }
        const T max = m_max;
        const T min = m_min;

        QString copy = stripped(input, &pos);
        state = QValidator::Acceptable;
        T num = min;

        if (max != min && (copy.isEmpty() || (min < 0 && copy == QLatin1String(
                "-")) || (min >= 0 && copy == QLatin1String("+"))))
        {
            state = QValidator::Intermediate;
        }
        else if (copy.startsWith(QLatin1Char('-')) && min >= 0)
        {
            state = QValidator::Invalid; // special-case -0 will be interpreted as 0 and thus not be invalid with a range from 0-100
        }
        else
        {
            bool ok = false;
            num = traits::value_from_QString < T >::get(copy, &ok, 10);
//            if (!ok && copy.contains(locale().groupSeparator()) && (max >= 1000 || min <= -1000)) {
//                QString copy2 = copy;
//                copy2.remove(locale().groupSeparator());
//                num = traits::value_from_QString< T >::get(copy2, &ok, 10); // num = locale.toInt(copy2, &ok, 10);
//            }
            if (!ok)
                state = QValidator::Invalid;
            else if (num >= min && num <= max)
                state = QValidator::Acceptable;
            else if (max == min)
                state = QValidator::Invalid;
            else
            {
                if ((num >= 0 && num > max) || (num < 0 && num < min))
                    state = QValidator::Invalid;
                else
                    state = QValidator::Intermediate;
            }
        }
        if (state != QValidator::Acceptable)
            num = max > 0 ? min : max;
        input = m_prefix + copy + m_suffix;
//        cachedText = input;
//        cachedState = state;
//        cachedValue = QVariant((int)num);

//        return cachedValue;
    }

}; // class TemplatedSpinBox

} // qt
} // corbasim

#endif // CORBASIM_QT_TEMPLATEDSPINBOX_HPP

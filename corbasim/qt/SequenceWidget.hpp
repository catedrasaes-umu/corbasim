// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SequenceWidget.hpp
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

#ifndef CORBASIM_QT_SEQUENCEWIDGET_HPP
#define CORBASIM_QT_SEQUENCEWIDGET_HPP

#include <QtGui>
#include <vector>
#include <corbasim/gui/widget_factory_fwd.hpp>
#include <corbasim/gui/widgets/sequence_fwd.hpp>

namespace corbasim 
{
namespace qt 
{

class SequenceWidget : public QWidget
{
    Q_OBJECT
public:
    SequenceWidget(gui::widget_factory_base* factory, QWidget * parent = 0);
    virtual ~SequenceWidget();

    typedef std::vector< widgets::widget_ptr > widgets_t;

    widgets_t& getWidgets();

public slots:

    void lengthChanged(int);
    void indexChanged(int);

protected:

    gui::widget_factory_base* m_factory;

    QSpinBox * m_sbLength;
    QSpinBox * m_sbCurrentIndex;

    QStackedWidget * m_stack;

    widgets_t m_widgets;
};

class SequenceWidget2 : public QWidget
{
    Q_OBJECT
public:
    SequenceWidget2(widgets::abstract_sequence_widget* factory, 
            QWidget * parent = 0);
    virtual ~SequenceWidget2();

    void notifyValueHasChanged(int length);

public slots:

    void lengthChanged(int);
    void indexChanged(int);

protected:

    widgets::abstract_sequence_widget * m_factory;

    QSpinBox * m_sbLength;
    QSpinBox * m_sbCurrentIndex;
    QWidget * m_widget;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_SEQUENCEWIDGET_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * LogWidget.hpp
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

#ifndef CORBASIM_QT_LOGWIDGET_HPP
#define CORBASIM_QT_LOGWIDGET_HPP

#include <QWidget>

#include <corbasim/event_fwd.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/qt/export.hpp>

namespace corbasim 
{
namespace qt 
{

class LogTreeWidget;

class CORBASIM_QT_DECLSPEC LogWidget : public QWidget
{
    Q_OBJECT
public:
    LogWidget(QWidget * parent = 0);
    virtual ~LogWidget();

    void initialize(gui::gui_factory_base const * factory);

public slots:

    void notifyEvent(corbasim::event::event_ptr);
    void notifyRequest(corbasim::event::request_ptr);
    void notifyResponse(corbasim::event::response_ptr);
    void notifyException(corbasim::event::exception_ptr);

protected:

    LogTreeWidget * m_tree;
    gui::gui_factory_base const * m_factory;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_LOGWIDGET_HPP */


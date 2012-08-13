// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * OperationForm.hpp
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

#ifndef CORBASIM_GUI_OPERATIONFORM_HPP
#define CORBASIM_GUI_OPERATIONFORM_HPP

#include <QtGui>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/ReflectiveGUI.hpp>
#include <corbasim/gui/export.hpp>

namespace corbasim 
{
namespace gui 
{

class ParametersFromFilesTool;

class CORBASIM_GUI_DECLSPEC OperationFormWidget : 
    public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)
public:
    OperationFormWidget(
            core::operation_reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~OperationFormWidget();

    core::operation_reflective_base const * getReflective() const;

    // Property value
    void setValue(const QVariant& var);
    QVariant value();

    event::request_ptr createRequest();

    void setValue(event::request_ptr req);

    void dragEnterEvent(QDragEnterEvent *event);
    
    void dragLeaveEvent(QDragLeaveEvent *event);

    void dropEvent(QDropEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void save(QVariant& settings);
    void load(const QVariant& settings);

protected:

    core::operation_reflective_base const * m_reflective;

    std::vector< ReflectiveWidgetBase * > m_widgets;

    QPoint m_dragStartPosition;

};


class CORBASIM_GUI_DECLSPEC OperationForm : 
    public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString code READ code WRITE setCode)
public:
    OperationForm(QWidget * parent = 0);
    virtual ~OperationForm();
    
    void initialize(core::operation_reflective_base const *);

    // Property code
    void setCode(const QString& code);
    QString code();
    
    event::request_ptr createRequest();

    void save(QVariant& settings);
    void load(const QVariant& settings);

protected:

    core::operation_reflective_base const * m_reflective;

    QPlainTextEdit * m_code;
    OperationFormWidget * m_widget;
    ParametersFromFilesTool * m_files;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_OPERATIONFORM_HPP */


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
#include <corbasim/gui/export.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/gui/ReflectiveGUI.hpp>
#include <corbasim/gui/Sender.hpp>

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

    void dragEnterEvent(QDragEnterEvent *event);
    
    void dragLeaveEvent(QDragLeaveEvent *event);

    void dropEvent(QDropEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void setValue(corbasim::event::request_ptr req);

protected:

    bool eventFilter(QObject * obj, QEvent * event);

    void childEvent(QChildEvent * event);

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
    Q_PROPERTY(QString objectId READ objectId)
public:
    OperationForm(const QString& objectId = "this",
            QWidget * parent = 0);
    virtual ~OperationForm();
    
    void initialize(core::operation_reflective_base const *);

    // Property code
    void setCode(const QString& code);
    QString code() const;
    
    const QString& objectId() const;
    
    event::request_ptr createRequest();

    OperationFormWidget * getWidget();

    void save(QVariant& settings);
    void load(const QVariant& settings);

protected:

    const QString m_objectId;
    core::operation_reflective_base const * m_reflective;

    QPlainTextEdit * m_code;
    OperationFormWidget * m_widget;
    ParametersFromFilesTool * m_files;
};

class CORBASIM_GUI_DECLSPEC OperationSender : 
    public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString objectId READ objectId)
public:
    OperationSender(const QString& objectId = "this",
            QWidget * parent = 0);
    virtual ~OperationSender();

    void initialize(core::operation_reflective_base const *);

    const QString& objectId() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

    OperationForm * getForm() const;


    core::operation_reflective_base const * getReflective() const
    {
        return m_reflective;
    }

signals:

    void updateForm(corbasim::event::request_ptr req);
    void addSender(SenderConfig_ptr cfg);
    void deleteSender(SenderConfig_ptr cfg);

protected slots:

    void reset();

    void playClicked(bool play);
    void finished();
    void activeUpdateForm(bool update);

protected:

    const QString m_objectId;
    core::operation_reflective_base const * m_reflective;

    OperationForm * m_form;
    QSpinBox * m_times;
    QSpinBox * m_period;
    QCheckBox * m_updateForm;
    QPushButton * m_playButton;

    SenderConfig_ptr m_config;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_OPERATIONFORM_HPP */


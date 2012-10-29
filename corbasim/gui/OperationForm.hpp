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
#include <corbasim/gui/types.hpp>
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
            OperationDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~OperationFormWidget();

    OperationDescriptor_ptr getReflective() const;

    // Property value
    void setValue(const QVariant& var);
    QVariant value();

    Request_ptr createRequest();

    void dragEnterEvent(QDragEnterEvent *event);
    
    void dragLeaveEvent(QDragLeaveEvent *event);

    void dropEvent(QDropEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void save(QVariant& settings);
    void load(const QVariant& settings);
    
    void _setReadOnly(bool readOnly);

public slots:

    void setValue(Request_ptr req);

protected:

    bool eventFilter(QObject * obj, QEvent * event);

    void childEvent(QChildEvent * event);

protected:

    OperationDescriptor_ptr m_reflective;

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
    
    void initialize(Objref_ptr, OperationDescriptor_ptr);

    // Property code
    void setCode(const QString& code);
    QString code() const;
    
    Request_ptr createRequest();

    OperationFormWidget * getWidget();
    ParametersFromFilesTool * getFiles();

    void save(QVariant& settings);
    void load(const QVariant& settings);
    
    void _setReadOnly(bool readOnly);

protected:

    OperationDescriptor_ptr m_reflective;

    QPlainTextEdit * m_code;
    OperationFormWidget * m_widget;
    ParametersFromFilesTool * m_files;
};

class CORBASIM_GUI_DECLSPEC OperationSender : 
    public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Objref_ptr object READ object)
public:
    OperationSender(Objref_ptr object,
            QWidget * parent = 0);
    virtual ~OperationSender();

    void initialize(OperationDescriptor_ptr);

    Objref_ptr object() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

    OperationForm * getForm() const;


    OperationDescriptor_ptr getReflective() const
    {
        return m_reflective;
    }

    void _setReadOnly(bool readOnly);

public slots:

    void stop();

signals:

    void updateForm(Request_ptr req);
    void addSender(SenderConfig_ptr cfg);
    void deleteSender(SenderConfig_ptr cfg);

protected slots:

    void reset();

    void playClicked(bool play);
    void finished();
    void activeUpdateForm(bool update);

protected:

    Objref_ptr m_object;
    OperationDescriptor_ptr m_reflective;

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


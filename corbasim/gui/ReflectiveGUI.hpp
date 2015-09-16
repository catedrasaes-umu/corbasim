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
#include <QButtonGroup>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPlainTextEdit>

#include <corbasim/gui/ObjrefWidget.hpp>
#include <corbasim/qt/MultiFileSelectionWidget.hpp>
#include <corbasim/qt/TabWidget.hpp>
#include <corbasim/qt/FormWidget.hpp>

#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>

#include <boost/function.hpp>

#ifdef CORBASIM_USE_QTSCRIPT
#include <QtScript>
#endif /* CORBASIM_USE_QTSCRIPT*/

namespace corbasim
{
namespace gui
{

typedef boost::function< QWidget * (
    TypeDescriptor_ptr,
    QWidget *) > WidgetFactory_t;

QWidget * CORBASIM_GUI_DECLSPEC createWidget(
    TypeDescriptor_ptr reflective,
    QWidget * parent);

QWidget * CORBASIM_GUI_DECLSPEC createSimpleWidget(
    TypeDescriptor_ptr reflective,
    QWidget * parent);

/**
 * @brief This is the base class of all widget abstraction
 * associated to a type descriptor.
 */
class CORBASIM_GUI_DECLSPEC ReflectiveWidgetBase
{
protected:

    ReflectiveWidgetBase(TypeDescriptor_ptr reflective);

public:

    virtual ~ReflectiveWidgetBase();

    TypeDescriptor_ptr getReflective() const;

    virtual void toHolder(Holder& holder) = 0;
    virtual void fromHolder(Holder& holder) = 0;

    virtual void save(QVariant& settings) = 0;
    virtual void load(const QVariant& settings) = 0;

    virtual void _setReadOnly(bool readOnly);

protected:

    TypeDescriptor_ptr m_reflective;
};

/**
 * @brief Will be deprecated.
 */
class CORBASIM_GUI_DECLSPEC AlternativesWidget :
    public QWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
    Q_PROPERTY(int selectionIndex
            READ selectionIndex
            WRITE setSelectionIndex)
public:
    AlternativesWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~AlternativesWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void addAlternative(const QString& id,
            const QString& toolTip,
            ReflectiveWidgetBase * widget);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    int selectionIndex() const;
    void setSelectionIndex(int index);

    void _setReadOnly(bool readOnly);

protected slots:

    void changeWidget(int);

protected:

    QButtonGroup m_group;
    QStackedWidget * m_stack;
    QVBoxLayout * m_btnLayout;

    std::vector< ReflectiveWidgetBase * > m_widgets;
};

class CORBASIM_GUI_DECLSPEC FloatWidget :
    public QDoubleSpinBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    FloatWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~FloatWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);
};

class CORBASIM_GUI_DECLSPEC IntegerWidget :
    public QSpinBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    IntegerWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~IntegerWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);
};

class CORBASIM_GUI_DECLSPEC StringWidget :
    public QLineEdit, public ReflectiveWidgetBase
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue)
public:
    StringWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~StringWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    QString value() const;
    void setValue(const QString& value);

    void _setReadOnly(bool readOnly);
};

class CORBASIM_GUI_DECLSPEC EnumWidget :
    public QComboBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    EnumWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~EnumWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);
};

class CORBASIM_GUI_DECLSPEC BoolWidget :
    public QCheckBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    BoolWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~BoolWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);
};

class CORBASIM_GUI_DECLSPEC StructWidget :
    public qt::FormWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)
public:
    StructWidget(TypeDescriptor_ptr reflective,
            WidgetFactory_t factory = createWidget,
            QWidget * parent = 0);
    virtual ~StructWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void setValue(const QVariant& var);
    QVariant value();

    void _setReadOnly(bool readOnly);

protected:

    std::vector< ReflectiveWidgetBase * > m_widgets;
};

class CORBASIM_GUI_DECLSPEC UnionWidget :
    public QWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    UnionWidget(TypeDescriptor_ptr reflective,
            WidgetFactory_t factory = createWidget,
            QWidget * parent = 0);
    virtual ~UnionWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);

protected slots:

    void discriminatorChanged();

protected:

    std::vector< ReflectiveWidgetBase * > m_widgets;

    QStackedWidget * m_stack;
};

class CORBASIM_GUI_DECLSPEC SequenceWidget :
    public QWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)
public:
    SequenceWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~SequenceWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void setValue(const QVariant& var);
    QVariant value() const;

    void _setReadOnly(bool readOnly);

protected slots:

    void lengthChanged(int);
    void indexChanged(int);
    void saveCurrent();

protected:

    QSpinBox * m_sbLength;
    QSpinBox * m_sbCurrentIndex;

    ReflectiveWidgetBase * m_slice;
    QWidget * m_slice_widget;

    Holder m_holder;
};

class CORBASIM_GUI_DECLSPEC ComplexSequenceWidget :
    public QWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    ComplexSequenceWidget(TypeDescriptor_ptr reflective,
            WidgetFactory_t factory = createWidget,
            QWidget * parent = 0);
    virtual ~ComplexSequenceWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);

protected slots:

    void lengthChanged(int);
    void indexChanged(int);

protected:

    WidgetFactory_t m_factory;
    QStackedWidget * m_stack;
    QSpinBox * m_sbLength;
    QSpinBox * m_sbCurrentIndex;
};

class CORBASIM_GUI_DECLSPEC ObjrefvarWidget :
    public ObjrefWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    ObjrefvarWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~ObjrefvarWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);
};

class CORBASIM_GUI_DECLSPEC FilesWidget :
    public qt::MultiFileSelectionWidget,
    public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    FilesWidget(TypeDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~FilesWidget();

    virtual void toHolder(Holder& holder);
    virtual void fromHolder(Holder& holder);

    void save(QVariant& settings);
    void load(const QVariant& settings);

};

class CORBASIM_GUI_DECLSPEC OperationInputForm :
    public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)
public:
    OperationInputForm(
            OperationDescriptor_ptr reflective,
            QWidget * parent = 0);
    virtual ~OperationInputForm();

    OperationDescriptor_ptr getReflective() const;

    void setValue(const QVariant& var);
    QVariant value();

    Request_ptr createRequest();

    void setValue(Request_ptr req);

    void dragEnterEvent(QDragEnterEvent *event);

    void dragLeaveEvent(QDragLeaveEvent *event);

    void dropEvent(QDropEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    // bool eventFilter(QObject * watched, QEvent * event);

    void save(QVariant& settings);
    void load(const QVariant& settings);

    void _setReadOnly(bool readOnly);

public slots:

#ifdef CORBASIM_USE_QTSCRIPT
    void reloadScript();
#endif /* CORBASIM_USE_QTSCRIPT*/

protected:

    OperationDescriptor_ptr m_reflective;

    std::vector< ReflectiveWidgetBase * > m_widgets;

    QPoint m_dragStartPosition;

#ifdef CORBASIM_USE_QTSCRIPT
    // widgets
    qt::TabWidget * m_tabs;
    QPlainTextEdit * m_code;

    QScriptEngine m_engine;
    QScriptValue m_thisObject;
    QScriptValue m_initFunc;
    QScriptValue m_preFunc;
    QScriptValue m_postFunc;

#endif /* CORBASIM_USE_QTSCRIPT*/

};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_REFLECTIVEGUI_HPP */


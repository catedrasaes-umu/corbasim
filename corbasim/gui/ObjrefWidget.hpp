// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ObjrefWidget.hpp
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

#ifndef CORBASIM_GUI_OBJREFWIDGET_HPP
#define CORBASIM_GUI_OBJREFWIDGET_HPP

#include <QWidget>
#include <corbasim/gui/export.hpp>
#include <corbasim/core/caller_fwd.hpp>
#include <corbasim/gui/Model.hpp>

class QComboBox;
class QStackedWidget;
class QTextEdit;
class QAbstractItemModel;

namespace corbasim 
{
namespace qt
{
class Status;
} // namespace qt

namespace gui
{

class CORBASIM_GUI_DECLSPEC ObjrefWidget : public QWidget
{
    Q_OBJECT
public:
    ObjrefWidget(InterfaceDescriptor_ptr iface = NULL,
            QWidget * parent = 0);
    virtual ~ObjrefWidget();

    QString getNSEntry() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

    CORBA::Object_var reference() const;

    void setValidator(core::reference_validator_ptr validator);

protected slots:

    void valueChanged();
    void validatorHasChanged();
    void modelChanged();

public slots:

    void pasteIOR();

    void setModel(QAbstractItemModel * model);
    
    void setInterface(InterfaceDescriptor_ptr iface);

    void setReference(const CORBA::Object_var& ref);

    void setObjref(Objref_ptr objref);

signals:

    void valueHasChanged(const CORBA::Object_var&);

    void resolve(Objref_ptr);

protected:
    QComboBox * m_selector;
    QStackedWidget * m_stack;
    qt::Status * m_status;
    QTextEdit * m_ior;
    QTextEdit * m_resolve_str;
    QComboBox * m_object_selector;
    QAbstractItemModel * m_model;

    Objref_ptr m_objref;

    QString m_currentModelItem;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_OBJREFWIDGET_HPP */


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * CreateDialog.hpp
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

#ifndef CORBASIM_APP_VIEW_CREATEDIALOG_HPP
#define CORBASIM_APP_VIEW_CREATEDIALOG_HPP

#include <QtGui>
#include "../app_adapted.hpp"
#include <corbasim/reflective_gui/ReflectiveGUI.hpp>

namespace corbasim 
{
namespace app 
{
namespace view 
{

class ObjrefCreateDialog : public QDialog
{
    Q_OBJECT
public:
    ObjrefCreateDialog(QWidget * parent = 0);
    virtual ~ObjrefCreateDialog();

public slots:

    void createClicked();

signals:

    void createObjref(corbasim::app::ObjrefConfig);

protected:

    reflective_gui::StructWidget m_widget;
    
    void hideEvent(QHideEvent* event);
};

class ServantCreateDialog : public QDialog
{
    Q_OBJECT
public:
    ServantCreateDialog(QWidget * parent = 0);
    virtual ~ServantCreateDialog();

public slots:

    void createClicked();

signals:

    void createServant(corbasim::app::ServantConfig);

protected:

    reflective_gui::StructWidget m_widget;

    void hideEvent(QHideEvent* event);
};

class ReferenceValidatedWidget : public QWidget
{
    Q_OBJECT
public:
    ReferenceValidatedWidget(
            core::reference_validator_base * validator,
            QWidget * parent = 0);
    virtual ~ReferenceValidatedWidget();

public slots:    

    void updateReference(const CORBA::Object_var& ref);

    void applyClicked();

signals:

    void updatedReference(CORBA::Object_var);

protected:

    core::reference_validator_base * m_validator;
    qt::ObjrefWidget * m_widget;
};

} // namespace view
} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_VIEW_CREATEDIALOG_HPP */


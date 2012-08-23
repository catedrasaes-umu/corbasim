// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UpdateReferenceDialog.hpp
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

#ifndef CORBASIM_GUI_UPDATEREFERENCEDIALOG_HPP
#define CORBASIM_GUI_UPDATEREFERENCEDIALOG_HPP

#include <QtGui>
#include <corbasim/gui/types.hpp>
#include <corbasim/qt/ObjrefWidget.hpp>

namespace corbasim 
{
namespace gui 
{

class UpdateReferenceDialog : public QDialog
{
    Q_OBJECT
public:
    UpdateReferenceDialog(QWidget * parent = 0);
    virtual ~UpdateReferenceDialog();

public slots:

    void setObjref(Objref_ptr objref);

    void updatedReference(const CORBA::Object_var& reference);

signals:

    void updateReference(const CORBA::Object_var& reference);

protected slots:

    void update();

protected:
    
    void hideEvent(QHideEvent* event);

    qt::ObjrefWidget * m_status;
    qt::ObjrefWidget * m_reference;

    core::reference_validator_ptr m_statusValidator;
    core::reference_validator_ptr m_referenceValidator;

    Objref_ptr m_objref;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_UPDATEREFERENCEDIALOG_HPP */


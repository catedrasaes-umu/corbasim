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

#ifndef CORBASIM_GUI_CREATEDIALOG_HPP
#define CORBASIM_GUI_CREATEDIALOG_HPP

#include <QtGui>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/ObjrefWidget.hpp>

namespace corbasim 
{
namespace gui 
{

class ObjrefCreateDialog : public QDialog
{
    Q_OBJECT
public:
    ObjrefCreateDialog(QWidget * parent = 0);
    virtual ~ObjrefCreateDialog();

    void setFQNModel(QAbstractItemModel * model);

public slots:

    void createClicked();

protected slots:
    
    void browse();

signals:

    void createObjref(ObjrefConfig);

protected:
    
    void hideEvent(QHideEvent* event);

    QLineEdit * m_name;
    QComboBox * m_fqn;
    ObjrefWidget * m_reference;
    QLineEdit * m_watchFile;

    core::reference_validator_ptr m_validator;
};

class ServantCreateDialog : public QDialog
{
    Q_OBJECT
public:
    ServantCreateDialog(QWidget * parent = 0);
    virtual ~ServantCreateDialog();
    
    void setFQNModel(QAbstractItemModel * model);

public slots:

    void createClicked();

protected slots:
    
    void browse();

signals:

    void createServant(ServantConfig);

protected:

    void hideEvent(QHideEvent* event);

    QLineEdit * m_name;
    QComboBox * m_fqn;
    QLineEdit * m_entry;
    QLineEdit * m_saveFile;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_CREATEDIALOG_HPP */


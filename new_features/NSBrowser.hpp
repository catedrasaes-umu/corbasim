// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * NSBrowser.hpp
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

#ifndef CORBASIM_APP_NSBROWSER_HPP
#define CORBASIM_APP_NSBROWSER_HPP

#include <QtGui>
#include <corbasim/impl.hpp>
#include <corbasim/cosnaming/CosnamingC.h>

namespace corbasim 
{
namespace app 
{

class NSModel : public QStandardItemModel
{
    Q_OBJECT
public:
    NSModel(QObject * parent = 0);
    virtual ~NSModel();

public slots:

    void updateModel();

    void start();

protected:

    void processNC(const CosNaming::NamingContext_ptr nc,
            QStandardItem * parent);

    void processNCIteration(const CosNaming::NamingContext_ptr nc,
            const CosNaming::BindingList& bl,
            QStandardItem * parent);

    CORBA::ORB_var m_orb;

    CosNaming::NamingContext_var m_rootNC;

    QTimer m_timer;
};

class NSBrowser : public QWidget
{
    Q_OBJECT
public:
    NSBrowser(QWidget * parent = 0);
    virtual ~NSBrowser();

protected:
    NSModel m_model;

    QTreeView * m_view; 
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_NSBROWSER_HPP */


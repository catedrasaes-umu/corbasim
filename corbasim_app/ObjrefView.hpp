// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Objref.hpp
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

#ifndef CORBASIM_APP_VIEW_OBJREF_HPP
#define CORBASIM_APP_VIEW_OBJREF_HPP

#include <QtGui>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/RequestDialog.hpp>
#include <corbasim/gui/OperationForm.hpp>
#include <corbasim/gui/tools/SimpleScriptEditor.hpp>
#include <corbasim/gui/client/SimpleClient.hpp>
#include <corbasim/gui/dialog/UpdateReferenceDialog.hpp>

namespace corbasim 
{
namespace app 
{

using namespace corbasim::gui;

class ObjrefView : public QObject
{
    Q_OBJECT
public:
    ObjrefView(QMdiArea * area,
            Objref_ptr objref,
            QObject * parent = 0);
    virtual ~ObjrefView();

    QMenu * getMenu() const;

    RequestDialog * getRequestDialog(int idx);
    QMdiSubWindow * getRequestWindow(int idx);

    OperationSender * getSenderDialog(int idx);
    QMdiSubWindow * getSenderWindow(int idx);

    InterfaceDescriptor_ptr getFactory() const;

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void deleteObjref();

    void showRequestDialog(int idx);
    void showRequestDialog(QAction * act);
    void showSenderDialog(int idx);
    void showSenderDialog(QAction * act);
    void showScriptEditor();

    void showSetReference();
    void showClient();

    void stopAll();

signals:

    void deleteObjref(ObjectId);

protected:

    QMdiArea * m_mdi_area;

    Objref_ptr m_objref;

    // Operation dialogs
    typedef std::vector< RequestDialog * > dialogs_t;
    dialogs_t m_dialogs;
    
    typedef std::vector< QMdiSubWindow * > subwindows_t;
    subwindows_t m_subwindows;

    // Senders
    typedef std::vector< OperationSender * > senders_t;
    senders_t m_senders;

    subwindows_t m_subwindows_senders;

    QMdiSubWindow * m_sub_script;
    SimpleScriptEditor * m_script;

    QMdiSubWindow * m_subUpdateReference;
    UpdateReferenceDialog * m_updateReference;

    SimpleClient * m_client;

    QMenu * m_menu;
};

typedef boost::shared_ptr< ObjrefView > ObjrefView_ptr;

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_VIEW_OBJREF_HPP */


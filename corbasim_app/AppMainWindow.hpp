// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppMainWindow.hpp
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

#ifndef CORBASIM_APP_APPMAINWINDOW_HPP
#define CORBASIM_APP_APPMAINWINDOW_HPP

#include <QtGui>
#include <vector>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/Model.hpp>
#include <corbasim/gui/item/LogModel.hpp>

#include "ObjrefView.hpp"
#include "ui_AppMainWindow.h"

namespace corbasim 
{
namespace gui 
{
    class ObjrefCreateDialog;
    class ServantCreateDialog;

    class OperationSequenceTool;
    class SenderSequenceTool;
} // namespace gui

namespace app 
{

using namespace corbasim::gui;

class AppMainWindow : public QMainWindow, private Ui_AppMainWindow
{
    Q_OBJECT
public:
    AppMainWindow(QWidget * parent = 0);
    virtual ~AppMainWindow();

    // void save(QVariant& settings);
    // void load(const QVariant& settings);

public slots:

    // Notificaciones del controlador

    void objrefCreated(Objref_ptr objref);
    void objrefDeleted(ObjectId id);

    void servantCreated(Objref_ptr servant);
    void servantDeleted(ObjectId id);

    void displayError(const QString& err);
    void displayMessage(const QString& msg);

    // Dialogs
    void showCreateObjrefDialog();
    void showCreateServantDialog();

    // Tools
    void createOperationSequenceTool();
    void showOperationSequenceTool();
    void createSenderSequenceTool();
    void showSenderSequenceTool();

signals:

    void createObjref(const ObjrefConfig&);
    void deleteObjref(ObjectId);
    
    void createServant(const ServantConfig&);
    void deleteServant(ObjectId);

protected:

    ObjrefRepository m_objrefs;
    ObjrefRepository m_servants;
    LogModel m_logModel;

    QActionGroup m_actions;

    std::vector< QMdiSubWindow * > m_subWindows;

    // Dialogs
    ObjrefCreateDialog * m_createObjrefDialog;
    ServantCreateDialog * m_createServantDialog;

    // Tools
    OperationSequenceTool * m_operationSequenceTool;
    SenderSequenceTool * m_senderSequenceTool;

    typedef QMap< ObjectId, ObjrefView_ptr > ObjrefViews_t;
    ObjrefViews_t m_objrefViews;
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPMAINWINDOW_HPP */


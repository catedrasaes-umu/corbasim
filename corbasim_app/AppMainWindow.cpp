// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppMainWindow.cpp
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

#include "AppMainWindow.hpp"

// Tools
#include <corbasim/gui/OperationSequence.hpp>
#include <corbasim/gui/SenderSequence.hpp>

using namespace corbasim::app;

namespace  
{
    enum SubWindows
    {
        kOperationSequenceTool,
        kSenderSequenceTool,

        kSubWindowsMax
    };

    const char * SubWindowTitles[] = {
        "Operation sequence tool",
        "Sender sequence tool"
    };
} // namespace

AppMainWindow::AppMainWindow(QWidget * parent) :
    QMainWindow(parent), 
    m_objrefs(this), 
    m_servants(this),
    m_logModel(this),
    m_actions(this),

    // Tools
    m_operationSequenceTool(NULL),
    m_senderSequenceTool(NULL)

{
    setupUi(this);
    
    // TODO
    centralWidget()->layout()->setMargin(0);

    setWindowIcon(QIcon(":/resources/images/csu.png"));

    // No more window

    menuTool->addAction("&Operation sequences", 
            this, SLOT(showOperationSequenceTool()));
    menuTool->addAction("&Sender sequences", 
            this, SLOT(showSenderSequenceTool()));

    // Subwindows
    m_subWindows.resize(kSubWindowsMax, NULL);
}

AppMainWindow::~AppMainWindow()
{
}

void AppMainWindow::objrefCreated(Objref_ptr objref)
{
    m_objrefs.add(objref);
    m_logModel.registerInstance(objref);

    ObjrefView_ptr view(new ObjrefView(mdiArea, objref, this));
    m_objrefViews.insert(objref->id(), view);

    // connect signals
    connect(objref.get(), SIGNAL(requestSent(ObjectId, Request_ptr, Event_ptr)),
        &m_logModel, SLOT(outputRequest(ObjectId, Request_ptr, Event_ptr)));

    if (m_operationSequenceTool)
        m_operationSequenceTool->objrefCreated(objref);

    if (m_senderSequenceTool)
        m_senderSequenceTool->objrefCreated(objref);
}

void AppMainWindow::objrefDeleted(ObjectId id)
{
    m_objrefs.del(id);
    m_logModel.unregisterInstance(id);

    m_objrefViews.remove(id);

    if (m_operationSequenceTool)
        m_operationSequenceTool->objrefDeleted(id);

    if (m_senderSequenceTool)
        m_senderSequenceTool->objrefDeleted(id);
}

void AppMainWindow::servantCreated(Objref_ptr servant)
{
    m_servants.add(servant);
    m_logModel.registerInstance(servant);
    
    // connect signals
    connect(servant.get(), SIGNAL(requestReceived(ObjectId, Request_ptr, Event_ptr)),
        &m_logModel, SLOT(inputRequest(ObjectId, Request_ptr, Event_ptr)));
}

void AppMainWindow::servantDeleted(ObjectId id)
{
    m_servants.del(id);
    m_logModel.unregisterInstance(id);
}

void AppMainWindow::displayError(const QString& err)
{
    QMessageBox::critical(this, "Error", err);
}

void AppMainWindow::displayMessage(const QString& msg)
{
}

// 
//
// Tools
//
//
void AppMainWindow::createOperationSequenceTool()
{
    if (!m_operationSequenceTool)
    {
        m_operationSequenceTool = new OperationSequenceTool(this);
        
        m_subWindows[kOperationSequenceTool] = 
            mdiArea->addSubWindow(m_operationSequenceTool);
        
        m_subWindows[kOperationSequenceTool]->setWindowTitle(SubWindowTitles[kOperationSequenceTool]);

        // Initilizes the tool
        ObjrefRepository::const_iterator it = m_objrefs.begin();
        ObjrefRepository::const_iterator end = m_objrefs.begin();

        for(; it != end; it++)
            m_operationSequenceTool->objrefCreated(it.value());
    }
}

void AppMainWindow::showOperationSequenceTool()
{
    createOperationSequenceTool();

    m_subWindows[kOperationSequenceTool]->show();
}

void AppMainWindow::createSenderSequenceTool()
{
    if (!m_senderSequenceTool)
    {
        m_senderSequenceTool = new SenderSequenceTool(this);

        m_subWindows[kSenderSequenceTool] = 
            mdiArea->addSubWindow(m_senderSequenceTool);
        
        m_subWindows[kSenderSequenceTool]->setWindowTitle(SubWindowTitles[kSenderSequenceTool]);

        // Initilizes the tool
        ObjrefRepository::const_iterator it = m_objrefs.begin();
        ObjrefRepository::const_iterator end = m_objrefs.begin();

        for(; it != end; it++)
            m_senderSequenceTool->objrefCreated(it.value());
    }
}

void AppMainWindow::showSenderSequenceTool()
{
    createSenderSequenceTool();

    m_subWindows[kSenderSequenceTool]->show();
}


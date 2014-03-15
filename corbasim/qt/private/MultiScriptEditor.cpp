// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * MultiScriptEditor.cpp
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

#include "MultiScriptEditor.hpp"
#include "ScriptEditor.hpp"

using namespace corbasim::qt::priv;

MultiScriptEditor::MultiScriptEditor(QWidget * parent) :
    QMainWindow(parent)
{
    m_tabs = new QTabWidget;
    m_tabs->setTabsClosable(true);
    m_tabs->setMovable(true);
    setCentralWidget(m_tabs);

    // Actions
    // New
    QAction * newAction = new QAction(
            style()->standardIcon(QStyle::SP_FileIcon),
            "&Load", this);
    newAction->setShortcut(QKeySequence::New);
    QObject::connect(newAction, SIGNAL(triggered()),
            this, SLOT(new_()));

    // Tool bars
    QToolBar * toolBar = addToolBar("File");
    toolBar->addAction(newAction);
}

MultiScriptEditor::~MultiScriptEditor()
{
}

void MultiScriptEditor::new_()
{
    m_tabs->addTab(new ScriptEditor(), "<unknown>");
}


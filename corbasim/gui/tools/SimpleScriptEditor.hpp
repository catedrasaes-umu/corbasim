// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SimpleScriptEditor.hpp
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

#ifndef CORBASIM_GUI_SIMPLESCRIPTEDITOR_HPP
#define CORBASIM_GUI_SIMPLESCRIPTEDITOR_HPP

#include <QtGui>
#include <list>
#include <vector>

#include <corbasim/gui/export.hpp>
#include <corbasim/gui/types.hpp>
#include <corbasim/gui/item/ScriptModel.hpp>

namespace corbasim
{
namespace gui
{

class OperationInputForm;

class CORBASIM_GUI_DECLSPEC SimpleScriptEditor :
    public QMainWindow
{
    Q_OBJECT
public:

    SimpleScriptEditor(QWidget * parent = 0);
    virtual ~SimpleScriptEditor();

    void initialize(InterfaceDescriptor_ptr factory);

public slots:

    void appendRequest();
    void appendOneRequest();
    void sendNextRequest();
    void playClicked();
    void playFromSelected();
    void sendCurrent();
    void clearClicked();
    void stopClicked();
    void deleteSelected();

    void copySelected();
    void replaceSelected();
    void doSave();
    void doLoad();

    void moveUp();
    void moveDown();

signals:

    void sendRequest(Request_ptr);

protected:

    typedef std::vector< OperationInputForm * > forms_t;

    void doAppendRequest(Request_ptr,
            bool beforeSelected = false);
    int getSelected();

    QTimer m_timer;
    unsigned int m_current_request;

    QComboBox * m_selector;
    QStackedWidget * m_multi;
    QSpinBox * m_diff;
    QSpinBox * m_how_many;
    QTreeView * m_tree;
    QCheckBox * m_cbInsertAtEnd;
    ScriptModel m_model;

    forms_t m_forms;

    InterfaceDescriptor_ptr m_factory;

    void hideEvent(QHideEvent * event);
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_SIMPLESCRIPTEDITOR_HPP */


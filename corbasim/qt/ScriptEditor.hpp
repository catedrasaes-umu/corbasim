// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ScriptEditor.hpp
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

#ifndef CORBASIM_QT_SCRIPTEDITOR_HPP
#define CORBASIM_QT_SCRIPTEDITOR_HPP

#include <QtGui>
#include <list>
#include <corbasim/event.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>

namespace corbasim 
{
namespace qt 
{

class MultiInputWidget;

class ScriptEditor : public QMainWindow
{
    Q_OBJECT
public:
    ScriptEditor(QWidget * parent = 0);
    virtual ~ScriptEditor();

    void initialize(gui::gui_factory_base const * factory);

public slots:
    void appendRequest();
    void appendOneRequest();
    void sendNextRequest();
    void playClicked();
    void playFromSelected();
    void sendCurrent();
    void clearClicked();
    void stopClicked();
    
    void doSave();
    void doLoad();
    
signals:
    void sendRequest(corbasim::event::request_ptr);

protected:

    void doAppendRequest(corbasim::event::request_ptr, 
            bool beforeSelected = false);

    QComboBox * m_selector;
    MultiInputWidget * m_multi;
    QSpinBox * m_how_many; 
    QTextEdit * m_code;
    QCheckBox * m_cbInsertAtEnd;
    
    gui::gui_factory_base const * m_factory;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_SCRIPTEDITOR_HPP */


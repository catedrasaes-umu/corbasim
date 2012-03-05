// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * MultiInputWidget.hpp
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

#ifndef CORBASIM_QT_MULTIINPUTWIDGET_HPP
#define CORBASIM_QT_MULTIINPUTWIDGET_HPP

#include <QDialog>
#include <vector>

#include <corbasim/impl.hpp>
#include <corbasim/adapted.hpp>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include <corbasim/qt/export.hpp>
#include <corbasim/qt/types.hpp>

class QStackedWidget;
class QComboBox;

namespace corbasim 
{
namespace qt 
{

class CORBASIM_QT_DECLSPEC MultiInputWidget : public QWidget
{
    Q_OBJECT
public:

    MultiInputWidget(QWidget * parent = 0);
    virtual ~MultiInputWidget();

    typedef std::vector< dialogs::input_ptr > inputs_t;

    void initialize(gui::gui_factory_base const * factory);

    dialogs::input_ptr getCurrentDialog();
    
    dialogs::input_ptr getDialog(int idx);

public slots:
    void changeInputForm(int index);

protected:

    QStackedWidget * m_stack;
    inputs_t m_inputs;

    gui::gui_factory_base const * m_factory;
};

class CORBASIM_QT_DECLSPEC MultiInputForm : public QWidget
{
    Q_OBJECT
public:
    MultiInputForm (QWidget * parent = 0);
    virtual ~MultiInputForm ();

    void initialize(gui::gui_factory_base const * factory);

protected:
    QComboBox * m_selector;
    MultiInputWidget * m_multi;
};

class CORBASIM_QT_DECLSPEC MultiSenderDialog : public QDialog
{
    Q_OBJECT
public:
    MultiSenderDialog (QWidget * parent = 0);
    virtual ~MultiSenderDialog ();

    void initialize(gui::gui_factory_base const * factory);

public slots:
	void sendClicked(); 

signals:
    void sendRequest(corbasim::event::request_ptr);

protected:
    QComboBox * m_selector;
    MultiInputWidget * m_multi;
};


} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_MULTIINPUTWIDGET_HPP */


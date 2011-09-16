// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * initialize.hpp
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

#ifndef CORBASIM_GUI_INITIALIZE_HPP
#define CORBASIM_GUI_INITIALIZE_HPP

#include <vector>
#include <QtGui>
#include <corbasim/gui/dialogs.hpp>

namespace corbasim 
{
namespace gui 
{
namespace initialize 
{

struct stacked
{
    typedef std::vector< dialogs::input_ptr > inputs_t;

    inline stacked(inputs_t& inputs, QStackedWidget*& stack) :
        m_inputs(inputs), m_stack(stack)
    {
    }

    template< typename Value >
    void operator()(const Value& /* unused */)
    {
        typedef dialogs::input< Value > input_t;
        input_t * _input = new input_t;

        // Envuelve el formulario en un scroll area
        QScrollArea * scroll = new QScrollArea;
        scroll->setWidgetResizable(true);
        scroll->setWidget(_input->get_qwidget());

        // Añade el fomulario al stacked widget
        m_stack->addWidget(scroll);
        m_inputs.push_back(dialogs::input_ptr(_input));
    }

    // Data
    inputs_t& m_inputs;
    QStackedWidget*& m_stack;
};

struct combobox
{
    inline combobox(QComboBox *& selector) :
        m_selector(selector)
    {}

    template < typename Value >
    void operator()(const Value& /* unused */)
    {
        // operation name a partir de Value
        typedef typename adapted::name< Value > name_t;
        m_selector->addItem(name_t::call());
    }

    // Data
    QComboBox *& m_selector;
};

} // namespace initialize
} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_INITIALIZE_HPP */


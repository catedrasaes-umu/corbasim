// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AutoResponse.cpp
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

#include "AutoResponse.hpp"
#include <boost/bind.hpp>

using namespace corbasim::qt::python;

AutoResponseWidget::AutoResponseWidget(QWidget * parent) :
    QWidget(parent)
{
}

AutoResponseWidget::~AutoResponseWidget()
{
}

void AutoResponseWidget::initialize(
        gui::gui_factory_base * input_factory,
        gui::gui_factory_base* output_factory)
{
    m_auto_response.reset(new ::corbasim::python::auto_response(
                input_factory->get_core_factory(),
                output_factory->get_core_factory()));

    m_auto_response->connect_output(boost::bind(
                &AutoResponseWidget::notifyRequest, this, _1));
}

void AutoResponseWidget::requestReceived(event::request_ptr req)
{
    m_auto_response->new_input_message(req);
}

void AutoResponseWidget::notifyRequest(event::request_ptr req)
{
    emit sendRequest(req);
}


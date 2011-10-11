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
#include <vector>

using namespace corbasim::qt::python;

namespace  
{

struct item_data
{
    QGroupBox * gb;
    QPushButton * btn_save;
    QTextEdit * te_guard;
    QComboBox * cb_true;
    QComboBox * cb_false;
    QTextEdit * te_true;
    QTextEdit * te_false;
};

} // namespace

namespace corbasim 
{
namespace qt 
{
namespace python 
{

struct auto_response_data
{
    QButtonGroup * g;
    std::vector< item_data > v;
};

} // namespace python
} // namespace qt
} // namespace corbasim

AutoResponseWidget::AutoResponseWidget(QWidget * parent) :
    QWidget(parent), m_data(new auto_response_data)
{
    m_data->g = new QButtonGroup(this);
}

AutoResponseWidget::~AutoResponseWidget()
{
    delete m_data;
}

void AutoResponseWidget::initialize(
        gui::gui_factory_base * input_factory,
        gui::gui_factory_base* output_factory)
{
    m_auto_response.reset(new ::corbasim::python::auto_response(
                input_factory->get_core_factory(),
                output_factory->get_core_factory()));

    QVBoxLayout * layout = new QVBoxLayout;

    unsigned int icount = input_factory->operation_count();
    unsigned int ocount = output_factory->operation_count();

    m_data->v.reserve(icount);

    for (unsigned int i = 0; i < icount; i++) 
    {
        gui::operation_factory_base * iop = 
            output_factory->get_factory_by_index(i);

        QGroupBox * gb = new QGroupBox(iop->get_name(), this);
        gb->setCheckable(true);
        gb->setChecked(false);

        QGridLayout * gbLayout = new QGridLayout;
        gb->setLayout(gbLayout);

        gbLayout->addWidget(new QLabel("Guard"), 0, 0);
        gbLayout->addWidget(new QLabel("Response if true"), 0, 1);
        gbLayout->addWidget(new QLabel("Response if false"), 0, 2);

        QComboBox * cb_true = new QComboBox;
        QComboBox * cb_false = new QComboBox;

        // No response
        cb_true->addItem("(No response)");
        cb_false->addItem("(No response)");

        for (unsigned int j = 0; j < ocount; j++) 
        {
            gui::operation_factory_base * op = 
                output_factory->get_factory_by_index(j);
            const char * name = op->get_name();

            cb_true->addItem(name);
            cb_false->addItem(name);
        }

        gbLayout->addWidget(cb_true, 1, 1);
        gbLayout->addWidget(cb_false, 1, 2);

        gbLayout->addWidget(new QTextEdit, 2, 0);
        gbLayout->addWidget(new QTextEdit, 2, 1);
        gbLayout->addWidget(new QTextEdit, 2, 2);

        QPushButton * btn = new QPushButton("Save");
        m_data->g->addButton(btn);

        m_data->v[i].gb = gb;
        m_data->v[i].cb_true = cb_true;
        m_data->v[i].cb_false = cb_false;
        m_data->v[i].btn_save = btn;

        layout->addWidget(gb);
    }

    m_auto_response->connect_output(boost::bind(
                &AutoResponseWidget::notifyRequest, this, _1));

    setLayout(layout);
}

void AutoResponseWidget::requestReceived(event::request_ptr req)
{
    m_auto_response->new_input_message(req);
}

void AutoResponseWidget::notifyRequest(event::request_ptr req)
{
    emit sendRequest(req);
}


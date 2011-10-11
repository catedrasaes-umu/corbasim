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
#include <iostream>

using namespace corbasim::qt::python;

namespace  
{

struct item_data
{
    corbasim::tag_t tag;
    QGroupBox * gb;
    QCheckBox * chk;
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
    QObject::connect(m_data->g, SIGNAL(buttonClicked(int)),
            this, SLOT(saveConfig(int)));
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

        m_data->v[i].tag = iop->get_tag();

        QGroupBox * gb = new QGroupBox(iop->get_name(), this);

        QGridLayout * gbLayout = new QGridLayout;
        gb->setLayout(gbLayout);

        m_data->v[i].chk = new QCheckBox("Enable");
        gbLayout->addWidget(m_data->v[i].chk, 0, 0);

        gbLayout->addWidget(new QLabel("Guard"), 1, 0);
        gbLayout->addWidget(new QLabel("Response if true"), 0, 1);
        gbLayout->addWidget(new QLabel("Response if false"), 0, 2);

        QComboBox * cb_true = new QComboBox;
        QComboBox * cb_false = new QComboBox;

        // No response
        cb_true->addItem("(No response)", 0);
        cb_false->addItem("(No response)", 0);

        for (unsigned int j = 0; j < ocount; j++) 
        {
            gui::operation_factory_base * op = 
                output_factory->get_factory_by_index(j);
            const char * name = op->get_name();

            tag_t otag = op->get_tag();
            cb_true->addItem(name, otag);
            cb_false->addItem(name, otag);
        }

        gbLayout->addWidget(cb_true, 1, 1);
        gbLayout->addWidget(cb_false, 1, 2);

        // Code
        QTextEdit * te = new QTextEdit;
        m_data->v[i].te_guard = te; 
        gbLayout->addWidget(te, 2, 0);
        te = new QTextEdit;
        m_data->v[i].te_true = te; 
        gbLayout->addWidget(te, 2, 1);
        te = new QTextEdit;
        m_data->v[i].te_false = te; 
        gbLayout->addWidget(te, 2, 2);

        // Button and checkbox
        QHBoxLayout * hLayout = new QHBoxLayout;
        hLayout->addItem(new QSpacerItem(40, 20, 
                    QSizePolicy::Expanding, QSizePolicy::Minimum));
        QPushButton * btn = new QPushButton("Save");
        m_data->g->addButton(btn, i);
        hLayout->addWidget(btn);

        gbLayout->addLayout(hLayout, 3, 0, 1, 3);

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

void AutoResponseWidget::saveConfig(int idx)
{
    std::cout << "Saving configuration for: " << idx << std::endl;

    corbasim::python::auto_response_config_ptr cfg(
            new corbasim::python::auto_response_config);

    item_data& data = m_data->v[idx];

    cfg->active = data.chk->isChecked();
    cfg->input_message = data.tag;

    int cur = data.cb_true->currentIndex();
    cfg->true_output_message = (tag_t)
        data.cb_true->itemData(cur).toUInt();

    cur = data.cb_false->currentIndex();
    cfg->false_output_message = (tag_t) 
        data.cb_false->itemData(cur).toUInt();

    // Code
    cfg->guard = data.te_guard->toPlainText().toStdString();
    cfg->true_transformation = 
        data.te_true->toPlainText().toStdString();
    cfg->false_transformation = 
        data.te_false->toPlainText().toStdString();

    m_auto_response->configure(cfg); 
}


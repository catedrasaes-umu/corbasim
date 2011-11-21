// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Servant.cpp
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

#include "Servant.hpp"

using namespace corbasim::app::view;

Servant::Servant(QMdiArea * area,
        const QString& id, gui::gui_factory_base* factory,
        QObject * parent) :
    QObject(parent), m_mdi_area(area), m_id(id), m_factory(factory)
{
    QString menu_entry = QString("%1 (%2)").arg(m_id);
    // TODO menu_entry.arg(factory->get_core_factory()->get_name());

    m_menu = new QMenu(menu_entry);
    // TODO
    m_menu->addSeparator();
    m_menu->addAction("&Delete", this, SLOT(deleteServant()));
}

Servant::~Servant()
{
    std::cout << "Deleting: " << m_id.toStdString() << std::endl;

    m_menu->deleteLater();
}

QMenu * Servant::getMenu() const
{
    return m_menu;
}

void Servant::deleteServant()
{
    emit deleteServant(m_id);
}




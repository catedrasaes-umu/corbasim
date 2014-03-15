// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ClientApp.hpp
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

#ifndef CORBASIM_GUI_CLIENTAPP_HPP
#define CORBASIM_GUI_CLIENTAPP_HPP

#include <QApplication>

class QWidget;

namespace corbasim
{
namespace gui
{

class ClientApp
{
public:

    ClientApp(const char * fqn);
    ~ClientApp();

    QWidget * window() const;

protected:
    struct ClientData;
    ClientData * m_data;
};

} // namespace gui
} // namespace corbasim

#endif /* CORBASIM_GUI_CLIENTAPP_HPP */


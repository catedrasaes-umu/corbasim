// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * test.cpp
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

#include <iostream>
#include "appC.h"
#include "app_adapted.hpp"
#include <corbasim/impl.hpp>
#include <corbasim/qt/ReferenceModel.hpp>
#include <corbasim/qt/types.hpp>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    QComboBox cb;

    corbasim::qt::ReferenceModel refm;

    cb.setModel(&refm);

    refm.appendItem("my-id", CORBA::Object_var());

    QVariant v = cb.itemData(0);

    std::cout << v.canConvert< CORBA::Object_var >() << std::endl;
    cb.show();

    return app.exec();
}

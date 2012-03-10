// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * json.cpp
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

#include "json.hpp"

namespace corbasim 
{
namespace reflective_gui 
{

void toJson(json::ostream_writer_t& os, const QVariant& var)
{
    QVariant::Type type = var.type();

    switch(type)
    {
    case QVariant::Map:
        {
            const QVariantMap map = var.toMap();

            os.object_start();

            for (QVariantMap::const_iterator it = map.begin(); 
                    it != map.end(); ++it) 
            {
                os.new_string(it.key().toStdString().c_str());
                toJson(os, it.value());
            }

            os.object_end();
        }
        break;
    case QVariant::List:
        {
            const QVariantList list = var.toList();

            os.array_start();

            for (int i = 0; i < list.size(); i++) 
            {
                toJson(os, list.at(i));
            }

            os.array_end();
        }
        break;
    case QVariant::String:    
        {
            os.new_string(var.toString().toStdString().c_str());
        }
        break;
    case QVariant::Bool:
        {
            os.new_bool(var.toBool());
        }
        break;
    default:
        if (var.canConvert< double >())
        {
            os.new_double(var.toDouble());
            break;
        }
        os.new_string("unsupported yet!");
        break;
    }

}

} // namespace reflective_gui
} // namespace corbasim


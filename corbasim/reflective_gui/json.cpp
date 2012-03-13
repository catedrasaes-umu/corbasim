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
#include <fstream>

namespace corbasim 
{
namespace reflective_gui 
{

struct qvariant_helper : public json::helper::helper_base
{
    QVariant& dst;
    QVariantMap map;
    QVariantList list;

    enum NodeType
    {
        VARIANT,
        MAP,
        LIST
    };

    NodeType type;

    qvariant_helper(QVariant& dst_) : dst(dst_), type(VARIANT)
    {
    }

    virtual ~qvariant_helper()
    {
        switch(type)
        {
        case MAP:
            dst = map;
            break;
        case LIST:
            dst = list;
            break;
        default:
            break;
        }
    }

    void new_double(double d)
    {
        dst = d;
    }

    void new_string(const std::string& d)
    {
        dst = d.c_str();
    }

    void new_bool(bool d)
    {
        dst = d;
    }

    void new_null()
    {
        // QVariant is null by default
    }

    json::helper::helper_base* new_child(const std::string& name)
    {
        type = MAP;
        return new qvariant_helper(map[name.c_str()]);
    }

    json::helper::helper_base* new_child()
    {
        type = LIST;

        QVariant tmp;
        list.push_back(tmp);

        return new qvariant_helper(list.last());
    }
};

bool fromJson(QVariant& var, const char * str, size_t size)
{
    qvariant_helper * initial_helper = new qvariant_helper(var);
    json::semantic_state _ss(initial_helper);
    json::state _st(_ss, str, size);

    return csu::corbasim::json::parser::grammar::gram::match(_st);
}

bool fromJsonFile(const char * file, QVariant& var)
{
    int length;
    char * buffer = NULL;
    bool res = false;

    try {

        std::ifstream is(file);

        if (!is.is_open()) return false;
   
        // get length of file:
        is.seekg (0, std::ios::end);
        length = is.tellg();
        is.seekg (0, std::ios::beg);

        // allocate memory:
        buffer = new char [length];

        // read data as a block:
        is.read (buffer, length);
        is.close();

        res = fromJson(var, buffer, length);

    } catch (...) {
    }

    delete [] buffer;

    return res;
}

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


// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.hpp
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

#ifndef CORBASIM_JSON_REFLECTIVE_HPP
#define CORBASIM_JSON_REFLECTIVE_HPP

#include <ostream>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/json/helper.hpp>
#include <corbasim/json/writer.hpp>

namespace corbasim 
{
namespace json 
{

struct reflective_helper : public helper::helper_base
{
    reflective_helper(core::reflective_base const * reflective,
            core::holder holder);

    virtual ~reflective_helper();

    void new_double(double d);

    void new_string(const std::string& d);

    void new_bool(bool d);

    void new_null();

    // For structs
    helper::helper_base* new_child(const std::string& name);

    // For arrays
    helper::helper_base* new_child();

    core::reflective_base const * m_reflective;
    core::holder m_holder;
    unsigned int m_currentIndex;
};

typedef csu::corbasim::json::writer::json_writer< std::ostream > 
    std_writer_t;

void write(std_writer_t& w, 
        corbasim::core::reflective_base const * reflective, 
        corbasim::core::holder holder);

bool parse(core::reflective_base const * reflective, 
        core::holder& holder, const char * str, size_t size);

void write(std::ostream& os, core::reflective_base const * reflective, 
        core::holder& holder, bool indent = false);

} // namespace json
} // namespace corbasim

#endif /* CORBASIM_JSON_REFLECTIVE_HPP */


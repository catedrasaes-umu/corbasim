// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * file_format_helper.hpp
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

#ifndef CORBASIM_CORE_FILE_HELPER_HPP
#define CORBASIM_CORE_FILE_HELPER_HPP

#include <ostream>
#include <istream>
#include <corbasim/core/reflective_fwd.hpp>

namespace corbasim 
{
namespace core 
{

enum file_format
{
    FILE_FORMAT_BINARY,
    FILE_FORMAT_TEXT,
    FILE_FORMAT_JSON
};

class file_format_helper;

class file_format_factory
{
public:

    ~file_format_factory();

    static const file_format_factory* get_instance();

    const file_format_helper* get_helper(file_format format) const;

protected:

    file_format_factory();
};

class file_format_helper
{
public:

    virtual ~file_format_helper();

    virtual bool load(std::istream& is, 
            reflective_base const * reflective, 
            holder h) const = 0; 

    virtual bool save(std::ostream& os, 
            reflective_base const * reflective, 
            holder h) const = 0; 

protected:

    file_format_helper();
};

class json_file_format_helper : public file_format_helper
{
public:

    virtual ~json_file_format_helper();

    bool load(std::istream& is, 
            reflective_base const * reflective, 
            holder h) const; 

    bool save(std::ostream& os, 
            reflective_base const * reflective, 
            holder h) const; 

    static const json_file_format_helper* get_instance();

protected:

    json_file_format_helper();
};

class text_file_format_helper : public file_format_helper
{
public:

    virtual ~text_file_format_helper();

    bool load(std::istream& is, 
            reflective_base const * reflective, 
            holder h) const; 

    bool save(std::ostream& os, 
            reflective_base const * reflective, 
            holder h) const; 

    static const text_file_format_helper* get_instance();

protected:

    text_file_format_helper();
};

class binary_file_format_helper : public file_format_helper  
{
public:

    virtual ~binary_file_format_helper();

    bool load(std::istream& is, 
            reflective_base const * reflective, 
            holder h) const; 

    bool save(std::ostream& os, 
            reflective_base const * reflective, 
            holder h) const; 

    static const binary_file_format_helper* get_instance();

protected:

    binary_file_format_helper();
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_FILE_HELPER_HPP */


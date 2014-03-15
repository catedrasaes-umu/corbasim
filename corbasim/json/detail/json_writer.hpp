// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * json_writer.hpp
 * Copyright (C) Cátedra SAES-UMU 2010 <catedra-saes-umu@listas.um.es>
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

#ifndef CORBASIM_JSON_IMPL_JSON_WRITER_HPP
#define CORBASIM_JSON_IMPL_JSON_WRITER_HPP

#include <string>
#include <deque>
#include <exception> // Exceptions
#include <stdexcept>
#include <corbasim/json/detail/json.hpp>

namespace csu
{
namespace corbasim
{
namespace json
{
namespace writer
{

inline void encode(std::string& data)
{
    // Fast check for the most common case
    size_t pos;
    if (std::string::npos == (pos = data.find_first_of("\\\"")))
    return;

    std::string buffer;
    buffer.reserve(data.size());
    // Copy the first part, if it exists
    if (pos)
        buffer.append(&data[0], pos);
    for(; pos != data.size(); ++pos)
    {
        switch(data[pos])
        {
            case '"':  buffer.append("\\\"");       break; // Only " here
            case '\\': buffer.append("\\\\");      break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }
    data.swap(buffer);
}


// States
enum State
{
    BEGIN,
    END,

    IN_OBJECT_AWAIT_ID,
    IN_OBJECT_AWAIT_VALUE,

    IN_ARRAY_AWAIT_VALUE
};


// JSON semantic state
template <typename Ostream >
class json_writer
{
    struct state_struct
    {
        State s;
        bool first_in_object_or_array;
    };
    std::deque<state_struct> state_stack;

public:
    json_writer (Ostream& o, bool indent = false) :
        o_ (o), indent_(indent), level_(0)
    {
        state_struct ss = { BEGIN, false };
        state_stack.push_back (ss);
    }

    inline void new_null()
    {
        _check_pre();

        o_ << "null";

        _check_post();
    }

    inline void new_double(double d)
    {
        _check_pre();

        // TODO: optimize
        o_ << d;

        _check_post();
    }

    inline void new_string(match_pair  const& p)
    {
        _check_pre();

        std::string s (p.first, p.second);
        encode (s);
        o_ << '"' << s << '"';

        _check_post();
    }

    // Overload for ASCIIZ. This allows not having to pre-calculate
    // the string size for C strings.
    inline void new_string (const char* s)
    {
        _check_pre();

        std::string ss (s);
        encode (ss);
        o_ << '"' << ss << '"';

        _check_post();
    }

    inline void new_bool(bool b)
    {
        _check_pre();

        o_ << (b ? "true" : "false");

        _check_post();
    }

    inline void object_start()
    {
        _check_pre();

        state_struct ss = { IN_OBJECT_AWAIT_ID, true };
        state_stack.push_back (ss);

        o_ << "{";
        ++level_;
        _indent();
    }

    inline void object_end()
    {
        state_stack.pop_back();

        --level_;

        _indent();
        o_ << "}";

        _check_post();
    }

    inline void array_start()
    {
        _check_pre();

        state_struct ss  = { IN_ARRAY_AWAIT_VALUE, true};
        state_stack.push_back (ss);

        o_ << "[";
        ++level_;
        _indent();
    }

    inline void array_end()
    {
        state_stack.pop_back();

        --level_;

        _indent();
        o_ << "]";

        _check_post();
    }

    inline Ostream& ostream()
    {
        _check_pre();
        _check_post();
        return o_;
    }

private:

    inline void _indent()
    {
        if (indent_)
        {
            o_ << '\n';
            for (int i = 0; i < level_; i++)
                o_<< "    ";
        }
    }

    inline void _check_pre()
    {
        state_struct& ss = state_stack.back();
        if (ss.s == IN_OBJECT_AWAIT_ID ||
            ss.s == IN_ARRAY_AWAIT_VALUE)
        {
            if (!ss.first_in_object_or_array)
            {
                o_ << ",";

                _indent();
            }
            else
                ss.first_in_object_or_array = false;
        }
        else if (ss.s == IN_OBJECT_AWAIT_VALUE)
        {
            // Output the ":"
            o_ << ":";

            if (indent_)
                o_ << ' ';
        }
    }

    inline void _check_post()
    {
        state_struct& ss = state_stack.back();
        if (ss.s == IN_OBJECT_AWAIT_VALUE)
            ss.s = IN_OBJECT_AWAIT_ID;
        else if (ss.s == IN_OBJECT_AWAIT_ID)
            ss.s = IN_OBJECT_AWAIT_VALUE;
    }

    Ostream& o_;
    bool indent_;
    int level_;
};


} // writer
} // json
} // mycorba
} // csu


#endif

// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * base64_blob.hpp
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

#ifndef CORBASIM_JSON_IMPL_BASE64_BLOB_HPP
#define CORBASIM_JSON_IMPL_BASE64_BLOB_HPP

#include <corbasim/json/detail/modp_b64.h>

namespace csu
{
namespace corbasim
{
namespace json
{
namespace writer
{

struct base64_blob_emitter
{
    template<typename Ostream>
    static void new_blob_to_ostream (Ostream& os, match_pair const& p)
    {
        size_t outlen = modp_b64_encode_len (p.second);
        char* outbuf = new char[outlen + 1];

        // length
        os << outlen  << ":";

        // body
        ::modp_b64_encode(outbuf, p.first, p.second);
        os.write(outbuf, outlen);
        delete outbuf;
    }
};

struct base64_blob_reader
{
    static size_t decode_blob_length (const char* p)
    {
        const char* q = p;
        size_t outlen = 0;

        // Do this manually. Just easy
        while (*q != ':')
        {
            outlen *= 10;
            outlen += *q - '0';
            ++q;
        }

        // NOTE: The output length includes the base64 and the length
        // itself, including the ':'
        return outlen + (q - p) + 1;
    }

    static void decode_blob (char* dest, const char*p, size_t len)
    {
        // NOTE: Length includes the representation of length, the ':',
        // and the base64

        // Strip length
        while (*p != ':')
        {
            ++p;
            --len;
        }

        // Skip ':'
        ++p;
        --len;

        ::mdop_b64_decode (dest, p, len);
    }
};


} // writer
} // json
} // mycorba
} // csu


#endif


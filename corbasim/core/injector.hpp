// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * injector.hpp
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

#ifndef CORBASIM_CORE_INJECTOR_HPP
#define CORBASIM_CORE_INJECTOR_HPP

#include <vector>
#include <fstream>
#include <corbasim/core/caller.hpp>
#include <corbasim/core/request_serializer.hpp>

namespace corbasim 
{
namespace core 
{

template< typename Interface >
class injector
{
public:
    typedef interface_caller< Interface > caller_t;
    typedef request_serializer< Interface > serializer_t;
    typedef std::vector< event::request_ptr > requests_t;

    injector() : 
        m_delay(0)
    {
    }

    void set_reference(Interface * ref)
    {
        m_caller.set_reference(ref);
    }

    void run()
    {
        for (requests_t::iterator it = m_requests.begin(); 
                it != m_requests.end(); ++it) 
        {
            delete m_caller.do_call(it->get());
        }
    }

    void append_file(const char * file)
    {
        serializer_t * serializer = serializer_t::get_instance();
        std::ifstream ifs(file);

        try {
            while(ifs.good())
            {
                event::request_ptr _request(serializer->load(ifs));

                if (!_request)
                    continue;

                m_requests.push_back(_request);
            }
        } catch (...) 
        {
            std::cerr << "Error loading file: " << file << std::endl;
        }

    }

protected:
    caller_t m_caller;
    requests_t m_requests;
    unsigned int m_delay;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_INJECTOR_HPP */


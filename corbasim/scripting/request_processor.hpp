// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * request_processor.hpp
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

#ifndef CORBASIM_SCRIPTING_REQUEST_PROCESSOR_HPP
#define CORBASIM_SCRIPTING_REQUEST_PROCESSOR_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/scripting/interpreter.hpp>
#include <corbasim/core/factory_fwd.hpp>

namespace corbasim 
{
namespace scripting 
{

class request_processor;
typedef boost::shared_ptr< request_processor > request_processor_ptr;

/**
 * @brief Executes some trigger code into an interpreter.
 */
class request_processor 
{
public:

    struct configuration
    {
        bool active;
        tag_t request_type;
        std::string code;
    };

    typedef boost::shared_ptr< configuration > configuration_ptr;
    
    typedef std::map< tag_t, configuration_ptr > config_t;


    request_processor(interpreter_ptr interpreter_,
            core::factory_base * factory_);

    virtual ~request_processor();

    void process_message(event::request_ptr req);
    
    void configure(configuration_ptr config);

protected:

    config_t m_config;

    interpreter_ptr m_interpreter;
    
    core::factory_base * m_factory;
};

} // namespace scripting
} // namespace corbasim

#endif /* CORBASIM_SCRIPTING_REQUEST_PROCESSOR_HPP */


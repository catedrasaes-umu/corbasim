// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * auto_response.cpp
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

#include "auto_response.hpp"
#include <boost/bind.hpp>
#include <boost/python.hpp>
#include <iostream>

using namespace corbasim::python;

namespace corbasim
{
namespace python
{

struct auto_response_data
{
    boost::python::object main;
    boost::python::object global;
};

} // namespace python
} // namespace corbasim

auto_response::auto_response(core::factory_base * input_factory,
        core::factory_base * output_factory) :
    m_input_factory(input_factory), m_output_factory(output_factory),
    m_work(m_io_service), m_data(new auto_response_data)
{
    // TODO inicializar solo una vez
    Py_Initialize();

    // TODO configuration write mutex
    // threads -> m_io_service.run()
    for (int i = 0; i < 1; i++) 
        m_threads.create_thread(boost::bind(&boost::asio::io_service::run,
                    &m_io_service));

    m_data->main = boost::python::import("__main__");
    m_data->global = m_data->main.attr("__dict__");
}

auto_response::~auto_response()
{
    m_io_service.stop();
    m_threads.join_all();

    delete m_data;
}

void auto_response::load_config(const std::string& file) {}
void auto_response::save_config(const std::string& file) {}

void auto_response::new_input_message(event::request_ptr req)
{
    m_io_service.post(boost::bind(
                &auto_response::process_input_message, this, req));
}

void auto_response::process_input_message(event::request_ptr req)
{
    std::cout << "Processing input message" << std::endl;
    
    // TODO
    tag_t tag = req->get_tag();
    config_t::const_iterator it = m_config.find(tag);

    try {
        if (it != m_config.end() && it->second->active)
        {
            std::string json_request;
            m_input_factory->get_factory_by_tag(
                    tag)->to_json(req.get(), json_request);

            std::cout << "JSON request: " << json_request << std::endl;

            bool evaluated_guard = it->second->guard.empty();

            // TODO añadir json_request como input a global
            
            if(!evaluated_guard)
            {
                std::cout << "Evaluating guard" << std::endl;
                // evalua guarda
                boost::python::object res = boost::python::exec(
                        it->second->guard.c_str(),
                        m_data->global,
                        m_data->global);

                evaluated_guard = boost::python::extract< bool >(res);
            }

            tag_t response_tag = (evaluated_guard)? 
                it->second->true_output_message :
                it->second->false_output_message; 

            const std::string& transformation = (evaluated_guard)? 
                it->second->true_transformation : 
                it->second->false_transformation;

            core::operation_factory_base * factory = 
                m_output_factory->get_factory_by_tag(response_tag);

            std::cout << "Response tag: " << response_tag  << std::endl;

            // Asume que la configuración se ha validado
            if (factory)
            {
#if 0
                // evalua transformación
                boost::python::object res = boost::python::exec(
                        transformation.c_str(),
                        m_data->global,
                        m_data->global);

                // TODO pasar res a json
#endif
                const std::string json_response;
#if 0
                const std::string json_response = 
                    boost::python::extract< std::string >(res);
#endif
                event::request_ptr response(
                        factory->from_json(json_response));

                std::cout << "JSON response: " << json_response 
                    << std::endl;

                std::cout << "Sending response" << std::endl;
                m_output_signal(response);
            }
        }
    } catch(...) {
        std::cout << "Processing exception" << std::endl;
    }
}

void auto_response::configure(auto_response_config_ptr config)
{
    std::cout << "Configure" << std::endl;

    // TODO validar configuración
    m_io_service.post(boost::bind(
                &auto_response::apply_configuration, this, config));
}

void auto_response::apply_configuration(auto_response_config_ptr config)
{
    std::cout << "Applying configuration" << std::endl;

    // Copy the configuration
    auto_response_config_ptr new_config(
            new auto_response_config(*config.get()));

    m_config.insert(std::make_pair(new_config->input_message,
                new_config));
}


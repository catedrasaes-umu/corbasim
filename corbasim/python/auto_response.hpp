// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * auto_response.hpp
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

#ifndef CORBASIM_PYTHON_AUTO_RESPONSE_HPP
#define CORBASIM_PYTHON_AUTO_RESPONSE_HPP

#include <string>
#include <map>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <corbasim/event.hpp>
#include <corbasim/core/factory_fwd.hpp>

namespace corbasim 
{
namespace python 
{

struct auto_response_config
{
    bool active;

    tag_t input_message;
    std::string guard;

    std::string true_transformation;
    tag_t true_output_message;

    std::string false_transformation;
    tag_t false_output_message;
};

typedef boost::shared_ptr< auto_response_config > 
    auto_response_config_ptr;

struct auto_response_data;

class auto_response
{
public:

    auto_response(core::factory_base * input_factory,
            core::factory_base * output_factory);

    virtual ~auto_response();

    void load_config(const std::string& file);
    void save_config(const std::string& file);

    void configure(auto_response_config_ptr config);
    void new_input_message(event::request_ptr req);

    // Signals

    typedef boost::signals2::signal< void (event::request_ptr) > 
        request_signal_t;

    typedef boost::signals2::signal< void (auto_response_config_ptr) > 
        config_signal_t;

    // Signal Connection

    template< typename T >
    inline void connect_output(T t)
    {
        m_output_signal.connect(t);
    }

    template< typename T >
    inline void connect_config(T t)
    {
        m_config_signal.connect(t);
    }

protected:

    core::factory_base * m_input_factory;
    core::factory_base * m_output_factory;

    typedef std::map< tag_t, auto_response_config_ptr > config_t;
    config_t m_config;

    request_signal_t m_output_signal;
    config_signal_t m_config_signal;

    // Worker
    boost::asio::io_service m_io_service;
    boost::asio::io_service::work m_work;
    boost::thread_group m_threads;

    // Methods in worker thread
    void apply_configuration(auto_response_config_ptr config);
    void process_input_message(event::request_ptr req);

    auto_response_data * m_data;

};

} // namespace python
} // namespace corbasim

#endif /* CORBASIM_PYTHON_AUTO_RESPONSE_HPP */


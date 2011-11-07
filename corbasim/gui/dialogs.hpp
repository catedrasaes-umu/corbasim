// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * dialogs.hpp
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

#ifndef CORBASIM_DIALOGS_HPP
#define CORBASIM_DIALOGS_HPP

#include <boost/shared_ptr.hpp>
#include <sstream>

#include <corbasim/event.hpp>
#include <corbasim/gui/widgets/struct.hpp>
#include <corbasim/json/parser.hpp>
#include <corbasim/json/writer.hpp>

namespace corbasim 
{
namespace dialogs 
{
namespace detail 
{

template< typename Value >
struct only_inargs
{
    /**
     * @brief Lista de argumentos.
     */
    typedef typename Value::_arg_list arg_list;

    template< typename N >
    struct apply : 
        public cs_mpl::is_inarg< typename boost::mpl::at< arg_list, N >::type >
    {};
};

} // namespace detail

struct input_base
{
    virtual event::request* create_request() = 0;
    virtual void copy_from_request(event::request*) = 0;
    virtual QWidget* get_qwidget() = 0;
    virtual void from_json(const std::string& str) = 0;
    virtual void to_json(std::string& str) = 0;

    virtual const char * get_name() const = 0;
    
    virtual ~input_base() {}
};

typedef boost::shared_ptr< input_base > input_ptr;

/**
 * @brief El díalogo input de una operación es un formulario con los 
 *        parámetros de tipo IN e INOUT.
 *
 * @tparam Value
 */
template< typename Value >
struct input : 
    public input_base, 
    public widgets::detail::struct_as_grid< Value, 
        detail::only_inargs < Value > > 
{
    typedef event::request_impl< Value > request_t;

    event::request* create_request()
    {
        request_t * request = new request_t;
        get_value(request->m_values);

        return request;
    }
    
    void copy_from_request(event::request* req)
    {
        request_t * impl = static_cast< request_t* >(req);
        set_value(impl->m_values);
    }
    
    typedef widgets::detail::struct_as_grid< Value, 
        detail::only_inargs < Value > > widget_t;

    QWidget* get_qwidget()
    {
        return widget_t::get_QWidget();
    }
    
    void from_json(const std::string& str)
    {
        Value value;
        json::parse(value, str);
        set_value(value);
    }
     
    void to_json(std::string& str)
    {
        std::ostringstream ss;
        // Get value
        Value value;
        get_value(value);

        // Serializing
        json::write(ss, value);
        str = ss.str();
    }
    
    const char * get_name() const
    {
        return adapted::name< Value >::call(); 
    }
};

} // namespace dialogs
} // namespace corbasim

#endif /* CORBASIM_DIALOGS_HPP */


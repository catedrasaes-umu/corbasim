// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * dialogs_fwd.hpp
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

#ifndef CORBASIM_DIALOGS_FWD_HPP
#define CORBASIM_DIALOGS_FWD_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/event_fwd.hpp>

class QWidget;

namespace corbasim 
{
namespace dialogs 
{

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

} // namespace dialogs
} // namespace corbasim

#endif /* CORBASIM_DIALOGS_FWD_HPP */


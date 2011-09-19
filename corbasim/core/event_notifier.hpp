// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * event_notifier.hpp
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

#ifndef CORBASIM_CORE_EVENT_NOTIFIER_HPP
#define CORBASIM_CORE_EVENT_NOTIFIER_HPP

#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <corbasim/event.hpp>

namespace corbasim 
{
namespace core 
{

class event_notifier
{
public:

    typedef boost::signals2::signal< void (event::event_ptr) > 
        event_signal_t;

    static event_notifier * get_instance();

    void notify(event::event_ptr ev);
    
    template< typename T >
    inline void connect(T t)
    {
        m_event_signal.connect(t);
    }

protected:

    event_notifier();

    event_signal_t m_event_signal;
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_EVENT_NOTIFIER_HPP */


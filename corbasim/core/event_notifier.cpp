// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * event_notifier.cpp
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

#include "event_notifier.hpp"
#include <boost/shared_ptr.hpp>

using namespace corbasim::core;

event_notifier::event_notifier()
{
}

event_notifier * event_notifier::get_instance()
{
    static boost::shared_ptr< event_notifier > 
        _instance(new event_notifier);

    return _instance.get();
}

void event_notifier::notify(event::event_ptr ev)
{
    m_event_signal(ev);
}


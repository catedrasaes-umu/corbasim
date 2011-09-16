// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestNotifier.hpp
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

#ifndef CORBASIM_QT_REQUESTNOTIFIER_HPP
#define CORBASIM_QT_REQUESTNOTIFIER_HPP

#include <QObject>
#include <corbasim/event.hpp>

namespace corbasim 
{
namespace qt 
{

class RequestNotifier : public QObject 
{
public:
    RequestNotifier (QObject * parent = 0) {}
    virtual ~RequestNotifier () {}

    template< typename Value >
    inline void operator()(const Value& val)
    {
        event::request_ptr _request(new event::request_impl< Value >(val));
        emit notifyRequest(_request);
    }

signals:
    void notifyRequest(corbasim::event::request_ptr);
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_REQUESTNOTIFIER_HPP */


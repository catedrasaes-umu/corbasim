// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * sequence_fwd.hpp
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

#ifndef CORBASIM_WIDGETS_SEQUENCE_FWD_HPP
#define CORBASIM_WIDGETS_SEQUENCE_FWD_HPP

class QWidget;

namespace corbasim 
{
namespace widgets 
{

struct abstract_sequence_widget
{
    virtual QWidget * get_child_widget() const = 0;
    virtual void set_length(unsigned int length) = 0;
    virtual void change_to(unsigned int index) = 0;
};

} // namespace widgets
} // namespace corbasim

#endif /* CORBASIM_WIDGETS_SEQUENCE_FWD_HPP */


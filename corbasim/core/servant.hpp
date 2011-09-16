// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * servant.hpp
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

#ifndef CORBASIM_CORE_SERVANT_HPP
#define CORBASIM_CORE_SERVANT_HPP

#include <boost/shared_ptr.hpp>
#include <corbasim/adapted.hpp>

namespace corbasim 
{
namespace core 
{

struct servant_base
{
};

template< typename Inteface >
struct servant : public servant_base
{
    typedef adapted::servant< Interface > servant_t;

    static inline servant* get_instance()
    {
        static boost::shared_ptr< servant > _instance(new servant);
        return _instance.get();
    }
};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_SERVANT_HPP */


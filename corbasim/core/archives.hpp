// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * archives.hpp
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

#ifndef CORBA_CORE_ARCHIVES_HPP
#define CORBA_CORE_ARCHIVES_HPP

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace corbasim 
{
namespace core 
{

class text_oarchive : 
    public boost::archive::text_oarchive_impl < text_oarchive >
{
public:

    typedef boost::archive::text_oarchive_impl < text_oarchive >
        parent_type;

    text_oarchive(std::ostream& os) :
        parent_type(os, boost::archive::no_header)
    {
    }

    void save_override(const boost::archive::class_id_optional_type & t, int version)
    {
    }

    void save_override(const boost::archive::tracking_type & t, int version)
    {
    }

    void save_override(const boost::archive::version_type & t, int version)
    {
    }

    template< class T >
    void save(const T & t)
    {
        parent_type::save(t);
    }

    template < class T > void save_override(const T & t, int version)
    {
        parent_type::save_override(t, version);
    }
};

class text_iarchive : 
    public boost::archive::text_iarchive_impl < text_iarchive >
{
public:

    typedef boost::archive::text_iarchive_impl < text_iarchive >
        parent_type;

    text_iarchive(std::istream& is) :
        parent_type(is, boost::archive::no_header)
    {
    }

    void load_override(boost::archive::class_id_optional_type & t, int version)
    {
    }

    void load_override(boost::archive::tracking_type & t, int version)
    {
    }

    void load_override(boost::archive::version_type & t, int version)
    {
    }

    template < class T > void load_override(T & t, int version)
    {
        parent_type::load_override(t, version);
    }

    template< class T >
    void load(T & t)
    {
        parent_type::load(t);
    }

};

} // namespace core
} // namespace corbasim

#endif /* CORBA_CORE_ARCHIVES_HPP */


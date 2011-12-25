// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * request_serializer.hpp
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

#ifndef CORBASIM_CORE_REQUEST_SERIALIZER_HPP
#define CORBASIM_CORE_REQUEST_SERIALIZER_HPP

#include <ostream>
#include <istream>
#include <sstream>
#include <map>
#include <boost/shared_ptr.hpp>

#include <corbasim/adapted.hpp>
#include <corbasim/event.hpp>
#include <corbasim/core/archives.hpp>
#include <corbasim/core/inserter.hpp>

namespace corbasim 
{
namespace core 
{

struct request_serializer_base
{
    virtual void save(std::ostream& os, event::request* req) const = 0;
    virtual event::request* load(std::istream& is) const = 0;
    
    virtual ~request_serializer_base() {}
};

typedef boost::shared_ptr< request_serializer_base > request_serializer_ptr;

template< typename Value >
struct request_serializer_operation : public request_serializer_base
{
    void save(std::ostream& os, event::request* req) const
    {
        request_t * impl = static_cast< request_t * >(req);

        text_oarchive toa(os);
        toa << impl->m_values;
    }

    event::request* load(std::istream& is) const
    {
        request_t * impl = new request_t;

        text_iarchive tia(is);
        tia >> impl->m_values;

        return impl;
    }

    typedef event::request_impl< Value > request_t;

    static inline request_serializer_base * get_instance()
    {
        
        typedef boost::shared_ptr< request_serializer_operation > 
            impl_type;
        static impl_type _instance(new request_serializer_operation);
        return _instance.get();
    }
};

struct request_serializer_impl : public request_serializer_base
{
    void save(std::ostream& os, event::request * req) const;

    event::request * load(std::istream& is) const;

    // Data
    typedef std::map< tag_t, request_serializer_base* > serializers_t; 
    serializers_t m_serializers;

    typedef std::map< std::string, request_serializer_base* > 
        serializers_by_name_t; 
    serializers_by_name_t m_serializers_by_name;
};

template < typename Interface >
struct request_serializer : public request_serializer_impl
{
    request_serializer()
    {
        typedef typename interface_t::_op_list operations_t;
        typedef impl::inserter< request_serializer > inserter_t;
        cs_mpl::for_each_list< operations_t >(inserter_t(this));
    }

    typedef adapted::interface< Interface > interface_t;

    template < typename Value >
    void append()
    {
        typedef request_serializer_operation< Value > serializer_t;

        m_serializers.insert(std::make_pair(
                    tag< Value >::value(),
                    serializer_t::get_instance()));
        m_serializers_by_name.insert(std::make_pair(
                    adapted::name< Value >::call(),
                    serializer_t::get_instance()));
    }

    static inline request_serializer * get_instance()
    {
        typedef boost::shared_ptr< request_serializer > impl_type;
        static impl_type _instance(new request_serializer);
        return _instance.get();
    }

};

} // namespace core
} // namespace corbasim

#endif /* CORBASIM_CORE_REQUEST_SERIALIZER_HPP */


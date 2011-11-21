// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * helper.hpp
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

#ifndef CORBASIM_JSON_HELPER_HPP
#define CORBASIM_JSON_HELPER_HPP

#include <string>
#include <map>
#include <vector>
#include <deque>
#include <boost/shared_ptr.hpp>
//#include <boost/variant.hpp> // TODO
#include <corbasim/adapted.hpp>

namespace corbasim 
{
namespace json 
{
namespace helper 
{

struct helper_base;

template< typename T >
inline helper_base * create_helper(T& t);

template< typename Write, typename T >
inline void helper_write(Write& w, const T& t);

struct helper_base
{
    virtual void new_double(double d)
    {
        throw "Error!";
    }

    virtual void new_string(const std::string& d)
    {
        throw "Error!";
    }

    virtual void new_bool(bool d)
    {
        throw "Error!";
    }

    virtual void new_null()
    {
        throw "Error!";
    }

    // For structs
    virtual helper_base* new_child(const std::string& name)
    {
        throw "Error!";
    }

    // For arrays
    virtual helper_base* new_child()
    {
        throw "Error!";
    }

    virtual ~helper_base() {}

    template< typename Writer, typename T >
    static inline void write(const Writer& os, const T& t)
    {
        throw "Error!";
    }
};

namespace detail 
{

template< typename T >
struct unsupported_type_helper : public helper_base
{
    unsupported_type_helper(const T& t) {}
};

struct bool_helper : public helper_base
{
    bool& _b;
    bool_helper(bool& b) :
        _b(b)
    {
    }

    void new_bool(bool b)
    {
        _b = b;
    }

    template< typename Writer >
    static inline void write(Writer& w, bool b)
    {
        w.new_bool(b);
    }
};

template< typename T >
struct arithmetic_helper : public helper_base
{
    T& _t;
    arithmetic_helper(T& t) :
        _t(t)
    {
    }

    void new_double(double d)
    {
        _t = (T) d;
    }

    template< typename Writer >
    static inline void write(Writer& w, T t)
    {
        w.new_double((double) t);
    }
};

template< typename S >
struct helper_factory
{
    virtual helper_base * create(S& s) const = 0;
    virtual ~helper_factory() {}
};

template< typename S, typename N >
struct helper_factory_impl : public helper_factory< S >
{
    helper_base * create(S& s) const
    {
        return create_helper(boost::fusion::at< N >(s));
    }

    static inline helper_factory_impl const * get_instance()
    {
        typedef boost::shared_ptr< helper_factory_impl > ptr_t;
        static ptr_t _ptr(new helper_factory_impl);
        return _ptr.get();
    }
};

namespace iterator 
{
// Iteracion sobre una estructura
template < typename S, typename N >
struct StructImpl
{
    // Valor de N en la siguiente iteracion
    typedef typename boost::mpl::next < N >::type next_t;

    // Tipo que contiene el nombre del campo actual
    typedef cs_mpl::name_of_member< S, N > name_t;

    // Helper factory del campo actual
    typedef helper_factory_impl< S, N > factory_t;

    template< typename Map >
    static inline void insert(Map& map)
    {
        map.insert(std::make_pair(name_t::call(), 
                    factory_t::get_instance()));

        // Siguiente iteracion
        StructImpl < S, next_t >::insert(map);
    }

    template< typename Writer >
    static inline void write(Writer& w, const S& t)
    {
        w.new_string(name_t::call());
        helper_write(w, boost::fusion::at< N >(t));
        
        // Siguiente iteracion
        StructImpl < S, next_t >::write(w, t);
    }
};

// Fin de la iteracion sobre estructuras.
template < typename S >
struct StructImpl < S, typename cs_mpl::number_of_members< S >::type >
{
    template< typename Map >
    static inline void insert(const Map& /* unused */) {}

    template< typename Writer >
    static inline void write(const Writer& w, const S& t) {}
};

// Iterador sobre una estructura. Template fachada.
template < typename S >
struct Struct: public StructImpl < S, boost::mpl::int_ < 0 > >
{
};

} // namespace iterator

template< typename S >
struct helper_factories
{
    typedef helper_factory< S > factory_base;
    typedef std::map< std::string, factory_base const* > factories_t;
    factories_t m_factories;

    helper_factories()
    {
        iterator::Struct< S >::insert(m_factories);
    }

    helper_base * create(S& s, const std::string& name) const
    {
        // look up the map
        typename factories_t::const_iterator it = m_factories.find(name);

        if (it != m_factories.end())
            return it->second->create(s);

        throw "Error!";
    }

    static inline helper_factories const * get_instance()
    {
        typedef boost::shared_ptr< helper_factories > ptr_t;
        static ptr_t _ptr(new helper_factories);
        return _ptr.get();
    }
};

template< typename T >
struct struct_helper : public helper_base
{
    typedef helper_factories< T > factories_t;

    T& _t;
    struct_helper(T& t) :
        _t(t)
    {
    }

    helper_base* new_child(const std::string& name)
    {
        return factories_t::get_instance()->create(_t, name);
    }

    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        w.object_start();
        iterator::Struct< T >::write(w, t);
        w.object_end();
    }
};

template< typename T >
struct enum_helper : public helper_base
{
    typedef adapted::enumeration< T > adapted_t;

    T& _t;
    enum_helper(T& t) :
        _t(t)
    {
    }

    void new_string(const std::string& id)
    {
        const char ** values = adapted_t::values();

        for(int idx = 0; *values; values++, idx++)
            if (id == *values)
            {
                _t = static_cast< T >(idx);
                return;
            }

        throw "Error!";
    }

    template< typename Writer >
    static inline void write(Writer& w, T t)
    {
        const int idx = static_cast< int >(t);
        w.new_string(adapted_t::values()[idx]);
    }
};


template< typename T >
struct array_helper : public helper_base
{
    typedef typename boost::remove_bounds < T >::type slice_t;
    static const size_t size = sizeof(T) / sizeof(slice_t);

    T& _t;
    unsigned int _index;

    array_helper(T& t) :
        _t(t), _index(0)
    {
    }

    helper_base* new_child()
    {
        // check size
        if (_index == size)
            throw "Error!";

        return create_helper(_t[_index++]);
    }
    
    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        w.array_start();

        for (size_t i = 0; i < size; i++) 
            helper_write(w, t[i]);

        w.array_end();
    }
};

// TODO caso especial de las secuencias de strings
template< typename T >
struct corbaseq_helper : public helper_base
{
    T& _t;
    unsigned int _index;

    corbaseq_helper(T& t) :
        _t(t), _index(0)
    {
        _t.length(0);
    }

    helper_base* new_child()
    {
        _t.length(_index + 1);
        return create_helper(_t[_index++]);
    }

    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        w.array_start();

        size_t size = t.length();
        for (size_t i = 0; i < size; i++) 
            helper_write(w, t[i]);

        w.array_end();
    }
};

template< typename T >
struct corbaseq_string_helper : public helper_base
{
    T& _t;
    unsigned int _index;
    typedef typename adapted::is_corbaseq< T >::slice_type slice_type;
    slice_type last_inserted;

    corbaseq_string_helper(T& t) :
        _t(t), _index(0)
    {
        _t.length(0);
    }
    
    ~corbaseq_string_helper()
    {
        if (!(_index == 0))
            _t[_index - 1] = last_inserted;
    }

    helper_base* new_child()
    {
        if (!(_index == 0))
            _t[_index - 1] = last_inserted;

        _t.length(++_index);
        return create_helper(last_inserted);
    }

    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        w.array_start();

        size_t size = t.length();
        for (size_t i = 0; i < size; i++) 
        {
            // TODO try to avoid this copy
            slice_type sl = t[i].in();
            helper_write(w, sl);
        }

        w.array_end();
    }
};

template< typename T >
struct string_helper : public helper_base
{
    T& _t;
    string_helper(T& t) :
        _t(t)
    {
    }

    void new_string(const std::string& d)
    {
        _t = d.c_str();
    }

    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        w.new_string(t.in());
    }
};

template< typename T >
struct corba_objrefvar_helper : public helper_base
{
    T& _t;

    corba_objrefvar_helper(T& t) :
        _t(t)
    {
    }
    
    // TODO new_string and new_null
    void new_string(const std::string& d)
    {
        // TODO
    }

    void new_null()
    {
        // TODO
    }

    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        if (t.in())
        {
            // TODO
            w.new_string("TODO");
        }
        else
            w.new_null();
    }
};


//
//
// STL containers
//
//
template< typename T >
struct stl_string_helper : public helper_base
{
    T& _t;
    stl_string_helper(T& t) :
        _t(t)
    {
    }

    void new_string(const std::string& d)
    {
        _t = d;
    }

    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        w.new_string(t.c_str());
    }
};


template< typename T >
struct stl_map_helper : public helper_base
{
    T& _t;
    stl_map_helper(T& t) :
        _t(t)
    {
    }

    helper_base* new_child(const std::string& name)
    {
        return create_helper(_t[name]);
    }

    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        typedef typename T::const_iterator iterator_t;

        w.object_start();

        iterator_t end = t.end();
        for (iterator_t it = t.begin(); it != end; it++) 
        {
            w.new_string(it->first.c_str());
            helper_write(w, it->second);
        }

        w.object_end();
    }
};

template< typename T >
struct stl_pushbackable_helper : public helper_base
{
    T& _t;
    typedef typename T::value_type value_type;

    stl_pushbackable_helper(T& t) :
        _t(t)
    {
    }

    helper_base* new_child()
    {
        _t.push_back(value_type());
        return create_helper(_t.back());
    }
    
    template< typename Writer >
    static inline void write(Writer& w, const T& t)
    {
        w.array_start();

        typedef typename T::const_iterator iterator_t;
        iterator_t end = t.end();
        for (iterator_t it = t.begin(); it != end; it++) 
        {
            helper_write(w, *it);
        }

        w.array_end();
    }
};

template< typename T >
struct calculate_helper
{
    typedef typename 
        // if
        cs_mpl::eval_if_identity< cs_mpl::is_bool< T >, bool_helper,
        // else if
        cs_mpl::eval_if_identity< boost::is_arithmetic< T >, 
            arithmetic_helper< T >,
        // else if
        cs_mpl::eval_if_identity< boost::is_array< T >, 
            array_helper< T >,
        // else if
        cs_mpl::eval_if_identity< boost::is_enum< T >, 
            enum_helper< T >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_string< T >, 
            string_helper< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_corbaseq_string< T >, 
            corbaseq_string_helper< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_corbaseq< T >, 
            corbaseq_helper< T >,
        // else if
        cs_mpl::eval_if_identity< cs_mpl::is_struct< T >, 
            struct_helper< T >,
        // else if
        cs_mpl::eval_if_identity< adapted::is_objrefvar< T >, 
            corba_objrefvar_helper< T >,
        // else
            boost::mpl::identity< unsupported_type_helper< T > >
        > > > > > > > > >::type type;
};

template < typename T >
struct calculate_helper < std::map< std::string, T > >
{
    typedef stl_map_helper< std::map< std::string, T > > type;
};

template < typename T >
struct calculate_helper < std::vector< T > >
{
    typedef stl_pushbackable_helper< std::vector< T > > type;
};

template < typename T >
struct calculate_helper < std::deque< T > >
{
    typedef stl_pushbackable_helper< std::deque< T > > type;
};

template < typename T >
struct calculate_helper < std::list< T > >
{
    typedef stl_pushbackable_helper< std::list< T > > type;
};

template < >
struct calculate_helper< std::string >
{
    typedef stl_string_helper< std::string > type;
};

} // namespace detail

template< typename T >
inline helper_base * create_helper(T& t)
{
    typedef typename detail::calculate_helper< T >::type helper_t;
    return new helper_t(t);
}

template< typename Write, typename T >
inline void helper_write(Write& w, const T& t)
{
    typedef typename helper::detail::calculate_helper< T >::type helper_t;
    helper_t::write(w, t);
}

} // namespace helper
} // namespace json
} // namespace corbasim

#endif /* CORBASIM_JSON_HELPER_HPP */


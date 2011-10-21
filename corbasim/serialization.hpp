// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * serialization.hpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * CORBASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORBASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the iserializationied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#ifndef CORBASIM_SERIALIZATION_HPP
#define CORBASIM_SERIALIZATION_HPP

#include <string>

// Boost.MPL
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>

// Boost.Serialization
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

#include <corbasim/impl.hpp>

namespace corbasim 
{
namespace serialization 
{
namespace detail 
{

template < class Archive, typename Serializer, typename T >
void split(Archive & ar, T& t, 
        const unsigned int version)
{
    // split into save and load
    typedef typename boost::mpl::eval_if<
            typename Archive::is_saving,
            boost::mpl::identity< typename Serializer::saver >,
            boost::mpl::identity< typename Serializer::loader >
        >::type typex;
    typex::invoke(ar, t, version);
}

} // namespace detail

/**
 * @brief Serializador para clases del tipo String_var.
 *
 * Requiere que tengan un método in, que a partir de él se pueda construir
 * un std::string y se le pueda asignar un const char *.
 */
struct string
{
    struct saver
    {
        template < class Archive, typename String >
        static void invoke(Archive & ar, const String& str, 
                const unsigned int version)
        {
            std::string _tmp(str.in()); // Makes copy
            ar << _tmp;
        }
    };

    struct loader
    {
        template < class Archive, typename String >
        static void invoke(Archive & ar, String& str, 
                const unsigned int version)
        {
            std::string _tmp;
            ar >> _tmp;
            str = _tmp.c_str(); // Makes copy
        }
    };

    template < class Archive, typename String >
    static void serialize(Archive & ar, String& str, 
            const unsigned int version)
    {
        detail::split< Archive, string, String >(ar, str, version);
    }

};

/**
 * @brief Serializador para secuencias.
 *
 * Requiere método length y operador [].
 */
struct sequence 
{

    struct saver
    {
        template < class Archive, typename Sequence >
        static void invoke(Archive & ar, const Sequence& seq, 
                const unsigned int version)
        {
            unsigned int length = seq.length();
            ar << length;

            for (unsigned int i = 0; i < length; i++) 
                ar << seq[i];
        }
    };

    struct loader
    {
        template < class Archive, typename Sequence >
        static void invoke(Archive & ar, Sequence& seq, 
                const unsigned int version)
        {
            unsigned int length;
            ar >> length;

            seq.length(length);

            for (unsigned int i = 0; i < length; i++) 
                ar >> seq[i];
        }
    };

    template < class Archive, typename Sequence >
    static void serialize(Archive & ar, Sequence& seq, 
            const unsigned int version)
    {
        detail::split< Archive, sequence, Sequence >(ar, seq, version);
    }

}; // class sequence

/**
 * @brief Serializador para secuencias de strings.
 *
 * Requiere método length y operador [].
 */
struct string_sequence 
{

    struct saver
    {
        template < class Archive, typename Sequence >
        static void invoke(Archive & ar, const Sequence& seq, 
                const unsigned int version)
        {
            unsigned int length = seq.length();
            ar << length;

            for (unsigned int i = 0; i < length; i++) 
            {
                std::string tmp = seq[i].in();
                ar << tmp;
            }
        }
    };

    struct loader
    {
        template < class Archive, typename Sequence >
        static void invoke(Archive & ar, Sequence& seq, 
                const unsigned int version)
        {
            unsigned int length;
            ar >> length;

            seq.length(length);

            for (unsigned int i = 0; i < length; i++) 
            {
                std::string tmp;
                ar >> tmp;
                seq[i] = tmp.c_str();
            }
        }
    };

    template < class Archive, typename Sequence >
    static void serialize(Archive & ar, Sequence& seq, 
            const unsigned int version)
    {
        detail::split< Archive, string_sequence, Sequence >(
                ar, seq, version);
    }

}; // class string_sequence

} // namespace serialization
} // namespace corbasim


namespace boost 
{

/**
 * @brief Espacio de nombres para serialización no intrusiva con
 * Boost.Serialization 
 *
 * @see http://www.boost.org/doc/libs/1_47_0/libs/serialization/doc/tutorial.html#nonintrusiveversion
 */
namespace serialization 
{

//////////////////////////////////////////////////////////////////////////////////////
//
// String types
//
//////////////////////////////////////////////////////////////////////////////////////

template < class Archive >
void serialize(Archive & ar, ::corbasim::orbimpl::String_Manager& str, 
        const unsigned int version)
{
    ::corbasim::serialization::string::serialize(ar, str, version);
}

template < class Archive >
void serialize(Archive & ar, ::corbasim::orbimpl::string_for_seq& str, 
        const unsigned int version)
{
    // TODO
    // ::corbasim::serialization::string::serialize(ar, str, version);
}

template < class Archive >
void serialize(Archive & ar, ::corbasim::orbimpl::string_for_seq str, 
        const unsigned int version)
{
    // TODO
    // ::corbasim::serialization::string::serialize(ar, str, version);
}

template < class Archive >
void serialize(Archive & ar, CORBA::String_var& str, 
        const unsigned int version)
{
    ::corbasim::serialization::string::serialize(ar, str, version);
}

//////////////////////////////////////////////////////////////////////////////////////
//
// Object references
//
//////////////////////////////////////////////////////////////////////////////////////

template < class Archive >
void serialize(Archive & ar, CORBA::Object_var& obj, 
        const unsigned int version)
{
    // TODO split into save and load
}

} // namespace serialization
} // namespace boost


#endif /* CORBASIM_SERIALIZATION_HPP */


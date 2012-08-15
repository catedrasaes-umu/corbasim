// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * json_parse.hpp
 * Copyright (C) Cátedra SAES-UMU 2010 <catedra-saes-umu@listas.um.es>
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

#ifndef CORBASIM_JSON_IMPL_JSON_PARSE_HPP
#define CORBASIM_JSON_IMPL_JSON_PARSE_HPP

#include <string>
#include <deque>
#include <exception> // Exceptions
#include <stdexcept>
#include <corbasim/json/detail/json.hpp>

namespace csu
{
namespace corbasim
{
namespace json
{
namespace parser
{

inline double
parse_double (const char * p, int left)
{
    double val = 0;
    char c;
    bool g_sign_plus = true;

    c = *p;
    if (c == '+' || c=='-')
    {
        if (c == '-')
            g_sign_plus = false;
        ++p;
        --left;
    }

    while (left > 0)
    {
        c = *p;
        if (c >= '0' && c <= '9')
        {
            val *= 10;
            val += c - '0';
        }

        if (c == '.')
        {
            ++p;
            --left;

            double divider = 10;

            while (left > 0)
            {
                c = *p;
                if (c >= '0' && c <= '9')
                    val += (c - '0') / divider;
                else
                    break;

                ++p;
                --left;
                divider *= 10;
            }
        }

        if (c == 'e' || c=='E')
        {
            ++p;
            --left;

            // Note, we assume not the end of input.
            // FIXME: throw an exception otherwise
            c = *p;

            // Sign
            bool sign_plus = true;

            // eat up + and or -, adjust multiplier
            if (c == '+' || c == '-')
            {
                if (c == '-')
                    sign_plus = false;

                ++p;
                --left;
                c = *p;
            }

            size_t exponent = 0;
            while (left > 0)
            {
                //if (c >= '0' && c <= '9') // FIXME: ommited, but...
                {
                    exponent *= 10;
                    exponent += c - '0';
                }
                // FIXME: else raise excp.

                ++p;
                --left;
                c = *p;
            }

            // pow table
            static const double pow_table[] = {
                1.0,// 1e0,
                1e1,
                1e2,
                1e3,
                1e4,
                1e5,
                1e6,
                1e7,
                1e8,
                1e9,
                1e10,
                1e11,
                1e12,
                1e13,
                1e14,
                1e15,
                1e16,
                1e17,
                1e18,
                1e19,
                1e20,
                1e21,
                1e22,
                1e23,
                1e24,
                1e25,
                1e26,
                1e27,
                1e28,
                1e29,
                1e30,
                1e31,
                1e32,
                1e33,
                1e34,
                1e35,
                1e36,
                1e37,
                1e38,
                1e39,
                1e40,
                1e41,
                1e42,
                1e43,
                1e44,
                1e45,
                1e46,
                1e47,
                1e48,
                1e49,
                1e50,
                1e51,
                1e52,
                1e53,
                1e54,
                1e55,
                1e56,
                1e57,
                1e58,
                1e59,
                1e60,
                1e61,
                1e62,
                1e63,
                1e64,
                1e65,
                1e66,
                1e67,
                1e68,
                1e69,
                1e70,
                1e71,
                1e72,
                1e73,
                1e74,
                1e75,
                1e76,
                1e77,
                1e78,
                1e79,
                1e80,
                1e81,
                1e82,
                1e83,
                1e84,
                1e85,
                1e86,
                1e87,
                1e88,
                1e89,
                1e90,
                1e91,
                1e92,
                1e93,
                1e94,
                1e95,
                1e96,
                1e97,
                1e98,
                1e99,
                1e100,
                1e101,
                1e102,
                1e103,
                1e104,
                1e105,
                1e106,
                1e107,
                1e108,
                1e109,
                1e110,
                1e111,
                1e112,
                1e113,
                1e114,
                1e115,
                1e116,
                1e117,
                1e118,
                1e119,
                1e120,
                1e121,
                1e122,
                1e123,
                1e124,
                1e125,
                1e126,
                1e127,
                1e128,
                1e129,
                1e130,
                1e131,
                1e132,
                1e133,
                1e134,
                1e135,
                1e136,
                1e137,
                1e138,
                1e139,
                1e140,
                1e141,
                1e142,
                1e143,
                1e144,
                1e145,
                1e146,
                1e147,
                1e148,
                1e149,
                1e150,
                1e151,
                1e152,
                1e153,
                1e154,
                1e155,
                1e156,
                1e157,
                1e158,
                1e159,
                1e160,
                1e161,
                1e162,
                1e163,
                1e164,
                1e165,
                1e166,
                1e167,
                1e168,
                1e169,
                1e170,
                1e171,
                1e172,
                1e173,
                1e174,
                1e175,
                1e176,
                1e177,
                1e178,
                1e179,
                1e180,
                1e181,
                1e182,
                1e183,
                1e184,
                1e185,
                1e186,
                1e187,
                1e188,
                1e189,
                1e190,
                1e191,
                1e192,
                1e193,
                1e194,
                1e195,
                1e196,
                1e197,
                1e198,
                1e199,
                1e200,
                1e201,
                1e202,
                1e203,
                1e204,
                1e205,
                1e206,
                1e207,
                1e208,
                1e209,
                1e210,
                1e211,
                1e212,
                1e213,
                1e214,
                1e215,
                1e216,
                1e217,
                1e218,
                1e219,
                1e220,
                1e221,
                1e222,
                1e223,
                1e224,
                1e225,
                1e226,
                1e227,
                1e228,
                1e229,
                1e230,
                1e231,
                1e232,
                1e233,
                1e234,
                1e235,
                1e236,
                1e237,
                1e238,
                1e239,
                1e240,
                1e241,
                1e242,
                1e243,
                1e244,
                1e245,
                1e246,
                1e247,
                1e248,
                1e249,
                1e250,
                1e251,
                1e252,
                1e253,
                1e254,
                1e255,
                1e256,
                1e257,
                1e258,
                1e259,
                1e260,
                1e261,
                1e262,
                1e263,
                1e264,
                1e265,
                1e266,
                1e267,
                1e268,
                1e269,
                1e270,
                1e271,
                1e272,
                1e273,
                1e274,
                1e275,
                1e276,
                1e277,
                1e278,
                1e279,
                1e280,
                1e281,
                1e282,
                1e283,
                1e284,
                1e285,
                1e286,
                1e287,
                1e288,
                1e289,
                1e290,
                1e291,
                1e292,
                1e293,
                1e294,
                1e295,
                1e296,
                1e297,
                1e298,
                1e299,
                1e300,
                1e301,
                1e302,
                1e303,
                1e304,
                1e305,
                1e306,
                1e307,
                1e308
            };

            if (sign_plus)
                val *= pow_table[exponent];
            else
                val /= pow_table[exponent];
        }

        ++p;
        --left;
    }

    return g_sign_plus ? val : -val;
}

inline double
parse_double (match_pair const& pp)
{
    return parse_double(pp.first, pp.second);
}

inline void decode(std::string& data)
{
    // Fast check for the most common case. No copy.
    size_t pos;
    if (std::string::npos == (pos = data.find('\\')))
        return;

    std::string buffer;
    buffer.reserve(data.size());
    // Copy the first part, if it exists
    if (pos)
        buffer.append(&data[0], pos);
    for(; pos < data.size(); ++pos) // NOTE: '<' instead of '!='.
    {
        switch(data[pos])
        {
            // NOTE: Do not check for malformed input
            case '\\': buffer.append(&data[++pos], 1);      break;
            default:   buffer.append(&data[pos], 1);        break;
        }
    }
    data.swap(buffer);
}

////////////////////////////////////////////////////////////////////////
// parser state
template <typename SemanticState>
struct State
{
    // For reference, the SemanticState itself.
    typedef SemanticState SemType;

    // Position type
    typedef const char * PositionType;

    // buffer
    const char* buf_;
    // actual pos
    const char* pos_;
    // buf_fer length
    size_t len_;

    // The inner semantic state.
    SemanticState& ss_;

    // State stack, for backtracking
    std::deque< const char* > pos_stack_;

    // ctor
    State (SemanticState& ss, const char* b, size_t l)
        : buf_ (b), pos_ (b),  len_(l), ss_ (ss)
    {
    }

    SemanticState&
    semantic_state()
    {
        return ss_;
    }

    inline bool
    at_end() const
    {
        return static_cast<size_t>(pos_ - buf_) == len_;
    }

    inline bool
    match_at_pos_advance (char c)
    {
        if (!at_end() && (*pos_ == c))
        {
            ++pos_;
            return true;
        }
        return false;
    }

    inline bool
    match_at_pos (char c) const
    {
        return !at_end() && (*pos_ == c);
    }

    inline char
    char_at_pos() const
    {
        return *pos_;
    }

    inline const char* pos() const
    {
        return pos_;
    }

    inline void
    advance()
    {
        if (!at_end())
            ++pos_;

        // TODO: throw at_end
    }

    inline void
    skip(size_t how_many)
    {
        if (static_cast<size_t>(pos_ - buf_) + how_many <= len_)
            pos_ += how_many;

        // TODO: throw at_end
    }

    // Common interface
    inline void
    push_state()
    {
        pos_stack_.push_front (pos_);
    }

    inline void
    rollback()
    {
        pos_ = pos_stack_.front();
        pos_stack_.pop_front();
    }

    inline void
    commit()
    {
        pos_stack_.pop_front();
    }

    inline std::string
    to_string(const char * p, std::size_t size) const
    {
        return std::string(p, size);
    }
};

////////////////////////////////////////////////////////////////////////
// parser state
template <typename SemanticState>
struct IStreamState
{
    // For reference, the SemanticState itself.
    typedef SemanticState SemType;

    // Position type
    typedef std::streamoff PositionType;

    // stream
    std::istream& in_;

    // The inner semantic state.
    SemanticState& ss_;

    // State stack, for backtracking
    std::deque< std::streamoff > pos_stack_;

    // ctor
    IStreamState (SemanticState& ss, std::istream& in)
        : in_ (in), ss_ (ss)
    {
    }

    SemanticState&
    semantic_state()
    {
        return ss_;
    }

    inline bool
    at_end() const
    {
        return in_.eof();
    }

    inline bool
    match_at_pos_advance (char c)
    {
        if (!at_end())
        {
            if (in_.get() == c)
            {
                return true;
            }
            else
            {
                in_.unget();
            }
        }
        return false;
    }

    inline bool
    match_at_pos (char c) const
    {
        if (at_end())
            return false;

        char r = in_.peek();
        return (r == c);
    }

    inline char
    char_at_pos() const
    {
        return in_.peek();
    }

    inline PositionType pos() const
    {
        return in_.tellg();
    }

    inline void
    advance()
    {
        if (!at_end())
            in_.get();

        // TODO: throw at_end
    }

    inline void
    skip(size_t how_many)
    {
        in_.ignore(how_many);

        // TODO: throw at_end
    }

    // Common interface
    inline void
    push_state()
    {
        pos_stack_.push_front (in_.tellg());
    }

    inline void
    rollback()
    {
        in_.seekg(pos_stack_.front());
        pos_stack_.pop_front();
    }

    inline void
    commit()
    {
        pos_stack_.pop_front();
    }

    inline std::string
    to_string(std::streamoff p, std::size_t size)
    {
        std::streamoff old = in_.tellg();

        char buffer[size];
        in_.seekg(p);
        in_.read(buffer, size);
        in_.seekg(old);

        return std::string(buffer, size);
    }
};

////////////////////////////////////////////////////////////////////////
// parser
// based on the wonderful yard parser http://code.google.com/p/yardparser/
template <bool b>
struct identity
{
    template <typename whatever>
    static inline bool match (whatever const&)
    {
        return b;
    }
};

typedef identity<true> true_;
typedef identity<false> false_;

// lambda, empty rule
typedef true_ empty_;

template <char c>
struct char_
{
    template <typename S>
    static inline bool match (S& state)
    {
        return state.match_at_pos_advance (c);
    }
};

// NOTE: I could have implemented this in some other way
// but it would need a negative match with another Truth Environment
// or something...
template <char c>
struct notchar_
{
    template <typename S>
    static inline bool match (S& state)
    {
        if (state.at_end())
            return false;

        if (state.match_at_pos (c))
            return false;
        state.advance();
        return true;
    }
};

// NOTE: cannot be done this way
// template <typename C0>
// struct not_
// {
//     template <typename S>
//     static inline bool match (S& state)
//     {
//         return !C0::match (state);
//     }
// };


// character range, not inclusive
template <char c1, char c2>
struct crange_
{
    template <typename S>
    static inline bool match (S& state)
    {
        if (state.at_end())
            return false;

        char c = state.char_at_pos();
        if (c >= c1 && c < c2)
        {
            state.advance();
            return true;
        }
        return false;
    }
};

// character range, inclusive
template <char c1, char c2>
struct cirange_
{
    template <typename S>
    static inline bool match (S& state)
    {
        if (state.at_end())
            return false;

        char c = state.char_at_pos();
        if (c >= c1 && c <= c2)
        {
            state.advance();
            return true;
        }
        return false;
    }
};

struct anychar_
{
    template <typename S>
    static inline bool match (S& state)
    {
        if (state.at_end())
            return false;

        state.advance();
        return true;
    }
};


// Semantic Rule: for rules that want a process_match operation to be
// called in their A type. Usually tends to be the class itself, but
// I'll try different approaches using the state...
template <typename A, typename C0>
struct semantic_rule
{
    template <typename S>
    static inline bool match (S& state)
    {
        typename S::PositionType p = state.pos();

        // Try the rule itself
        bool result;
        if (true == (result = C0::match (state)))
            A::process_match (state, std::make_pair (p, state.pos() - p));

        return result;
    }
};

// Ordered sequence of elements: abc
template <typename C0,
          typename C1,
          typename C2 = true_,
          typename C3 = true_,
          typename C4 = true_,
          typename C5 = true_,
          typename C6 = true_,
          typename C7 = true_>
struct seq_
{
    template <typename S>
    static inline bool match (S& state)
    {
        state.push_state();

        bool var = C0::match (state)
            && C1::match (state)
            && C2::match (state)
            && C3::match (state)
            && C4::match (state)
            && C5::match (state)
            && C6::match (state)
            && C7::match (state);
        var ? state.commit() : state.rollback();

        return var;
    }
};

// Element decission: a|b
template <typename C0,
          typename C1,
          typename C2 = false_,
          typename C3 = false_,
          typename C4 = false_,
          typename C5 = false_,
          typename C6 = false_,
          typename C7 = false_>
struct or_
{
    template <typename S>
    static inline bool match (S& state)
    {
        state.push_state();

        bool var = C0::match (state)
            || C1::match (state)
            || C2::match (state)
            || C3::match (state)
            || C4::match (state)
            || C5::match (state)
            || C6::match (state)
            || C7::match (state);

        var ? state.commit() : state.rollback();

        return var;
    }
};

// One or more repetitions: a+
template <typename C0>
struct plus_
{
    template <typename S>
    static inline bool match (S& state)
    {
        if (!C0::match (state))
            return false;
        // Note: yes, I unroll this loop intentionally
        while (C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state))
            ;
        return true;
    }
};

// Zero or more repetitions: a*
template <typename C0>
struct star_
{
    template <typename S>
    static inline bool match (S& state)
    {
        while (C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state)
               && C0::match (state))
            ;
        return true;
    }
};

// Optional (special star_ case): a?
template <typename C0>
struct opt_
{
    template <typename S>
    static inline bool match (S& state)
    {
        C0::match (state);
        return true;
    }
};

/// JSON grammar
namespace grammar
{
using namespace parser;

// space
struct space : or_ < char_<' '>, char_<'\t'>, char_<'\n'>, char_<'\r'> >
{
};

// Zero or more spaces
struct spaces_ : star_ < space >
{
};


// strings
struct string_ :
    semantic_rule <string_,
                   seq_< char_< '"' >,
                         star_ < or_ <
                                     seq_< char_ <'\\'>, anychar_ >, // escape
                                     notchar_<'"'> // normal chars
                                     > >,
                         char_<'"'> > >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        std::string s (state.to_string(mp.first + 1, mp.second - 2));
        state.semantic_state().new_string (s);
    }
};

// true
struct true_p : semantic_rule <true_p,
                               seq_ < char_<'t'>, char_<'r'>, char_< 'u' >, char_<'e'> > >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        state.semantic_state().new_bool (true);
    }
};

// false
struct false_p :
    semantic_rule <false_p,
                   seq_ < char_<'f'>,  char_<'a'>, char_< 'l' >, char_<'s'>, char_<'e' > > >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const&)
    {
        state.semantic_state().new_bool (false);
    }
};

// bool
struct bool_ : or_ < true_p, false_p >
{
};

// null
struct null_ :
        semantic_rule < null_,
                        seq_ < char_<'n'>, char_<'u'>,
                               char_< 'l' >, char_<'l'> > >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        state.semantic_state().new_null ();
    }
};

// Aux: e
struct e_ : seq_ < or_ < char_<'e'>, char_<'E'> >,
                   opt_ < or_ <char_<'-'>, char_<'+'> > > >
{
};

// double, not complete
struct double_ :
        semantic_rule < double_,
                        seq_ < opt_ < char_<'-'> >, plus_< cirange_ <'0', '9'> >,
                               opt_ < seq_ < char_<'.'> , plus_ < cirange_ <'0', '9'> > > >,
                               opt_ < seq_< e_, plus_<cirange_<'0', '9'>  > > > > >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        // TODO avoid conversion to string
        const std::string str(state.to_string(mp.first, mp.second));
        double d = parse_double (str.c_str(), str.size());
        state.semantic_state().new_double (d);
    }
};

// array
// start
struct array_start :
        semantic_rule<array_start,
                      char_<'['>
                      >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const&)
    {
        state.semantic_state().array_start();
    }
};

// end
struct array_end :
        semantic_rule<array_end,
                      char_<']'>
                      >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const&)
    {
        state.semantic_state().array_end();
    }
};

// object
// start
struct object_start :
        semantic_rule<object_start,
                      char_<'{'>
                      >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const&)
    {
        state.semantic_state().object_start();
    }
};

// end
struct object_end :
        semantic_rule<object_end,
                      char_<'}'>
                      >
{
    // Semantic rule
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const&)
    {
        state.semantic_state().object_end();
    }
};

// fwd, as array and object are also atoms
struct array_;
struct object_;

// atom
struct atom : or_ < bool_, double_, string_ , array_, object_, null_ >
{
};

// array body
struct array_body : seq_ <
    spaces_,
    or_ < seq_ <atom, star_< seq_< spaces_, char_<','>, spaces_, atom> > >,
           empty_>,
    spaces_ >
{
};

struct array_: seq_<array_start, array_body, array_end>
{
};

// object member
struct member_ : seq_ < string_, spaces_, char_<':'>, spaces_, atom >
{
};

// object body
struct object_body : seq_ <
    spaces_,
    or_ < seq_ <member_, star_< seq_< spaces_, char_<','>, spaces_, member_> > >,
          empty_>,
    spaces_ >
{
};

struct object_: seq_<object_start, object_body, object_end>
{
};


struct gram : or_< seq_ < spaces_, object_, spaces_>, seq_ < spaces_, atom, spaces_> , empty_>
{
};

} // grammar
} // parser

// JSON semantic state
struct SemanticState
{
    inline void new_null()
    {
        //std::cout << "new null" << std::endl;
    }

    inline void new_double(double d)
    {
        //std::cout << "new double: " << d << std::endl;
    }

    inline void new_string(std::string const& p)
    {
        //std::cout << "new string: " << std::string(p.first,p.second)
        //          <<  std::endl;
    }

    inline void new_bool(bool b)
    {
        //std::cout << "new bool: " << b << std::endl;
    }

    inline void object_start()
    {
        //std::cout << "object start" << std::endl;
    }

    inline void object_end()
    {
        //std::cout << "object end" << std::endl;
    }

    inline void array_start()
    {
        //std::cout << "array start" << std::endl;
    }

    inline void array_end()
    {
        //std::cout << "array end" << std::endl;
    }
};


} // json
} // mycorba
} // csu


#endif

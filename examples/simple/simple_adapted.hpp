#ifndef SIMPLE_ADAPTED_HPP
#define SIMPLE_ADAPTED_HPP

#include "simpleC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>

// StructDef: SimpleExample::St
BOOST_FUSION_ADAPT_STRUCT(
        SimpleExample::St,
        ( SimpleExample::St::_l_seq, l)
        ( SimpleExample::St::_ss_seq, ss)
        ( ::CORBA::Long, b)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::St& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("l", t.l);
            ar & boost::serialization::make_nvp("ss", t.ss);
            ar & boost::serialization::make_nvp("b", t.b);
        }

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::St_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, SimpleExample::St::_l_seq& t,
                const unsigned int version)
        {
            ::corbasim::serialization::sequence::serialize( ar, t, version);
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_corbaseq< SimpleExample::St::_l_seq > : public cs_mpl::true_
        {
            typedef ::CORBA::Long slice_type;
        };

    } // adapted
} // corbasim

namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, SimpleExample::St::_ss_seq& t,
                const unsigned int version)
        {
            ::corbasim::serialization::string_sequence::serialize( ar, t,
                    version);
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_corbaseq< SimpleExample::St::_ss_seq > : public cs_mpl::true_
        {
            typedef ::TAO::String_Manager slice_type;
        };

    } // adapted
} // corbasim


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, SimpleExample::Test_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_objrefvar< SimpleExample::Test_var > : public cs_mpl::true_
        {
            typedef SimpleExample::Test interface;
        };

    } // adapted
} // corbasim


// StructDef: SimpleExample::Hijo
BOOST_FUSION_ADAPT_STRUCT(
        SimpleExample::Hijo,
        ( ::CORBA::Long, b)
        ( ::CORBA::Boolean, l)
        ( ::TAO::String_Manager, s)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::Hijo& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("b", t.b);
            ar & boost::serialization::make_nvp("l", t.l);
            ar & boost::serialization::make_nvp("s", t.s);
        }

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::Hijo_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


// StructDef: SimpleExample::Padre
BOOST_FUSION_ADAPT_STRUCT(
        SimpleExample::Padre,
        ( SimpleExample::Hijo, h)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::Padre& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("h", t.h);
        }

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::Padre_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


// StructDef: SimpleExample::Abuelo
BOOST_FUSION_ADAPT_STRUCT(
        SimpleExample::Abuelo,
        ( SimpleExample::Padres, p)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::Abuelo& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("p", t.p);
        }

        template < class Archive >
        void serialize(Archive& ar, SimpleExample::Abuelo_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


namespace _corbasim_SimpleExample
{
    struct St
    {
        typedef corbasim::adapted::member< ::SimpleExample::St, 0 >
                l_corbasim_member;
        typedef corbasim::adapted::member< ::SimpleExample::St, 1 >
                ss_corbasim_member;
        typedef corbasim::adapted::member< ::SimpleExample::St, 2 >
                b_corbasim_member;

    };

    namespace Test
    {

        struct __operation1
        {
            typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long >,
                    corbasim::Arg_IN< ::CORBA::Long >, corbasim::Arg_IN<
                            const SimpleExample::St& > > _arg_list;

            typedef corbasim::adapted::member< __operation1, 0 > a_corbasim_member;
            typedef corbasim::adapted::member< __operation1, 1 > b_corbasim_member;
            typedef corbasim::adapted::member< __operation1, 2 > c_corbasim_member;

            ::CORBA::Long a;
            ::CORBA::Long b;
            SimpleExample::St c;

            __operation1()
            {
            }

            __operation1(::CORBA::Long _a, ::CORBA::Long _b, const SimpleExample::St& _c):
            a(_a), b(_b), c(_c)
            {

            }

            // Copy constructor
            __operation1(const __operation1& o) :
            a(o.a), b(o.b), c(o.c)
            {

            }

            template< typename Archive >
            void serialize(Archive& ar, const unsigned int /* unused */)
            {
                ar & boost::serialization::make_nvp("a", a);
                ar & boost::serialization::make_nvp("b", b);
                ar & boost::serialization::make_nvp("c", c);
            }
        };

        typedef __operation1 operation1;

        struct __operation4
        {
            typedef boost::mpl::vector< corbasim::Arg_IN< SimpleExample::Test_ptr > > _arg_list;

            typedef corbasim::adapted::member< __operation4, 0 > a_corbasim_member;

            SimpleExample::Test_var a;

            __operation4()
            {
            }

            __operation4(SimpleExample::Test_ptr _a)
            {

                a = SimpleExample::Test::_duplicate(_a);
            }

            // Copy constructor
            __operation4(const __operation4& o)
            {

                a = o.a;
            }

            template< typename Archive >
            void serialize(Archive& ar, const unsigned int /* unused */)
            {
                ar & boost::serialization::make_nvp("a", a);
            }
        };

        typedef __operation4 operation4;

    } // Test


    struct Hijo
    {
        typedef corbasim::adapted::member< ::SimpleExample::Hijo, 0 > b_corbasim_member;
        typedef corbasim::adapted::member< ::SimpleExample::Hijo, 1 > l_corbasim_member;
        typedef corbasim::adapted::member< ::SimpleExample::Hijo, 2 > s_corbasim_member;

    };

    struct Padre
    {
        typedef corbasim::adapted::member< ::SimpleExample::Padre, 0 > h_corbasim_member;

    };

    struct Abuelo
    {
        typedef corbasim::adapted::member< ::SimpleExample::Abuelo, 0 > p_corbasim_member;

    };

} // _corbasim_SimpleExample


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct interface< SimpleExample::Test >
        {
            typedef cs_mpl::vector< _corbasim_SimpleExample::Test::operation1,
                    _corbasim_SimpleExample::Test::operation4 > _op_list;
            typedef cs_mpl::vector< _corbasim_SimpleExample::Test::operation1,
                    _corbasim_SimpleExample::Test::operation4 > _sorted_op_list;
            typedef cs_mpl::vector< _corbasim_SimpleExample::Test::operation1,
                    _corbasim_SimpleExample::Test::operation4 > _own_op_list;
            typedef cs_mpl::vector< > _parent_list;
        };

    } // adapted
} // corbasim

// OperationDef: SimpleExample::Test::operation1
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_SimpleExample::Test::operation1,
        ( ::CORBA::Long, a)
        ( ::CORBA::Long, b)
        ( SimpleExample::St, c)
)

namespace corbasim
{
    namespace adapted
    {
        template< >
        struct is_oneway< _corbasim_SimpleExample::Test::operation1 > : public cs_mpl::true_
        {
        };

        template< >
        struct call< _corbasim_SimpleExample::Test::operation1 >
        {
            typedef _corbasim_SimpleExample::Test::operation1 Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->operation1(value.a, value.b, value.c);
            }
        };

        template< >
        struct name< _corbasim_SimpleExample::Test::operation1 >
        {
            static inline const char * call()
            {
                return "operation1";
            }
        };

    } // adapted
} // corbasim


// OperationDef: SimpleExample::Test::operation4
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_SimpleExample::Test::operation4,
        ( SimpleExample::Test_var, a)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_SimpleExample::Test::operation4 >
        {
            typedef _corbasim_SimpleExample::Test::operation4 Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->operation4(value.a);
            }
        };

        template< >
        struct name< _corbasim_SimpleExample::Test::operation4 >
        {
            static inline const char * call()
            {
                return "operation4";
            }
        };

    } // adapted
} // corbasim


#endif // SIMPLE_ADAPTED_HPP


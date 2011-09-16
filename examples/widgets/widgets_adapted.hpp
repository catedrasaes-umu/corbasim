#ifndef WIDGETS_ADAPTED_HPP
#define WIDGETS_ADAPTED_HPP

#include "widgetsC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>

// StructDef: Test::St
BOOST_FUSION_ADAPT_STRUCT(
        Test::St,
        ( ::TAO::String_Manager, a)
        ( ::TAO::String_Manager, b)
        ( Test::Prueba_var, reffff)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, Test::St& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("a", t.a);
            ar & boost::serialization::make_nvp("b", t.b);
            ar & boost::serialization::make_nvp("reffff", t.reffff);
        }

        template < class Archive >
        void serialize(Archive& ar, Test::St_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost


// StructDef: Test::St2
BOOST_FUSION_ADAPT_STRUCT(
        Test::St2,
        ( Test::St, a)
        ( Test::St, b)
        ( ::TAO::String_Manager, c)
        ( ::CORBA::Long, unsupported)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, Test::St2& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("a", t.a);
            ar & boost::serialization::make_nvp("b", t.b);
            ar & boost::serialization::make_nvp("c", t.c);
            ar & boost::serialization::make_nvp("unsupported", t.unsupported);
        }

        template < class Archive >
        void serialize(Archive& ar, Test::St2_var& t, const unsigned int /* unused */)
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
        void serialize(Archive& ar, Test::Prueba_var& t,
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
        struct is_objrefvar< Test::Prueba_var > : public cs_mpl::true_
        {
            typedef Test::Prueba interface;
        };

    } // adapted
} // corbasim


namespace _corbasim_Test
{

    struct St
    {
        typedef corbasim::adapted::member< ::Test::St, 0 > a_corbasim_member;
        typedef corbasim::adapted::member< ::Test::St, 1 > b_corbasim_member;
        typedef corbasim::adapted::member< ::Test::St, 2 >
                reffff_corbasim_member;

    };

    struct St2
    {
        typedef corbasim::adapted::member< ::Test::St2, 0 > a_corbasim_member;
        typedef corbasim::adapted::member< ::Test::St2, 1 > b_corbasim_member;
        typedef corbasim::adapted::member< ::Test::St2, 2 > c_corbasim_member;
        typedef corbasim::adapted::member< ::Test::St2, 3 >
                unsupported_corbasim_member;

    };

    namespace Prueba
    {

        struct __operacion1
        {
            typedef boost::mpl::vector< corbasim::Arg_IN< const Test::St2& >,
                    corbasim::Arg_IN< const Test::St& > > _arg_list;

            typedef corbasim::adapted::member< __operacion1, 0 > a_corbasim_member;
            typedef corbasim::adapted::member< __operacion1, 1 > b_corbasim_member;

            Test::St2 a;
            Test::St b;

            __operacion1()
            {
            }

            __operacion1(const Test::St2& _a, const Test::St& _b):
            a(_a), b(_b)
            {
            }

            // Copy constructor
            __operacion1(const __operacion1& o) :
            a(o.a), b(o.b)
            {
            }

            template< typename Archive >
            void serialize(Archive& ar, const unsigned int /* unused */)
            {
                ar & boost::serialization::make_nvp("a", a);
                ar & boost::serialization::make_nvp("b", b);
            }
        };

        typedef __operacion1 operacion1;

        struct __operacion2
        {
            typedef boost::mpl::vector< corbasim::Arg_IN< Test::Prueba_ptr > > _arg_list;

            typedef corbasim::adapted::member< __operacion2, 0 > myref_corbasim_member;

            Test::Prueba_var myref;

            __operacion2()
            {
            }

            __operacion2(Test::Prueba_ptr _myref):
            myref(_myref)
            {
            }

            // Copy constructor
            __operacion2(const __operacion2& o) :
            myref(o.myref)
            {
            }

            template< typename Archive >
            void serialize(Archive& ar, const unsigned int /* unused */)
            {
                ar & boost::serialization::make_nvp("myref", myref);
            }
        };

        typedef __operacion2 operacion2;

        struct __operacion3
        {
            typedef boost::mpl::vector< > _arg_list;

            __operacion3()
            {
            }

            // Copy constructor
            __operacion3(const __operacion3& o)
            {
            }

            template< typename Archive >
            void serialize(Archive& ar, const unsigned int /* unused */)
            {
            }
        };

        typedef __operacion3 operacion3;

    } // Prueba

} // _corbasim_Test


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct interface< Test::Prueba >
        {
            typedef cs_mpl::vector< _corbasim_Test::Prueba::operacion1,
                    _corbasim_Test::Prueba::operacion2,
                    _corbasim_Test::Prueba::operacion3 > _op_list;
            typedef cs_mpl::vector< _corbasim_Test::Prueba::operacion1,
                    _corbasim_Test::Prueba::operacion2,
                    _corbasim_Test::Prueba::operacion3 > _sorted_op_list;
            typedef cs_mpl::vector< _corbasim_Test::Prueba::operacion1,
                    _corbasim_Test::Prueba::operacion2,
                    _corbasim_Test::Prueba::operacion3 > _own_op_list;
            typedef cs_mpl::vector< > _parent_list;
        };

    } // adapted
} // corbasim

// OperationDef: Test::Prueba::operacion1
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_Test::Prueba::operacion1,
        ( Test::St2, a)
        ( Test::St, b)
)

namespace corbasim
{
    namespace adapted
    {
        template< >
        struct is_oneway< _corbasim_Test::Prueba::operacion1 > : public cs_mpl::true_
        {
        };

        template< >
        struct call< _corbasim_Test::Prueba::operacion1 >
        {
            typedef _corbasim_Test::Prueba::operacion1 Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->operacion1(value.a, value.b);
            }
        };

        template< >
        struct name< _corbasim_Test::Prueba::operacion1 >
        {
            static inline const char * call()
            {
                return "operacion1";
            }
        };

    } // adapted
} // corbasim


// OperationDef: Test::Prueba::operacion2
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_Test::Prueba::operacion2,
        ( Test::Prueba_var, myref)
)

namespace corbasim
{
    namespace adapted
    {
        template< >
        struct is_oneway< _corbasim_Test::Prueba::operacion2 > : public cs_mpl::true_
        {
        };

        template< >
        struct call< _corbasim_Test::Prueba::operacion2 >
        {
            typedef _corbasim_Test::Prueba::operacion2 Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->operacion2(value.myref);
            }
        };

        template< >
        struct name< _corbasim_Test::Prueba::operacion2 >
        {
            static inline const char * call()
            {
                return "operacion2";
            }
        };

    } // adapted
} // corbasim


// OperationDef: Test::Prueba::operacion3
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_Test::Prueba::operacion3,
)

namespace corbasim
{
    namespace adapted
    {
        template< >
        struct is_oneway< _corbasim_Test::Prueba::operacion3 > : public cs_mpl::true_
        {
        };

        template< >
        struct call< _corbasim_Test::Prueba::operacion3 >
        {
            typedef _corbasim_Test::Prueba::operacion3 Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->operacion3();
            }
        };

        template< >
        struct name< _corbasim_Test::Prueba::operacion3 >
        {
            static inline const char * call()
            {
                return "operacion3";
            }
        };

    } // adapted
} // corbasim


#endif // WIDGETS_ADAPTED_HPP


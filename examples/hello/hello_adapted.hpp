#ifndef HELLO_ADAPTED_HPP
#define HELLO_ADAPTED_HPP

#include "helloC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>

namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, HelloApp::Names& t,
                const unsigned int version)
        {
            ::corbasim::serialization::string_sequence::serialize( ar, t,
                    version);
        }

        template< class Archive >
        void serialize(Archive& ar, HelloApp::Names_var& t,
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
        struct is_corbaseq< HelloApp::Names > : public cs_mpl::true_
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
        void serialize(Archive& ar, HelloApp::Hello_var& t,
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
        struct is_objrefvar< HelloApp::Hello_var > : public cs_mpl::true_
        {
            typedef HelloApp::Hello interface;
        };

    } // adapted
} // corbasim


namespace _corbasim_HelloApp
{

    namespace Hello
    {

        struct __sayHello
        {
            typedef boost::mpl::vector< > _arg_list;

            ::TAO::String_Manager _return;

            __sayHello()
            {
            }

            // Copy constructor
            __sayHello(const __sayHello& o) :

            _return(o._return)
            {

            }

            template< typename Archive >
            void serialize(Archive& ar, const unsigned int /* unused */)
            {
                ar & boost::serialization::make_nvp("return", _return);
            }
        };

        typedef __sayHello sayHello;

        struct __sayHelloTo
        {
            typedef boost::mpl::vector< corbasim::Arg_IN< const HelloApp::Names& > > _arg_list;

	typedef corbasim::adapted::member< __sayHelloTo, 0 > people_corbasim_member;

	HelloApp::Names people;
	
	::TAO::String_Manager _return;
	
	__sayHelloTo()
	{
	}
	
	__sayHelloTo(const HelloApp::Names& _people):
		people(_people)
	{
		
	}
	
	// Copy constructor
	__sayHelloTo(const __sayHelloTo& o) :
		people(o.people)
, _return(o._return)	{
		
	}

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
		ar & boost::serialization::make_nvp("people", people);
		ar & boost::serialization::make_nvp("return", _return);
	}
};

typedef __sayHelloTo sayHelloTo;




struct __shutdown
{
	typedef boost::mpl::vector<  > _arg_list;


	
	
	__shutdown()
	{
	}
	
	
	// Copy constructor
	__shutdown(const __shutdown& o)
	{
		
	}

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
	}
};

typedef __shutdown shutdown;


} // Hello

        } // _corbasim_HelloApp


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct interface< HelloApp::Hello >
        {
            typedef cs_mpl::vector< _corbasim_HelloApp::Hello::sayHello,
                    _corbasim_HelloApp::Hello::sayHelloTo,
                    _corbasim_HelloApp::Hello::shutdown > _op_list;
            typedef cs_mpl::vector< _corbasim_HelloApp::Hello::sayHello,
                    _corbasim_HelloApp::Hello::sayHelloTo,
                    _corbasim_HelloApp::Hello::shutdown > _sorted_op_list;
            typedef cs_mpl::vector< _corbasim_HelloApp::Hello::sayHello,
                    _corbasim_HelloApp::Hello::sayHelloTo,
                    _corbasim_HelloApp::Hello::shutdown > _own_op_list;
            typedef cs_mpl::vector< > _parent_list;
        };

    } // adapted
} // corbasim

// OperationDef: HelloApp::Hello::sayHello
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_HelloApp::Hello::sayHello,
        ( ::TAO::String_Manager, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_HelloApp::Hello::sayHello >
        {
            typedef _corbasim_HelloApp::Hello::sayHello Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->sayHello();
            }
        };

        template< >
        struct name< _corbasim_HelloApp::Hello::sayHello >
        {
            static inline const char * call()
            {
                return "sayHello";
            }
        };

    } // adapted
} // corbasim


// OperationDef: HelloApp::Hello::sayHelloTo
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_HelloApp::Hello::sayHelloTo,
        ( HelloApp::Names, people)
        ( ::TAO::String_Manager, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_HelloApp::Hello::sayHelloTo >
        {
            typedef _corbasim_HelloApp::Hello::sayHelloTo Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->sayHelloTo(value.people);
            }
        };

        template< >
        struct name< _corbasim_HelloApp::Hello::sayHelloTo >
        {
            static inline const char * call()
            {
                return "sayHelloTo";
            }
        };

    } // adapted
} // corbasim


// OperationDef: HelloApp::Hello::shutdown
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_HelloApp::Hello::shutdown,
)

namespace corbasim
{
    namespace adapted
    {
        template< >
        struct is_oneway< _corbasim_HelloApp::Hello::shutdown > : public cs_mpl::true_
        {
        };

        template< >
        struct call< _corbasim_HelloApp::Hello::shutdown >
        {
            typedef _corbasim_HelloApp::Hello::shutdown Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->shutdown();
            }
        };

        template< >
        struct name< _corbasim_HelloApp::Hello::shutdown >
        {
            static inline const char * call()
            {
                return "shutdown";
            }
        };

    } // adapted
} // corbasim


#endif // HELLO_ADAPTED_HPP


#ifndef SIMPLE_ADAPTED_HPP
#define SIMPLE_ADAPTED_HPP

#include "simpleC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>



// UnionDef: SimpleExample::MyUnion
BOOST_FUSION_ADAPT_ADT(
	SimpleExample::MyUnion,
	( ::CORBA::Long, ::CORBA::Long, obj._d(), obj._d(val)) // Discriminator
	( ::CORBA::Long, ::CORBA::Long, obj.aa(), obj.aa(val))
	( ::CORBA::Long, ::CORBA::Long, obj.bb(), obj.bb(val))
     )

namespace boost
{
namespace fusion
{
namespace extension
{

template< >
struct struct_member_name< SimpleExample::MyUnion, 0>
{
	static inline const char * call()
	{
		return "_d";
	}
};

template< >
struct struct_member_name< SimpleExample::MyUnion, 1>
{
	static inline const char * call()
	{
		return "aa";
	}
};
template< >
struct struct_member_name< SimpleExample::MyUnion, 2>
{
	static inline const char * call()
	{
		return "bb";
	}
};

} // extension
} // fusion
} // boost

namespace corbasim
{
namespace adapted
{

template< >
struct is_union< SimpleExample::MyUnion > : public cs_mpl::true_
{
	typedef ::CORBA::Long discriminator_t;
	
	static const size_t size = 2;
	
	static inline discriminator_t* discriminators()
	{
		static discriminator_t _disc[] = { 
					100
			, 									101
			};		
		return _disc;
	}
	
	static inline unsigned int* member()
	{
		static unsigned int _members[] = { 
					1
			, 									2
			};		
		return _members;
	}
};

} // adapted
} // corbasim



// StructDef: SimpleExample::St
BOOST_FUSION_ADAPT_STRUCT(
	SimpleExample::St,
	( SimpleExample::St::_l_seq, l)
	( SimpleExample::St::_ss_seq, ss)
	( ::CORBA::Long, b)
	( SimpleExample::MyUnion, uniii)
     )

		
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< SimpleExample::St::_l_seq > : public cs_mpl::true_
{
	typedef ::CORBA::Long slice_type;
};

} // adapted
} // corbasim
		
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< SimpleExample::St::_ss_seq > : public cs_mpl::true_
{
	typedef ::TAO::String_Manager slice_type;
};

} // adapted
} // corbasim
	



namespace corbasim
{
namespace adapted
{

template < >
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

	



// StructDef: SimpleExample::Padre
BOOST_FUSION_ADAPT_STRUCT(
	SimpleExample::Padre,
	( SimpleExample::Hijo, h)
     )

	





// StructDef: SimpleExample::Abuelo
BOOST_FUSION_ADAPT_STRUCT(
	SimpleExample::Abuelo,
	( SimpleExample::Padres, p)
	( SimpleExample::Test_var, tt)
     )

	




namespace _corbasim_SimpleExample 
{


struct St
{
	typedef corbasim::adapted::member< ::SimpleExample::St, 0 > l_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::St, 1 > ss_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::St, 2 > b_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::St, 3 > uniii_corbasim_member;
	
};


namespace Test 
{
struct __operation1
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long >, corbasim::Arg_IN< ::CORBA::Long >, corbasim::Arg_IN< const SimpleExample::St& > > _arg_list;

	typedef corbasim::adapted::member< __operation1, 0 > a_corbasim_member;
	typedef corbasim::adapted::member< __operation1, 1 > b_corbasim_member;
	typedef corbasim::adapted::member< __operation1, 2 > c_corbasim_member;

	::CORBA::Long a;
	::CORBA::Long b;
	SimpleExample::St c;
	
	
	__operation1();
	
	__operation1(::CORBA::Long _a, ::CORBA::Long _b, const SimpleExample::St& _c);
	
	// Copy constructor
	__operation1(const __operation1& o);
};

typedef __operation1 operation1;




struct __operation4
{
	typedef boost::mpl::vector< corbasim::Arg_IN< SimpleExample::Test_ptr > > _arg_list;

	typedef corbasim::adapted::member< __operation4, 0 > a_corbasim_member;

	SimpleExample::Test_var a;
	
	
	__operation4();
	
	__operation4(SimpleExample::Test_ptr _a);
	
	// Copy constructor
	__operation4(const __operation4& o);
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
	typedef corbasim::adapted::member< ::SimpleExample::Abuelo, 1 > tt_corbasim_member;
	
};

} // _corbasim_SimpleExample







namespace corbasim
{
namespace adapted
{

template < >
struct interface < SimpleExample::Test >
{
	typedef cs_mpl::list< _corbasim_SimpleExample::Test::operation1, cs_mpl::list< _corbasim_SimpleExample::Test::operation4  >  >   _op_list;
	
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

} // adapted
} // corbasim












#endif // SIMPLE_ADAPTED_HPP



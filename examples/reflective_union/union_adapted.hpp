#ifndef UNION_ADAPTED_HPP
#define UNION_ADAPTED_HPP

#include "unionC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>



// Enum: MyModule::MyEnum
namespace corbasim
{
namespace adapted
{

template< >
struct enumeration< MyModule::MyEnum >
{
	static const unsigned int size = 3;
	
	static inline const char** values()
	{
		static const char* _data[] = {"AAA", "BBB", "CCC", 0};
		return _data;
	}
};

} // adapted
} // corbasim



// UnionDef: MyModule::MyUnion
BOOST_FUSION_ADAPT_ADT(
	MyModule::MyUnion,
	( MyModule::MyEnum, MyModule::MyEnum, obj._d(), obj._d(val)) // Discriminator
	( ::CORBA::Long, ::CORBA::Long, obj.one(), obj.one(val))
	( ::CORBA::Long, ::CORBA::Long, obj.other(), obj.other(val))
     )

namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, MyModule::MyUnion& t, const unsigned int /* unused */)
{	
	
}



} // serialization
} // boost

namespace boost
{
namespace fusion
{
namespace extension
{

template< >
struct struct_member_name< MyModule::MyUnion, 0>
{
	static inline const char * call()
	{
		return "_d";
	}
};

template< >
struct struct_member_name< MyModule::MyUnion, 1>
{
	static inline const char * call()
	{
		return "one";
	}
};
template< >
struct struct_member_name< MyModule::MyUnion, 2>
{
	static inline const char * call()
	{
		return "other";
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
struct is_union< MyModule::MyUnion > : public cs_mpl::true_
{
	typedef MyModule::MyEnum discriminator_t;
	
	static const size_t size = 3;
	
	static inline discriminator_t* discriminators()
	{
		static discriminator_t _disc[] = { 
					MyModule::AAA
			, 									MyModule::BBB
				, 					MyModule::CCC
			};		
		return _disc;
	}
	
	static inline unsigned int* member()
	{
		static unsigned int _members[] = { 
					1
			, 									2
				, 					2
			};		
		return _members;
	}
};

} // adapted
} // corbasim



// StructDef: MyModule::MyStruct
BOOST_FUSION_ADAPT_STRUCT(
	MyModule::MyStruct,
	( MyModule::MyStruct::_a, a)
     )

namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, MyModule::MyStruct& t, const unsigned int /* unused */)
{	
	ar & boost::serialization::make_nvp("a", t.a);
}



} // serialization
} // boost

	



namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, MyModule::MyInterface_var& t, const unsigned int version)
{	
	// TODO
}

} // serialization
} // boost

namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< MyModule::MyInterface_var > : public cs_mpl::true_
{
	typedef MyModule::MyInterface interface;
};

} // adapted
} // corbasim







namespace _corbasim_MyModule 
{




struct MyStruct
{
	typedef corbasim::adapted::member< ::MyModule::MyStruct, 0 > a_corbasim_member;
	
};


namespace MyInterface 
{
struct __operation
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const MyModule::MyUnion& > > _arg_list;

	typedef corbasim::adapted::member< __operation, 0 > uni_corbasim_member;

	MyModule::MyUnion uni;
	
	
	__operation();
	
	__operation(const MyModule::MyUnion& _uni);
	
	// Copy constructor
	__operation(const __operation& o);

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
		ar & boost::serialization::make_nvp("uni", uni);
	}
};

typedef __operation operation;


struct __operation2
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const MyModule::MyStruct& > > _arg_list;

	typedef corbasim::adapted::member< __operation2, 0 > uni_corbasim_member;

	MyModule::MyStruct uni;
	
	
	__operation2();
	
	__operation2(const MyModule::MyStruct& _uni);
	
	// Copy constructor
	__operation2(const __operation2& o);

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
		ar & boost::serialization::make_nvp("uni", uni);
	}
};

typedef __operation2 operation2;

} // MyInterface

} // _corbasim_MyModule









namespace corbasim
{
namespace adapted
{

template < >
struct interface < MyModule::MyInterface >
{
	typedef cs_mpl::list< _corbasim_MyModule::MyInterface::operation, cs_mpl::list< _corbasim_MyModule::MyInterface::operation2  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: MyModule::MyInterface::operation
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_MyModule::MyInterface::operation,
	( MyModule::MyUnion, uni)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_MyModule::MyInterface::operation >
{
	typedef _corbasim_MyModule::MyInterface::operation Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation(value.uni);
    }
};

} // adapted
} // corbasim


// OperationDef: MyModule::MyInterface::operation2
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_MyModule::MyInterface::operation2,
	( MyModule::MyStruct, uni)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_MyModule::MyInterface::operation2 >
{
	typedef _corbasim_MyModule::MyInterface::operation2 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation2(value.uni);
    }
};

} // adapted
} // corbasim




#endif // UNION_ADAPTED_HPP



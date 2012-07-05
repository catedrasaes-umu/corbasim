#ifndef STRING_ADAPTED_HPP
#define STRING_ADAPTED_HPP

#include "stringC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>





        
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< StringTest::NameSeq > : public cs_mpl::true_
{
	typedef StringTest::Name slice_type;
};

} // adapted
} // corbasim




        
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< StringTest::NameIDSeq > : public cs_mpl::true_
{
	typedef StringTest::NameID slice_type;
};

} // adapted
} // corbasim


// StructDef: StringTest::StructWithStrings
BOOST_FUSION_ADAPT_STRUCT(
	StringTest::StructWithStrings,
	( ::TAO::String_Manager, str)
	( ::TAO::String_Manager, nam)
	( ::TAO::String_Manager, id)
     )

	



namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< StringTest::InterfaceString_var > : public cs_mpl::true_
{
	typedef StringTest::InterfaceString interface;
};

} // adapted
} // corbasim















namespace _corbasim_StringTest 
{








struct StructWithStrings
{
	typedef corbasim::adapted::member< ::StringTest::StructWithStrings, 0 > str_corbasim_member;
	typedef corbasim::adapted::member< ::StringTest::StructWithStrings, 1 > nam_corbasim_member;
	typedef corbasim::adapted::member< ::StringTest::StructWithStrings, 2 > id_corbasim_member;
	
};


namespace InterfaceString 
{
struct __operation1
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

	typedef corbasim::adapted::member< __operation1, 0 > s_corbasim_member;

	::TAO::String_Manager s;
	
	
	__operation1();
	
	__operation1(const char* _s);
	
	// Copy constructor
	__operation1(const __operation1& o);
};

typedef __operation1 operation1;


struct __operation2
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

	typedef corbasim::adapted::member< __operation2, 0 > n_corbasim_member;

	::TAO::String_Manager n;
	
	
	__operation2();
	
	__operation2(const char* _n);
	
	// Copy constructor
	__operation2(const __operation2& o);
};

typedef __operation2 operation2;


struct __operation3
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const StringTest::NameSeq& > > _arg_list;

	typedef corbasim::adapted::member< __operation3, 0 > n_corbasim_member;

	StringTest::NameSeq n;
	
	
	__operation3();
	
	__operation3(const StringTest::NameSeq& _n);
	
	// Copy constructor
	__operation3(const __operation3& o);
};

typedef __operation3 operation3;


struct __operation4
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const StringTest::StructWithStrings& > > _arg_list;

	typedef corbasim::adapted::member< __operation4, 0 > n_corbasim_member;

	StringTest::StructWithStrings n;
	
	
	__operation4();
	
	__operation4(const StringTest::StructWithStrings& _n);
	
	// Copy constructor
	__operation4(const __operation4& o);
};

typedef __operation4 operation4;


struct __operation5
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

	typedef corbasim::adapted::member< __operation5, 0 > n_corbasim_member;

	::TAO::String_Manager n;
	
	
	__operation5();
	
	__operation5(const char* _n);
	
	// Copy constructor
	__operation5(const __operation5& o);
};

typedef __operation5 operation5;


struct __operation6
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const StringTest::NameIDSeq& > > _arg_list;

	typedef corbasim::adapted::member< __operation6, 0 > n_corbasim_member;

	StringTest::NameIDSeq n;
	
	
	__operation6();
	
	__operation6(const StringTest::NameIDSeq& _n);
	
	// Copy constructor
	__operation6(const __operation6& o);
};

typedef __operation6 operation6;

} // InterfaceString

} // _corbasim_StringTest













namespace corbasim
{
namespace adapted
{

template < >
struct interface < StringTest::InterfaceString >
{
	typedef cs_mpl::list< _corbasim_StringTest::InterfaceString::operation1, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation2, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation3, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation4, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation5, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation6  >  >  >  >  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: StringTest::InterfaceString::operation1
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation1,
	( ::TAO::String_Manager, s)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation1 >
{
	typedef _corbasim_StringTest::InterfaceString::operation1 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation1(value.s);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation2
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation2,
	( ::TAO::String_Manager, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation2 >
{
	typedef _corbasim_StringTest::InterfaceString::operation2 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation2(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation3
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation3,
	( StringTest::NameSeq, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation3 >
{
	typedef _corbasim_StringTest::InterfaceString::operation3 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation3(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation4
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation4,
	( StringTest::StructWithStrings, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation4 >
{
	typedef _corbasim_StringTest::InterfaceString::operation4 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation4(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation5
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation5,
	( ::TAO::String_Manager, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation5 >
{
	typedef _corbasim_StringTest::InterfaceString::operation5 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation5(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation6
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation6,
	( StringTest::NameIDSeq, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation6 >
{
	typedef _corbasim_StringTest::InterfaceString::operation6 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation6(value.n);
    }
};

} // adapted
} // corbasim




#endif // STRING_ADAPTED_HPP



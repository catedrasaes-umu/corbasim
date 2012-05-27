#include "string_adapted.hpp"

namespace corbasim
{
namespace adapted
{








template< >
const char * full_qualified_name< StringTest::StructWithStrings >::call()
{
	return "StringTest::StructWithStrings";
}

template< >
const char * name< StringTest::StructWithStrings >::call()
{
	return "StructWithStrings";
}



template< >
const char * full_qualified_name< StringTest::InterfaceString >::call()
{
	return "StringTest::InterfaceString";
}

template< >
const char * name< StringTest::InterfaceString >::call()
{
	return "InterfaceString";
}

template< >
CORBA::TypeCode const *  typecode< StringTest::InterfaceString >::call()
{
	return StringTest::_tc_InterfaceString;
}

template< >
const char * name< _corbasim_StringTest::InterfaceString::operation1 >::call()
{
	return "operation1";
}


template< >
const char * name< _corbasim_StringTest::InterfaceString::operation2 >::call()
{
	return "operation2";
}


template< >
const char * name< _corbasim_StringTest::InterfaceString::operation3 >::call()
{
	return "operation3";
}


template< >
const char * name< _corbasim_StringTest::InterfaceString::operation4 >::call()
{
	return "operation4";
}


template< >
const char * name< _corbasim_StringTest::InterfaceString::operation5 >::call()
{
	return "operation5";
}


template< >
const char * name< _corbasim_StringTest::InterfaceString::operation6 >::call()
{
	return "operation6";
}



} // namespace adapted
} // namespace corbasim

namespace _corbasim_StringTest 
{










namespace InterfaceString 
{

__operation1::__operation1()
{
}

__operation1::__operation1(const char* _s):
	s(_s)
{
	
}

// Copy constructor
__operation1::__operation1(const __operation1& o) :
	s(o.s)
{
	
}




__operation2::__operation2()
{
}

__operation2::__operation2(const char* _n):
	n(_n)
{
	
}

// Copy constructor
__operation2::__operation2(const __operation2& o) :
	n(o.n)
{
	
}




__operation3::__operation3()
{
}

__operation3::__operation3(const StringTest::NameSeq& _n):
	n(_n)
{
	
}

// Copy constructor
__operation3::__operation3(const __operation3& o) :
	n(o.n)
{
	
}




__operation4::__operation4()
{
}

__operation4::__operation4(const StringTest::StructWithStrings& _n):
	n(_n)
{
	
}

// Copy constructor
__operation4::__operation4(const __operation4& o) :
	n(o.n)
{
	
}




__operation5::__operation5()
{
}

__operation5::__operation5(const char* _n):
	n(_n)
{
	
}

// Copy constructor
__operation5::__operation5(const __operation5& o) :
	n(o.n)
{
	
}




__operation6::__operation6()
{
}

__operation6::__operation6(const StringTest::NameIDSeq& _n):
	n(_n)
{
	
}

// Copy constructor
__operation6::__operation6(const __operation6& o) :
	n(o.n)
{
	
}


} // InterfaceString

} // _corbasim_StringTest



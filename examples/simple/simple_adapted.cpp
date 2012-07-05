#include "simple_adapted.hpp"

namespace corbasim
{
namespace adapted
{
template< >
const char * full_qualified_name< SimpleExample::MyUnion >::call()
{
	return "SimpleExample::MyUnion";
}

template< >
const char * name< SimpleExample::MyUnion >::call()
{
	return "MyUnion";
}


template< >
const char * full_qualified_name< SimpleExample::St >::call()
{
	return "SimpleExample::St";
}

template< >
const char * name< SimpleExample::St >::call()
{
	return "St";
}



template< >
const char * full_qualified_name< SimpleExample::Test >::call()
{
	return "SimpleExample::Test";
}

template< >
const char * name< SimpleExample::Test >::call()
{
	return "Test";
}

template< >
CORBA::TypeCode const *  typecode< SimpleExample::Test >::call()
{
	return SimpleExample::_tc_Test;
}

template< >
const char * name< _corbasim_SimpleExample::Test::operation1 >::call()
{
	return "operation1";
}




template< >
const char * name< _corbasim_SimpleExample::Test::operation4 >::call()
{
	return "operation4";
}



template< >
const char * full_qualified_name< SimpleExample::Hijo >::call()
{
	return "SimpleExample::Hijo";
}

template< >
const char * name< SimpleExample::Hijo >::call()
{
	return "Hijo";
}



template< >
const char * full_qualified_name< SimpleExample::Padre >::call()
{
	return "SimpleExample::Padre";
}

template< >
const char * name< SimpleExample::Padre >::call()
{
	return "Padre";
}





template< >
const char * full_qualified_name< SimpleExample::Abuelo >::call()
{
	return "SimpleExample::Abuelo";
}

template< >
const char * name< SimpleExample::Abuelo >::call()
{
	return "Abuelo";
}



} // namespace adapted
} // namespace corbasim

namespace _corbasim_SimpleExample 
{




namespace Test 
{

__operation1::__operation1()
{
}

__operation1::__operation1(::CORBA::Long _a, ::CORBA::Long _b, const SimpleExample::St& _c):
	a(_a), b(_b), c(_c)
{
	
}

// Copy constructor
__operation1::__operation1(const __operation1& o) :
	a(o.a), b(o.b), c(o.c)
{
	
}






__operation4::__operation4()
{
}

__operation4::__operation4(SimpleExample::Test_ptr _a)
{
	
	a = SimpleExample::Test::_duplicate(_a);
}

// Copy constructor
__operation4::__operation4(const __operation4& o)
{
	
	a = o.a;
}


} // Test









} // _corbasim_SimpleExample



#include "union_adapted.hpp"

namespace corbasim
{
namespace adapted
{


template< >
const char * full_qualified_name< MyModule::MyUnion >::call()
{
	return "MyModule::MyUnion";
}

template< >
const char * name< MyModule::MyUnion >::call()
{
	return "MyUnion";
}


template< >
const char * full_qualified_name< MyModule::MyUnion2 >::call()
{
	return "MyModule::MyUnion2";
}

template< >
const char * name< MyModule::MyUnion2 >::call()
{
	return "MyUnion2";
}


template< >
const char * full_qualified_name< MyModule::MyUnion3 >::call()
{
	return "MyModule::MyUnion3";
}

template< >
const char * name< MyModule::MyUnion3 >::call()
{
	return "MyUnion3";
}


template< >
const char * full_qualified_name< MyModule::MyStruct >::call()
{
	return "MyModule::MyStruct";
}

template< >
const char * name< MyModule::MyStruct >::call()
{
	return "MyStruct";
}



template< >
const char * full_qualified_name< MyModule::MyInterface >::call()
{
	return "MyModule::MyInterface";
}

template< >
const char * name< MyModule::MyInterface >::call()
{
	return "MyInterface";
}

template< >
CORBA::TypeCode const *  typecode< MyModule::MyInterface >::call()
{
	return MyModule::_tc_MyInterface;
}

template< >
const char * name< _corbasim_MyModule::MyInterface::operation >::call()
{
	return "operation";
}


template< >
const char * name< _corbasim_MyModule::MyInterface::operation1 >::call()
{
	return "operation1";
}


template< >
const char * name< _corbasim_MyModule::MyInterface::operation2 >::call()
{
	return "operation2";
}


template< >
const char * name< _corbasim_MyModule::MyInterface::operation3 >::call()
{
	return "operation3";
}



} // namespace adapted
} // namespace corbasim

namespace _corbasim_MyModule 
{










namespace MyInterface 
{

__operation::__operation()
{
}

__operation::__operation(const MyModule::MyUnion& _uni):
	uni(_uni)
{
	
}

// Copy constructor
__operation::__operation(const __operation& o) :
	uni(o.uni)
{
	
}




__operation1::__operation1()
{
}

__operation1::__operation1(const MyModule::MyUnion2& _uni):
	uni(_uni)
{
	
}

// Copy constructor
__operation1::__operation1(const __operation1& o) :
	uni(o.uni)
{
	
}




__operation2::__operation2()
{
}

__operation2::__operation2(const MyModule::MyStruct& _uni):
	uni(_uni)
{
	
}

// Copy constructor
__operation2::__operation2(const __operation2& o) :
	uni(o.uni)
{
	
}




__operation3::__operation3()
{
}

__operation3::__operation3(const MyModule::MyUnion3& _uni):
	uni(_uni)
{
	
}

// Copy constructor
__operation3::__operation3(const __operation3& o) :
	uni(o.uni)
{
	
}


} // MyInterface

} // _corbasim_MyModule



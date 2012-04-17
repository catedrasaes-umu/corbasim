#include "return_adapted.hpp"

namespace corbasim
{
namespace adapted
{
template< >
const char * full_qualified_name< AAAAAAAAA::ESS >::call()
{
	return "AAAAAAAAA::ESS";
}

template< >
const char * name< AAAAAAAAA::ESS >::call()
{
	return "ESS";
}







template< >
const char * full_qualified_name< AAAAAAAAA::IIIIIIIIII >::call()
{
	return "AAAAAAAAA::IIIIIIIIII";
}

template< >
const char * name< AAAAAAAAA::IIIIIIIIII >::call()
{
	return "IIIIIIIIII";
}

template< >
CORBA::TypeCode const *  typecode< AAAAAAAAA::IIIIIIIIII >::call()
{
	return AAAAAAAAA::_tc_IIIIIIIIII;
}

template< >
const char * name< _corbasim_AAAAAAAAA::IIIIIIIIII::op1 >::call()
{
	return "op1";
}


template< >
const char * name< _corbasim_AAAAAAAAA::IIIIIIIIII::op2 >::call()
{
	return "op2";
}



} // namespace adapted
} // namespace corbasim

namespace _corbasim_AAAAAAAAA 
{






namespace IIIIIIIIII 
{

__op1::__op1()
{
}


// Copy constructor
__op1::__op1(const __op1& o) :
	
_return(o._return){
	
}




__op2::__op2()
{
}


// Copy constructor
__op2::__op2(const __op2& o) :
	
_return(o._return){
	
}


} // IIIIIIIIII

} // _corbasim_AAAAAAAAA



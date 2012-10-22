#include "server_example_adapted.hpp"

namespace corbasim
{
namespace adapted
{
template< >
const char * full_qualified_name< prueba::Iface >::call()
{
	return "prueba::Iface";
}

template< >
const char * name< prueba::Iface >::call()
{
	return "Iface";
}

template< >
CORBA::TypeCode const *  typecode< prueba::Iface >::call()
{
	return prueba::_tc_Iface;
}

template< >
const char * name< _corbasim_prueba::Iface::operation >::call()
{
	return "operation";
}



} // namespace adapted
} // namespace corbasim

namespace _corbasim_prueba 
{
namespace Iface 
{

__operation::__operation()
{
}


// Copy constructor
__operation::__operation(const __operation& o)
{
	
}


} // Iface

} // _corbasim_prueba



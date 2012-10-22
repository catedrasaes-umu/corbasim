#ifndef SERVER_EXAMPLE_ADAPTED_HPP
#define SERVER_EXAMPLE_ADAPTED_HPP

#include "server_exampleC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>



namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< prueba::Iface_var > : public cs_mpl::true_
{
	typedef prueba::Iface interface;
};

} // adapted
} // corbasim





namespace _corbasim_prueba 
{
namespace Iface 
{
struct __operation
{
	typedef boost::mpl::vector<  > _arg_list;


	
	
	__operation();
	
	
	// Copy constructor
	__operation(const __operation& o);
};

typedef __operation operation;

} // Iface

} // _corbasim_prueba



namespace corbasim
{
namespace adapted
{

template < >
struct interface < prueba::Iface >
{
	typedef cs_mpl::list< _corbasim_prueba::Iface::operation  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: prueba::Iface::operation
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_prueba::Iface::operation,
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_prueba::Iface::operation >
{
	typedef _corbasim_prueba::Iface::operation Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation();
    }
};

} // adapted
} // corbasim




#endif // SERVER_EXAMPLE_ADAPTED_HPP



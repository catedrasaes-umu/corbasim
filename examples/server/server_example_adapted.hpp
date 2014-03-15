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


namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< prueba::Iface::FloatSeq > : public cs_mpl::true_
{
    typedef ::CORBA::Float slice_type;
};

} // adapted
} // corbasim






namespace _corbasim_prueba
{
namespace Iface
{


struct __operation
{
    typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long >, corbasim::Arg_IN< const prueba::Iface::FloatSeq& > > _arg_list;

    typedef corbasim::adapted::member< __operation, 0 > a_corbasim_member;
    typedef corbasim::adapted::member< __operation, 1 > fs_corbasim_member;

    ::CORBA::Long a;
    prueba::Iface::FloatSeq fs;


    __operation();

    __operation(::CORBA::Long _a, const prueba::Iface::FloatSeq& _fs);

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
    ( ::CORBA::Long, a)
    ( prueba::Iface::FloatSeq, fs)
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
 ref->operation(value.a, value.fs);
    }
};

} // adapted
} // corbasim




#endif // SERVER_EXAMPLE_ADAPTED_HPP



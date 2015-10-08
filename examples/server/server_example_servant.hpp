#ifndef SERVER_EXAMPLE_SERVANT_HPP
#define SERVER_EXAMPLE_SERVANT_HPP

#include "server_exampleS.h"
#include "server_example_adapted.hpp"

namespace corbasim
{
namespace adapted
{

template< >
struct servant< prueba::Iface >
{
    template < typename F >
    class _type : public virtual POA_prueba::Iface
    {
    public:

        _type(F f) :
            __f(f)
        {
        }

        void operation(CORBA::Long a, const prueba::Iface::FloatSeq& fs)
        {
            _corbasim_prueba::Iface::operation _val(a, fs);

            __f(_val);

        }

        
    protected:
        F __f;
    };

    class interceptor : public virtual POA_prueba::Iface
    {
    public:

        interceptor()
        {
        }

        void _set_reference(CORBA::Object_ptr obj)
        {
            __ref = prueba::Iface::_narrow(obj);
        }

        virtual void operation(CORBA::Long a, const prueba::Iface::FloatSeq& fs)
        {
            _corbasim_prueba::Iface::operation _val(a, fs);

            if (!CORBA::is_nil(__ref.in()))
            {
                __ref->operation(_val.a, _val.fs);
            }

        }

        
    protected:
        prueba::Iface_var __ref;
    };
};

} // adapted
} // corbasim


#endif // SERVER_EXAMPLE_SERVANT_HPP



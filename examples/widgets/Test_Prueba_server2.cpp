#include <tao/ORB.h>
#include "widgetsS.h"
#include "widgets_adapted.hpp"
#include "widgets_servant.hpp"

#include <corbasim/core/archives.hpp>
#include <corbasim/qt/RequestNotifier.hpp>

#include <iostream>

#define CORBASIM_OP_FUNCTOR(fqn)                    \
    void operator()(const _corbasim_ ## fqn & val)  \
    /***/

template< typename F >
class request_functor
{
public:

    request_functor(F f) : __f(f) {}

    template< typename Value >
    void operator()(const Value& val)
    {
    }

protected:

    F __f;
};

int main(int argc, char **argv)
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    corbasim::qt::RequestNotifier notifier;
    request_functor< corbasim::qt::RequestNotifier& > functor(notifier);
    POA_Test::Prueba* _impl = 
        corbasim::adapted::create_servant< Test::Prueba >(functor);

    CORBA::Object_var rootPOAObj = orb->resolve_initial_references( "RootPOA");

    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(
            rootPOAObj.in());

    PortableServer::POAManager_var manager = rootPOA->the_POAManager();

    PortableServer::ObjectId_var myObjID = rootPOA->activate_object( _impl);

    CORBA::Object_var obj = rootPOA->servant_to_reference( _impl);

    CORBA::String_var ref = orb->object_to_string( obj);
    std::cout << ref << std::endl;

    manager->activate();
    orb->run();

    delete _impl;

    return 0;
}

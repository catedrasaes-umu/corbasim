#include <tao/ORB.h>
#include "widgetsC.h"
#include "widgets_adapted.hpp"
#include <corbasim/core/injector.hpp>

int main(int argc, char **argv)
{
    assert( argc > 1);

    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);
    CORBA::Object_var obj;
    obj = orb->string_to_object( argv[1]);

    Test::Prueba_var _Prueba = Test::Prueba::_narrow( obj.in());

    corbasim::core::injector < Test::Prueba > _injector;
    _injector.set_reference( _Prueba.in());

    for (int i = 2; i < argc; i++)
        _injector.append_file( argv[i]);

    _injector.run();

    return 0;
}

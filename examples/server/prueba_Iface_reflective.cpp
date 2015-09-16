
#include "server_exampleC.h"
#include "server_example_adapted.hpp"
#include "server_example_servant.hpp"
#include <corbasim/core/reflective.hpp>

namespace corbasim
{
    namespace core
    {
        template struct interface_reflective< prueba::Iface >;
    }
}

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_prueba_Iface()
{
    return corbasim::core::interface_reflective< prueba::Iface >::get_instance();
}


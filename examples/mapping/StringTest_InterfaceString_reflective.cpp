
#include "mappingC.h"
#include "mapping_adapted.hpp"
#include "mapping_servant.hpp"
#include <corbasim/core/reflective.hpp>

namespace corbasim
{
    namespace core
    {
        template struct interface_reflective< StringTest::InterfaceString >;
    }
}

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_StringTest_InterfaceString()
{
    return corbasim::core::interface_reflective< StringTest::InterfaceString >::get_instance();
}


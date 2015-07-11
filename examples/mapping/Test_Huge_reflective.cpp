
#include "mappingC.h"
#include "mapping_adapted.hpp"
#include "mapping_servant.hpp"
#include <corbasim/core/reflective.hpp>

namespace corbasim
{
    namespace core
    {
        template struct interface_reflective< Test::Huge >;
    }
}

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_Test_Huge()
{
    return corbasim::core::interface_reflective< Test::Huge >::get_instance();
}


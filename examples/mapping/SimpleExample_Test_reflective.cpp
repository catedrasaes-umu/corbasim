
#include "mappingC.h"
#include "mapping_adapted.hpp"
#include "mapping_servant.hpp"
#include <corbasim/core/reflective.hpp>

namespace corbasim
{
    namespace core
    {
        template struct interface_reflective< SimpleExample::Test >;
    }
}

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_SimpleExample_Test()
{
    return corbasim::core::interface_reflective< SimpleExample::Test >::get_instance();
}


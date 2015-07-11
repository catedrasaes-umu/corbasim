
#include "mappingC.h"
#include "mapping_adapted.hpp"
#include "mapping_servant.hpp"
#include <corbasim/core/reflective.hpp>

namespace corbasim
{
    namespace core
    {
        template struct interface_reflective< AAAAAAAAA::IIIIIIIIII >;
    }
}

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_AAAAAAAAA_IIIIIIIIII()
{
    return corbasim::core::interface_reflective< AAAAAAAAA::IIIIIIIIII >::get_instance();
}


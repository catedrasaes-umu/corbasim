
#include "CosnamingC.h"
#include "Cosnaming_adapted.hpp"
#include "Cosnaming_servant.hpp"
#include <corbasim/core/reflective.hpp>

namespace corbasim
{
    namespace core
    {
        template struct interface_reflective< CosNaming::NameContextExt >;
    }
}

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_CosNaming_NamingContextExt()
{
    return corbasim::core::interface_reflective< CosNaming::NamingContextExt >::get_instance();
}


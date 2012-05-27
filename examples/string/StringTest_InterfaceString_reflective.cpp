
#include "stringC.h"
#include "string_adapted.hpp"
#include "string_servant.hpp"
#include <corbasim/core/reflective.hpp>

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_StringTest_InterfaceString()
{
	return corbasim::core::interface_reflective< StringTest::InterfaceString >::get_instance();
}


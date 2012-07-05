
#include "simpleC.h"
#include "simple_adapted.hpp"
#include "simple_servant.hpp"
#include <corbasim/core/reflective.hpp>

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_SimpleExample_Test()
{
	return corbasim::core::interface_reflective< SimpleExample::Test >::get_instance();
}


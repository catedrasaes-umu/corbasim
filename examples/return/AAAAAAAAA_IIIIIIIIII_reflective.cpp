
#include "returnC.h"
#include "return_adapted.hpp"
#include "return_servant.hpp"
#include <corbasim/core/reflective.hpp>

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_AAAAAAAAA_IIIIIIIIII()
{
	return corbasim::core::interface_reflective< AAAAAAAAA::IIIIIIIIII >::get_instance();
}


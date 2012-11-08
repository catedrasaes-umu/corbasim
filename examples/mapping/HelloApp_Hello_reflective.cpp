
#include "mappingC.h"
#include "mapping_adapted.hpp"
#include "mapping_servant.hpp"
#include <corbasim/core/reflective.hpp>

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_HelloApp_Hello()
{
	return corbasim::core::interface_reflective< HelloApp::Hello >::get_instance();
}


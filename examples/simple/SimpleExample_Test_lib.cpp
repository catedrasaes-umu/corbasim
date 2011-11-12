#include "simpleC.h"
#include "simple_adapted.hpp"
#include "simple_servant.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/gui/gui_factory.hpp>

extern "C" corbasim::gui::gui_factory_base * corbasim_lib_SimpleExample_Test()
{
    return corbasim::gui::gui_factory< SimpleExample::Test >::get_instance();
}


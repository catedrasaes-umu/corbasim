#include "hugeC.h"
#include "huge_adapted.hpp"
#include "huge_servant.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/gui/gui_factory.hpp>

/*PROTECTED REGION ID(corbasim_lib_Test_Huge::custom_widgets_region) ENABLED START*/
/*PROTECTED REGION END*/

extern "C" corbasim::gui::gui_factory_base * corbasim_lib_Test_Huge()
{
    return corbasim::gui::gui_factory< Test::Huge >::get_instance();
}


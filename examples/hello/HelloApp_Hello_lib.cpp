#include "helloC.h"
#include "hello_adapted.hpp"
#include "hello_servant.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/gui/gui_factory.hpp>

/*PROTECTED REGION ID(corbasim_lib_HelloApp_Hello::custom_widgets_region) ENABLED START*/
/*PROTECTED REGION END*/

extern "C" const corbasim::gui::gui_factory_base * corbasim_lib_HelloApp_Hello()
{
    return corbasim::gui::gui_factory< HelloApp::Hello >::get_instance();
}


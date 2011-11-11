#include <corbasim/impl.hpp>
#include "simpleC.h"
#include "simple_adapted.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/dialogs.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/qt/client/SimpleClient.hpp>

/*PROTECTED REGION ID(SimpleExample_Test::custom_widgets_region) ENABLED START*/
/*PROTECTED REGION END*/

int main(int argc, char **argv)
{
    QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale());
    QApplication app( argc, argv);

    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);
    CORBA::Object_var obj;

    if (argc > 1)
        obj = orb->string_to_object( argv[1]);

    SimpleExample::Test_var _Test = SimpleExample::Test::_narrow( obj.in());

    corbasim::qt::client::SimpleClient window;
    window.initialize( _Test.in());
    window.show();
    return app.exec();
}

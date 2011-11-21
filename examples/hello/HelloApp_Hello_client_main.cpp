#include <corbasim/impl.hpp>
#include "helloC.h"
#include "hello_adapted.hpp"
#include "hello_servant.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/dialogs.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/qt/client/SimpleClient.hpp>

/*PROTECTED REGION ID(HelloApp_Hello::custom_widgets_region) ENABLED START*/
/*PROTECTED REGION END*/

int main(int argc, char **argv)
{
    QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale());
    QApplication app( argc, argv);

    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);
    CORBA::Object_var obj;

    if (argc > 1)
        obj = orb->string_to_object( argv[1]);

    HelloApp::Hello_var _Hello = HelloApp::Hello::_narrow( obj.in());

    corbasim::qt::client::SimpleClient window;
    window.initialize( _Hello.in());
    window.show();
    return app.exec();
}

#include <tao/ORB.h>
#include "CosnamingC.h"
#include "Cosnaming_adapted.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/gui/dialogs.hpp>
#include <corbasim/gui/trees.hpp>
#include <corbasim/qt/client/SimpleClient.hpp>

/*PROTECTED REGION ID(CosNaming_BindingIterator::custom_widgets_region) ENABLED START*/
/*PROTECTED REGION END*/

int main(int argc, char **argv)
{
    QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale());
    QApplication app( argc, argv);

    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);
    CORBA::Object_var obj;

    if (argc > 1)
        obj = orb->string_to_object( argv[1]);

    CosNaming::BindingIterator_var _BindingIterator =
            CosNaming::BindingIterator::_narrow( obj.in());

    corbasim::qt::client::SimpleClient window;
    window.initialize( _BindingIterator.in());
    window.show();
    return app.exec();
}

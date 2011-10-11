#include <tao/ORB.h>
#include "widgetsC.h"
#include "widgets_adapted.hpp"
#include <corbasim/gui/widgets.hpp>
#include <corbasim/qt/python/AutoResponse.hpp>
#include <corbasim/qt/SimpleScriptEditor.hpp>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale());
    QApplication app( argc, argv);

    corbasim::gui::gui_factory_base * factory = 
        corbasim::gui::gui_factory< Test::Prueba >::get_instance();
 
    corbasim::qt::SimpleScriptEditor client;
    client.initialize(factory);

    corbasim::qt::python::AutoResponseWidget window;
    window.initialize( factory, factory);

    QObject::connect(&client,
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            &window,
            SLOT(requestReceived(corbasim::event::request_ptr)));

    client.show();
    window.show();
    return app.exec();
}


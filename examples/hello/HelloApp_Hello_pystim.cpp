#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <corbasim/impl.hpp>
#include <corbasim/gui/widgets.hpp>
#include <corbasim/qt/RequestProcessor.hpp>
#include <corbasim/qt/RequestNotifier.hpp>

#include "helloS.h"
#include "hello_adapted.hpp"
#include "hello_servant.hpp"

/*PROTECTED REGION ID(HelloApp_Hello_pystim::___config) ENABLED START*/
typedef HelloApp::Hello Opposite;
/*PROTECTED REGION END*/

int main(int argc, char **argv)
{
    // Initialization
    QTextCodec::setCodecForCStrings( QTextCodec::codecForLocale());
    QApplication app( argc, argv);

    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    corbasim::gui::gui_factory_base * input_factory =
            corbasim::gui::gui_factory< HelloApp::Hello >::get_instance();
    corbasim::gui::gui_factory_base * output_factory =
            corbasim::gui::gui_factory< Opposite >::get_instance();

    // Registring the servant
    corbasim::qt::RequestNotifier notifier;
    PortableServer::ServantBase_var _impl( corbasim::adapted::create_servant<
            HelloApp::Hello >( notifier));

    CORBA::Object_var rootPOAObj = orb->resolve_initial_references( "RootPOA");

    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(
            rootPOAObj.in());

    PortableServer::POAManager_var manager = rootPOA->the_POAManager();

    PortableServer::ObjectId_var myObjID =
            rootPOA->activate_object( _impl.in());

    CORBA::Object_var obj = rootPOA->servant_to_reference( _impl.in());

    CORBA::String_var ref = orb->object_to_string( obj);
    std::cout << ref << std::endl;

    manager->activate();

    // Window
    corbasim::qt::RequestProcessorMain window;
    window.initialize( input_factory, output_factory);

    QObject::connect( &notifier, SIGNAL( notifyRequest(
            corbasim::event::request_ptr)), &window, SLOT( setInputRequest(
            corbasim::event::request_ptr)));

    window.show();

    // Running
    boost::thread orbThread( boost::bind( &CORBA::ORB::run, orb.in()));

    int res = app.exec();

    orb->shutdown();
    orbThread.join();
    orb->destroy();

    return res;
}

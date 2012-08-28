#include <corbasim/impl.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/Application.hpp>
#include <corbasim/gui/client/SimpleClient.hpp>
#include <iostream>

using namespace corbasim::gui;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "You must specify an interface full qualified name" 
            << std::endl;
        return -1;
    }

    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
	QApplication app(argc, argv);
    QThread applicationThread;
    Application application;
	SimpleClient window;

    // Connect signals
    QObject::connect(&application, SIGNAL(objrefCreated(Objref_ptr)), 
            &window, SLOT(initialize(Objref_ptr)));

    // Create the object
    ObjrefConfig cfg;
    cfg.name = "Object reference";
    cfg.fqn = argv[1];

    application.createObjref(cfg);

    // Run
    application.moveToThread(&applicationThread);
    applicationThread.start();

	window.show();
	int res = app.exec();

    applicationThread.quit();
    applicationThread.wait();

    return res;
}


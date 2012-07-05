
#include <corbasim/impl.hpp>
#include "simpleC.h"
#include <corbasim/reflective_gui/SimpleClient.hpp>

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_SimpleExample_Test();

int main(int argc, char **argv)
{
	QTextCodec::setCodecForCStrings (QTextCodec::codecForLocale());
	QApplication app(argc, argv);

	CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
	CORBA::Object_var obj;
	
	corbasim::reflective_gui::SimpleClient window;
	window.initialize(corbasim_reflective_SimpleExample_Test());
	
	if(argc > 1)
	{
		obj = orb->string_to_object(argv[1]);
		
		window.setReference(obj);
	}
	
	window.show();
	return app.exec();
}

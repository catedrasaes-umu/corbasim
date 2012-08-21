#include <corbasim/impl.hpp>
#include <corbasim/gui/utils.hpp>
#include <corbasim/gui/SimpleClient.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "You must specify an interface full qualified name" 
            << std::endl;
        return -1;
    }

    for (int i = 0; i < argc; i++) 
    {
        std::cout << "[" << i << "] " << argv[i] << std::endl;
    }

	QTextCodec::setCodecForCStrings (QTextCodec::codecForLocale());
	QApplication app(argc, argv);

    ::corbasim::core::interface_reflective_base const * reflective = 
        ::corbasim::gui::getReflectiveByFQN(argv[1]);

    if (!reflective)
    {
        std::cerr << "Library not found: " << argv[1] << std::endl;
        return -1;
    }

	CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
	CORBA::Object_var obj;
	
	corbasim::gui::SimpleClient window;
	window.initialize(reflective);
	
	if(argc > 2)
	{
		obj = orb->string_to_object(argv[2]);
		
		window.setReference(obj);
	}
	
	window.show();
	return app.exec();
}


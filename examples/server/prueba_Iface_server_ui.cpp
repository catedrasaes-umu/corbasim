
#include <corbasim/impl.hpp>
#include "server_exampleS.h"
#include "server_example_adapted.hpp"
#include <corbasim/gui/server/ServerApp.hpp>

/*PROTECTED REGION ID(prueba_Iface_server_ui::___prolog) ENABLED START*/
#include <iostream>
/*PROTECTED REGION END*/

class prueba_Iface_impl : virtual public POA_prueba::Iface
{
public:

	prueba_Iface_impl( ::corbasim::gui::ServerApp& app) :
		m_app(app)
	{
	}

	
	void operation(::CORBA::Long a, const prueba::Iface::FloatSeq& fs)
	{
		_corbasim_prueba::Iface::operation _val(a, fs);
		
		/*PROTECTED REGION ID(prueba_Iface_server_ui::prueba_Iface_operation) ENABLED START*/
        std::cout << __FUNCTION__  << std::endl;
		/*PROTECTED REGION END*/

	}
	

    /*PROTECTED REGION ID(prueba_Iface_server_ui::___body) ENABLED START*/
    /*PROTECTED REGION END*/

protected:
	
	::corbasim::gui::ServerApp& m_app;
};

int main(int argc, char **argv)
{
    corbasim::gui::ServerApp app(argc, argv);

	// Servant
    prueba_Iface_impl _impl(app);

    CORBA::Object_var myRef = app.setServant("prueba::Iface", "this", &_impl);

    /*PROTECTED REGION ID(prueba_Iface_server_ui::___main) ENABLED START*/
    app.setClient("prueba::Iface", "prueba", myRef);
    app.setClient("prueba::Iface", "nil", prueba::Iface::_nil());

    app.setClient("prueba::Iface", "prueba1", myRef);
    app.setClient("prueba::Iface", "prueba2", myRef);
    app.setClient("prueba::Iface", "prueba3", myRef);
    app.setClient("prueba::Iface", "prueba4", myRef);
    app.setClient("prueba::Iface", "prueba5", myRef);
    app.setClient("prueba::Iface", "prueba7", myRef);
    app.setClient("prueba::Iface", "prueba8", myRef);
    app.setClient("prueba::Iface", "prueba9", myRef);
    app.setClient("prueba::Iface", "prueba10", myRef);
    /*PROTECTED REGION END*/
   
    return app.exec();
}

/*PROTECTED REGION ID(prueba_Iface_server_ui::___epilog) ENABLED START*/
/*PROTECTED REGION END*/


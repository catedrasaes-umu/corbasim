
#include <corbasim/impl.hpp>
#include <corbasim/cosnaming/CosnamingC.h>
#include "server_exampleS.h"
#include "server_example_adapted.hpp"

#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

/*PROTECTED REGION ID(prueba_Iface_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class prueba_Iface_impl : virtual public POA_prueba::Iface
{
public:

    /*PROTECTED REGION ID(prueba_Iface_impl::___public) ENABLED START*/
    prueba_Iface_impl(prueba::Iface_ptr _reference) :
        __m_reference(prueba::Iface::_duplicate(_reference))
    {
    }
    /*PROTECTED REGION END*/

    
    void operation(CORBA::Long a, const prueba::Iface::FloatSeq& fs)
    {
        /*PROTECTED REGION ID(prueba_Iface_impl::prueba_Iface_operation___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        _corbasim_prueba::Iface::operation _val(a, fs);

        try {
            if (!CORBA::is_nil(__m_reference))
__m_reference->operation(_val.a, _val.fs);
        } catch(...) {
            std::cerr << "CORBA exception!" << std::endl;
        }

        /*PROTECTED REGION ID(prueba_Iface_impl::prueba_Iface_operation___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operation" << std::endl;

    }
    

protected:

    prueba::Iface_var __m_reference;
};

namespace _po = boost::program_options;

int main(int argc, char **argv)
{
    // Removes ORB related arguments
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // Program options
    std::string register_servant;
    std::string proxy_reference;

    _po::options_description _desc("Proxy Server options");
    _desc.add_options()
        ("help,h", "produce help message")
        ("register-servant,r", _po::value< std::string >(&register_servant),
         "register the servant into the name service")
        ("proxy-reference,p", _po::value< std::string >(&proxy_reference),
         "forward received calls to another servant");

    _po::variables_map _vm;
    _po::store(_po::parse_command_line(argc, argv, _desc), _vm);
    _po::notify(_vm);

    if (_vm.count("help"))
    {
        std::cout << _desc << std::endl;
        return 0;
    }

    bool reference_is_ns_entry = false;
    // TODO

    // Name Service
    CosNaming::NamingContextExt_var nc;

    if (reference_is_ns_entry || !register_servant.empty())
    {
        try {
            CORBA::Object_var ncObj = orb->resolve_initial_references("NameService");

            nc = CosNaming::NamingContextExt::_narrow(ncObj);
        } catch(...) {
        }

        if (CORBA::is_nil(nc))
            std::cerr << "Name service unavailable!" << std::endl;
    }

    // Proxy reference
    prueba::Iface_var reference;

    if (!proxy_reference.empty())
    {
        CORBA::Object_var refObj;

        if (reference_is_ns_entry && !CORBA::is_nil(nc))
            refObj = nc->resolve_str(proxy_reference.c_str());
        else
            refObj = orb->string_to_object(proxy_reference.c_str());

        reference = prueba::Iface::_narrow(refObj);
    }

    // Servant
    prueba_Iface_impl _impl(reference.in());

    CORBA::Object_var rootPOAObj =
            orb->resolve_initial_references("RootPOA");

    PortableServer::POA_var rootPOA =
            PortableServer::POA::_narrow(rootPOAObj.in());

    PortableServer::POAManager_var manager = rootPOA->the_POAManager();

    PortableServer::ObjectId_var myObjID =
                rootPOA->activate_object(&_impl);

    CORBA::Object_var obj = rootPOA->servant_to_reference(&_impl);

    // Displaying reference
    CORBA::String_var ref = orb->object_to_string(obj);
    std::cout << ref << std::endl;

    // Registring servant
    CosNaming::Name_var name;

    if (!register_servant.empty() && !CORBA::is_nil(nc))
    {
        name = nc->to_name(register_servant.c_str());

        nc->rebind(name, obj);
    }

    /*PROTECTED REGION ID(prueba_Iface_impl_server::___main) ENABLED START*/
    /*PROTECTED REGION END*/

    // Running
    manager->activate();
    orb->run();

    // Unbinding servant
    if (!CORBA::is_nil(nc) && name)
        nc->unbind(name);

    return 0;
}

#include <corbasim/impl.hpp>
#include <corbasim/cosnaming/CosnamingC.h>
#include "simpleS.h"
#include "simple_adapted.hpp"

#include <corbasim/core/archives.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/program_options.hpp>

/*PROTECTED REGION ID(SimpleExample_Test_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class SimpleExample_Test_impl: virtual public POA_SimpleExample::Test
{
public:

    /*PROTECTED REGION ID(SimpleExample_Test_impl::___public) ENABLED START*/
    SimpleExample_Test_impl(const std::string& log_file,
            SimpleExample::Test_ptr _reference) :
        __m_ofstream( log_file.c_str()),
                __m_reference( SimpleExample::Test::_duplicate( _reference))
    {
    }
    /*PROTECTED REGION END*/

    void operation1(::CORBA::Long a, ::CORBA::Long b,
            const SimpleExample::St& c)
    {
        std::ostringstream __oss;
        std::cout << ">";
        __oss << "operation1 ";

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation1___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        _corbasim_SimpleExample::Test::operation1 _val( a, b, c);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << __oss.str();

        if (__m_ofstream.is_open())
        {
            __m_ofstream << __oss.str();
            __m_ofstream.flush();
        }

        try
        {
            if (!CORBA::is_nil( __m_reference))
                __m_reference->operation1( _val.a, _val.b, _val.c);
        } catch (...)
        {
            std::cerr << "CORBA exception!" << std::endl;
        }

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation1___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operation1" << std::endl;

    }

    void operation4(SimpleExample::Test_ptr a)
    {
        std::ostringstream __oss;
        std::cout << ">";
        __oss << "operation4 ";

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation4___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        _corbasim_SimpleExample::Test::operation4 _val( a);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << __oss.str();

        if (__m_ofstream.is_open())
        {
            __m_ofstream << __oss.str();
            __m_ofstream.flush();
        }

        try
        {
            if (!CORBA::is_nil( __m_reference))
                __m_reference->operation4( _val.a);
        } catch (...)
        {
            std::cerr << "CORBA exception!" << std::endl;
        }

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation4___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operation4" << std::endl;

    }

protected:

    std::ofstream __m_ofstream;

    SimpleExample::Test_var __m_reference;
};

namespace _po = boost::program_options;

int main(int argc, char **argv)
{
    // Removes ORB related arguments
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    // Program options
    std::string register_servant;
    std::string log_file;
    std::string proxy_reference;

    _po::options_description _desc( "Proxy Server options");
    _desc.add_options()( "help,h", "produce help message")(
            "register-servant,r",
            _po::value< std::string >( &register_servant),
            "register the servant into the name service")( "proxy-reference,p",
            _po::value< std::string >( &proxy_reference),
            "forward received calls to another servant")( "log-file,l",
            _po::value< std::string >( &log_file),
            "store received calls in CORBASIM script format");

    _po::variables_map _vm;
    _po::store( _po::parse_command_line( argc, argv, _desc), _vm);
    _po::notify( _vm);

    if (_vm.count( "help"))
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
        try
        {
            CORBA::Object_var ncObj = orb->resolve_initial_references(
                    "NameService");

            nc = CosNaming::NamingContextExt::_narrow( ncObj);
        } catch (...)
        {
        }

        if (CORBA::is_nil( nc))
            std::cerr << "Name service unavailable!" << std::endl;
    }

    // Proxy reference
    SimpleExample::Test_var reference;

    if (!proxy_reference.empty())
    {
        CORBA::Object_var refObj;

        if (reference_is_ns_entry && !CORBA::is_nil( nc))
            refObj = nc->resolve_str( proxy_reference.c_str());
        else
            refObj = orb->string_to_object( proxy_reference.c_str());

        reference = SimpleExample::Test::_narrow( refObj);
    }

    // Servant
    SimpleExample_Test_impl _impl( log_file, reference.in());

    CORBA::Object_var rootPOAObj = orb->resolve_initial_references( "RootPOA");

    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(
            rootPOAObj.in());

    PortableServer::POAManager_var manager = rootPOA->the_POAManager();

    PortableServer::ObjectId_var myObjID = rootPOA->activate_object( &_impl);

    CORBA::Object_var obj = rootPOA->servant_to_reference( &_impl);

    // Displaying reference
    CORBA::String_var ref = orb->object_to_string( obj);
    std::cout << ref << std::endl;

    // Registring servant
    CosNaming::Name_var name;

    if (!register_servant.empty() && !CORBA::is_nil( nc))
    {
        name = nc->to_name( register_servant.c_str());

        nc->rebind( name, obj);
    }

    /*PROTECTED REGION ID(SimpleExample_Test_impl_server::___main) ENABLED START*/
    /*PROTECTED REGION END*/

    // Running
    manager->activate();
    orb->run();

    // Unbinding servant    
    if (!CORBA::is_nil( nc) && name)
        nc->unbind( name);

    return 0;
}

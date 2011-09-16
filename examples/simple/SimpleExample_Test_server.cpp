#include <tao/ORB.h>
#include "simpleS.h"
#include "simple_adapted.hpp"

#include <corbasim/core/archives.hpp>

#include <iostream>
#include <sstream>

/*PROTECTED REGION ID(SimpleExample_Test_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class SimpleExample_Test_impl: virtual public POA_SimpleExample::Test
{
public:

    /*PROTECTED REGION ID(SimpleExample_Test_impl::___public) ENABLED START*/
    /*PROTECTED REGION END*/

    void operation1(::CORBA::Long a, ::CORBA::Long b,
            const SimpleExample::St& c)
    {
        std::ostringstream __oss;
        std::cout << ">operation1" << std::endl;
        __oss << "operation1 ";

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation1___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_SimpleExample::Test::operation1 _val( a, b, c);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation1___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operation1" << std::endl;

    }

    void operation4(SimpleExample::Test_ptr a)
    {
        std::ostringstream __oss;
        std::cout << ">operation4" << std::endl;
        __oss << "operation4 ";

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation4___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_SimpleExample::Test::operation4 _val( a);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(SimpleExample_Test_impl::SimpleExample_Test_operation4___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operation4" << std::endl;

    }

};

int main(int argc, char **argv)
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    SimpleExample_Test_impl _impl;

    CORBA::Object_var rootPOAObj = orb->resolve_initial_references( "RootPOA");

    PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(
            rootPOAObj.in());

    PortableServer::POAManager_var manager = rootPOA->the_POAManager();

    PortableServer::ObjectId_var myObjID = rootPOA->activate_object( &_impl);

    CORBA::Object_var obj = rootPOA->servant_to_reference( &_impl);

    CORBA::String_var ref = orb->object_to_string( obj);
    std::cout << ref << std::endl;

    manager->activate();
    orb->run();
}

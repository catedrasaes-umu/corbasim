#include <tao/ORB.h>
#include "widgetsS.h"
#include "widgets_adapted.hpp"

#include <corbasim/core/archives.hpp>

#include <iostream>
#include <sstream>

/*PROTECTED REGION ID(Test_Prueba_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class Test_Prueba_impl: virtual public POA_Test::Prueba
{
public:

    /*PROTECTED REGION ID(Test_Prueba_impl::___public) ENABLED START*/
    /*PROTECTED REGION END*/

    void operacion1(const Test::St2& a, const Test::St& b)
    {
        std::ostringstream __oss;
        std::cout << ">operacion1" << std::endl;
        __oss << "operacion1 ";

        /*PROTECTED REGION ID(Test_Prueba_impl::Test_Prueba_operacion1___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_Test::Prueba::operacion1 _val( a, b);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(Test_Prueba_impl::Test_Prueba_operacion1___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operacion1" << std::endl;

    }

    void operacion2(Test::Prueba_ptr myref)
    {
        std::ostringstream __oss;
        std::cout << ">operacion2" << std::endl;
        __oss << "operacion2 ";

        /*PROTECTED REGION ID(Test_Prueba_impl::Test_Prueba_operacion2___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_Test::Prueba::operacion2 _val( myref);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(Test_Prueba_impl::Test_Prueba_operacion2___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operacion2" << std::endl;

    }

    void operacion3()
    {
        std::ostringstream __oss;
        std::cout << ">operacion3" << std::endl;
        __oss << "operacion3 ";

        /*PROTECTED REGION ID(Test_Prueba_impl::Test_Prueba_operacion3___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        __oss << std::endl;

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(Test_Prueba_impl::Test_Prueba_operacion3___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<operacion3" << std::endl;

    }

};

int main(int argc, char **argv)
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    Test_Prueba_impl _impl;

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

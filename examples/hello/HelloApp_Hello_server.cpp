#include <tao/ORB.h>
#include "helloS.h"
#include "hello_adapted.hpp"

#include <corbasim/core/archives.hpp>

#include <iostream>
#include <sstream>

/*PROTECTED REGION ID(HelloApp_Hello_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class HelloApp_Hello_impl: virtual public POA_HelloApp::Hello
{
public:

    /*PROTECTED REGION ID(HelloApp_Hello_impl::___public) ENABLED START*/
    /*PROTECTED REGION END*/

    char* sayHello()
    {
        std::ostringstream __oss;
        std::cout << ">sayHello" << std::endl;
        __oss << "sayHello ";

        /*PROTECTED REGION ID(HelloApp_Hello_impl::HelloApp_Hello_sayHello___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_HelloApp::Hello::sayHello _val;
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(HelloApp_Hello_impl::HelloApp_Hello_sayHello___post) ENABLED START*/
        _val._return = "Hello world!";
        /*PROTECTED REGION END*/

        std::cout << "<sayHello" << std::endl;

        return CORBA::string_dup( _val._return);
    }

    char* sayHelloTo(const HelloApp::Names& people)
    {
        std::ostringstream __oss;
        std::cout << ">sayHelloTo" << std::endl;
        __oss << "sayHelloTo ";

        /*PROTECTED REGION ID(HelloApp_Hello_impl::HelloApp_Hello_sayHelloTo___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_HelloApp::Hello::sayHelloTo _val( people);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(HelloApp_Hello_impl::HelloApp_Hello_sayHelloTo___post) ENABLED START*/
        std::ostringstream hoss;
        for (int i = 0; i < people.length(); i++) 
        {
            hoss << "hello " << people[i];
            if (i + 1 == people.length())
            {
            } 
            else if (i + 2 == people.length())
            {
                hoss << " and ";
            }
            else 
                hoss << ", ";
        }
        _val._return = hoss.str().c_str();
        /*PROTECTED REGION END*/

        std::cout << "<sayHelloTo" << std::endl;

        return CORBA::string_dup( _val._return);
    }

    void shutdown()
    {
        std::ostringstream __oss;
        std::cout << ">shutdown" << std::endl;
        __oss << "shutdown ";

        /*PROTECTED REGION ID(HelloApp_Hello_impl::HelloApp_Hello_shutdown___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        __oss << std::endl;

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(HelloApp_Hello_impl::HelloApp_Hello_shutdown___post) ENABLED START*/
        exit( 0);
        /*PROTECTED REGION END*/

        std::cout << "<shutdown" << std::endl;

    }

};

int main(int argc, char **argv)
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    HelloApp_Hello_impl _impl;

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

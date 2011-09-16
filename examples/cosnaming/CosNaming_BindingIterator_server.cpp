#include <tao/ORB.h>
#include "CosnamingS.h"
#include "Cosnaming_adapted.hpp"

#include <corbasim/core/archives.hpp>

#include <iostream>
#include <sstream>

/*PROTECTED REGION ID(CosNaming_BindingIterator_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class CosNaming_BindingIterator_impl: virtual public POA_CosNaming::BindingIterator
{
public:

    /*PROTECTED REGION ID(CosNaming_BindingIterator_impl::___public) ENABLED START*/
    /*PROTECTED REGION END*/

    ::CORBA::Boolean next_one(CosNaming::Binding_out b)
    {
        std::ostringstream __oss;
        std::cout << ">next_one" << std::endl;
        __oss << "next_one ";

        /*PROTECTED REGION ID(CosNaming_BindingIterator_impl::CosNaming_BindingIterator_next_one___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::BindingIterator::next_one _val( b);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_BindingIterator_impl::CosNaming_BindingIterator_next_one___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<next_one" << std::endl;

        return _val._return;
    }

    ::CORBA::Boolean next_n(::CORBA::ULong how_many,
            CosNaming::BindingList_out bl)
    {
        std::ostringstream __oss;
        std::cout << ">next_n" << std::endl;
        __oss << "next_n ";

        /*PROTECTED REGION ID(CosNaming_BindingIterator_impl::CosNaming_BindingIterator_next_n___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::BindingIterator::next_n _val( how_many, bl);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_BindingIterator_impl::CosNaming_BindingIterator_next_n___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<next_n" << std::endl;

        return _val._return;
    }

    void destroy()
    {
        std::ostringstream __oss;
        std::cout << ">destroy" << std::endl;
        __oss << "destroy ";

        /*PROTECTED REGION ID(CosNaming_BindingIterator_impl::CosNaming_BindingIterator_destroy___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        __oss << std::endl;

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_BindingIterator_impl::CosNaming_BindingIterator_destroy___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<destroy" << std::endl;

    }

};

int main(int argc, char **argv)
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    CosNaming_BindingIterator_impl _impl;

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

#include <tao/ORB.h>
#include "CosnamingS.h"
#include "Cosnaming_adapted.hpp"

#include <corbasim/core/archives.hpp>

#include <iostream>
#include <sstream>

/*PROTECTED REGION ID(CosNaming_NamingContext_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class CosNaming_NamingContext_impl: virtual public POA_CosNaming::NamingContext
{
public:

    /*PROTECTED REGION ID(CosNaming_NamingContext_impl::___public) ENABLED START*/
    /*PROTECTED REGION END*/

    void bind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
    {
        std::ostringstream __oss;
        std::cout << ">bind" << std::endl;
        __oss << "bind ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_bind___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::bind _val( n, obj);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_bind___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<bind" << std::endl;

    }

    void rebind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
    {
        std::ostringstream __oss;
        std::cout << ">rebind" << std::endl;
        __oss << "rebind ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_rebind___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::rebind _val( n, obj);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_rebind___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<rebind" << std::endl;

    }

    void bind_context(const CosNaming::Name& n, CosNaming::NamingContext_ptr nc)
    {
        std::ostringstream __oss;
        std::cout << ">bind_context" << std::endl;
        __oss << "bind_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_bind_context___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::bind_context _val( n, nc);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_bind_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<bind_context" << std::endl;

    }

    void rebind_context(const CosNaming::Name& n,
            CosNaming::NamingContext_ptr nc)
    {
        std::ostringstream __oss;
        std::cout << ">rebind_context" << std::endl;
        __oss << "rebind_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_rebind_context___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::rebind_context _val( n, nc);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_rebind_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<rebind_context" << std::endl;

    }

    ::CORBA::Object_ptr resolve(const CosNaming::Name& n)
    {
        std::ostringstream __oss;
        std::cout << ">resolve" << std::endl;
        __oss << "resolve ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_resolve___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::resolve _val( n);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_resolve___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<resolve" << std::endl;

        return _val._return;
    }

    void unbind(const CosNaming::Name& n)
    {
        std::ostringstream __oss;
        std::cout << ">unbind" << std::endl;
        __oss << "unbind ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_unbind___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::unbind _val( n);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_unbind___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<unbind" << std::endl;

    }

    CosNaming::NamingContext_ptr new_context()
    {
        std::ostringstream __oss;
        std::cout << ">new_context" << std::endl;
        __oss << "new_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_new_context___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::new_context _val;
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_new_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<new_context" << std::endl;

        return _val._return;
    }

    CosNaming::NamingContext_ptr bind_new_context(const CosNaming::Name& n)
    {
        std::ostringstream __oss;
        std::cout << ">bind_new_context" << std::endl;
        __oss << "bind_new_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_bind_new_context___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::bind_new_context _val( n);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_bind_new_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<bind_new_context" << std::endl;

        return _val._return;
    }

    void destroy()
    {
        std::ostringstream __oss;
        std::cout << ">destroy" << std::endl;
        __oss << "destroy ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_destroy___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        __oss << std::endl;

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_destroy___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<destroy" << std::endl;

    }

    void list(::CORBA::ULong how_many, CosNaming::BindingList_out bl,
            CosNaming::BindingIterator_out bi)
    {
        std::ostringstream __oss;
        std::cout << ">list" << std::endl;
        __oss << "list ";

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_list___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContext::list _val( how_many, bl, bi);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContext_impl::CosNaming_NamingContext_list___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<list" << std::endl;

    }

};

int main(int argc, char **argv)
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    CosNaming_NamingContext_impl _impl;

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

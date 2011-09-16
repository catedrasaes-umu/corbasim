#include <tao/ORB.h>
#include "CosnamingS.h"
#include "Cosnaming_adapted.hpp"

#include <corbasim/core/archives.hpp>

#include <iostream>
#include <sstream>

/*PROTECTED REGION ID(CosNaming_NamingContextExt_impl_server::___includes) ENABLED START*/
/*PROTECTED REGION END*/

class CosNaming_NamingContextExt_impl: virtual public POA_CosNaming::NamingContextExt
{
public:

    /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::___public) ENABLED START*/
    /*PROTECTED REGION END*/

    CosNaming::NamingContextExt::StringName to_string(const CosNaming::Name& n)
    {
        std::ostringstream __oss;
        std::cout << ">to_string" << std::endl;
        __oss << "to_string ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_to_string___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContextExt::to_string _val( n);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_to_string___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<to_string" << std::endl;

        return CORBA::string_dup( _val._return);
    }

    CosNaming::Name* to_name(const char* sn)
    {
        std::ostringstream __oss;
        std::cout << ">to_name" << std::endl;
        __oss << "to_name ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_to_name___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContextExt::to_name _val( sn);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_to_name___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<to_name" << std::endl;

        return _val._return;
    }

    CosNaming::NamingContextExt::URLString to_url(const char* addr,
            const char* sn)
    {
        std::ostringstream __oss;
        std::cout << ">to_url" << std::endl;
        __oss << "to_url ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_to_url___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContextExt::to_url _val( addr, sn);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_to_url___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<to_url" << std::endl;

        return CORBA::string_dup( _val._return);
    }

    ::CORBA::Object_ptr resolve_str(const char* n)
    {
        std::ostringstream __oss;
        std::cout << ">resolve_str" << std::endl;
        __oss << "resolve_str ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_resolve_str___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        _corbasim_CosNaming::NamingContextExt::resolve_str _val( n);
        try
        {
            corbasim::core::text_oarchive toa( __oss);
            toa << _val;
        } catch (...)
        {
            std::cerr << "Serialization exception!" << std::endl;
        }

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContextExt_resolve_str___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<resolve_str" << std::endl;

        return _val._return;
    }

    void bind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
    {
        std::ostringstream __oss;
        std::cout << ">bind" << std::endl;
        __oss << "bind ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_bind___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_bind___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<bind" << std::endl;

    }

    void rebind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
    {
        std::ostringstream __oss;
        std::cout << ">rebind" << std::endl;
        __oss << "rebind ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_rebind___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_rebind___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<rebind" << std::endl;

    }

    void bind_context(const CosNaming::Name& n, CosNaming::NamingContext_ptr nc)
    {
        std::ostringstream __oss;
        std::cout << ">bind_context" << std::endl;
        __oss << "bind_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_bind_context___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_bind_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<bind_context" << std::endl;

    }

    void rebind_context(const CosNaming::Name& n,
            CosNaming::NamingContext_ptr nc)
    {
        std::ostringstream __oss;
        std::cout << ">rebind_context" << std::endl;
        __oss << "rebind_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_rebind_context___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_rebind_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<rebind_context" << std::endl;

    }

    ::CORBA::Object_ptr resolve(const CosNaming::Name& n)
    {
        std::ostringstream __oss;
        std::cout << ">resolve" << std::endl;
        __oss << "resolve ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_resolve___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_resolve___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<resolve" << std::endl;

        return _val._return;
    }

    void unbind(const CosNaming::Name& n)
    {
        std::ostringstream __oss;
        std::cout << ">unbind" << std::endl;
        __oss << "unbind ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_unbind___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_unbind___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<unbind" << std::endl;

    }

    CosNaming::NamingContext_ptr new_context()
    {
        std::ostringstream __oss;
        std::cout << ">new_context" << std::endl;
        __oss << "new_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_new_context___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_new_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<new_context" << std::endl;

        return _val._return;
    }

    CosNaming::NamingContext_ptr bind_new_context(const CosNaming::Name& n)
    {
        std::ostringstream __oss;
        std::cout << ">bind_new_context" << std::endl;
        __oss << "bind_new_context ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_bind_new_context___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_bind_new_context___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<bind_new_context" << std::endl;

        return _val._return;
    }

    void destroy()
    {
        std::ostringstream __oss;
        std::cout << ">destroy" << std::endl;
        __oss << "destroy ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_destroy___pre) ENABLED START*/
        /*PROTECTED REGION END*/

        __oss << ' ';
        __oss << std::endl;

        std::cout << ' ' << __oss.str();

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_destroy___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<destroy" << std::endl;

    }

    void list(::CORBA::ULong how_many, CosNaming::BindingList_out bl,
            CosNaming::BindingIterator_out bi)
    {
        std::ostringstream __oss;
        std::cout << ">list" << std::endl;
        __oss << "list ";

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_list___pre) ENABLED START*/
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

        /*PROTECTED REGION ID(CosNaming_NamingContextExt_impl::CosNaming_NamingContext_list___post) ENABLED START*/
        /*PROTECTED REGION END*/

        std::cout << "<list" << std::endl;

    }

};

int main(int argc, char **argv)
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv);

    CosNaming_NamingContextExt_impl _impl;

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

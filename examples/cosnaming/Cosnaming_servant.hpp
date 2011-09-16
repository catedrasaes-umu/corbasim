#ifndef COSNAMING_SERVANT_HPP
#define COSNAMING_SERVANT_HPP

#include "CosnamingS.h"
#include "Cosnaming_adapted.hpp"

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct sevant< CosNaming::NamingContext >
        {
            template< typename F >
            class _type: public virtual POA_CosNaming::NamingContext
            {
            public:

                _type(F f) :
                    __f( f)
                {
                }

                void bind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
                {
                    _corbasim_CosNaming::NamingContext::bind _val( n, obj);

                    __f( _val);

                }

                void rebind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
                {
                    _corbasim_CosNaming::NamingContext::rebind _val( n, obj);

                    __f( _val);

                }

                void bind_context(const CosNaming::Name& n,
                        CosNaming::NamingContext_ptr nc)
                {
                    _corbasim_CosNaming::NamingContext::bind_context _val( n,
                            nc);

                    __f( _val);

                }

                void rebind_context(const CosNaming::Name& n,
                        CosNaming::NamingContext_ptr nc)
                {
                    _corbasim_CosNaming::NamingContext::rebind_context _val( n,
                            nc);

                    __f( _val);

                }

                ::CORBA::Object_ptr resolve(const CosNaming::Name& n)
                {
                    _corbasim_CosNaming::NamingContext::resolve _val( n);

                    __f( _val);

                    return _val._return;
                }

                void unbind(const CosNaming::Name& n)
                {
                    _corbasim_CosNaming::NamingContext::unbind _val( n);

                    __f( _val);

                }

                CosNaming::NamingContext_ptr new_context()
                {
                    _corbasim_CosNaming::NamingContext::new_context _val;

                    __f( _val);

                    return _val._return;
                }

                CosNaming::NamingContext_ptr bind_new_context(
                        const CosNaming::Name& n)
                {
                    _corbasim_CosNaming::NamingContext::bind_new_context _val(
                            n);

                    __f( _val);

                    return _val._return;
                }

                void destroy()
                {
                    _corbasim_CosNaming::NamingContext::destroy _val;

                    __f( _val);

                }

                void list(::CORBA::ULong how_many,
                        CosNaming::BindingList_out bl,
                        CosNaming::BindingIterator_out bi)
                {
                    _corbasim_CosNaming::NamingContext::list _val( how_many,
                            bl, bi);

                    __f( _val);

                }

            protected:
                F __f;
            };
        };

    } // adapted
} // corbasim


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct sevant< CosNaming::BindingIterator >
        {
            template< typename F >
            class _type: public virtual POA_CosNaming::BindingIterator
            {
            public:

                _type(F f) :
                    __f( f)
                {
                }

                ::CORBA::Boolean next_one(CosNaming::Binding_out b)
                {
                    _corbasim_CosNaming::BindingIterator::next_one _val( b);

                    __f( _val);

                    return _val._return;
                }

                ::CORBA::Boolean next_n(::CORBA::ULong how_many,
                        CosNaming::BindingList_out bl)
                {
                    _corbasim_CosNaming::BindingIterator::next_n _val(
                            how_many, bl);

                    __f( _val);

                    return _val._return;
                }

                void destroy()
                {
                    _corbasim_CosNaming::BindingIterator::destroy _val;

                    __f( _val);

                }

            protected:
                F __f;
            };
        };

    } // adapted
} // corbasim


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct sevant< CosNaming::NamingContextExt >
        {
            template< typename F >
            class _type: public virtual POA_CosNaming::NamingContextExt
            {
            public:

                _type(F f) :
                    __f( f)
                {
                }

                CosNaming::NamingContextExt::StringName to_string(
                        const CosNaming::Name& n)
                {
                    _corbasim_CosNaming::NamingContextExt::to_string _val( n);

                    __f( _val);

                    return CORBA::string_dup( _val._return);
                }

                CosNaming::Name* to_name(const char* sn)
                {
                    _corbasim_CosNaming::NamingContextExt::to_name _val( sn);

                    __f( _val);

                    return _val._return;
                }

                CosNaming::NamingContextExt::URLString to_url(const char* addr,
                        const char* sn)
                {
                    _corbasim_CosNaming::NamingContextExt::to_url _val( addr,
                            sn);

                    __f( _val);

                    return CORBA::string_dup( _val._return);
                }

                ::CORBA::Object_ptr resolve_str(const char* n)
                {
                    _corbasim_CosNaming::NamingContextExt::resolve_str _val( n);

                    __f( _val);

                    return _val._return;
                }

                void bind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
                {
                    _corbasim_CosNaming::NamingContext::bind _val( n, obj);

                    __f( _val);

                }

                void rebind(const CosNaming::Name& n, ::CORBA::Object_ptr obj)
                {
                    _corbasim_CosNaming::NamingContext::rebind _val( n, obj);

                    __f( _val);

                }

                void bind_context(const CosNaming::Name& n,
                        CosNaming::NamingContext_ptr nc)
                {
                    _corbasim_CosNaming::NamingContext::bind_context _val( n,
                            nc);

                    __f( _val);

                }

                void rebind_context(const CosNaming::Name& n,
                        CosNaming::NamingContext_ptr nc)
                {
                    _corbasim_CosNaming::NamingContext::rebind_context _val( n,
                            nc);

                    __f( _val);

                }

                ::CORBA::Object_ptr resolve(const CosNaming::Name& n)
                {
                    _corbasim_CosNaming::NamingContext::resolve _val( n);

                    __f( _val);

                    return _val._return;
                }

                void unbind(const CosNaming::Name& n)
                {
                    _corbasim_CosNaming::NamingContext::unbind _val( n);

                    __f( _val);

                }

                CosNaming::NamingContext_ptr new_context()
                {
                    _corbasim_CosNaming::NamingContext::new_context _val;

                    __f( _val);

                    return _val._return;
                }

                CosNaming::NamingContext_ptr bind_new_context(
                        const CosNaming::Name& n)
                {
                    _corbasim_CosNaming::NamingContext::bind_new_context _val(
                            n);

                    __f( _val);

                    return _val._return;
                }

                void destroy()
                {
                    _corbasim_CosNaming::NamingContext::destroy _val;

                    __f( _val);

                }

                void list(::CORBA::ULong how_many,
                        CosNaming::BindingList_out bl,
                        CosNaming::BindingIterator_out bi)
                {
                    _corbasim_CosNaming::NamingContext::list _val( how_many,
                            bl, bi);

                    __f( _val);

                }

            protected:
                F __f;
            };
        };

    } // adapted
} // corbasim


#endif // COSNAMING_SERVANT_HPP


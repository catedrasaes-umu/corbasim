#ifndef COSNAMING_ADAPTED_HPP
#define COSNAMING_ADAPTED_HPP

#include "CosnamingC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>

// StructDef: CosNaming::NameComponent
BOOST_FUSION_ADAPT_STRUCT(
        CosNaming::NameComponent,
        ( ::TAO::String_Manager, id)
        ( ::TAO::String_Manager, kind)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, CosNaming::NameComponent& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("id", t.id);
            ar & boost::serialization::make_nvp("kind", t.kind);
        }

        template < class Archive >
        void serialize(Archive& ar, CosNaming::NameComponent_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct full_qualified_name< CosNaming::NameComponent >
        {
            static inline const char * call()
            {
                return "CosNaming::NameComponent";
            }
        };

        template< >
        struct name< CosNaming::NameComponent >
        {
            static inline const char * call()
            {
                return "NameComponent";
            }
        };

    } // adapted
} // corbasim


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, CosNaming::Name& t,
                const unsigned int version)
        {
            ::corbasim::serialization::sequence::serialize( ar, t, version);
        }

        template< class Archive >
        void serialize(Archive& ar, CosNaming::Name_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_corbaseq< CosNaming::Name > : public cs_mpl::true_
        {
            typedef CosNaming::NameComponent slice_type;
        };

    } // adapted
} // corbasim


// Enum: CosNaming::BindingType
namespace corbasim
{
    namespace adapted
    {

        template< >
        struct enumeration< CosNaming::BindingType >
        {
            static const unsigned int size = 2;

            static inline const char** values()
            {
                static const char* _data[] =
                { "nobject", "ncontext", 0 };
                return _data;
            }
        };

    } // adapted
} // corbasim


// StructDef: CosNaming::Binding
BOOST_FUSION_ADAPT_STRUCT(
        CosNaming::Binding,
        ( CosNaming::Name, binding_name)
        ( CosNaming::BindingType, binding_type)
)

namespace boost
{
    namespace serialization
    {

        template < class Archive >
        void serialize(Archive& ar, CosNaming::Binding& t, const unsigned int /* unused */)
        {
            ar & boost::serialization::make_nvp("binding_name", t.binding_name);
            ar & boost::serialization::make_nvp("binding_type", t.binding_type);
        }

        template < class Archive >
        void serialize(Archive& ar, CosNaming::Binding_var& t, const unsigned int /* unused */)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct full_qualified_name< CosNaming::Binding >
        {
            static inline const char * call()
            {
                return "CosNaming::Binding";
            }
        };

        template< >
        struct name< CosNaming::Binding >
        {
            static inline const char * call()
            {
                return "Binding";
            }
        };

    } // adapted
} // corbasim


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, CosNaming::BindingList& t,
                const unsigned int version)
        {
            ::corbasim::serialization::sequence::serialize( ar, t, version);
        }

        template< class Archive >
        void serialize(Archive& ar, CosNaming::BindingList_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_corbaseq< CosNaming::BindingList > : public cs_mpl::true_
        {
            typedef CosNaming::Binding slice_type;
        };

    } // adapted
} // corbasim


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, CosNaming::NamingContext_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_objrefvar< CosNaming::NamingContext_var > : public cs_mpl::true_
        {
            typedef CosNaming::NamingContext interface;
        };

        template< >
        struct full_qualified_name< CosNaming::NamingContext >
        {
            static inline const char * call()
            {
                return "CosNaming::NamingContext";
            }
        };

        template< >
        struct name< CosNaming::NamingContext >
        {
            static inline const char * call()
            {
                return "NamingContext";
            }
        };

        template< >
        struct typecode< CosNaming::NamingContext >
        {
            static inline CORBA::TypeCode const * call()
            {
                return CosNaming::_tc_NamingContext;
            }
        };

    } // adapted
} // corbasim

// Enum: CosNaming::NamingContext::NotFoundReason
namespace corbasim
{
    namespace adapted
    {

        template< >
        struct enumeration< CosNaming::NamingContext::NotFoundReason >
        {
            static const unsigned int size = 3;

            static inline const char** values()
            {
                static const char* _data[] =
                { "missing_node", "not_context", "not_object", 0 };
                return _data;
            }
        };

    } // adapted
} // corbasim


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, CosNaming::BindingIterator_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_objrefvar< CosNaming::BindingIterator_var > : public cs_mpl::true_
        {
            typedef CosNaming::BindingIterator interface;
        };

        template< >
        struct full_qualified_name< CosNaming::BindingIterator >
        {
            static inline const char * call()
            {
                return "CosNaming::BindingIterator";
            }
        };

        template< >
        struct name< CosNaming::BindingIterator >
        {
            static inline const char * call()
            {
                return "BindingIterator";
            }
        };

        template< >
        struct typecode< CosNaming::BindingIterator >
        {
            static inline CORBA::TypeCode const * call()
            {
                return CosNaming::_tc_BindingIterator;
            }
        };

    } // adapted
} // corbasim


namespace boost
{
    namespace serialization
    {

        template< class Archive >
        void serialize(Archive& ar, CosNaming::NamingContextExt_var& t,
                const unsigned int version)
        {
            // TODO
        }

    } // serialization
} // boost

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct is_objrefvar< CosNaming::NamingContextExt_var > : public cs_mpl::true_
        {
            typedef CosNaming::NamingContextExt interface;
        };

        template< >
        struct full_qualified_name< CosNaming::NamingContextExt >
        {
            static inline const char * call()
            {
                return "CosNaming::NamingContextExt";
            }
        };

        template< >
        struct name< CosNaming::NamingContextExt >
        {
            static inline const char * call()
            {
                return "NamingContextExt";
            }
        };

        template< >
        struct typecode< CosNaming::NamingContextExt >
        {
            static inline CORBA::TypeCode const * call()
            {
                return CosNaming::_tc_NamingContextExt;
            }
        };

    } // adapted
} // corbasim


namespace _corbasim_CosNaming
{

    struct NameComponent
    {
        typedef corbasim::adapted::member< ::CosNaming::NameComponent, 0 >
                id_corbasim_member;
        typedef corbasim::adapted::member< ::CosNaming::NameComponent, 1 >
                kind_corbasim_member;

    };

    struct Binding
    {
        typedef corbasim::adapted::member< ::CosNaming::Binding, 0 >
                binding_name_corbasim_member;
        typedef corbasim::adapted::member< ::CosNaming::Binding, 1 >
                binding_type_corbasim_member;

    };

    namespace NamingContext
    {

        struct __bind
        {
            typedef boost::mpl::vector< corbasim::Arg_IN<
                    const CosNaming::Name& >, corbasim::Arg_IN<
                    ::CORBA::Object_ptr > > _arg_list;

            typedef corbasim::adapted::member< __bind, 0 > n_corbasim_member;
            typedef corbasim::adapted::member< __bind, 1 > obj_corbasim_member;

            CosNaming::Name n;
            ::CORBA::Object_var obj;

            __bind()
            {
            }

            __bind(const CosNaming::Name& _n, ::CORBA::Object_ptr _obj):
            n(_n)
            {

                obj = ::CORBA::Object::_duplicate(_obj);
            }

            // Copy constructor
                    __bind(const __bind& o) :
                    n(o.n)
                    {

                        obj = o.obj;
                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("obj", obj);
                    }
                };

                typedef __bind bind;

                struct __rebind
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& >, corbasim::Arg_IN< ::CORBA::Object_ptr > > _arg_list;

                    typedef corbasim::adapted::member< __rebind, 0 > n_corbasim_member;
                    typedef corbasim::adapted::member< __rebind, 1 > obj_corbasim_member;

                    CosNaming::Name n;
                    ::CORBA::Object_var obj;

                    __rebind()
                    {
                    }

                    __rebind(const CosNaming::Name& _n, ::CORBA::Object_ptr _obj):
                    n(_n)
                    {

                        obj = ::CORBA::Object::_duplicate(_obj);
                    }

                    // Copy constructor
                    __rebind(const __rebind& o) :
                    n(o.n)
                    {

                        obj = o.obj;
                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("obj", obj);
                    }
                };

                typedef __rebind rebind;

                struct __bind_context
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& >, corbasim::Arg_IN< CosNaming::NamingContext_ptr > > _arg_list;

                    typedef corbasim::adapted::member< __bind_context, 0 > n_corbasim_member;
                    typedef corbasim::adapted::member< __bind_context, 1 > nc_corbasim_member;

                    CosNaming::Name n;
                    CosNaming::NamingContext_var nc;

                    __bind_context()
                    {
                    }

                    __bind_context(const CosNaming::Name& _n, CosNaming::NamingContext_ptr _nc):
                    n(_n)
                    {

                        nc = CosNaming::NamingContext::_duplicate(_nc);
                    }

                    // Copy constructor
                    __bind_context(const __bind_context& o) :
                    n(o.n)
                    {

                        nc = o.nc;
                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("nc", nc);
                    }
                };

                typedef __bind_context bind_context;

                struct __rebind_context
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& >, corbasim::Arg_IN< CosNaming::NamingContext_ptr > > _arg_list;

                    typedef corbasim::adapted::member< __rebind_context, 0 > n_corbasim_member;
                    typedef corbasim::adapted::member< __rebind_context, 1 > nc_corbasim_member;

                    CosNaming::Name n;
                    CosNaming::NamingContext_var nc;

                    __rebind_context()
                    {
                    }

                    __rebind_context(const CosNaming::Name& _n, CosNaming::NamingContext_ptr _nc):
                    n(_n)
                    {

                        nc = CosNaming::NamingContext::_duplicate(_nc);
                    }

                    // Copy constructor
                    __rebind_context(const __rebind_context& o) :
                    n(o.n)
                    {

                        nc = o.nc;
                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("nc", nc);
                    }
                };

                typedef __rebind_context rebind_context;

                struct __resolve
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& > > _arg_list;

                    typedef corbasim::adapted::member< __resolve, 0 > n_corbasim_member;

                    CosNaming::Name n;

                    ::CORBA::Object_var _return;

                    __resolve()
                    {
                    }

                    __resolve(const CosNaming::Name& _n):
                    n(_n)
                    {

                    }

                    // Copy constructor
                    __resolve(const __resolve& o) :
                    n(o.n)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __resolve resolve;

                struct __unbind
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& > > _arg_list;

                    typedef corbasim::adapted::member< __unbind, 0 > n_corbasim_member;

                    CosNaming::Name n;

                    __unbind()
                    {
                    }

                    __unbind(const CosNaming::Name& _n):
                    n(_n)
                    {

                    }

                    // Copy constructor
                    __unbind(const __unbind& o) :
                    n(o.n)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                    }
                };

                typedef __unbind unbind;

                struct __new_context
                {
                    typedef boost::mpl::vector< > _arg_list;

                    CosNaming::NamingContext_var _return;

                    __new_context()
                    {
                    }

                    // Copy constructor
                    __new_context(const __new_context& o) :

                    _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __new_context new_context;

                struct __bind_new_context
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& > > _arg_list;

                    typedef corbasim::adapted::member< __bind_new_context, 0 > n_corbasim_member;

                    CosNaming::Name n;

                    CosNaming::NamingContext_var _return;

                    __bind_new_context()
                    {
                    }

                    __bind_new_context(const CosNaming::Name& _n):
                    n(_n)
                    {

                    }

                    // Copy constructor
                    __bind_new_context(const __bind_new_context& o) :
                    n(o.n)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __bind_new_context bind_new_context;

                struct __destroy
                {
                    typedef boost::mpl::vector< > _arg_list;

                    __destroy()
                    {
                    }

                    // Copy constructor
                    __destroy(const __destroy& o)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                    }
                };

                typedef __destroy destroy;

                struct __list
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::ULong >, corbasim::Arg_OUT< CosNaming::BindingList_out >, corbasim::Arg_OUT< CosNaming::BindingIterator_out > > _arg_list;

                    typedef corbasim::adapted::member< __list, 0 > how_many_corbasim_member;
                    typedef corbasim::adapted::member< __list, 1 > bl_corbasim_member;
                    typedef corbasim::adapted::member< __list, 2 > bi_corbasim_member;

                    ::CORBA::ULong how_many;
                    CosNaming::BindingList_var bl;
                    CosNaming::BindingIterator_var bi;

                    __list()
                    {
                    }

                    __list(::CORBA::ULong _how_many, CosNaming::BindingList_out _bl, CosNaming::BindingIterator_out _bi):
                    how_many(_how_many), bl(_bl)
                    {

                        bi = CosNaming::BindingIterator::_duplicate(_bi);
                    }

                    // Copy constructor
                    __list(const __list& o) :
                    how_many(o.how_many), bl(o.bl)
                    {

                        bi = o.bi;
                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("how_many", how_many);
                        ar & boost::serialization::make_nvp("bl", bl);
                        ar & boost::serialization::make_nvp("bi", bi);
                    }
                };

                typedef __list list;

            } // NamingContext


            namespace BindingIterator
            {

                struct __next_one
                {
                    typedef boost::mpl::vector< corbasim::Arg_OUT< CosNaming::Binding_out > > _arg_list;

                    typedef corbasim::adapted::member< __next_one, 0 > b_corbasim_member;

                    CosNaming::Binding_var b;

                    ::CORBA::Boolean _return;

                    __next_one()
                    {
                    }

                    __next_one(CosNaming::Binding_out _b):
                    b(_b)
                    {

                    }

                    // Copy constructor
                    __next_one(const __next_one& o) :
                    b(o.b)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("b", b);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __next_one next_one;

                struct __next_n
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::ULong >, corbasim::Arg_OUT< CosNaming::BindingList_out > > _arg_list;

                    typedef corbasim::adapted::member< __next_n, 0 > how_many_corbasim_member;
                    typedef corbasim::adapted::member< __next_n, 1 > bl_corbasim_member;

                    ::CORBA::ULong how_many;
                    CosNaming::BindingList_var bl;

                    ::CORBA::Boolean _return;

                    __next_n()
                    {
                    }

                    __next_n(::CORBA::ULong _how_many, CosNaming::BindingList_out _bl):
                    how_many(_how_many), bl(_bl)
                    {

                    }

                    // Copy constructor
                    __next_n(const __next_n& o) :
                    how_many(o.how_many), bl(o.bl)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("how_many", how_many);
                        ar & boost::serialization::make_nvp("bl", bl);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __next_n next_n;

                struct __destroy
                {
                    typedef boost::mpl::vector< > _arg_list;

                    __destroy()
                    {
                    }

                    // Copy constructor
                    __destroy(const __destroy& o)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                    }
                };

                typedef __destroy destroy;

            } // BindingIterator


            namespace NamingContextExt
            {

                struct __to_string
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& > > _arg_list;

                    typedef corbasim::adapted::member< __to_string, 0 > n_corbasim_member;

                    CosNaming::Name n;

                    ::TAO::String_Manager _return;

                    __to_string()
                    {
                    }

                    __to_string(const CosNaming::Name& _n):
                    n(_n)
                    {

                    }

                    // Copy constructor
                    __to_string(const __to_string& o) :
                    n(o.n)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __to_string to_string;

                struct __to_name
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

                    typedef corbasim::adapted::member< __to_name, 0 > sn_corbasim_member;

                    ::TAO::String_Manager sn;

                    CosNaming::Name_var _return;

                    __to_name()
                    {
                    }

                    __to_name(const char* _sn):
                    sn(_sn)
                    {

                    }

                    // Copy constructor
                    __to_name(const __to_name& o) :
                    sn(o.sn)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("sn", sn);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __to_name to_name;

                struct __to_url
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const char* >, corbasim::Arg_IN< const char* > > _arg_list;

                    typedef corbasim::adapted::member< __to_url, 0 > addr_corbasim_member;
                    typedef corbasim::adapted::member< __to_url, 1 > sn_corbasim_member;

                    ::TAO::String_Manager addr;
                    ::TAO::String_Manager sn;

                    ::TAO::String_Manager _return;

                    __to_url()
                    {
                    }

                    __to_url(const char* _addr, const char* _sn):
                    addr(_addr), sn(_sn)
                    {

                    }

                    // Copy constructor
                    __to_url(const __to_url& o) :
                    addr(o.addr), sn(o.sn)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("addr", addr);
                        ar & boost::serialization::make_nvp("sn", sn);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __to_url to_url;

                struct __resolve_str
                {
                    typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

                    typedef corbasim::adapted::member< __resolve_str, 0 > n_corbasim_member;

                    ::TAO::String_Manager n;

                    ::CORBA::Object_var _return;

                    __resolve_str()
                    {
                    }

                    __resolve_str(const char* _n):
                    n(_n)
                    {

                    }

                    // Copy constructor
                    __resolve_str(const __resolve_str& o) :
                    n(o.n)
                    , _return(o._return)
                    {

                    }

                    template< typename Archive >
                    void serialize(Archive& ar, const unsigned int /* unused */)
                    {
                        ar & boost::serialization::make_nvp("n", n);
                        ar & boost::serialization::make_nvp("return", _return);
                    }
                };

                typedef __resolve_str resolve_str;

            } // NamingContextExt

        }  // _corbasim_CosNaming


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct interface< CosNaming::NamingContext >
        {
            typedef cs_mpl::list<
                    _corbasim_CosNaming::NamingContext::bind,
                    cs_mpl::list<
                            _corbasim_CosNaming::NamingContext::rebind,
                            cs_mpl::list<
                                    _corbasim_CosNaming::NamingContext::bind_context,
                                    cs_mpl::list<
                                            _corbasim_CosNaming::NamingContext::rebind_context,
                                            cs_mpl::list<
                                                    _corbasim_CosNaming::NamingContext::resolve,
                                                    cs_mpl::list<
                                                            _corbasim_CosNaming::NamingContext::unbind,
                                                            cs_mpl::list<
                                                                    _corbasim_CosNaming::NamingContext::new_context,
                                                                    cs_mpl::list<
                                                                            _corbasim_CosNaming::NamingContext::bind_new_context,
                                                                            cs_mpl::list<
                                                                                    _corbasim_CosNaming::NamingContext::destroy,
                                                                                    cs_mpl::list<
                                                                                            _corbasim_CosNaming::NamingContext::list > > > > > > > > > >
                    _op_list;

        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::bind
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::bind,
        ( CosNaming::Name, n)
        ( ::CORBA::Object_var, obj)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::bind >
        {
            typedef _corbasim_CosNaming::NamingContext::bind Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->bind(value.n, value.obj);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::bind >
        {
            static inline const char * call()
            {
                return "bind";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::rebind
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::rebind,
        ( CosNaming::Name, n)
        ( ::CORBA::Object_var, obj)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::rebind >
        {
            typedef _corbasim_CosNaming::NamingContext::rebind Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->rebind(value.n, value.obj);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::rebind >
        {
            static inline const char * call()
            {
                return "rebind";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::bind_context
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::bind_context,
        ( CosNaming::Name, n)
        ( CosNaming::NamingContext_var, nc)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::bind_context >
        {
            typedef _corbasim_CosNaming::NamingContext::bind_context Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->bind_context(value.n, value.nc);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::bind_context >
        {
            static inline const char * call()
            {
                return "bind_context";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::rebind_context
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::rebind_context,
        ( CosNaming::Name, n)
        ( CosNaming::NamingContext_var, nc)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::rebind_context >
        {
            typedef _corbasim_CosNaming::NamingContext::rebind_context Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->rebind_context(value.n, value.nc);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::rebind_context >
        {
            static inline const char * call()
            {
                return "rebind_context";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::resolve
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::resolve,
        ( CosNaming::Name, n)
        ( ::CORBA::Object_var, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::resolve >
        {
            typedef _corbasim_CosNaming::NamingContext::resolve Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->resolve(value.n);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::resolve >
        {
            static inline const char * call()
            {
                return "resolve";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::unbind
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::unbind,
        ( CosNaming::Name, n)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::unbind >
        {
            typedef _corbasim_CosNaming::NamingContext::unbind Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->unbind(value.n);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::unbind >
        {
            static inline const char * call()
            {
                return "unbind";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::new_context
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::new_context,
        ( CosNaming::NamingContext_var, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::new_context >
        {
            typedef _corbasim_CosNaming::NamingContext::new_context Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->new_context();
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::new_context >
        {
            static inline const char * call()
            {
                return "new_context";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::bind_new_context
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::bind_new_context,
        ( CosNaming::Name, n)
        ( CosNaming::NamingContext_var, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::bind_new_context >
        {
            typedef _corbasim_CosNaming::NamingContext::bind_new_context Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->bind_new_context(value.n);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::bind_new_context >
        {
            static inline const char * call()
            {
                return "bind_new_context";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::destroy
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::destroy,
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::destroy >
        {
            typedef _corbasim_CosNaming::NamingContext::destroy Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->destroy();
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::destroy >
        {
            static inline const char * call()
            {
                return "destroy";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContext::list
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContext::list,
        ( ::CORBA::ULong, how_many)
        ( CosNaming::BindingList_var, bl)
        ( CosNaming::BindingIterator_var, bi)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContext::list >
        {
            typedef _corbasim_CosNaming::NamingContext::list Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->list(value.how_many, value.bl, value.bi);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContext::list >
        {
            static inline const char * call()
            {
                return "list";
            }
        };

    } // adapted
} // corbasim


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct interface< CosNaming::BindingIterator >
        {
            typedef cs_mpl::list<
                    _corbasim_CosNaming::BindingIterator::next_one,
                    cs_mpl::list<
                            _corbasim_CosNaming::BindingIterator::next_n,
                            cs_mpl::list<
                                    _corbasim_CosNaming::BindingIterator::destroy > > >
                    _op_list;

        };

    } // adapted
} // corbasim

// OperationDef: CosNaming::BindingIterator::next_one
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::BindingIterator::next_one,
        ( CosNaming::Binding_var, b)
        ( ::CORBA::Boolean, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::BindingIterator::next_one >
        {
            typedef _corbasim_CosNaming::BindingIterator::next_one Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->next_one(value.b);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::BindingIterator::next_one >
        {
            static inline const char * call()
            {
                return "next_one";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::BindingIterator::next_n
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::BindingIterator::next_n,
        ( ::CORBA::ULong, how_many)
        ( CosNaming::BindingList_var, bl)
        ( ::CORBA::Boolean, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::BindingIterator::next_n >
        {
            typedef _corbasim_CosNaming::BindingIterator::next_n Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->next_n(value.how_many, value.bl);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::BindingIterator::next_n >
        {
            static inline const char * call()
            {
                return "next_n";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::BindingIterator::destroy
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::BindingIterator::destroy,
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::BindingIterator::destroy >
        {
            typedef _corbasim_CosNaming::BindingIterator::destroy Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                ref->destroy();
            }
        };

        template< >
        struct name< _corbasim_CosNaming::BindingIterator::destroy >
        {
            static inline const char * call()
            {
                return "destroy";
            }
        };

    } // adapted
} // corbasim


namespace corbasim
{
    namespace adapted
    {

        template< >
        struct interface< CosNaming::NamingContextExt >
        {
            typedef cs_mpl::list<
                    _corbasim_CosNaming::NamingContextExt::to_string,
                    cs_mpl::list<
                            _corbasim_CosNaming::NamingContextExt::to_name,
                            cs_mpl::list<
                                    _corbasim_CosNaming::NamingContextExt::to_url,
                                    cs_mpl::list<
                                            _corbasim_CosNaming::NamingContextExt::resolve_str,
                                            cs_mpl::list<
                                                    _corbasim_CosNaming::NamingContext::bind,
                                                    cs_mpl::list<
                                                            _corbasim_CosNaming::NamingContext::rebind,
                                                            cs_mpl::list<
                                                                    _corbasim_CosNaming::NamingContext::bind_context,
                                                                    cs_mpl::list<
                                                                            _corbasim_CosNaming::NamingContext::rebind_context,
                                                                            cs_mpl::list<
                                                                                    _corbasim_CosNaming::NamingContext::resolve,
                                                                                    cs_mpl::list<
                                                                                            _corbasim_CosNaming::NamingContext::unbind,
                                                                                            cs_mpl::list<
                                                                                                    _corbasim_CosNaming::NamingContext::new_context,
                                                                                                    cs_mpl::list<
                                                                                                            _corbasim_CosNaming::NamingContext::bind_new_context,
                                                                                                            cs_mpl::list<
                                                                                                                    _corbasim_CosNaming::NamingContext::destroy,
                                                                                                                    cs_mpl::list<
                                                                                                                            _corbasim_CosNaming::NamingContext::list > > > > > > > > > > > > > >
                    _op_list;

        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContextExt::to_string
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContextExt::to_string,
        ( CosNaming::Name, n)
        ( ::TAO::String_Manager, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContextExt::to_string >
        {
            typedef _corbasim_CosNaming::NamingContextExt::to_string Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->to_string(value.n);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContextExt::to_string >
        {
            static inline const char * call()
            {
                return "to_string";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContextExt::to_name
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContextExt::to_name,
        ( ::TAO::String_Manager, sn)
        ( CosNaming::Name_var, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContextExt::to_name >
        {
            typedef _corbasim_CosNaming::NamingContextExt::to_name Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->to_name(value.sn);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContextExt::to_name >
        {
            static inline const char * call()
            {
                return "to_name";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContextExt::to_url
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContextExt::to_url,
        ( ::TAO::String_Manager, addr)
        ( ::TAO::String_Manager, sn)
        ( ::TAO::String_Manager, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContextExt::to_url >
        {
            typedef _corbasim_CosNaming::NamingContextExt::to_url Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->to_url(value.addr, value.sn);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContextExt::to_url >
        {
            static inline const char * call()
            {
                return "to_url";
            }
        };

    } // adapted
} // corbasim


// OperationDef: CosNaming::NamingContextExt::resolve_str
BOOST_FUSION_ADAPT_STRUCT(
        _corbasim_CosNaming::NamingContextExt::resolve_str,
        ( ::TAO::String_Manager, n)
        ( ::CORBA::Object_var, _return)
)

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct call< _corbasim_CosNaming::NamingContextExt::resolve_str >
        {
            typedef _corbasim_CosNaming::NamingContextExt::resolve_str Value;

            template < typename Interface >
            static inline void invoke(Interface * ref, Value& value)
            {
                value._return = ref->resolve_str(value.n);
            }
        };

        template< >
        struct name< _corbasim_CosNaming::NamingContextExt::resolve_str >
        {
            static inline const char * call()
            {
                return "resolve_str";
            }
        };

    } // adapted
} // corbasim


#endif // COSNAMING_ADAPTED_HPP


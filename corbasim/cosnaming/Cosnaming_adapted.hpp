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

	



        
namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, CosNaming::Name& t, const unsigned int version)
{	
	::corbasim::serialization::sequence::serialize(ar, t, version);
}
	
template < class Archive >
void serialize(Archive& ar, CosNaming::Name_var& t, const unsigned int version)
{	
	// TODO
}
	
} // serialization
} // boost

namespace corbasim
{
namespace adapted
{

template < >
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
		static const char* _data[] = {"nobject", "ncontext", 0};
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

	



        
namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, CosNaming::BindingList& t, const unsigned int version)
{	
	::corbasim::serialization::sequence::serialize(ar, t, version);
}
	
template < class Archive >
void serialize(Archive& ar, CosNaming::BindingList_var& t, const unsigned int version)
{	
	// TODO
}
	
} // serialization
} // boost

namespace corbasim
{
namespace adapted
{

template < >
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

template < class Archive >
void serialize(Archive& ar, CosNaming::NamingContext_var& t, const unsigned int version)
{	
	// TODO
}

} // serialization
} // boost

namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< CosNaming::NamingContext_var > : public cs_mpl::true_
{
	typedef CosNaming::NamingContext interface;
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
		static const char* _data[] = {"missing_node", "not_context", "not_object", 0};
		return _data;
	}
};

} // adapted
} // corbasim


































namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, CosNaming::BindingIterator_var& t, const unsigned int version)
{	
	// TODO
}

} // serialization
} // boost

namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< CosNaming::BindingIterator_var > : public cs_mpl::true_
{
	typedef CosNaming::BindingIterator interface;
};

} // adapted
} // corbasim








namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, CosNaming::NamingContextExt_var& t, const unsigned int version)
{	
	// TODO
}

} // serialization
} // boost

namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< CosNaming::NamingContextExt_var > : public cs_mpl::true_
{
	typedef CosNaming::NamingContextExt interface;
};

} // adapted
} // corbasim



















namespace _corbasim_CosNaming 
{


struct NameComponent
{
	typedef corbasim::adapted::member< ::CosNaming::NameComponent, 0 > id_corbasim_member;
	typedef corbasim::adapted::member< ::CosNaming::NameComponent, 1 > kind_corbasim_member;
	
};






struct Binding
{
	typedef corbasim::adapted::member< ::CosNaming::Binding, 0 > binding_name_corbasim_member;
	typedef corbasim::adapted::member< ::CosNaming::Binding, 1 > binding_type_corbasim_member;
	
};






namespace NamingContext 
{












struct __bind
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const CosNaming::Name& >, corbasim::Arg_IN< ::CORBA::Object_ptr > > _arg_list;

	typedef corbasim::adapted::member< __bind, 0 > n_corbasim_member;
	typedef corbasim::adapted::member< __bind, 1 > obj_corbasim_member;

	CosNaming::Name n;
	::CORBA::Object_var obj;
	
	
	__bind();
	
	__bind(const CosNaming::Name& _n, ::CORBA::Object_ptr _obj);
	
	// Copy constructor
	__bind(const __bind& o);

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
	
	
	__rebind();
	
	__rebind(const CosNaming::Name& _n, ::CORBA::Object_ptr _obj);
	
	// Copy constructor
	__rebind(const __rebind& o);

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
	
	
	__bind_context();
	
	__bind_context(const CosNaming::Name& _n, CosNaming::NamingContext_ptr _nc);
	
	// Copy constructor
	__bind_context(const __bind_context& o);

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
	
	
	__rebind_context();
	
	__rebind_context(const CosNaming::Name& _n, CosNaming::NamingContext_ptr _nc);
	
	// Copy constructor
	__rebind_context(const __rebind_context& o);

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
	
	__resolve();
	
	__resolve(const CosNaming::Name& _n);
	
	// Copy constructor
	__resolve(const __resolve& o);

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
	
	
	__unbind();
	
	__unbind(const CosNaming::Name& _n);
	
	// Copy constructor
	__unbind(const __unbind& o);

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
		ar & boost::serialization::make_nvp("n", n);
	}
};

typedef __unbind unbind;


struct __new_context
{
	typedef boost::mpl::vector<  > _arg_list;


	
	CosNaming::NamingContext_var _return;
	
	__new_context();
	
	
	// Copy constructor
	__new_context(const __new_context& o);

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
	
	__bind_new_context();
	
	__bind_new_context(const CosNaming::Name& _n);
	
	// Copy constructor
	__bind_new_context(const __bind_new_context& o);

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
	typedef boost::mpl::vector<  > _arg_list;


	
	
	__destroy();
	
	
	// Copy constructor
	__destroy(const __destroy& o);

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
	
	
	__list();
	
	__list(::CORBA::ULong _how_many, CosNaming::BindingList_out _bl, CosNaming::BindingIterator_out _bi);
	
	// Copy constructor
	__list(const __list& o);

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
	
	__next_one();
	
	__next_one(CosNaming::Binding_out _b);
	
	// Copy constructor
	__next_one(const __next_one& o);

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
	
	__next_n();
	
	__next_n(::CORBA::ULong _how_many, CosNaming::BindingList_out _bl);
	
	// Copy constructor
	__next_n(const __next_n& o);

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
	typedef boost::mpl::vector<  > _arg_list;


	
	
	__destroy();
	
	
	// Copy constructor
	__destroy(const __destroy& o);

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
	
	__to_string();
	
	__to_string(const CosNaming::Name& _n);
	
	// Copy constructor
	__to_string(const __to_string& o);

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
	
	__to_name();
	
	__to_name(const char* _sn);
	
	// Copy constructor
	__to_name(const __to_name& o);

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
	
	__to_url();
	
	__to_url(const char* _addr, const char* _sn);
	
	// Copy constructor
	__to_url(const __to_url& o);

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
	
	__resolve_str();
	
	__resolve_str(const char* _n);
	
	// Copy constructor
	__resolve_str(const __resolve_str& o);

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
		ar & boost::serialization::make_nvp("n", n);
		ar & boost::serialization::make_nvp("return", _return);
	}
};

typedef __resolve_str resolve_str;

} // NamingContextExt

} // _corbasim_CosNaming

















namespace corbasim
{
namespace adapted
{

template < >
struct interface < CosNaming::NamingContext >
{
	typedef cs_mpl::list< _corbasim_CosNaming::NamingContext::bind, cs_mpl::list< _corbasim_CosNaming::NamingContext::rebind, cs_mpl::list< _corbasim_CosNaming::NamingContext::bind_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::rebind_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::resolve, cs_mpl::list< _corbasim_CosNaming::NamingContext::unbind, cs_mpl::list< _corbasim_CosNaming::NamingContext::new_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::bind_new_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::destroy, cs_mpl::list< _corbasim_CosNaming::NamingContext::list  >  >  >  >  >  >  >  >  >  >   _op_list;
	
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

} // adapted
} // corbasim




namespace corbasim
{
namespace adapted
{

template < >
struct interface < CosNaming::BindingIterator >
{
	typedef cs_mpl::list< _corbasim_CosNaming::BindingIterator::next_one, cs_mpl::list< _corbasim_CosNaming::BindingIterator::next_n, cs_mpl::list< _corbasim_CosNaming::BindingIterator::destroy  >  >  >   _op_list;
	
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

} // adapted
} // corbasim




namespace corbasim
{
namespace adapted
{

template < >
struct interface < CosNaming::NamingContextExt >
{
	typedef cs_mpl::list< _corbasim_CosNaming::NamingContextExt::to_string, cs_mpl::list< _corbasim_CosNaming::NamingContextExt::to_name, cs_mpl::list< _corbasim_CosNaming::NamingContextExt::to_url, cs_mpl::list< _corbasim_CosNaming::NamingContextExt::resolve_str, cs_mpl::list< _corbasim_CosNaming::NamingContext::bind, cs_mpl::list< _corbasim_CosNaming::NamingContext::rebind, cs_mpl::list< _corbasim_CosNaming::NamingContext::bind_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::rebind_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::resolve, cs_mpl::list< _corbasim_CosNaming::NamingContext::unbind, cs_mpl::list< _corbasim_CosNaming::NamingContext::new_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::bind_new_context, cs_mpl::list< _corbasim_CosNaming::NamingContext::destroy, cs_mpl::list< _corbasim_CosNaming::NamingContext::list  >  >  >  >  >  >  >  >  >  >  >  >  >  >   _op_list;
	
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

} // adapted
} // corbasim




#endif // COSNAMING_ADAPTED_HPP



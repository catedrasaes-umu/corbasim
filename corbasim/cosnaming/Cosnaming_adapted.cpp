#include "Cosnaming_adapted.hpp"

namespace corbasim
{
namespace adapted
{


template< >
const char * full_qualified_name< CosNaming::NameComponent >::call()
{
	return "CosNaming::NameComponent";
}

template< >
const char * name< CosNaming::NameComponent >::call()
{
	return "NameComponent";
}







template< >
const char * full_qualified_name< CosNaming::Binding >::call()
{
	return "CosNaming::Binding";
}

template< >
const char * name< CosNaming::Binding >::call()
{
	return "Binding";
}







template< >
const char * full_qualified_name< CosNaming::NamingContext >::call()
{
	return "CosNaming::NamingContext";
}

template< >
const char * name< CosNaming::NamingContext >::call()
{
	return "NamingContext";
}

template< >
CORBA::TypeCode const *  typecode< CosNaming::NamingContext >::call()
{
	return CosNaming::_tc_NamingContext;
}













template< >
const char * name< _corbasim_CosNaming::NamingContext::bind >::call()
{
	return "bind";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::rebind >::call()
{
	return "rebind";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::bind_context >::call()
{
	return "bind_context";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::rebind_context >::call()
{
	return "rebind_context";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::resolve >::call()
{
	return "resolve";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::unbind >::call()
{
	return "unbind";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::new_context >::call()
{
	return "new_context";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::bind_new_context >::call()
{
	return "bind_new_context";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::destroy >::call()
{
	return "destroy";
}


template< >
const char * name< _corbasim_CosNaming::NamingContext::list >::call()
{
	return "list";
}



template< >
const char * full_qualified_name< CosNaming::BindingIterator >::call()
{
	return "CosNaming::BindingIterator";
}

template< >
const char * name< CosNaming::BindingIterator >::call()
{
	return "BindingIterator";
}

template< >
CORBA::TypeCode const *  typecode< CosNaming::BindingIterator >::call()
{
	return CosNaming::_tc_BindingIterator;
}

template< >
const char * name< _corbasim_CosNaming::BindingIterator::next_one >::call()
{
	return "next_one";
}


template< >
const char * name< _corbasim_CosNaming::BindingIterator::next_n >::call()
{
	return "next_n";
}


template< >
const char * name< _corbasim_CosNaming::BindingIterator::destroy >::call()
{
	return "destroy";
}



template< >
const char * full_qualified_name< CosNaming::NamingContextExt >::call()
{
	return "CosNaming::NamingContextExt";
}

template< >
const char * name< CosNaming::NamingContextExt >::call()
{
	return "NamingContextExt";
}

template< >
CORBA::TypeCode const *  typecode< CosNaming::NamingContextExt >::call()
{
	return CosNaming::_tc_NamingContextExt;
}







template< >
const char * name< _corbasim_CosNaming::NamingContextExt::to_string >::call()
{
	return "to_string";
}


template< >
const char * name< _corbasim_CosNaming::NamingContextExt::to_name >::call()
{
	return "to_name";
}




template< >
const char * name< _corbasim_CosNaming::NamingContextExt::to_url >::call()
{
	return "to_url";
}


template< >
const char * name< _corbasim_CosNaming::NamingContextExt::resolve_str >::call()
{
	return "resolve_str";
}



} // namespace adapted
} // namespace corbasim

namespace _corbasim_CosNaming 
{














namespace NamingContext 
{













__bind::__bind()
{
}

__bind::__bind(const CosNaming::Name& _n, ::CORBA::Object_ptr _obj):
	n(_n)
{
	
	obj = ::CORBA::Object::_duplicate(_obj);
}

// Copy constructor
__bind::__bind(const __bind& o) :
	n(o.n)
{
	
	obj = o.obj;
}




__rebind::__rebind()
{
}

__rebind::__rebind(const CosNaming::Name& _n, ::CORBA::Object_ptr _obj):
	n(_n)
{
	
	obj = ::CORBA::Object::_duplicate(_obj);
}

// Copy constructor
__rebind::__rebind(const __rebind& o) :
	n(o.n)
{
	
	obj = o.obj;
}




__bind_context::__bind_context()
{
}

__bind_context::__bind_context(const CosNaming::Name& _n, CosNaming::NamingContext_ptr _nc):
	n(_n)
{
	
	nc = CosNaming::NamingContext::_duplicate(_nc);
}

// Copy constructor
__bind_context::__bind_context(const __bind_context& o) :
	n(o.n)
{
	
	nc = o.nc;
}




__rebind_context::__rebind_context()
{
}

__rebind_context::__rebind_context(const CosNaming::Name& _n, CosNaming::NamingContext_ptr _nc):
	n(_n)
{
	
	nc = CosNaming::NamingContext::_duplicate(_nc);
}

// Copy constructor
__rebind_context::__rebind_context(const __rebind_context& o) :
	n(o.n)
{
	
	nc = o.nc;
}




__resolve::__resolve()
{
}

__resolve::__resolve(const CosNaming::Name& _n):
	n(_n)
{
	
}

// Copy constructor
__resolve::__resolve(const __resolve& o) :
	n(o.n)
, _return(o._return){
	
}




__unbind::__unbind()
{
}

__unbind::__unbind(const CosNaming::Name& _n):
	n(_n)
{
	
}

// Copy constructor
__unbind::__unbind(const __unbind& o) :
	n(o.n)
{
	
}




__new_context::__new_context()
{
}


// Copy constructor
__new_context::__new_context(const __new_context& o) :
	
_return(o._return){
	
}




__bind_new_context::__bind_new_context()
{
}

__bind_new_context::__bind_new_context(const CosNaming::Name& _n):
	n(_n)
{
	
}

// Copy constructor
__bind_new_context::__bind_new_context(const __bind_new_context& o) :
	n(o.n)
, _return(o._return){
	
}




__destroy::__destroy()
{
}


// Copy constructor
__destroy::__destroy(const __destroy& o)
{
	
}




__list::__list()
{
}

__list::__list(::CORBA::ULong _how_many, CosNaming::BindingList_out _bl, CosNaming::BindingIterator_out _bi):
	how_many(_how_many), bl(_bl)
{
	
	bi = CosNaming::BindingIterator::_duplicate(_bi);
}

// Copy constructor
__list::__list(const __list& o) :
	how_many(o.how_many), bl(o.bl)
{
	
	bi = o.bi;
}


} // NamingContext


namespace BindingIterator 
{

__next_one::__next_one()
{
}

__next_one::__next_one(CosNaming::Binding_out _b):
	b(_b)
{
	
}

// Copy constructor
__next_one::__next_one(const __next_one& o) :
	b(o.b)
, _return(o._return){
	
}




__next_n::__next_n()
{
}

__next_n::__next_n(::CORBA::ULong _how_many, CosNaming::BindingList_out _bl):
	how_many(_how_many), bl(_bl)
{
	
}

// Copy constructor
__next_n::__next_n(const __next_n& o) :
	how_many(o.how_many), bl(o.bl)
, _return(o._return){
	
}




__destroy::__destroy()
{
}


// Copy constructor
__destroy::__destroy(const __destroy& o)
{
	
}


} // BindingIterator


namespace NamingContextExt 
{







__to_string::__to_string()
{
}

__to_string::__to_string(const CosNaming::Name& _n):
	n(_n)
{
	
}

// Copy constructor
__to_string::__to_string(const __to_string& o) :
	n(o.n)
, _return(o._return){
	
}




__to_name::__to_name()
{
}

__to_name::__to_name(const char* _sn):
	sn(_sn)
{
	
}

// Copy constructor
__to_name::__to_name(const __to_name& o) :
	sn(o.sn)
, _return(o._return){
	
}






__to_url::__to_url()
{
}

__to_url::__to_url(const char* _addr, const char* _sn):
	addr(_addr), sn(_sn)
{
	
}

// Copy constructor
__to_url::__to_url(const __to_url& o) :
	addr(o.addr), sn(o.sn)
, _return(o._return){
	
}




__resolve_str::__resolve_str()
{
}

__resolve_str::__resolve_str(const char* _n):
	n(_n)
{
	
}

// Copy constructor
__resolve_str::__resolve_str(const __resolve_str& o) :
	n(o.n)
, _return(o._return){
	
}


} // NamingContextExt

} // _corbasim_CosNaming



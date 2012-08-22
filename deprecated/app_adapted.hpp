#ifndef APP_ADAPTED_HPP
#define APP_ADAPTED_HPP

#include "appC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>



// StructDef: corbasim::app::ObjrefConfig
BOOST_FUSION_ADAPT_STRUCT(
	corbasim::app::ObjrefConfig,
	( ::corbasim::orbimpl::String_Manager, id)
	( ::corbasim::orbimpl::String_Manager, fqn)
	( ::corbasim::orbimpl::String_Manager, entry)
	( ::CORBA::Object_var, ref)
     )

	



        
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< corbasim::app::ObjrefConfigSeq > : public cs_mpl::true_
{
	typedef corbasim::app::ObjrefConfig slice_type;
};

} // adapted
} // corbasim


// StructDef: corbasim::app::ServantConfig
BOOST_FUSION_ADAPT_STRUCT(
	corbasim::app::ServantConfig,
	( ::corbasim::orbimpl::String_Manager, id)
	( ::corbasim::orbimpl::String_Manager, fqn)
	( ::corbasim::orbimpl::String_Manager, entry)
	( ::corbasim::orbimpl::String_Manager, behaviour)
     )

	



        
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< corbasim::app::ServantConfigSeq > : public cs_mpl::true_
{
	typedef corbasim::app::ServantConfig slice_type;
};

} // adapted
} // corbasim


// StructDef: corbasim::app::Configuration
BOOST_FUSION_ADAPT_STRUCT(
	corbasim::app::Configuration,
	( corbasim::app::ServantConfigSeq, servants)
	( corbasim::app::ObjrefConfigSeq, objects)
     )

	





namespace _corbasim_corbasim 
{
namespace app 
{
struct ObjrefConfig
{
	typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 0 > id_corbasim_member;
	typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 1 > fqn_corbasim_member;
	typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 2 > entry_corbasim_member;
	typedef corbasim::adapted::member< ::corbasim::app::ObjrefConfig, 3 > ref_corbasim_member;
	
};




struct ServantConfig
{
	typedef corbasim::adapted::member< ::corbasim::app::ServantConfig, 0 > id_corbasim_member;
	typedef corbasim::adapted::member< ::corbasim::app::ServantConfig, 1 > fqn_corbasim_member;
	typedef corbasim::adapted::member< ::corbasim::app::ServantConfig, 2 > entry_corbasim_member;
	typedef corbasim::adapted::member< ::corbasim::app::ServantConfig, 3 > behaviour_corbasim_member;
	
};




struct Configuration
{
	typedef corbasim::adapted::member< ::corbasim::app::Configuration, 0 > servants_corbasim_member;
	typedef corbasim::adapted::member< ::corbasim::app::Configuration, 1 > objects_corbasim_member;
	
};

} // app

} // _corbasim_corbasim














#endif // APP_ADAPTED_HPP



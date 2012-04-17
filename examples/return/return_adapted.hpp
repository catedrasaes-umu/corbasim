#ifndef RETURN_ADAPTED_HPP
#define RETURN_ADAPTED_HPP

#include "returnC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>



// StructDef: AAAAAAAAA::ESS
BOOST_FUSION_ADAPT_STRUCT(
	AAAAAAAAA::ESS,
	( ::TAO::String_Manager, a)
     )

namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, AAAAAAAAA::ESS& t, const unsigned int /* unused */)
{	
	ar & boost::serialization::make_nvp("a", t.a);
}


template < class Archive >
void serialize(Archive& ar, AAAAAAAAA::ESS_var& t, const unsigned int /* unused */)
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
void serialize(Archive& ar, AAAAAAAAA::EEESeq& t, const unsigned int version)
{	
	::corbasim::serialization::sequence::serialize(ar, t, version);
}
	
template < class Archive >
void serialize(Archive& ar, AAAAAAAAA::EEESeq_var& t, const unsigned int version)
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
struct is_corbaseq< AAAAAAAAA::EEESeq > : public cs_mpl::true_
{
	typedef AAAAAAAAA::ESS slice_type;
};

} // adapted
} // corbasim




namespace boost
{
namespace serialization
{

template < class Archive >
void serialize(Archive& ar, AAAAAAAAA::IIIIIIIIII_var& t, const unsigned int version)
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
struct is_objrefvar< AAAAAAAAA::IIIIIIIIII_var > : public cs_mpl::true_
{
	typedef AAAAAAAAA::IIIIIIIIII interface;
};

} // adapted
} // corbasim







namespace _corbasim_AAAAAAAAA 
{
struct ESS
{
	typedef corbasim::adapted::member< ::AAAAAAAAA::ESS, 0 > a_corbasim_member;
	
};






namespace IIIIIIIIII 
{
struct __op1
{
	typedef boost::mpl::vector<  > _arg_list;


	
	AAAAAAAAA::EEESeq_var _return;
	
	__op1();
	
	
	// Copy constructor
	__op1(const __op1& o);

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
		ar & boost::serialization::make_nvp("return", _return);
	}
};

typedef __op1 op1;


struct __op2
{
	typedef boost::mpl::vector<  > _arg_list;


	
	AAAAAAAAA::ESS_var _return;
	
	__op2();
	
	
	// Copy constructor
	__op2(const __op2& o);

    template< typename Archive >
    void serialize(Archive& ar, const unsigned int /* unused */)
    {
		ar & boost::serialization::make_nvp("return", _return);
	}
};

typedef __op2 op2;

} // IIIIIIIIII

} // _corbasim_AAAAAAAAA









namespace corbasim
{
namespace adapted
{

template < >
struct interface < AAAAAAAAA::IIIIIIIIII >
{
	typedef cs_mpl::list< _corbasim_AAAAAAAAA::IIIIIIIIII::op1, cs_mpl::list< _corbasim_AAAAAAAAA::IIIIIIIIII::op2  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: AAAAAAAAA::IIIIIIIIII::op1
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_AAAAAAAAA::IIIIIIIIII::op1,
	( AAAAAAAAA::EEESeq_var, _return)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_AAAAAAAAA::IIIIIIIIII::op1 >
{
	typedef _corbasim_AAAAAAAAA::IIIIIIIIII::op1 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
value._return = ref->op1();
    }
};

} // adapted
} // corbasim


// OperationDef: AAAAAAAAA::IIIIIIIIII::op2
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_AAAAAAAAA::IIIIIIIIII::op2,
	( AAAAAAAAA::ESS_var, _return)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_AAAAAAAAA::IIIIIIIIII::op2 >
{
	typedef _corbasim_AAAAAAAAA::IIIIIIIIII::op2 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
value._return = ref->op2();
    }
};

} // adapted
} // corbasim




#endif // RETURN_ADAPTED_HPP



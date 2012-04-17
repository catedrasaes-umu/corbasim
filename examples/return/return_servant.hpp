#ifndef RETURN_SERVANT_HPP
#define RETURN_SERVANT_HPP

#include "returnS.h"
#include "return_adapted.hpp"







namespace corbasim
{
namespace adapted
{

template< >
struct servant< AAAAAAAAA::IIIIIIIIII >
{
	template < typename F >
	class _type : public virtual POA_AAAAAAAAA::IIIIIIIIII
	{
	public:
	
		_type(F f) : 
			__f(f)
		{
		}
	
		
		AAAAAAAAA::EEESeq* op1()
		{
			_corbasim_AAAAAAAAA::IIIIIIIIII::op1 _val;
	
			__f(_val);		
			
			return _val._return._retn();
		}
		
		AAAAAAAAA::ESS* op2()
		{
			_corbasim_AAAAAAAAA::IIIIIIIIII::op2 _val;
	
			__f(_val);		
			
			return _val._return._retn();
		}
		
		
	protected:
		F __f;
	};
};

} // adapted
} // corbasim



#endif // RETURN_SERVANT_HPP



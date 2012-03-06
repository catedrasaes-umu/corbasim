#ifndef UNION_SERVANT_HPP
#define UNION_SERVANT_HPP

#include "unionS.h"
#include "union_adapted.hpp"





namespace corbasim
{
namespace adapted
{

template< >
struct servant< MyModule::MyInterface >
{
	template < typename F >
	class _type : public virtual POA_MyModule::MyInterface
	{
	public:
	
		_type(F f) : 
			__f(f)
		{
		}
	
		
		void operation(const MyModule::MyUnion& uni)
		{
			_corbasim_MyModule::MyInterface::operation _val(uni);
	
			__f(_val);		
			
		}
		
		
	protected:
		F __f;
	};
};

} // adapted
} // corbasim



#endif // UNION_SERVANT_HPP



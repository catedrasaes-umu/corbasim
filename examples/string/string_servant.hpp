#ifndef STRING_SERVANT_HPP
#define STRING_SERVANT_HPP

#include "stringS.h"
#include "string_adapted.hpp"











namespace corbasim
{
namespace adapted
{

template< >
struct servant< StringTest::InterfaceString >
{
	template < typename F >
	class _type : public virtual POA_StringTest::InterfaceString
	{
	public:
	
		_type(F f) : 
			__f(f)
		{
		}
	
		
		void operation1(const char* s)
		{
			_corbasim_StringTest::InterfaceString::operation1 _val(s);
	
			__f(_val);		
			
		}
		
		void operation2(const char* n)
		{
			_corbasim_StringTest::InterfaceString::operation2 _val(n);
	
			__f(_val);		
			
		}
		
		void operation3(const StringTest::NameSeq& n)
		{
			_corbasim_StringTest::InterfaceString::operation3 _val(n);
	
			__f(_val);		
			
		}
		
		void operation4(const StringTest::StructWithStrings& n)
		{
			_corbasim_StringTest::InterfaceString::operation4 _val(n);
	
			__f(_val);		
			
		}
		
		void operation5(const char* n)
		{
			_corbasim_StringTest::InterfaceString::operation5 _val(n);
	
			__f(_val);		
			
		}
		
		void operation6(const StringTest::NameIDSeq& n)
		{
			_corbasim_StringTest::InterfaceString::operation6 _val(n);
	
			__f(_val);		
			
		}
		
		
	protected:
		F __f;
	};
};

} // adapted
} // corbasim



#endif // STRING_SERVANT_HPP



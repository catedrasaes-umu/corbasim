#ifndef MAPPING_ADAPTED_HPP
#define MAPPING_ADAPTED_HPP

#include "mappingC.h"
#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>



        
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< HelloApp::Names > : public cs_mpl::true_
{
	typedef ::corbasim::orbimpl::String_Manager slice_type;
};

} // adapted
} // corbasim


namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< HelloApp::Hello_var > : public cs_mpl::true_
{
	typedef HelloApp::Hello interface;
};

} // adapted
} // corbasim









namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< Test::Huge_var > : public cs_mpl::true_
{
	typedef Test::Huge interface;
};

} // adapted
} // corbasim

















































































































































































































































































































































































































// StructDef: AAAAAAAAA::ESS
BOOST_FUSION_ADAPT_STRUCT(
	AAAAAAAAA::ESS,
	( ::corbasim::orbimpl::String_Manager, a)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < AAAAAAAAA::ESS, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            AAAAAAAAA::ESS s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.a, parent, 0);
        }

        template< typename T >
        static inline void set(AAAAAAAAA::ESS& s_, const T& t_)
        {
            s_.a = t_;
        }

        template< typename T >
        static inline void get(const AAAAAAAAA::ESS& s_, T& t_)
        {
            t_ = s_.a;
        }
    };
} // adapted
} // corbasim


        
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







// UnionDef: SimpleExample::MyUnion
BOOST_FUSION_ADAPT_ADT(
	SimpleExample::MyUnion,
	( ::CORBA::Long, ::CORBA::Long, obj._d(), obj._d(val)) // Discriminator
	( ::CORBA::Long, ::CORBA::Long, obj.aa(), obj.aa(val))
	( ::CORBA::Long, ::CORBA::Long, obj.bb(), obj.bb(val))
     )

namespace boost
{
namespace fusion
{
namespace extension
{

template< >
struct struct_member_name< SimpleExample::MyUnion, 0>
{
	static inline const char * call()
	{
		return "_d";
	}
};

template< >
struct struct_member_name< SimpleExample::MyUnion, 1>
{
	static inline const char * call()
	{
		return "aa";
	}
};
template< >
struct struct_member_name< SimpleExample::MyUnion, 2>
{
	static inline const char * call()
	{
		return "bb";
	}
};

} // extension
} // fusion
} // boost

namespace corbasim
{
namespace adapted
{

template< >
struct is_union< SimpleExample::MyUnion > : public cs_mpl::true_
{
	typedef ::CORBA::Long discriminator_t;
	
	static const size_t size = 2;
	
	static inline discriminator_t* discriminators()
	{
		static discriminator_t _disc[] = { 
					100
			, 									101
			};		
		return _disc;
	}
	
	static inline unsigned int* member()
	{
		static unsigned int _members[] = { 
					1
			, 									2
			};		
		return _members;
	}
};

} // adapted
} // corbasim



// StructDef: SimpleExample::St
BOOST_FUSION_ADAPT_STRUCT(
	SimpleExample::St,
	( SimpleExample::St::_l_seq, l)
	( SimpleExample::St::_ss_seq, ss)
	( ::CORBA::Long, b)
	( SimpleExample::MyUnion, uniii)
     )

		
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< SimpleExample::St::_l_seq > : public cs_mpl::true_
{
	typedef ::CORBA::Long slice_type;
};

} // adapted
} // corbasim
		
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< SimpleExample::St::_ss_seq > : public cs_mpl::true_
{
	typedef ::corbasim::orbimpl::String_Manager slice_type;
};

} // adapted
} // corbasim
	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < SimpleExample::St, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::St s_;
            SimpleExample::St::_l_seq t_;
            return ::corbasim::core::create_reflective(t_, s_.l, parent, 0);
        }

        template< typename T >
        static inline void set(SimpleExample::St& s_, const T& t_)
        {
            s_.l = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::St& s_, T& t_)
        {
            t_ = s_.l;
        }
    };
    template< > struct member_helper < SimpleExample::St, 1 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::St s_;
            SimpleExample::St::_ss_seq t_;
            return ::corbasim::core::create_reflective(t_, s_.ss, parent, 1);
        }

        template< typename T >
        static inline void set(SimpleExample::St& s_, const T& t_)
        {
            s_.ss = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::St& s_, T& t_)
        {
            t_ = s_.ss;
        }
    };
    template< > struct member_helper < SimpleExample::St, 2 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::St s_;
            ::CORBA::Long t_;
            return ::corbasim::core::create_reflective(t_, s_.b, parent, 2);
        }

        template< typename T >
        static inline void set(SimpleExample::St& s_, const T& t_)
        {
            s_.b = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::St& s_, T& t_)
        {
            t_ = s_.b;
        }
    };
    template< > struct member_helper < SimpleExample::St, 3 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::St s_;
            SimpleExample::MyUnion t_;
            return ::corbasim::core::create_reflective(t_, s_.uniii, parent, 3);
        }

        template< typename T >
        static inline void set(SimpleExample::St& s_, const T& t_)
        {
            s_.uniii = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::St& s_, T& t_)
        {
            t_ = s_.uniii;
        }
    };
} // adapted
} // corbasim


namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< SimpleExample::Test_var > : public cs_mpl::true_
{
	typedef SimpleExample::Test interface;
};

} // adapted
} // corbasim








// StructDef: SimpleExample::Hijo
BOOST_FUSION_ADAPT_STRUCT(
	SimpleExample::Hijo,
	( ::CORBA::Long, b)
	( ::CORBA::Boolean, l)
	( ::corbasim::orbimpl::String_Manager, s)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < SimpleExample::Hijo, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::Hijo s_;
            ::CORBA::Long t_;
            return ::corbasim::core::create_reflective(t_, s_.b, parent, 0);
        }

        template< typename T >
        static inline void set(SimpleExample::Hijo& s_, const T& t_)
        {
            s_.b = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::Hijo& s_, T& t_)
        {
            t_ = s_.b;
        }
    };
    template< > struct member_helper < SimpleExample::Hijo, 1 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::Hijo s_;
            ::CORBA::Boolean t_;
            return ::corbasim::core::create_reflective(t_, s_.l, parent, 1);
        }

        template< typename T >
        static inline void set(SimpleExample::Hijo& s_, const T& t_)
        {
            s_.l = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::Hijo& s_, T& t_)
        {
            t_ = s_.l;
        }
    };
    template< > struct member_helper < SimpleExample::Hijo, 2 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::Hijo s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.s, parent, 2);
        }

        template< typename T >
        static inline void set(SimpleExample::Hijo& s_, const T& t_)
        {
            s_.s = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::Hijo& s_, T& t_)
        {
            t_ = s_.s;
        }
    };
} // adapted
} // corbasim


// StructDef: SimpleExample::Padre
BOOST_FUSION_ADAPT_STRUCT(
	SimpleExample::Padre,
	( SimpleExample::Hijo, h)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < SimpleExample::Padre, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::Padre s_;
            SimpleExample::Hijo t_;
            return ::corbasim::core::create_reflective(t_, s_.h, parent, 0);
        }

        template< typename T >
        static inline void set(SimpleExample::Padre& s_, const T& t_)
        {
            s_.h = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::Padre& s_, T& t_)
        {
            t_ = s_.h;
        }
    };
} // adapted
} // corbasim




// StructDef: SimpleExample::Abuelo
BOOST_FUSION_ADAPT_STRUCT(
	SimpleExample::Abuelo,
	( SimpleExample::Padres, p)
	( SimpleExample::Test_var, tt)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < SimpleExample::Abuelo, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::Abuelo s_;
            SimpleExample::Padres t_;
            return ::corbasim::core::create_reflective(t_, s_.p, parent, 0);
        }

        template< typename T >
        static inline void set(SimpleExample::Abuelo& s_, const T& t_)
        {
            s_.p = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::Abuelo& s_, T& t_)
        {
            t_ = s_.p;
        }
    };
    template< > struct member_helper < SimpleExample::Abuelo, 1 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            SimpleExample::Abuelo s_;
            SimpleExample::Test_var t_;
            return ::corbasim::core::create_reflective(t_, s_.tt, parent, 1);
        }

        template< typename T >
        static inline void set(SimpleExample::Abuelo& s_, const T& t_)
        {
            s_.tt = t_;
        }

        template< typename T >
        static inline void get(const SimpleExample::Abuelo& s_, T& t_)
        {
            t_ = s_.tt;
        }
    };
} // adapted
} // corbasim





        
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< StringTest::NameSeq > : public cs_mpl::true_
{
	typedef StringTest::Name slice_type;
};

} // adapted
} // corbasim




        
namespace corbasim
{
namespace adapted
{

template < >
struct is_corbaseq< StringTest::NameIDSeq > : public cs_mpl::true_
{
	typedef StringTest::NameID slice_type;
};

} // adapted
} // corbasim


// StructDef: StringTest::StructWithStrings
BOOST_FUSION_ADAPT_STRUCT(
	StringTest::StructWithStrings,
	( ::corbasim::orbimpl::String_Manager, str)
	( ::corbasim::orbimpl::String_Manager, nam)
	( ::corbasim::orbimpl::String_Manager, id)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < StringTest::StructWithStrings, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            StringTest::StructWithStrings s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.str, parent, 0);
        }

        template< typename T >
        static inline void set(StringTest::StructWithStrings& s_, const T& t_)
        {
            s_.str = t_;
        }

        template< typename T >
        static inline void get(const StringTest::StructWithStrings& s_, T& t_)
        {
            t_ = s_.str;
        }
    };
    template< > struct member_helper < StringTest::StructWithStrings, 1 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            StringTest::StructWithStrings s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.nam, parent, 1);
        }

        template< typename T >
        static inline void set(StringTest::StructWithStrings& s_, const T& t_)
        {
            s_.nam = t_;
        }

        template< typename T >
        static inline void get(const StringTest::StructWithStrings& s_, T& t_)
        {
            t_ = s_.nam;
        }
    };
    template< > struct member_helper < StringTest::StructWithStrings, 2 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            StringTest::StructWithStrings s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.id, parent, 2);
        }

        template< typename T >
        static inline void set(StringTest::StructWithStrings& s_, const T& t_)
        {
            s_.id = t_;
        }

        template< typename T >
        static inline void get(const StringTest::StructWithStrings& s_, T& t_)
        {
            t_ = s_.id;
        }
    };
} // adapted
} // corbasim


namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< StringTest::InterfaceString_var > : public cs_mpl::true_
{
	typedef StringTest::InterfaceString interface;
};

} // adapted
} // corbasim















// Enum: MyModule::MyEnum
namespace corbasim
{
namespace adapted
{

template< >
struct enumeration< MyModule::MyEnum >
{
	static const unsigned int size = 3;
	
	static inline const char** values()
	{
		static const char* _data[] = {"AAA", "BBB", "CCC", 0};
		return _data;
	}
};

} // adapted
} // corbasim



// UnionDef: MyModule::MyUnion
BOOST_FUSION_ADAPT_ADT(
	MyModule::MyUnion,
	( MyModule::MyEnum, MyModule::MyEnum, obj._d(), obj._d(val)) // Discriminator
	( ::CORBA::Long, ::CORBA::Long, obj.one(), obj.one(val))
	( ::CORBA::Long, ::CORBA::Long, obj.other(), obj.other(val))
     )

namespace boost
{
namespace fusion
{
namespace extension
{

template< >
struct struct_member_name< MyModule::MyUnion, 0>
{
	static inline const char * call()
	{
		return "_d";
	}
};

template< >
struct struct_member_name< MyModule::MyUnion, 1>
{
	static inline const char * call()
	{
		return "one";
	}
};
template< >
struct struct_member_name< MyModule::MyUnion, 2>
{
	static inline const char * call()
	{
		return "other";
	}
};

} // extension
} // fusion
} // boost

namespace corbasim
{
namespace adapted
{

template< >
struct is_union< MyModule::MyUnion > : public cs_mpl::true_
{
	typedef MyModule::MyEnum discriminator_t;
	
	static const size_t size = 3;
	
	static inline discriminator_t* discriminators()
	{
		static discriminator_t _disc[] = { 
					MyModule::AAA
			, 									MyModule::BBB
				, 					MyModule::CCC
			};		
		return _disc;
	}
	
	static inline unsigned int* member()
	{
		static unsigned int _members[] = { 
					1
			, 									2
				, 					2
			};		
		return _members;
	}
};

} // adapted
} // corbasim



// UnionDef: MyModule::MyUnion2
BOOST_FUSION_ADAPT_ADT(
	MyModule::MyUnion2,
	( ::CORBA::Long, ::CORBA::Long, obj._d(), obj._d(val)) // Discriminator
	( const MyModule::MyUnion&, const MyModule::MyUnion&, obj.one(), obj.one(val))
	( ::CORBA::Long, ::CORBA::Long, obj.other(), obj.other(val))
     )

namespace boost
{
namespace fusion
{
namespace extension
{

template< >
struct struct_member_name< MyModule::MyUnion2, 0>
{
	static inline const char * call()
	{
		return "_d";
	}
};

template< >
struct struct_member_name< MyModule::MyUnion2, 1>
{
	static inline const char * call()
	{
		return "one";
	}
};
template< >
struct struct_member_name< MyModule::MyUnion2, 2>
{
	static inline const char * call()
	{
		return "other";
	}
};

} // extension
} // fusion
} // boost

namespace corbasim
{
namespace adapted
{

template< >
struct is_union< MyModule::MyUnion2 > : public cs_mpl::true_
{
	typedef ::CORBA::Long discriminator_t;
	
	static const size_t size = 2;
	
	static inline discriminator_t* discriminators()
	{
		static discriminator_t _disc[] = { 
					100
			, 									200
			};		
		return _disc;
	}
	
	static inline unsigned int* member()
	{
		static unsigned int _members[] = { 
					1
			, 									2
			};		
		return _members;
	}
};

} // adapted
} // corbasim



// UnionDef: MyModule::MyUnion3
BOOST_FUSION_ADAPT_ADT(
	MyModule::MyUnion3,
	( ::CORBA::Boolean, ::CORBA::Boolean, obj._d(), obj._d(val)) // Discriminator
	( const MyModule::MyUnion&, const MyModule::MyUnion&, obj.one(), obj.one(val))
	( ::CORBA::Long, ::CORBA::Long, obj.other(), obj.other(val))
     )

namespace boost
{
namespace fusion
{
namespace extension
{

template< >
struct struct_member_name< MyModule::MyUnion3, 0>
{
	static inline const char * call()
	{
		return "_d";
	}
};

template< >
struct struct_member_name< MyModule::MyUnion3, 1>
{
	static inline const char * call()
	{
		return "one";
	}
};
template< >
struct struct_member_name< MyModule::MyUnion3, 2>
{
	static inline const char * call()
	{
		return "other";
	}
};

} // extension
} // fusion
} // boost

namespace corbasim
{
namespace adapted
{

template< >
struct is_union< MyModule::MyUnion3 > : public cs_mpl::true_
{
	typedef ::CORBA::Boolean discriminator_t;
	
	static const size_t size = 2;
	
	static inline discriminator_t* discriminators()
	{
		static discriminator_t _disc[] = { 
					true
			, 									false
			};		
		return _disc;
	}
	
	static inline unsigned int* member()
	{
		static unsigned int _members[] = { 
					1
			, 									2
			};		
		return _members;
	}
};

} // adapted
} // corbasim



// StructDef: MyModule::MyStruct
BOOST_FUSION_ADAPT_STRUCT(
	MyModule::MyStruct,
	( MyModule::MyStruct::_a, a)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < MyModule::MyStruct, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            MyModule::MyStruct s_;
            MyModule::MyStruct::_a t_;
            return ::corbasim::core::create_reflective(t_, s_.a, parent, 0);
        }

        template< typename T >
        static inline void set(MyModule::MyStruct& s_, const T& t_)
        {
            s_.a = t_;
        }

        template< typename T >
        static inline void get(const MyModule::MyStruct& s_, T& t_)
        {
            t_ = s_.a;
        }
    };
} // adapted
} // corbasim


namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< MyModule::MyInterface_var > : public cs_mpl::true_
{
	typedef MyModule::MyInterface interface;
};

} // adapted
} // corbasim













// StructDef: Test::St
BOOST_FUSION_ADAPT_STRUCT(
	Test::St,
	( ::corbasim::orbimpl::String_Manager, a)
	( ::corbasim::orbimpl::String_Manager, b)
	( Test::Prueba_var, reffff)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < Test::St, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            Test::St s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.a, parent, 0);
        }

        template< typename T >
        static inline void set(Test::St& s_, const T& t_)
        {
            s_.a = t_;
        }

        template< typename T >
        static inline void get(const Test::St& s_, T& t_)
        {
            t_ = s_.a;
        }
    };
    template< > struct member_helper < Test::St, 1 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            Test::St s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.b, parent, 1);
        }

        template< typename T >
        static inline void set(Test::St& s_, const T& t_)
        {
            s_.b = t_;
        }

        template< typename T >
        static inline void get(const Test::St& s_, T& t_)
        {
            t_ = s_.b;
        }
    };
    template< > struct member_helper < Test::St, 2 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            Test::St s_;
            Test::Prueba_var t_;
            return ::corbasim::core::create_reflective(t_, s_.reffff, parent, 2);
        }

        template< typename T >
        static inline void set(Test::St& s_, const T& t_)
        {
            s_.reffff = t_;
        }

        template< typename T >
        static inline void get(const Test::St& s_, T& t_)
        {
            t_ = s_.reffff;
        }
    };
} // adapted
} // corbasim


// StructDef: Test::St2
BOOST_FUSION_ADAPT_STRUCT(
	Test::St2,
	( Test::St, a)
	( Test::St, b)
	( ::corbasim::orbimpl::String_Manager, c)
	( ::CORBA::Long, unsupported)
     )

	

namespace corbasim
{
namespace adapted
{ 
    template< > struct member_helper < Test::St2, 0 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            Test::St2 s_;
            Test::St t_;
            return ::corbasim::core::create_reflective(t_, s_.a, parent, 0);
        }

        template< typename T >
        static inline void set(Test::St2& s_, const T& t_)
        {
            s_.a = t_;
        }

        template< typename T >
        static inline void get(const Test::St2& s_, T& t_)
        {
            t_ = s_.a;
        }
    };
    template< > struct member_helper < Test::St2, 1 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            Test::St2 s_;
            Test::St t_;
            return ::corbasim::core::create_reflective(t_, s_.b, parent, 1);
        }

        template< typename T >
        static inline void set(Test::St2& s_, const T& t_)
        {
            s_.b = t_;
        }

        template< typename T >
        static inline void get(const Test::St2& s_, T& t_)
        {
            t_ = s_.b;
        }
    };
    template< > struct member_helper < Test::St2, 2 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            Test::St2 s_;
            ::corbasim::orbimpl::String_Manager t_;
            return ::corbasim::core::create_reflective(t_, s_.c, parent, 2);
        }

        template< typename T >
        static inline void set(Test::St2& s_, const T& t_)
        {
            s_.c = t_;
        }

        template< typename T >
        static inline void get(const Test::St2& s_, T& t_)
        {
            t_ = s_.c;
        }
    };
    template< > struct member_helper < Test::St2, 3 >
    {
        static inline ::corbasim::core::reflective_base * create_reflective(
            ::corbasim::core::reflective_base const * parent)
        {
            Test::St2 s_;
            ::CORBA::Long t_;
            return ::corbasim::core::create_reflective(t_, s_.unsupported, parent, 3);
        }

        template< typename T >
        static inline void set(Test::St2& s_, const T& t_)
        {
            s_.unsupported = t_;
        }

        template< typename T >
        static inline void get(const Test::St2& s_, T& t_)
        {
            t_ = s_.unsupported;
        }
    };
} // adapted
} // corbasim


namespace corbasim
{
namespace adapted
{

template < >
struct is_objrefvar< Test::Prueba_var > : public cs_mpl::true_
{
	typedef Test::Prueba interface;
};

} // adapted
} // corbasim









namespace _corbasim_HelloApp 
{


namespace Hello 
{
struct __sayHello
{
	typedef boost::mpl::vector<  > _arg_list;


	
	::corbasim::orbimpl::String_Manager _return;
	
	__sayHello();
	
	
	// Copy constructor
	__sayHello(const __sayHello& o);
};

typedef __sayHello sayHello;


struct __sayHelloTo
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const HelloApp::Names& > > _arg_list;

	typedef corbasim::adapted::member< __sayHelloTo, 0 > people_corbasim_member;

	HelloApp::Names people;
	
	::corbasim::orbimpl::String_Manager _return;
	
	__sayHelloTo();
	
	__sayHelloTo(const HelloApp::Names& _people);
	
	// Copy constructor
	__sayHelloTo(const __sayHelloTo& o);
};

typedef __sayHelloTo sayHelloTo;


struct __shutdown
{
	typedef boost::mpl::vector<  > _arg_list;


	
	
	__shutdown();
	
	
	// Copy constructor
	__shutdown(const __shutdown& o);
};

typedef __shutdown shutdown;

} // Hello

} // _corbasim_HelloApp


namespace _corbasim_Test 
{
namespace Huge 
{
struct __operation1
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation1, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation1();
	
	__operation1(::CORBA::Long _a);
	
	// Copy constructor
	__operation1(const __operation1& o);
};

typedef __operation1 operation1;


struct __operation2
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation2, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation2();
	
	__operation2(::CORBA::Long _a);
	
	// Copy constructor
	__operation2(const __operation2& o);
};

typedef __operation2 operation2;


struct __operation3
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation3, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation3();
	
	__operation3(::CORBA::Long _a);
	
	// Copy constructor
	__operation3(const __operation3& o);
};

typedef __operation3 operation3;


struct __operation4
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation4, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation4();
	
	__operation4(::CORBA::Long _a);
	
	// Copy constructor
	__operation4(const __operation4& o);
};

typedef __operation4 operation4;


struct __operation5
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation5, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation5();
	
	__operation5(::CORBA::Long _a);
	
	// Copy constructor
	__operation5(const __operation5& o);
};

typedef __operation5 operation5;


struct __operation6
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation6, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation6();
	
	__operation6(::CORBA::Long _a);
	
	// Copy constructor
	__operation6(const __operation6& o);
};

typedef __operation6 operation6;


struct __operation7
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation7, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation7();
	
	__operation7(::CORBA::Long _a);
	
	// Copy constructor
	__operation7(const __operation7& o);
};

typedef __operation7 operation7;


struct __operation8
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation8, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation8();
	
	__operation8(::CORBA::Long _a);
	
	// Copy constructor
	__operation8(const __operation8& o);
};

typedef __operation8 operation8;


struct __operation9
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation9, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation9();
	
	__operation9(::CORBA::Long _a);
	
	// Copy constructor
	__operation9(const __operation9& o);
};

typedef __operation9 operation9;


struct __operation10
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation10, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation10();
	
	__operation10(::CORBA::Long _a);
	
	// Copy constructor
	__operation10(const __operation10& o);
};

typedef __operation10 operation10;


struct __operation11
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation11, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation11();
	
	__operation11(::CORBA::Long _a);
	
	// Copy constructor
	__operation11(const __operation11& o);
};

typedef __operation11 operation11;


struct __operation12
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation12, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation12();
	
	__operation12(::CORBA::Long _a);
	
	// Copy constructor
	__operation12(const __operation12& o);
};

typedef __operation12 operation12;


struct __operation13
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation13, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation13();
	
	__operation13(::CORBA::Long _a);
	
	// Copy constructor
	__operation13(const __operation13& o);
};

typedef __operation13 operation13;


struct __operation14
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation14, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation14();
	
	__operation14(::CORBA::Long _a);
	
	// Copy constructor
	__operation14(const __operation14& o);
};

typedef __operation14 operation14;


struct __operation15
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation15, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation15();
	
	__operation15(::CORBA::Long _a);
	
	// Copy constructor
	__operation15(const __operation15& o);
};

typedef __operation15 operation15;


struct __operation16
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation16, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation16();
	
	__operation16(::CORBA::Long _a);
	
	// Copy constructor
	__operation16(const __operation16& o);
};

typedef __operation16 operation16;


struct __operation17
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation17, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation17();
	
	__operation17(::CORBA::Long _a);
	
	// Copy constructor
	__operation17(const __operation17& o);
};

typedef __operation17 operation17;


struct __operation18
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation18, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation18();
	
	__operation18(::CORBA::Long _a);
	
	// Copy constructor
	__operation18(const __operation18& o);
};

typedef __operation18 operation18;


struct __operation19
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation19, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation19();
	
	__operation19(::CORBA::Long _a);
	
	// Copy constructor
	__operation19(const __operation19& o);
};

typedef __operation19 operation19;


struct __operation20
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation20, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation20();
	
	__operation20(::CORBA::Long _a);
	
	// Copy constructor
	__operation20(const __operation20& o);
};

typedef __operation20 operation20;


struct __operation21
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation21, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation21();
	
	__operation21(::CORBA::Long _a);
	
	// Copy constructor
	__operation21(const __operation21& o);
};

typedef __operation21 operation21;


struct __operation22
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation22, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation22();
	
	__operation22(::CORBA::Long _a);
	
	// Copy constructor
	__operation22(const __operation22& o);
};

typedef __operation22 operation22;


struct __operation23
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation23, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation23();
	
	__operation23(::CORBA::Long _a);
	
	// Copy constructor
	__operation23(const __operation23& o);
};

typedef __operation23 operation23;


struct __operation24
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation24, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation24();
	
	__operation24(::CORBA::Long _a);
	
	// Copy constructor
	__operation24(const __operation24& o);
};

typedef __operation24 operation24;


struct __operation25
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation25, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation25();
	
	__operation25(::CORBA::Long _a);
	
	// Copy constructor
	__operation25(const __operation25& o);
};

typedef __operation25 operation25;


struct __operation26
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation26, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation26();
	
	__operation26(::CORBA::Long _a);
	
	// Copy constructor
	__operation26(const __operation26& o);
};

typedef __operation26 operation26;


struct __operation27
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation27, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation27();
	
	__operation27(::CORBA::Long _a);
	
	// Copy constructor
	__operation27(const __operation27& o);
};

typedef __operation27 operation27;


struct __operation28
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation28, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation28();
	
	__operation28(::CORBA::Long _a);
	
	// Copy constructor
	__operation28(const __operation28& o);
};

typedef __operation28 operation28;


struct __operation29
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation29, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation29();
	
	__operation29(::CORBA::Long _a);
	
	// Copy constructor
	__operation29(const __operation29& o);
};

typedef __operation29 operation29;


struct __operation30
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation30, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation30();
	
	__operation30(::CORBA::Long _a);
	
	// Copy constructor
	__operation30(const __operation30& o);
};

typedef __operation30 operation30;


struct __operation31
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation31, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation31();
	
	__operation31(::CORBA::Long _a);
	
	// Copy constructor
	__operation31(const __operation31& o);
};

typedef __operation31 operation31;


struct __operation32
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation32, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation32();
	
	__operation32(::CORBA::Long _a);
	
	// Copy constructor
	__operation32(const __operation32& o);
};

typedef __operation32 operation32;


struct __operation33
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation33, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation33();
	
	__operation33(::CORBA::Long _a);
	
	// Copy constructor
	__operation33(const __operation33& o);
};

typedef __operation33 operation33;


struct __operation34
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation34, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation34();
	
	__operation34(::CORBA::Long _a);
	
	// Copy constructor
	__operation34(const __operation34& o);
};

typedef __operation34 operation34;


struct __operation35
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation35, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation35();
	
	__operation35(::CORBA::Long _a);
	
	// Copy constructor
	__operation35(const __operation35& o);
};

typedef __operation35 operation35;


struct __operation36
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation36, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation36();
	
	__operation36(::CORBA::Long _a);
	
	// Copy constructor
	__operation36(const __operation36& o);
};

typedef __operation36 operation36;


struct __operation37
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation37, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation37();
	
	__operation37(::CORBA::Long _a);
	
	// Copy constructor
	__operation37(const __operation37& o);
};

typedef __operation37 operation37;


struct __operation38
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation38, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation38();
	
	__operation38(::CORBA::Long _a);
	
	// Copy constructor
	__operation38(const __operation38& o);
};

typedef __operation38 operation38;


struct __operation39
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation39, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation39();
	
	__operation39(::CORBA::Long _a);
	
	// Copy constructor
	__operation39(const __operation39& o);
};

typedef __operation39 operation39;


struct __operation40
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation40, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation40();
	
	__operation40(::CORBA::Long _a);
	
	// Copy constructor
	__operation40(const __operation40& o);
};

typedef __operation40 operation40;


struct __operation41
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation41, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation41();
	
	__operation41(::CORBA::Long _a);
	
	// Copy constructor
	__operation41(const __operation41& o);
};

typedef __operation41 operation41;


struct __operation42
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation42, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation42();
	
	__operation42(::CORBA::Long _a);
	
	// Copy constructor
	__operation42(const __operation42& o);
};

typedef __operation42 operation42;


struct __operation43
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation43, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation43();
	
	__operation43(::CORBA::Long _a);
	
	// Copy constructor
	__operation43(const __operation43& o);
};

typedef __operation43 operation43;


struct __operation44
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation44, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation44();
	
	__operation44(::CORBA::Long _a);
	
	// Copy constructor
	__operation44(const __operation44& o);
};

typedef __operation44 operation44;


struct __operation45
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation45, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation45();
	
	__operation45(::CORBA::Long _a);
	
	// Copy constructor
	__operation45(const __operation45& o);
};

typedef __operation45 operation45;


struct __operation46
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation46, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation46();
	
	__operation46(::CORBA::Long _a);
	
	// Copy constructor
	__operation46(const __operation46& o);
};

typedef __operation46 operation46;


struct __operation47
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation47, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation47();
	
	__operation47(::CORBA::Long _a);
	
	// Copy constructor
	__operation47(const __operation47& o);
};

typedef __operation47 operation47;


struct __operation48
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation48, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation48();
	
	__operation48(::CORBA::Long _a);
	
	// Copy constructor
	__operation48(const __operation48& o);
};

typedef __operation48 operation48;


struct __operation49
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation49, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation49();
	
	__operation49(::CORBA::Long _a);
	
	// Copy constructor
	__operation49(const __operation49& o);
};

typedef __operation49 operation49;


struct __operation50
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation50, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation50();
	
	__operation50(::CORBA::Long _a);
	
	// Copy constructor
	__operation50(const __operation50& o);
};

typedef __operation50 operation50;


struct __operation51
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation51, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation51();
	
	__operation51(::CORBA::Long _a);
	
	// Copy constructor
	__operation51(const __operation51& o);
};

typedef __operation51 operation51;


struct __operation52
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation52, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation52();
	
	__operation52(::CORBA::Long _a);
	
	// Copy constructor
	__operation52(const __operation52& o);
};

typedef __operation52 operation52;


struct __operation53
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation53, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation53();
	
	__operation53(::CORBA::Long _a);
	
	// Copy constructor
	__operation53(const __operation53& o);
};

typedef __operation53 operation53;


struct __operation54
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation54, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation54();
	
	__operation54(::CORBA::Long _a);
	
	// Copy constructor
	__operation54(const __operation54& o);
};

typedef __operation54 operation54;


struct __operation55
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation55, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation55();
	
	__operation55(::CORBA::Long _a);
	
	// Copy constructor
	__operation55(const __operation55& o);
};

typedef __operation55 operation55;


struct __operation56
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation56, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation56();
	
	__operation56(::CORBA::Long _a);
	
	// Copy constructor
	__operation56(const __operation56& o);
};

typedef __operation56 operation56;


struct __operation57
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation57, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation57();
	
	__operation57(::CORBA::Long _a);
	
	// Copy constructor
	__operation57(const __operation57& o);
};

typedef __operation57 operation57;


struct __operation58
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation58, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation58();
	
	__operation58(::CORBA::Long _a);
	
	// Copy constructor
	__operation58(const __operation58& o);
};

typedef __operation58 operation58;


struct __operation59
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation59, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation59();
	
	__operation59(::CORBA::Long _a);
	
	// Copy constructor
	__operation59(const __operation59& o);
};

typedef __operation59 operation59;


struct __operation60
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation60, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation60();
	
	__operation60(::CORBA::Long _a);
	
	// Copy constructor
	__operation60(const __operation60& o);
};

typedef __operation60 operation60;


struct __operation61
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation61, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation61();
	
	__operation61(::CORBA::Long _a);
	
	// Copy constructor
	__operation61(const __operation61& o);
};

typedef __operation61 operation61;


struct __operation62
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation62, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation62();
	
	__operation62(::CORBA::Long _a);
	
	// Copy constructor
	__operation62(const __operation62& o);
};

typedef __operation62 operation62;


struct __operation63
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation63, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation63();
	
	__operation63(::CORBA::Long _a);
	
	// Copy constructor
	__operation63(const __operation63& o);
};

typedef __operation63 operation63;


struct __operation64
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation64, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation64();
	
	__operation64(::CORBA::Long _a);
	
	// Copy constructor
	__operation64(const __operation64& o);
};

typedef __operation64 operation64;


struct __operation65
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation65, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation65();
	
	__operation65(::CORBA::Long _a);
	
	// Copy constructor
	__operation65(const __operation65& o);
};

typedef __operation65 operation65;


struct __operation66
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation66, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation66();
	
	__operation66(::CORBA::Long _a);
	
	// Copy constructor
	__operation66(const __operation66& o);
};

typedef __operation66 operation66;


struct __operation67
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation67, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation67();
	
	__operation67(::CORBA::Long _a);
	
	// Copy constructor
	__operation67(const __operation67& o);
};

typedef __operation67 operation67;


struct __operation68
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation68, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation68();
	
	__operation68(::CORBA::Long _a);
	
	// Copy constructor
	__operation68(const __operation68& o);
};

typedef __operation68 operation68;


struct __operation69
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation69, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation69();
	
	__operation69(::CORBA::Long _a);
	
	// Copy constructor
	__operation69(const __operation69& o);
};

typedef __operation69 operation69;


struct __operation70
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation70, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation70();
	
	__operation70(::CORBA::Long _a);
	
	// Copy constructor
	__operation70(const __operation70& o);
};

typedef __operation70 operation70;


struct __operation71
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation71, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation71();
	
	__operation71(::CORBA::Long _a);
	
	// Copy constructor
	__operation71(const __operation71& o);
};

typedef __operation71 operation71;


struct __operation72
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation72, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation72();
	
	__operation72(::CORBA::Long _a);
	
	// Copy constructor
	__operation72(const __operation72& o);
};

typedef __operation72 operation72;


struct __operation73
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation73, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation73();
	
	__operation73(::CORBA::Long _a);
	
	// Copy constructor
	__operation73(const __operation73& o);
};

typedef __operation73 operation73;


struct __operation74
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation74, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation74();
	
	__operation74(::CORBA::Long _a);
	
	// Copy constructor
	__operation74(const __operation74& o);
};

typedef __operation74 operation74;


struct __operation75
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation75, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation75();
	
	__operation75(::CORBA::Long _a);
	
	// Copy constructor
	__operation75(const __operation75& o);
};

typedef __operation75 operation75;


struct __operation76
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation76, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation76();
	
	__operation76(::CORBA::Long _a);
	
	// Copy constructor
	__operation76(const __operation76& o);
};

typedef __operation76 operation76;


struct __operation77
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation77, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation77();
	
	__operation77(::CORBA::Long _a);
	
	// Copy constructor
	__operation77(const __operation77& o);
};

typedef __operation77 operation77;


struct __operation78
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation78, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation78();
	
	__operation78(::CORBA::Long _a);
	
	// Copy constructor
	__operation78(const __operation78& o);
};

typedef __operation78 operation78;


struct __operation79
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation79, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation79();
	
	__operation79(::CORBA::Long _a);
	
	// Copy constructor
	__operation79(const __operation79& o);
};

typedef __operation79 operation79;


struct __operation80
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation80, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation80();
	
	__operation80(::CORBA::Long _a);
	
	// Copy constructor
	__operation80(const __operation80& o);
};

typedef __operation80 operation80;


struct __operation81
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation81, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation81();
	
	__operation81(::CORBA::Long _a);
	
	// Copy constructor
	__operation81(const __operation81& o);
};

typedef __operation81 operation81;


struct __operation82
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation82, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation82();
	
	__operation82(::CORBA::Long _a);
	
	// Copy constructor
	__operation82(const __operation82& o);
};

typedef __operation82 operation82;


struct __operation83
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation83, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation83();
	
	__operation83(::CORBA::Long _a);
	
	// Copy constructor
	__operation83(const __operation83& o);
};

typedef __operation83 operation83;


struct __operation84
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation84, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation84();
	
	__operation84(::CORBA::Long _a);
	
	// Copy constructor
	__operation84(const __operation84& o);
};

typedef __operation84 operation84;


struct __operation85
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation85, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation85();
	
	__operation85(::CORBA::Long _a);
	
	// Copy constructor
	__operation85(const __operation85& o);
};

typedef __operation85 operation85;


struct __operation86
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation86, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation86();
	
	__operation86(::CORBA::Long _a);
	
	// Copy constructor
	__operation86(const __operation86& o);
};

typedef __operation86 operation86;


struct __operation87
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation87, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation87();
	
	__operation87(::CORBA::Long _a);
	
	// Copy constructor
	__operation87(const __operation87& o);
};

typedef __operation87 operation87;


struct __operation88
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation88, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation88();
	
	__operation88(::CORBA::Long _a);
	
	// Copy constructor
	__operation88(const __operation88& o);
};

typedef __operation88 operation88;


struct __operation89
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation89, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation89();
	
	__operation89(::CORBA::Long _a);
	
	// Copy constructor
	__operation89(const __operation89& o);
};

typedef __operation89 operation89;


struct __operation90
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation90, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation90();
	
	__operation90(::CORBA::Long _a);
	
	// Copy constructor
	__operation90(const __operation90& o);
};

typedef __operation90 operation90;


struct __operation91
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation91, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation91();
	
	__operation91(::CORBA::Long _a);
	
	// Copy constructor
	__operation91(const __operation91& o);
};

typedef __operation91 operation91;


struct __operation92
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation92, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation92();
	
	__operation92(::CORBA::Long _a);
	
	// Copy constructor
	__operation92(const __operation92& o);
};

typedef __operation92 operation92;


struct __operation93
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation93, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation93();
	
	__operation93(::CORBA::Long _a);
	
	// Copy constructor
	__operation93(const __operation93& o);
};

typedef __operation93 operation93;


struct __operation94
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation94, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation94();
	
	__operation94(::CORBA::Long _a);
	
	// Copy constructor
	__operation94(const __operation94& o);
};

typedef __operation94 operation94;


struct __operation95
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation95, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation95();
	
	__operation95(::CORBA::Long _a);
	
	// Copy constructor
	__operation95(const __operation95& o);
};

typedef __operation95 operation95;


struct __operation96
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation96, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation96();
	
	__operation96(::CORBA::Long _a);
	
	// Copy constructor
	__operation96(const __operation96& o);
};

typedef __operation96 operation96;


struct __operation97
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation97, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation97();
	
	__operation97(::CORBA::Long _a);
	
	// Copy constructor
	__operation97(const __operation97& o);
};

typedef __operation97 operation97;


struct __operation98
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation98, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation98();
	
	__operation98(::CORBA::Long _a);
	
	// Copy constructor
	__operation98(const __operation98& o);
};

typedef __operation98 operation98;


struct __operation99
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation99, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation99();
	
	__operation99(::CORBA::Long _a);
	
	// Copy constructor
	__operation99(const __operation99& o);
};

typedef __operation99 operation99;


struct __operation100
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation100, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation100();
	
	__operation100(::CORBA::Long _a);
	
	// Copy constructor
	__operation100(const __operation100& o);
};

typedef __operation100 operation100;


struct __operation101
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation101, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation101();
	
	__operation101(::CORBA::Long _a);
	
	// Copy constructor
	__operation101(const __operation101& o);
};

typedef __operation101 operation101;


struct __operation102
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation102, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation102();
	
	__operation102(::CORBA::Long _a);
	
	// Copy constructor
	__operation102(const __operation102& o);
};

typedef __operation102 operation102;


struct __operation103
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation103, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation103();
	
	__operation103(::CORBA::Long _a);
	
	// Copy constructor
	__operation103(const __operation103& o);
};

typedef __operation103 operation103;


struct __operation104
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation104, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation104();
	
	__operation104(::CORBA::Long _a);
	
	// Copy constructor
	__operation104(const __operation104& o);
};

typedef __operation104 operation104;


struct __operation105
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation105, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation105();
	
	__operation105(::CORBA::Long _a);
	
	// Copy constructor
	__operation105(const __operation105& o);
};

typedef __operation105 operation105;


struct __operation106
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation106, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation106();
	
	__operation106(::CORBA::Long _a);
	
	// Copy constructor
	__operation106(const __operation106& o);
};

typedef __operation106 operation106;


struct __operation107
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation107, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation107();
	
	__operation107(::CORBA::Long _a);
	
	// Copy constructor
	__operation107(const __operation107& o);
};

typedef __operation107 operation107;


struct __operation108
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation108, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation108();
	
	__operation108(::CORBA::Long _a);
	
	// Copy constructor
	__operation108(const __operation108& o);
};

typedef __operation108 operation108;


struct __operation109
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation109, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation109();
	
	__operation109(::CORBA::Long _a);
	
	// Copy constructor
	__operation109(const __operation109& o);
};

typedef __operation109 operation109;


struct __operation110
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation110, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation110();
	
	__operation110(::CORBA::Long _a);
	
	// Copy constructor
	__operation110(const __operation110& o);
};

typedef __operation110 operation110;


struct __operation111
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation111, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation111();
	
	__operation111(::CORBA::Long _a);
	
	// Copy constructor
	__operation111(const __operation111& o);
};

typedef __operation111 operation111;


struct __operation112
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation112, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation112();
	
	__operation112(::CORBA::Long _a);
	
	// Copy constructor
	__operation112(const __operation112& o);
};

typedef __operation112 operation112;


struct __operation113
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation113, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation113();
	
	__operation113(::CORBA::Long _a);
	
	// Copy constructor
	__operation113(const __operation113& o);
};

typedef __operation113 operation113;


struct __operation114
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation114, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation114();
	
	__operation114(::CORBA::Long _a);
	
	// Copy constructor
	__operation114(const __operation114& o);
};

typedef __operation114 operation114;


struct __operation115
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation115, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation115();
	
	__operation115(::CORBA::Long _a);
	
	// Copy constructor
	__operation115(const __operation115& o);
};

typedef __operation115 operation115;


struct __operation116
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation116, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation116();
	
	__operation116(::CORBA::Long _a);
	
	// Copy constructor
	__operation116(const __operation116& o);
};

typedef __operation116 operation116;


struct __operation117
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation117, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation117();
	
	__operation117(::CORBA::Long _a);
	
	// Copy constructor
	__operation117(const __operation117& o);
};

typedef __operation117 operation117;


struct __operation118
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation118, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation118();
	
	__operation118(::CORBA::Long _a);
	
	// Copy constructor
	__operation118(const __operation118& o);
};

typedef __operation118 operation118;


struct __operation119
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation119, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation119();
	
	__operation119(::CORBA::Long _a);
	
	// Copy constructor
	__operation119(const __operation119& o);
};

typedef __operation119 operation119;


struct __operation120
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation120, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation120();
	
	__operation120(::CORBA::Long _a);
	
	// Copy constructor
	__operation120(const __operation120& o);
};

typedef __operation120 operation120;


struct __operation121
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation121, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation121();
	
	__operation121(::CORBA::Long _a);
	
	// Copy constructor
	__operation121(const __operation121& o);
};

typedef __operation121 operation121;


struct __operation122
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation122, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation122();
	
	__operation122(::CORBA::Long _a);
	
	// Copy constructor
	__operation122(const __operation122& o);
};

typedef __operation122 operation122;


struct __operation123
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation123, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation123();
	
	__operation123(::CORBA::Long _a);
	
	// Copy constructor
	__operation123(const __operation123& o);
};

typedef __operation123 operation123;


struct __operation124
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation124, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation124();
	
	__operation124(::CORBA::Long _a);
	
	// Copy constructor
	__operation124(const __operation124& o);
};

typedef __operation124 operation124;


struct __operation125
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation125, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation125();
	
	__operation125(::CORBA::Long _a);
	
	// Copy constructor
	__operation125(const __operation125& o);
};

typedef __operation125 operation125;


struct __operation126
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation126, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation126();
	
	__operation126(::CORBA::Long _a);
	
	// Copy constructor
	__operation126(const __operation126& o);
};

typedef __operation126 operation126;


struct __operation127
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation127, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation127();
	
	__operation127(::CORBA::Long _a);
	
	// Copy constructor
	__operation127(const __operation127& o);
};

typedef __operation127 operation127;


struct __operation128
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation128, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation128();
	
	__operation128(::CORBA::Long _a);
	
	// Copy constructor
	__operation128(const __operation128& o);
};

typedef __operation128 operation128;


struct __operation129
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation129, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation129();
	
	__operation129(::CORBA::Long _a);
	
	// Copy constructor
	__operation129(const __operation129& o);
};

typedef __operation129 operation129;


struct __operation130
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation130, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation130();
	
	__operation130(::CORBA::Long _a);
	
	// Copy constructor
	__operation130(const __operation130& o);
};

typedef __operation130 operation130;


struct __operation131
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation131, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation131();
	
	__operation131(::CORBA::Long _a);
	
	// Copy constructor
	__operation131(const __operation131& o);
};

typedef __operation131 operation131;


struct __operation132
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation132, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation132();
	
	__operation132(::CORBA::Long _a);
	
	// Copy constructor
	__operation132(const __operation132& o);
};

typedef __operation132 operation132;


struct __operation133
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation133, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation133();
	
	__operation133(::CORBA::Long _a);
	
	// Copy constructor
	__operation133(const __operation133& o);
};

typedef __operation133 operation133;


struct __operation134
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation134, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation134();
	
	__operation134(::CORBA::Long _a);
	
	// Copy constructor
	__operation134(const __operation134& o);
};

typedef __operation134 operation134;


struct __operation135
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation135, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation135();
	
	__operation135(::CORBA::Long _a);
	
	// Copy constructor
	__operation135(const __operation135& o);
};

typedef __operation135 operation135;


struct __operation136
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation136, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation136();
	
	__operation136(::CORBA::Long _a);
	
	// Copy constructor
	__operation136(const __operation136& o);
};

typedef __operation136 operation136;


struct __operation137
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation137, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation137();
	
	__operation137(::CORBA::Long _a);
	
	// Copy constructor
	__operation137(const __operation137& o);
};

typedef __operation137 operation137;


struct __operation138
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation138, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation138();
	
	__operation138(::CORBA::Long _a);
	
	// Copy constructor
	__operation138(const __operation138& o);
};

typedef __operation138 operation138;


struct __operation139
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation139, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation139();
	
	__operation139(::CORBA::Long _a);
	
	// Copy constructor
	__operation139(const __operation139& o);
};

typedef __operation139 operation139;


struct __operation140
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation140, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation140();
	
	__operation140(::CORBA::Long _a);
	
	// Copy constructor
	__operation140(const __operation140& o);
};

typedef __operation140 operation140;


struct __operation141
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation141, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation141();
	
	__operation141(::CORBA::Long _a);
	
	// Copy constructor
	__operation141(const __operation141& o);
};

typedef __operation141 operation141;


struct __operation142
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation142, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation142();
	
	__operation142(::CORBA::Long _a);
	
	// Copy constructor
	__operation142(const __operation142& o);
};

typedef __operation142 operation142;


struct __operation143
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation143, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation143();
	
	__operation143(::CORBA::Long _a);
	
	// Copy constructor
	__operation143(const __operation143& o);
};

typedef __operation143 operation143;


struct __operation144
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation144, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation144();
	
	__operation144(::CORBA::Long _a);
	
	// Copy constructor
	__operation144(const __operation144& o);
};

typedef __operation144 operation144;


struct __operation145
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation145, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation145();
	
	__operation145(::CORBA::Long _a);
	
	// Copy constructor
	__operation145(const __operation145& o);
};

typedef __operation145 operation145;


struct __operation146
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation146, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation146();
	
	__operation146(::CORBA::Long _a);
	
	// Copy constructor
	__operation146(const __operation146& o);
};

typedef __operation146 operation146;


struct __operation147
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation147, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation147();
	
	__operation147(::CORBA::Long _a);
	
	// Copy constructor
	__operation147(const __operation147& o);
};

typedef __operation147 operation147;


struct __operation148
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation148, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation148();
	
	__operation148(::CORBA::Long _a);
	
	// Copy constructor
	__operation148(const __operation148& o);
};

typedef __operation148 operation148;


struct __operation149
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation149, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation149();
	
	__operation149(::CORBA::Long _a);
	
	// Copy constructor
	__operation149(const __operation149& o);
};

typedef __operation149 operation149;


struct __operation150
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation150, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation150();
	
	__operation150(::CORBA::Long _a);
	
	// Copy constructor
	__operation150(const __operation150& o);
};

typedef __operation150 operation150;


struct __operation151
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation151, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation151();
	
	__operation151(::CORBA::Long _a);
	
	// Copy constructor
	__operation151(const __operation151& o);
};

typedef __operation151 operation151;


struct __operation152
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation152, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation152();
	
	__operation152(::CORBA::Long _a);
	
	// Copy constructor
	__operation152(const __operation152& o);
};

typedef __operation152 operation152;


struct __operation153
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation153, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation153();
	
	__operation153(::CORBA::Long _a);
	
	// Copy constructor
	__operation153(const __operation153& o);
};

typedef __operation153 operation153;


struct __operation154
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation154, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation154();
	
	__operation154(::CORBA::Long _a);
	
	// Copy constructor
	__operation154(const __operation154& o);
};

typedef __operation154 operation154;


struct __operation155
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation155, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation155();
	
	__operation155(::CORBA::Long _a);
	
	// Copy constructor
	__operation155(const __operation155& o);
};

typedef __operation155 operation155;


struct __operation156
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation156, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation156();
	
	__operation156(::CORBA::Long _a);
	
	// Copy constructor
	__operation156(const __operation156& o);
};

typedef __operation156 operation156;


struct __operation157
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation157, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation157();
	
	__operation157(::CORBA::Long _a);
	
	// Copy constructor
	__operation157(const __operation157& o);
};

typedef __operation157 operation157;


struct __operation158
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation158, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation158();
	
	__operation158(::CORBA::Long _a);
	
	// Copy constructor
	__operation158(const __operation158& o);
};

typedef __operation158 operation158;


struct __operation159
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation159, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation159();
	
	__operation159(::CORBA::Long _a);
	
	// Copy constructor
	__operation159(const __operation159& o);
};

typedef __operation159 operation159;


struct __operation160
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation160, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation160();
	
	__operation160(::CORBA::Long _a);
	
	// Copy constructor
	__operation160(const __operation160& o);
};

typedef __operation160 operation160;


struct __operation161
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation161, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation161();
	
	__operation161(::CORBA::Long _a);
	
	// Copy constructor
	__operation161(const __operation161& o);
};

typedef __operation161 operation161;


struct __operation162
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation162, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation162();
	
	__operation162(::CORBA::Long _a);
	
	// Copy constructor
	__operation162(const __operation162& o);
};

typedef __operation162 operation162;


struct __operation163
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation163, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation163();
	
	__operation163(::CORBA::Long _a);
	
	// Copy constructor
	__operation163(const __operation163& o);
};

typedef __operation163 operation163;


struct __operation164
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation164, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation164();
	
	__operation164(::CORBA::Long _a);
	
	// Copy constructor
	__operation164(const __operation164& o);
};

typedef __operation164 operation164;


struct __operation165
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation165, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation165();
	
	__operation165(::CORBA::Long _a);
	
	// Copy constructor
	__operation165(const __operation165& o);
};

typedef __operation165 operation165;


struct __operation166
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation166, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation166();
	
	__operation166(::CORBA::Long _a);
	
	// Copy constructor
	__operation166(const __operation166& o);
};

typedef __operation166 operation166;


struct __operation167
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation167, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation167();
	
	__operation167(::CORBA::Long _a);
	
	// Copy constructor
	__operation167(const __operation167& o);
};

typedef __operation167 operation167;


struct __operation168
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation168, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation168();
	
	__operation168(::CORBA::Long _a);
	
	// Copy constructor
	__operation168(const __operation168& o);
};

typedef __operation168 operation168;


struct __operation169
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation169, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation169();
	
	__operation169(::CORBA::Long _a);
	
	// Copy constructor
	__operation169(const __operation169& o);
};

typedef __operation169 operation169;


struct __operation170
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation170, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation170();
	
	__operation170(::CORBA::Long _a);
	
	// Copy constructor
	__operation170(const __operation170& o);
};

typedef __operation170 operation170;


struct __operation171
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation171, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation171();
	
	__operation171(::CORBA::Long _a);
	
	// Copy constructor
	__operation171(const __operation171& o);
};

typedef __operation171 operation171;


struct __operation172
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation172, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation172();
	
	__operation172(::CORBA::Long _a);
	
	// Copy constructor
	__operation172(const __operation172& o);
};

typedef __operation172 operation172;


struct __operation173
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation173, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation173();
	
	__operation173(::CORBA::Long _a);
	
	// Copy constructor
	__operation173(const __operation173& o);
};

typedef __operation173 operation173;


struct __operation174
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation174, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation174();
	
	__operation174(::CORBA::Long _a);
	
	// Copy constructor
	__operation174(const __operation174& o);
};

typedef __operation174 operation174;


struct __operation175
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation175, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation175();
	
	__operation175(::CORBA::Long _a);
	
	// Copy constructor
	__operation175(const __operation175& o);
};

typedef __operation175 operation175;


struct __operation176
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation176, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation176();
	
	__operation176(::CORBA::Long _a);
	
	// Copy constructor
	__operation176(const __operation176& o);
};

typedef __operation176 operation176;


struct __operation177
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation177, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation177();
	
	__operation177(::CORBA::Long _a);
	
	// Copy constructor
	__operation177(const __operation177& o);
};

typedef __operation177 operation177;


struct __operation178
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation178, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation178();
	
	__operation178(::CORBA::Long _a);
	
	// Copy constructor
	__operation178(const __operation178& o);
};

typedef __operation178 operation178;


struct __operation179
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation179, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation179();
	
	__operation179(::CORBA::Long _a);
	
	// Copy constructor
	__operation179(const __operation179& o);
};

typedef __operation179 operation179;


struct __operation180
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation180, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation180();
	
	__operation180(::CORBA::Long _a);
	
	// Copy constructor
	__operation180(const __operation180& o);
};

typedef __operation180 operation180;


struct __operation181
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation181, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation181();
	
	__operation181(::CORBA::Long _a);
	
	// Copy constructor
	__operation181(const __operation181& o);
};

typedef __operation181 operation181;


struct __operation182
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation182, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation182();
	
	__operation182(::CORBA::Long _a);
	
	// Copy constructor
	__operation182(const __operation182& o);
};

typedef __operation182 operation182;


struct __operation183
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation183, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation183();
	
	__operation183(::CORBA::Long _a);
	
	// Copy constructor
	__operation183(const __operation183& o);
};

typedef __operation183 operation183;


struct __operation184
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation184, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation184();
	
	__operation184(::CORBA::Long _a);
	
	// Copy constructor
	__operation184(const __operation184& o);
};

typedef __operation184 operation184;


struct __operation185
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation185, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation185();
	
	__operation185(::CORBA::Long _a);
	
	// Copy constructor
	__operation185(const __operation185& o);
};

typedef __operation185 operation185;


struct __operation186
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation186, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation186();
	
	__operation186(::CORBA::Long _a);
	
	// Copy constructor
	__operation186(const __operation186& o);
};

typedef __operation186 operation186;


struct __operation187
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation187, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation187();
	
	__operation187(::CORBA::Long _a);
	
	// Copy constructor
	__operation187(const __operation187& o);
};

typedef __operation187 operation187;


struct __operation188
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation188, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation188();
	
	__operation188(::CORBA::Long _a);
	
	// Copy constructor
	__operation188(const __operation188& o);
};

typedef __operation188 operation188;


struct __operation189
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation189, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation189();
	
	__operation189(::CORBA::Long _a);
	
	// Copy constructor
	__operation189(const __operation189& o);
};

typedef __operation189 operation189;


struct __operation190
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation190, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation190();
	
	__operation190(::CORBA::Long _a);
	
	// Copy constructor
	__operation190(const __operation190& o);
};

typedef __operation190 operation190;


struct __operation191
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation191, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation191();
	
	__operation191(::CORBA::Long _a);
	
	// Copy constructor
	__operation191(const __operation191& o);
};

typedef __operation191 operation191;


struct __operation192
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation192, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation192();
	
	__operation192(::CORBA::Long _a);
	
	// Copy constructor
	__operation192(const __operation192& o);
};

typedef __operation192 operation192;


struct __operation193
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation193, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation193();
	
	__operation193(::CORBA::Long _a);
	
	// Copy constructor
	__operation193(const __operation193& o);
};

typedef __operation193 operation193;


struct __operation194
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation194, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation194();
	
	__operation194(::CORBA::Long _a);
	
	// Copy constructor
	__operation194(const __operation194& o);
};

typedef __operation194 operation194;


struct __operation195
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation195, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation195();
	
	__operation195(::CORBA::Long _a);
	
	// Copy constructor
	__operation195(const __operation195& o);
};

typedef __operation195 operation195;


struct __operation196
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation196, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation196();
	
	__operation196(::CORBA::Long _a);
	
	// Copy constructor
	__operation196(const __operation196& o);
};

typedef __operation196 operation196;


struct __operation197
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation197, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation197();
	
	__operation197(::CORBA::Long _a);
	
	// Copy constructor
	__operation197(const __operation197& o);
};

typedef __operation197 operation197;


struct __operation198
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation198, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation198();
	
	__operation198(::CORBA::Long _a);
	
	// Copy constructor
	__operation198(const __operation198& o);
};

typedef __operation198 operation198;


struct __operation199
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long > > _arg_list;

	typedef corbasim::adapted::member< __operation199, 0 > a_corbasim_member;

	::CORBA::Long a;
	
	
	__operation199();
	
	__operation199(::CORBA::Long _a);
	
	// Copy constructor
	__operation199(const __operation199& o);
};

typedef __operation199 operation199;

} // Huge

} // _corbasim_Test


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
};

typedef __op1 op1;


struct __op2
{
	typedef boost::mpl::vector<  > _arg_list;


	
	AAAAAAAAA::ESS_var _return;
	
	__op2();
	
	
	// Copy constructor
	__op2(const __op2& o);
};

typedef __op2 op2;

} // IIIIIIIIII

} // _corbasim_AAAAAAAAA


namespace _corbasim_SimpleExample 
{


struct St
{
	typedef corbasim::adapted::member< ::SimpleExample::St, 0 > l_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::St, 1 > ss_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::St, 2 > b_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::St, 3 > uniii_corbasim_member;
	
};


namespace Test 
{
struct __operation1
{
	typedef boost::mpl::vector< corbasim::Arg_IN< ::CORBA::Long >, corbasim::Arg_IN< ::CORBA::Long >, corbasim::Arg_IN< const SimpleExample::St& > > _arg_list;

	typedef corbasim::adapted::member< __operation1, 0 > a_corbasim_member;
	typedef corbasim::adapted::member< __operation1, 1 > b_corbasim_member;
	typedef corbasim::adapted::member< __operation1, 2 > c_corbasim_member;

	::CORBA::Long a;
	::CORBA::Long b;
	SimpleExample::St c;
	
	
	__operation1();
	
	__operation1(::CORBA::Long _a, ::CORBA::Long _b, const SimpleExample::St& _c);
	
	// Copy constructor
	__operation1(const __operation1& o);
};

typedef __operation1 operation1;




struct __operation4
{
	typedef boost::mpl::vector< corbasim::Arg_IN< SimpleExample::Test_ptr > > _arg_list;

	typedef corbasim::adapted::member< __operation4, 0 > a_corbasim_member;

	SimpleExample::Test_var a;
	
	
	__operation4();
	
	__operation4(SimpleExample::Test_ptr _a);
	
	// Copy constructor
	__operation4(const __operation4& o);
};

typedef __operation4 operation4;

} // Test


struct Hijo
{
	typedef corbasim::adapted::member< ::SimpleExample::Hijo, 0 > b_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::Hijo, 1 > l_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::Hijo, 2 > s_corbasim_member;
	
};


struct Padre
{
	typedef corbasim::adapted::member< ::SimpleExample::Padre, 0 > h_corbasim_member;
	
};




struct Abuelo
{
	typedef corbasim::adapted::member< ::SimpleExample::Abuelo, 0 > p_corbasim_member;
	typedef corbasim::adapted::member< ::SimpleExample::Abuelo, 1 > tt_corbasim_member;
	
};

} // _corbasim_SimpleExample


namespace _corbasim_StringTest 
{








struct StructWithStrings
{
	typedef corbasim::adapted::member< ::StringTest::StructWithStrings, 0 > str_corbasim_member;
	typedef corbasim::adapted::member< ::StringTest::StructWithStrings, 1 > nam_corbasim_member;
	typedef corbasim::adapted::member< ::StringTest::StructWithStrings, 2 > id_corbasim_member;
	
};


namespace InterfaceString 
{
struct __operation1
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

	typedef corbasim::adapted::member< __operation1, 0 > s_corbasim_member;

	::corbasim::orbimpl::String_Manager s;
	
	
	__operation1();
	
	__operation1(const char* _s);
	
	// Copy constructor
	__operation1(const __operation1& o);
};

typedef __operation1 operation1;


struct __operation2
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

	typedef corbasim::adapted::member< __operation2, 0 > n_corbasim_member;

	::corbasim::orbimpl::String_Manager n;
	
	
	__operation2();
	
	__operation2(const char* _n);
	
	// Copy constructor
	__operation2(const __operation2& o);
};

typedef __operation2 operation2;


struct __operation3
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const StringTest::NameSeq& > > _arg_list;

	typedef corbasim::adapted::member< __operation3, 0 > n_corbasim_member;

	StringTest::NameSeq n;
	
	
	__operation3();
	
	__operation3(const StringTest::NameSeq& _n);
	
	// Copy constructor
	__operation3(const __operation3& o);
};

typedef __operation3 operation3;


struct __operation4
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const StringTest::StructWithStrings& > > _arg_list;

	typedef corbasim::adapted::member< __operation4, 0 > n_corbasim_member;

	StringTest::StructWithStrings n;
	
	
	__operation4();
	
	__operation4(const StringTest::StructWithStrings& _n);
	
	// Copy constructor
	__operation4(const __operation4& o);
};

typedef __operation4 operation4;


struct __operation5
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const char* > > _arg_list;

	typedef corbasim::adapted::member< __operation5, 0 > n_corbasim_member;

	::corbasim::orbimpl::String_Manager n;
	
	
	__operation5();
	
	__operation5(const char* _n);
	
	// Copy constructor
	__operation5(const __operation5& o);
};

typedef __operation5 operation5;


struct __operation6
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const StringTest::NameIDSeq& > > _arg_list;

	typedef corbasim::adapted::member< __operation6, 0 > n_corbasim_member;

	StringTest::NameIDSeq n;
	
	
	__operation6();
	
	__operation6(const StringTest::NameIDSeq& _n);
	
	// Copy constructor
	__operation6(const __operation6& o);
};

typedef __operation6 operation6;

} // InterfaceString

} // _corbasim_StringTest


namespace _corbasim_MyModule 
{








struct MyStruct
{
	typedef corbasim::adapted::member< ::MyModule::MyStruct, 0 > a_corbasim_member;
	
};


namespace MyInterface 
{
struct __operation
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const MyModule::MyUnion& > > _arg_list;

	typedef corbasim::adapted::member< __operation, 0 > uni_corbasim_member;

	MyModule::MyUnion uni;
	
	
	__operation();
	
	__operation(const MyModule::MyUnion& _uni);
	
	// Copy constructor
	__operation(const __operation& o);
};

typedef __operation operation;


struct __operation1
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const MyModule::MyUnion2& > > _arg_list;

	typedef corbasim::adapted::member< __operation1, 0 > uni_corbasim_member;

	MyModule::MyUnion2 uni;
	
	
	__operation1();
	
	__operation1(const MyModule::MyUnion2& _uni);
	
	// Copy constructor
	__operation1(const __operation1& o);
};

typedef __operation1 operation1;


struct __operation2
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const MyModule::MyStruct& > > _arg_list;

	typedef corbasim::adapted::member< __operation2, 0 > uni_corbasim_member;

	MyModule::MyStruct uni;
	
	
	__operation2();
	
	__operation2(const MyModule::MyStruct& _uni);
	
	// Copy constructor
	__operation2(const __operation2& o);
};

typedef __operation2 operation2;


struct __operation3
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const MyModule::MyUnion3& > > _arg_list;

	typedef corbasim::adapted::member< __operation3, 0 > uni_corbasim_member;

	MyModule::MyUnion3 uni;
	
	
	__operation3();
	
	__operation3(const MyModule::MyUnion3& _uni);
	
	// Copy constructor
	__operation3(const __operation3& o);
};

typedef __operation3 operation3;

} // MyInterface

} // _corbasim_MyModule


namespace _corbasim_Test 
{


struct St
{
	typedef corbasim::adapted::member< ::Test::St, 0 > a_corbasim_member;
	typedef corbasim::adapted::member< ::Test::St, 1 > b_corbasim_member;
	typedef corbasim::adapted::member< ::Test::St, 2 > reffff_corbasim_member;
	
};


struct St2
{
	typedef corbasim::adapted::member< ::Test::St2, 0 > a_corbasim_member;
	typedef corbasim::adapted::member< ::Test::St2, 1 > b_corbasim_member;
	typedef corbasim::adapted::member< ::Test::St2, 2 > c_corbasim_member;
	typedef corbasim::adapted::member< ::Test::St2, 3 > unsupported_corbasim_member;
	
};


namespace Prueba 
{
struct __operacion1
{
	typedef boost::mpl::vector< corbasim::Arg_IN< const Test::St2& >, corbasim::Arg_IN< const Test::St& > > _arg_list;

	typedef corbasim::adapted::member< __operacion1, 0 > a_corbasim_member;
	typedef corbasim::adapted::member< __operacion1, 1 > b_corbasim_member;

	Test::St2 a;
	Test::St b;
	
	
	__operacion1();
	
	__operacion1(const Test::St2& _a, const Test::St& _b);
	
	// Copy constructor
	__operacion1(const __operacion1& o);
};

typedef __operacion1 operacion1;


struct __operacion2
{
	typedef boost::mpl::vector< corbasim::Arg_IN< Test::Prueba_ptr > > _arg_list;

	typedef corbasim::adapted::member< __operacion2, 0 > myref_corbasim_member;

	Test::Prueba_var myref;
	
	
	__operacion2();
	
	__operacion2(Test::Prueba_ptr _myref);
	
	// Copy constructor
	__operacion2(const __operacion2& o);
};

typedef __operacion2 operacion2;


struct __operacion3
{
	typedef boost::mpl::vector<  > _arg_list;


	
	
	__operacion3();
	
	
	// Copy constructor
	__operacion3(const __operacion3& o);
};

typedef __operacion3 operacion3;

} // Prueba

} // _corbasim_Test





namespace corbasim
{
namespace adapted
{

template < >
struct interface < HelloApp::Hello >
{
	typedef cs_mpl::list< _corbasim_HelloApp::Hello::sayHello, cs_mpl::list< _corbasim_HelloApp::Hello::sayHelloTo, cs_mpl::list< _corbasim_HelloApp::Hello::shutdown  >  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: HelloApp::Hello::sayHello
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_HelloApp::Hello::sayHello,
	( ::corbasim::orbimpl::String_Manager, _return)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_HelloApp::Hello::sayHello >
{
	typedef _corbasim_HelloApp::Hello::sayHello Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
value._return = ref->sayHello();
    }
};

} // adapted
} // corbasim


// OperationDef: HelloApp::Hello::sayHelloTo
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_HelloApp::Hello::sayHelloTo,
	( HelloApp::Names, people)
	( ::corbasim::orbimpl::String_Manager, _return)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_HelloApp::Hello::sayHelloTo >
{
	typedef _corbasim_HelloApp::Hello::sayHelloTo Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
value._return = ref->sayHelloTo(value.people);
    }
};

} // adapted
} // corbasim


// OperationDef: HelloApp::Hello::shutdown
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_HelloApp::Hello::shutdown,
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_HelloApp::Hello::shutdown > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_HelloApp::Hello::shutdown >
{
	typedef _corbasim_HelloApp::Hello::shutdown Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->shutdown();
    }
};

} // adapted
} // corbasim





namespace corbasim
{
namespace adapted
{

template < >
struct interface < Test::Huge >
{
	typedef cs_mpl::list< _corbasim_Test::Huge::operation1, cs_mpl::list< _corbasim_Test::Huge::operation2, cs_mpl::list< _corbasim_Test::Huge::operation3, cs_mpl::list< _corbasim_Test::Huge::operation4, cs_mpl::list< _corbasim_Test::Huge::operation5, cs_mpl::list< _corbasim_Test::Huge::operation6, cs_mpl::list< _corbasim_Test::Huge::operation7, cs_mpl::list< _corbasim_Test::Huge::operation8, cs_mpl::list< _corbasim_Test::Huge::operation9, cs_mpl::list< _corbasim_Test::Huge::operation10, cs_mpl::list< _corbasim_Test::Huge::operation11, cs_mpl::list< _corbasim_Test::Huge::operation12, cs_mpl::list< _corbasim_Test::Huge::operation13, cs_mpl::list< _corbasim_Test::Huge::operation14, cs_mpl::list< _corbasim_Test::Huge::operation15, cs_mpl::list< _corbasim_Test::Huge::operation16, cs_mpl::list< _corbasim_Test::Huge::operation17, cs_mpl::list< _corbasim_Test::Huge::operation18, cs_mpl::list< _corbasim_Test::Huge::operation19, cs_mpl::list< _corbasim_Test::Huge::operation20, cs_mpl::list< _corbasim_Test::Huge::operation21, cs_mpl::list< _corbasim_Test::Huge::operation22, cs_mpl::list< _corbasim_Test::Huge::operation23, cs_mpl::list< _corbasim_Test::Huge::operation24, cs_mpl::list< _corbasim_Test::Huge::operation25, cs_mpl::list< _corbasim_Test::Huge::operation26, cs_mpl::list< _corbasim_Test::Huge::operation27, cs_mpl::list< _corbasim_Test::Huge::operation28, cs_mpl::list< _corbasim_Test::Huge::operation29, cs_mpl::list< _corbasim_Test::Huge::operation30, cs_mpl::list< _corbasim_Test::Huge::operation31, cs_mpl::list< _corbasim_Test::Huge::operation32, cs_mpl::list< _corbasim_Test::Huge::operation33, cs_mpl::list< _corbasim_Test::Huge::operation34, cs_mpl::list< _corbasim_Test::Huge::operation35, cs_mpl::list< _corbasim_Test::Huge::operation36, cs_mpl::list< _corbasim_Test::Huge::operation37, cs_mpl::list< _corbasim_Test::Huge::operation38, cs_mpl::list< _corbasim_Test::Huge::operation39, cs_mpl::list< _corbasim_Test::Huge::operation40, cs_mpl::list< _corbasim_Test::Huge::operation41, cs_mpl::list< _corbasim_Test::Huge::operation42, cs_mpl::list< _corbasim_Test::Huge::operation43, cs_mpl::list< _corbasim_Test::Huge::operation44, cs_mpl::list< _corbasim_Test::Huge::operation45, cs_mpl::list< _corbasim_Test::Huge::operation46, cs_mpl::list< _corbasim_Test::Huge::operation47, cs_mpl::list< _corbasim_Test::Huge::operation48, cs_mpl::list< _corbasim_Test::Huge::operation49, cs_mpl::list< _corbasim_Test::Huge::operation50, cs_mpl::list< _corbasim_Test::Huge::operation51, cs_mpl::list< _corbasim_Test::Huge::operation52, cs_mpl::list< _corbasim_Test::Huge::operation53, cs_mpl::list< _corbasim_Test::Huge::operation54, cs_mpl::list< _corbasim_Test::Huge::operation55, cs_mpl::list< _corbasim_Test::Huge::operation56, cs_mpl::list< _corbasim_Test::Huge::operation57, cs_mpl::list< _corbasim_Test::Huge::operation58, cs_mpl::list< _corbasim_Test::Huge::operation59, cs_mpl::list< _corbasim_Test::Huge::operation60, cs_mpl::list< _corbasim_Test::Huge::operation61, cs_mpl::list< _corbasim_Test::Huge::operation62, cs_mpl::list< _corbasim_Test::Huge::operation63, cs_mpl::list< _corbasim_Test::Huge::operation64, cs_mpl::list< _corbasim_Test::Huge::operation65, cs_mpl::list< _corbasim_Test::Huge::operation66, cs_mpl::list< _corbasim_Test::Huge::operation67, cs_mpl::list< _corbasim_Test::Huge::operation68, cs_mpl::list< _corbasim_Test::Huge::operation69, cs_mpl::list< _corbasim_Test::Huge::operation70, cs_mpl::list< _corbasim_Test::Huge::operation71, cs_mpl::list< _corbasim_Test::Huge::operation72, cs_mpl::list< _corbasim_Test::Huge::operation73, cs_mpl::list< _corbasim_Test::Huge::operation74, cs_mpl::list< _corbasim_Test::Huge::operation75, cs_mpl::list< _corbasim_Test::Huge::operation76, cs_mpl::list< _corbasim_Test::Huge::operation77, cs_mpl::list< _corbasim_Test::Huge::operation78, cs_mpl::list< _corbasim_Test::Huge::operation79, cs_mpl::list< _corbasim_Test::Huge::operation80, cs_mpl::list< _corbasim_Test::Huge::operation81, cs_mpl::list< _corbasim_Test::Huge::operation82, cs_mpl::list< _corbasim_Test::Huge::operation83, cs_mpl::list< _corbasim_Test::Huge::operation84, cs_mpl::list< _corbasim_Test::Huge::operation85, cs_mpl::list< _corbasim_Test::Huge::operation86, cs_mpl::list< _corbasim_Test::Huge::operation87, cs_mpl::list< _corbasim_Test::Huge::operation88, cs_mpl::list< _corbasim_Test::Huge::operation89, cs_mpl::list< _corbasim_Test::Huge::operation90, cs_mpl::list< _corbasim_Test::Huge::operation91, cs_mpl::list< _corbasim_Test::Huge::operation92, cs_mpl::list< _corbasim_Test::Huge::operation93, cs_mpl::list< _corbasim_Test::Huge::operation94, cs_mpl::list< _corbasim_Test::Huge::operation95, cs_mpl::list< _corbasim_Test::Huge::operation96, cs_mpl::list< _corbasim_Test::Huge::operation97, cs_mpl::list< _corbasim_Test::Huge::operation98, cs_mpl::list< _corbasim_Test::Huge::operation99, cs_mpl::list< _corbasim_Test::Huge::operation100, cs_mpl::list< _corbasim_Test::Huge::operation101, cs_mpl::list< _corbasim_Test::Huge::operation102, cs_mpl::list< _corbasim_Test::Huge::operation103, cs_mpl::list< _corbasim_Test::Huge::operation104, cs_mpl::list< _corbasim_Test::Huge::operation105, cs_mpl::list< _corbasim_Test::Huge::operation106, cs_mpl::list< _corbasim_Test::Huge::operation107, cs_mpl::list< _corbasim_Test::Huge::operation108, cs_mpl::list< _corbasim_Test::Huge::operation109, cs_mpl::list< _corbasim_Test::Huge::operation110, cs_mpl::list< _corbasim_Test::Huge::operation111, cs_mpl::list< _corbasim_Test::Huge::operation112, cs_mpl::list< _corbasim_Test::Huge::operation113, cs_mpl::list< _corbasim_Test::Huge::operation114, cs_mpl::list< _corbasim_Test::Huge::operation115, cs_mpl::list< _corbasim_Test::Huge::operation116, cs_mpl::list< _corbasim_Test::Huge::operation117, cs_mpl::list< _corbasim_Test::Huge::operation118, cs_mpl::list< _corbasim_Test::Huge::operation119, cs_mpl::list< _corbasim_Test::Huge::operation120, cs_mpl::list< _corbasim_Test::Huge::operation121, cs_mpl::list< _corbasim_Test::Huge::operation122, cs_mpl::list< _corbasim_Test::Huge::operation123, cs_mpl::list< _corbasim_Test::Huge::operation124, cs_mpl::list< _corbasim_Test::Huge::operation125, cs_mpl::list< _corbasim_Test::Huge::operation126, cs_mpl::list< _corbasim_Test::Huge::operation127, cs_mpl::list< _corbasim_Test::Huge::operation128, cs_mpl::list< _corbasim_Test::Huge::operation129, cs_mpl::list< _corbasim_Test::Huge::operation130, cs_mpl::list< _corbasim_Test::Huge::operation131, cs_mpl::list< _corbasim_Test::Huge::operation132, cs_mpl::list< _corbasim_Test::Huge::operation133, cs_mpl::list< _corbasim_Test::Huge::operation134, cs_mpl::list< _corbasim_Test::Huge::operation135, cs_mpl::list< _corbasim_Test::Huge::operation136, cs_mpl::list< _corbasim_Test::Huge::operation137, cs_mpl::list< _corbasim_Test::Huge::operation138, cs_mpl::list< _corbasim_Test::Huge::operation139, cs_mpl::list< _corbasim_Test::Huge::operation140, cs_mpl::list< _corbasim_Test::Huge::operation141, cs_mpl::list< _corbasim_Test::Huge::operation142, cs_mpl::list< _corbasim_Test::Huge::operation143, cs_mpl::list< _corbasim_Test::Huge::operation144, cs_mpl::list< _corbasim_Test::Huge::operation145, cs_mpl::list< _corbasim_Test::Huge::operation146, cs_mpl::list< _corbasim_Test::Huge::operation147, cs_mpl::list< _corbasim_Test::Huge::operation148, cs_mpl::list< _corbasim_Test::Huge::operation149, cs_mpl::list< _corbasim_Test::Huge::operation150, cs_mpl::list< _corbasim_Test::Huge::operation151, cs_mpl::list< _corbasim_Test::Huge::operation152, cs_mpl::list< _corbasim_Test::Huge::operation153, cs_mpl::list< _corbasim_Test::Huge::operation154, cs_mpl::list< _corbasim_Test::Huge::operation155, cs_mpl::list< _corbasim_Test::Huge::operation156, cs_mpl::list< _corbasim_Test::Huge::operation157, cs_mpl::list< _corbasim_Test::Huge::operation158, cs_mpl::list< _corbasim_Test::Huge::operation159, cs_mpl::list< _corbasim_Test::Huge::operation160, cs_mpl::list< _corbasim_Test::Huge::operation161, cs_mpl::list< _corbasim_Test::Huge::operation162, cs_mpl::list< _corbasim_Test::Huge::operation163, cs_mpl::list< _corbasim_Test::Huge::operation164, cs_mpl::list< _corbasim_Test::Huge::operation165, cs_mpl::list< _corbasim_Test::Huge::operation166, cs_mpl::list< _corbasim_Test::Huge::operation167, cs_mpl::list< _corbasim_Test::Huge::operation168, cs_mpl::list< _corbasim_Test::Huge::operation169, cs_mpl::list< _corbasim_Test::Huge::operation170, cs_mpl::list< _corbasim_Test::Huge::operation171, cs_mpl::list< _corbasim_Test::Huge::operation172, cs_mpl::list< _corbasim_Test::Huge::operation173, cs_mpl::list< _corbasim_Test::Huge::operation174, cs_mpl::list< _corbasim_Test::Huge::operation175, cs_mpl::list< _corbasim_Test::Huge::operation176, cs_mpl::list< _corbasim_Test::Huge::operation177, cs_mpl::list< _corbasim_Test::Huge::operation178, cs_mpl::list< _corbasim_Test::Huge::operation179, cs_mpl::list< _corbasim_Test::Huge::operation180, cs_mpl::list< _corbasim_Test::Huge::operation181, cs_mpl::list< _corbasim_Test::Huge::operation182, cs_mpl::list< _corbasim_Test::Huge::operation183, cs_mpl::list< _corbasim_Test::Huge::operation184, cs_mpl::list< _corbasim_Test::Huge::operation185, cs_mpl::list< _corbasim_Test::Huge::operation186, cs_mpl::list< _corbasim_Test::Huge::operation187, cs_mpl::list< _corbasim_Test::Huge::operation188, cs_mpl::list< _corbasim_Test::Huge::operation189, cs_mpl::list< _corbasim_Test::Huge::operation190, cs_mpl::list< _corbasim_Test::Huge::operation191, cs_mpl::list< _corbasim_Test::Huge::operation192, cs_mpl::list< _corbasim_Test::Huge::operation193, cs_mpl::list< _corbasim_Test::Huge::operation194, cs_mpl::list< _corbasim_Test::Huge::operation195, cs_mpl::list< _corbasim_Test::Huge::operation196, cs_mpl::list< _corbasim_Test::Huge::operation197, cs_mpl::list< _corbasim_Test::Huge::operation198, cs_mpl::list< _corbasim_Test::Huge::operation199  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: Test::Huge::operation1
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation1,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation1 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation1 >
{
	typedef _corbasim_Test::Huge::operation1 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation1(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation2
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation2,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation2 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation2 >
{
	typedef _corbasim_Test::Huge::operation2 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation2(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation3
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation3,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation3 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation3 >
{
	typedef _corbasim_Test::Huge::operation3 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation3(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation4
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation4,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation4 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation4 >
{
	typedef _corbasim_Test::Huge::operation4 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation4(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation5
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation5,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation5 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation5 >
{
	typedef _corbasim_Test::Huge::operation5 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation5(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation6
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation6,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation6 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation6 >
{
	typedef _corbasim_Test::Huge::operation6 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation6(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation7
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation7,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation7 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation7 >
{
	typedef _corbasim_Test::Huge::operation7 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation7(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation8
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation8,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation8 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation8 >
{
	typedef _corbasim_Test::Huge::operation8 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation8(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation9
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation9,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation9 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation9 >
{
	typedef _corbasim_Test::Huge::operation9 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation9(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation10
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation10,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation10 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation10 >
{
	typedef _corbasim_Test::Huge::operation10 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation10(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation11
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation11,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation11 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation11 >
{
	typedef _corbasim_Test::Huge::operation11 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation11(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation12
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation12,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation12 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation12 >
{
	typedef _corbasim_Test::Huge::operation12 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation12(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation13
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation13,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation13 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation13 >
{
	typedef _corbasim_Test::Huge::operation13 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation13(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation14
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation14,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation14 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation14 >
{
	typedef _corbasim_Test::Huge::operation14 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation14(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation15
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation15,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation15 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation15 >
{
	typedef _corbasim_Test::Huge::operation15 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation15(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation16
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation16,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation16 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation16 >
{
	typedef _corbasim_Test::Huge::operation16 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation16(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation17
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation17,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation17 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation17 >
{
	typedef _corbasim_Test::Huge::operation17 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation17(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation18
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation18,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation18 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation18 >
{
	typedef _corbasim_Test::Huge::operation18 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation18(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation19
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation19,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation19 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation19 >
{
	typedef _corbasim_Test::Huge::operation19 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation19(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation20
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation20,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation20 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation20 >
{
	typedef _corbasim_Test::Huge::operation20 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation20(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation21
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation21,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation21 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation21 >
{
	typedef _corbasim_Test::Huge::operation21 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation21(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation22
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation22,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation22 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation22 >
{
	typedef _corbasim_Test::Huge::operation22 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation22(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation23
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation23,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation23 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation23 >
{
	typedef _corbasim_Test::Huge::operation23 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation23(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation24
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation24,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation24 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation24 >
{
	typedef _corbasim_Test::Huge::operation24 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation24(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation25
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation25,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation25 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation25 >
{
	typedef _corbasim_Test::Huge::operation25 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation25(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation26
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation26,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation26 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation26 >
{
	typedef _corbasim_Test::Huge::operation26 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation26(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation27
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation27,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation27 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation27 >
{
	typedef _corbasim_Test::Huge::operation27 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation27(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation28
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation28,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation28 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation28 >
{
	typedef _corbasim_Test::Huge::operation28 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation28(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation29
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation29,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation29 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation29 >
{
	typedef _corbasim_Test::Huge::operation29 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation29(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation30
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation30,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation30 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation30 >
{
	typedef _corbasim_Test::Huge::operation30 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation30(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation31
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation31,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation31 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation31 >
{
	typedef _corbasim_Test::Huge::operation31 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation31(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation32
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation32,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation32 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation32 >
{
	typedef _corbasim_Test::Huge::operation32 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation32(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation33
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation33,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation33 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation33 >
{
	typedef _corbasim_Test::Huge::operation33 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation33(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation34
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation34,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation34 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation34 >
{
	typedef _corbasim_Test::Huge::operation34 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation34(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation35
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation35,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation35 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation35 >
{
	typedef _corbasim_Test::Huge::operation35 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation35(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation36
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation36,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation36 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation36 >
{
	typedef _corbasim_Test::Huge::operation36 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation36(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation37
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation37,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation37 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation37 >
{
	typedef _corbasim_Test::Huge::operation37 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation37(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation38
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation38,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation38 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation38 >
{
	typedef _corbasim_Test::Huge::operation38 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation38(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation39
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation39,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation39 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation39 >
{
	typedef _corbasim_Test::Huge::operation39 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation39(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation40
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation40,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation40 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation40 >
{
	typedef _corbasim_Test::Huge::operation40 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation40(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation41
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation41,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation41 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation41 >
{
	typedef _corbasim_Test::Huge::operation41 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation41(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation42
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation42,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation42 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation42 >
{
	typedef _corbasim_Test::Huge::operation42 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation42(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation43
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation43,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation43 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation43 >
{
	typedef _corbasim_Test::Huge::operation43 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation43(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation44
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation44,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation44 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation44 >
{
	typedef _corbasim_Test::Huge::operation44 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation44(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation45
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation45,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation45 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation45 >
{
	typedef _corbasim_Test::Huge::operation45 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation45(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation46
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation46,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation46 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation46 >
{
	typedef _corbasim_Test::Huge::operation46 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation46(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation47
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation47,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation47 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation47 >
{
	typedef _corbasim_Test::Huge::operation47 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation47(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation48
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation48,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation48 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation48 >
{
	typedef _corbasim_Test::Huge::operation48 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation48(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation49
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation49,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation49 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation49 >
{
	typedef _corbasim_Test::Huge::operation49 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation49(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation50
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation50,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation50 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation50 >
{
	typedef _corbasim_Test::Huge::operation50 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation50(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation51
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation51,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation51 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation51 >
{
	typedef _corbasim_Test::Huge::operation51 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation51(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation52
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation52,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation52 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation52 >
{
	typedef _corbasim_Test::Huge::operation52 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation52(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation53
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation53,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation53 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation53 >
{
	typedef _corbasim_Test::Huge::operation53 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation53(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation54
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation54,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation54 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation54 >
{
	typedef _corbasim_Test::Huge::operation54 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation54(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation55
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation55,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation55 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation55 >
{
	typedef _corbasim_Test::Huge::operation55 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation55(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation56
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation56,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation56 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation56 >
{
	typedef _corbasim_Test::Huge::operation56 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation56(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation57
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation57,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation57 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation57 >
{
	typedef _corbasim_Test::Huge::operation57 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation57(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation58
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation58,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation58 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation58 >
{
	typedef _corbasim_Test::Huge::operation58 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation58(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation59
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation59,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation59 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation59 >
{
	typedef _corbasim_Test::Huge::operation59 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation59(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation60
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation60,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation60 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation60 >
{
	typedef _corbasim_Test::Huge::operation60 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation60(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation61
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation61,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation61 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation61 >
{
	typedef _corbasim_Test::Huge::operation61 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation61(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation62
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation62,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation62 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation62 >
{
	typedef _corbasim_Test::Huge::operation62 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation62(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation63
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation63,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation63 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation63 >
{
	typedef _corbasim_Test::Huge::operation63 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation63(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation64
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation64,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation64 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation64 >
{
	typedef _corbasim_Test::Huge::operation64 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation64(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation65
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation65,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation65 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation65 >
{
	typedef _corbasim_Test::Huge::operation65 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation65(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation66
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation66,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation66 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation66 >
{
	typedef _corbasim_Test::Huge::operation66 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation66(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation67
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation67,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation67 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation67 >
{
	typedef _corbasim_Test::Huge::operation67 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation67(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation68
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation68,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation68 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation68 >
{
	typedef _corbasim_Test::Huge::operation68 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation68(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation69
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation69,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation69 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation69 >
{
	typedef _corbasim_Test::Huge::operation69 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation69(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation70
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation70,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation70 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation70 >
{
	typedef _corbasim_Test::Huge::operation70 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation70(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation71
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation71,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation71 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation71 >
{
	typedef _corbasim_Test::Huge::operation71 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation71(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation72
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation72,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation72 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation72 >
{
	typedef _corbasim_Test::Huge::operation72 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation72(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation73
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation73,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation73 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation73 >
{
	typedef _corbasim_Test::Huge::operation73 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation73(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation74
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation74,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation74 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation74 >
{
	typedef _corbasim_Test::Huge::operation74 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation74(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation75
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation75,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation75 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation75 >
{
	typedef _corbasim_Test::Huge::operation75 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation75(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation76
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation76,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation76 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation76 >
{
	typedef _corbasim_Test::Huge::operation76 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation76(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation77
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation77,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation77 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation77 >
{
	typedef _corbasim_Test::Huge::operation77 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation77(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation78
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation78,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation78 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation78 >
{
	typedef _corbasim_Test::Huge::operation78 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation78(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation79
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation79,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation79 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation79 >
{
	typedef _corbasim_Test::Huge::operation79 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation79(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation80
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation80,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation80 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation80 >
{
	typedef _corbasim_Test::Huge::operation80 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation80(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation81
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation81,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation81 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation81 >
{
	typedef _corbasim_Test::Huge::operation81 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation81(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation82
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation82,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation82 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation82 >
{
	typedef _corbasim_Test::Huge::operation82 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation82(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation83
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation83,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation83 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation83 >
{
	typedef _corbasim_Test::Huge::operation83 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation83(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation84
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation84,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation84 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation84 >
{
	typedef _corbasim_Test::Huge::operation84 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation84(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation85
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation85,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation85 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation85 >
{
	typedef _corbasim_Test::Huge::operation85 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation85(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation86
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation86,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation86 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation86 >
{
	typedef _corbasim_Test::Huge::operation86 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation86(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation87
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation87,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation87 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation87 >
{
	typedef _corbasim_Test::Huge::operation87 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation87(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation88
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation88,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation88 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation88 >
{
	typedef _corbasim_Test::Huge::operation88 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation88(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation89
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation89,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation89 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation89 >
{
	typedef _corbasim_Test::Huge::operation89 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation89(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation90
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation90,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation90 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation90 >
{
	typedef _corbasim_Test::Huge::operation90 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation90(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation91
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation91,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation91 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation91 >
{
	typedef _corbasim_Test::Huge::operation91 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation91(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation92
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation92,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation92 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation92 >
{
	typedef _corbasim_Test::Huge::operation92 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation92(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation93
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation93,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation93 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation93 >
{
	typedef _corbasim_Test::Huge::operation93 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation93(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation94
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation94,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation94 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation94 >
{
	typedef _corbasim_Test::Huge::operation94 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation94(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation95
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation95,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation95 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation95 >
{
	typedef _corbasim_Test::Huge::operation95 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation95(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation96
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation96,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation96 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation96 >
{
	typedef _corbasim_Test::Huge::operation96 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation96(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation97
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation97,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation97 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation97 >
{
	typedef _corbasim_Test::Huge::operation97 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation97(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation98
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation98,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation98 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation98 >
{
	typedef _corbasim_Test::Huge::operation98 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation98(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation99
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation99,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation99 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation99 >
{
	typedef _corbasim_Test::Huge::operation99 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation99(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation100
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation100,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation100 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation100 >
{
	typedef _corbasim_Test::Huge::operation100 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation100(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation101
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation101,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation101 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation101 >
{
	typedef _corbasim_Test::Huge::operation101 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation101(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation102
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation102,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation102 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation102 >
{
	typedef _corbasim_Test::Huge::operation102 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation102(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation103
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation103,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation103 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation103 >
{
	typedef _corbasim_Test::Huge::operation103 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation103(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation104
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation104,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation104 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation104 >
{
	typedef _corbasim_Test::Huge::operation104 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation104(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation105
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation105,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation105 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation105 >
{
	typedef _corbasim_Test::Huge::operation105 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation105(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation106
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation106,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation106 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation106 >
{
	typedef _corbasim_Test::Huge::operation106 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation106(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation107
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation107,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation107 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation107 >
{
	typedef _corbasim_Test::Huge::operation107 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation107(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation108
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation108,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation108 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation108 >
{
	typedef _corbasim_Test::Huge::operation108 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation108(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation109
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation109,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation109 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation109 >
{
	typedef _corbasim_Test::Huge::operation109 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation109(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation110
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation110,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation110 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation110 >
{
	typedef _corbasim_Test::Huge::operation110 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation110(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation111
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation111,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation111 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation111 >
{
	typedef _corbasim_Test::Huge::operation111 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation111(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation112
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation112,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation112 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation112 >
{
	typedef _corbasim_Test::Huge::operation112 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation112(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation113
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation113,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation113 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation113 >
{
	typedef _corbasim_Test::Huge::operation113 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation113(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation114
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation114,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation114 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation114 >
{
	typedef _corbasim_Test::Huge::operation114 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation114(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation115
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation115,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation115 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation115 >
{
	typedef _corbasim_Test::Huge::operation115 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation115(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation116
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation116,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation116 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation116 >
{
	typedef _corbasim_Test::Huge::operation116 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation116(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation117
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation117,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation117 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation117 >
{
	typedef _corbasim_Test::Huge::operation117 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation117(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation118
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation118,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation118 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation118 >
{
	typedef _corbasim_Test::Huge::operation118 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation118(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation119
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation119,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation119 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation119 >
{
	typedef _corbasim_Test::Huge::operation119 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation119(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation120
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation120,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation120 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation120 >
{
	typedef _corbasim_Test::Huge::operation120 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation120(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation121
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation121,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation121 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation121 >
{
	typedef _corbasim_Test::Huge::operation121 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation121(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation122
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation122,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation122 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation122 >
{
	typedef _corbasim_Test::Huge::operation122 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation122(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation123
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation123,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation123 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation123 >
{
	typedef _corbasim_Test::Huge::operation123 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation123(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation124
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation124,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation124 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation124 >
{
	typedef _corbasim_Test::Huge::operation124 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation124(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation125
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation125,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation125 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation125 >
{
	typedef _corbasim_Test::Huge::operation125 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation125(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation126
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation126,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation126 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation126 >
{
	typedef _corbasim_Test::Huge::operation126 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation126(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation127
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation127,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation127 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation127 >
{
	typedef _corbasim_Test::Huge::operation127 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation127(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation128
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation128,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation128 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation128 >
{
	typedef _corbasim_Test::Huge::operation128 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation128(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation129
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation129,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation129 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation129 >
{
	typedef _corbasim_Test::Huge::operation129 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation129(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation130
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation130,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation130 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation130 >
{
	typedef _corbasim_Test::Huge::operation130 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation130(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation131
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation131,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation131 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation131 >
{
	typedef _corbasim_Test::Huge::operation131 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation131(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation132
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation132,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation132 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation132 >
{
	typedef _corbasim_Test::Huge::operation132 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation132(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation133
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation133,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation133 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation133 >
{
	typedef _corbasim_Test::Huge::operation133 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation133(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation134
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation134,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation134 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation134 >
{
	typedef _corbasim_Test::Huge::operation134 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation134(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation135
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation135,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation135 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation135 >
{
	typedef _corbasim_Test::Huge::operation135 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation135(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation136
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation136,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation136 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation136 >
{
	typedef _corbasim_Test::Huge::operation136 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation136(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation137
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation137,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation137 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation137 >
{
	typedef _corbasim_Test::Huge::operation137 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation137(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation138
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation138,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation138 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation138 >
{
	typedef _corbasim_Test::Huge::operation138 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation138(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation139
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation139,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation139 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation139 >
{
	typedef _corbasim_Test::Huge::operation139 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation139(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation140
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation140,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation140 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation140 >
{
	typedef _corbasim_Test::Huge::operation140 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation140(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation141
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation141,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation141 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation141 >
{
	typedef _corbasim_Test::Huge::operation141 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation141(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation142
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation142,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation142 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation142 >
{
	typedef _corbasim_Test::Huge::operation142 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation142(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation143
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation143,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation143 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation143 >
{
	typedef _corbasim_Test::Huge::operation143 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation143(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation144
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation144,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation144 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation144 >
{
	typedef _corbasim_Test::Huge::operation144 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation144(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation145
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation145,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation145 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation145 >
{
	typedef _corbasim_Test::Huge::operation145 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation145(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation146
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation146,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation146 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation146 >
{
	typedef _corbasim_Test::Huge::operation146 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation146(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation147
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation147,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation147 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation147 >
{
	typedef _corbasim_Test::Huge::operation147 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation147(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation148
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation148,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation148 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation148 >
{
	typedef _corbasim_Test::Huge::operation148 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation148(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation149
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation149,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation149 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation149 >
{
	typedef _corbasim_Test::Huge::operation149 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation149(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation150
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation150,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation150 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation150 >
{
	typedef _corbasim_Test::Huge::operation150 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation150(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation151
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation151,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation151 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation151 >
{
	typedef _corbasim_Test::Huge::operation151 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation151(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation152
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation152,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation152 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation152 >
{
	typedef _corbasim_Test::Huge::operation152 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation152(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation153
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation153,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation153 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation153 >
{
	typedef _corbasim_Test::Huge::operation153 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation153(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation154
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation154,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation154 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation154 >
{
	typedef _corbasim_Test::Huge::operation154 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation154(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation155
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation155,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation155 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation155 >
{
	typedef _corbasim_Test::Huge::operation155 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation155(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation156
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation156,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation156 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation156 >
{
	typedef _corbasim_Test::Huge::operation156 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation156(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation157
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation157,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation157 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation157 >
{
	typedef _corbasim_Test::Huge::operation157 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation157(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation158
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation158,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation158 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation158 >
{
	typedef _corbasim_Test::Huge::operation158 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation158(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation159
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation159,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation159 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation159 >
{
	typedef _corbasim_Test::Huge::operation159 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation159(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation160
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation160,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation160 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation160 >
{
	typedef _corbasim_Test::Huge::operation160 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation160(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation161
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation161,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation161 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation161 >
{
	typedef _corbasim_Test::Huge::operation161 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation161(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation162
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation162,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation162 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation162 >
{
	typedef _corbasim_Test::Huge::operation162 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation162(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation163
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation163,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation163 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation163 >
{
	typedef _corbasim_Test::Huge::operation163 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation163(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation164
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation164,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation164 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation164 >
{
	typedef _corbasim_Test::Huge::operation164 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation164(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation165
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation165,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation165 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation165 >
{
	typedef _corbasim_Test::Huge::operation165 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation165(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation166
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation166,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation166 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation166 >
{
	typedef _corbasim_Test::Huge::operation166 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation166(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation167
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation167,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation167 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation167 >
{
	typedef _corbasim_Test::Huge::operation167 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation167(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation168
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation168,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation168 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation168 >
{
	typedef _corbasim_Test::Huge::operation168 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation168(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation169
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation169,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation169 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation169 >
{
	typedef _corbasim_Test::Huge::operation169 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation169(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation170
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation170,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation170 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation170 >
{
	typedef _corbasim_Test::Huge::operation170 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation170(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation171
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation171,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation171 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation171 >
{
	typedef _corbasim_Test::Huge::operation171 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation171(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation172
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation172,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation172 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation172 >
{
	typedef _corbasim_Test::Huge::operation172 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation172(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation173
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation173,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation173 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation173 >
{
	typedef _corbasim_Test::Huge::operation173 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation173(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation174
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation174,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation174 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation174 >
{
	typedef _corbasim_Test::Huge::operation174 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation174(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation175
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation175,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation175 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation175 >
{
	typedef _corbasim_Test::Huge::operation175 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation175(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation176
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation176,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation176 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation176 >
{
	typedef _corbasim_Test::Huge::operation176 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation176(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation177
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation177,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation177 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation177 >
{
	typedef _corbasim_Test::Huge::operation177 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation177(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation178
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation178,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation178 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation178 >
{
	typedef _corbasim_Test::Huge::operation178 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation178(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation179
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation179,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation179 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation179 >
{
	typedef _corbasim_Test::Huge::operation179 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation179(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation180
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation180,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation180 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation180 >
{
	typedef _corbasim_Test::Huge::operation180 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation180(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation181
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation181,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation181 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation181 >
{
	typedef _corbasim_Test::Huge::operation181 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation181(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation182
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation182,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation182 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation182 >
{
	typedef _corbasim_Test::Huge::operation182 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation182(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation183
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation183,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation183 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation183 >
{
	typedef _corbasim_Test::Huge::operation183 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation183(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation184
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation184,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation184 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation184 >
{
	typedef _corbasim_Test::Huge::operation184 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation184(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation185
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation185,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation185 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation185 >
{
	typedef _corbasim_Test::Huge::operation185 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation185(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation186
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation186,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation186 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation186 >
{
	typedef _corbasim_Test::Huge::operation186 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation186(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation187
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation187,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation187 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation187 >
{
	typedef _corbasim_Test::Huge::operation187 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation187(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation188
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation188,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation188 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation188 >
{
	typedef _corbasim_Test::Huge::operation188 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation188(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation189
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation189,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation189 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation189 >
{
	typedef _corbasim_Test::Huge::operation189 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation189(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation190
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation190,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation190 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation190 >
{
	typedef _corbasim_Test::Huge::operation190 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation190(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation191
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation191,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation191 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation191 >
{
	typedef _corbasim_Test::Huge::operation191 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation191(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation192
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation192,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation192 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation192 >
{
	typedef _corbasim_Test::Huge::operation192 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation192(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation193
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation193,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation193 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation193 >
{
	typedef _corbasim_Test::Huge::operation193 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation193(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation194
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation194,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation194 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation194 >
{
	typedef _corbasim_Test::Huge::operation194 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation194(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation195
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation195,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation195 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation195 >
{
	typedef _corbasim_Test::Huge::operation195 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation195(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation196
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation196,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation196 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation196 >
{
	typedef _corbasim_Test::Huge::operation196 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation196(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation197
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation197,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation197 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation197 >
{
	typedef _corbasim_Test::Huge::operation197 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation197(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation198
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation198,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation198 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation198 >
{
	typedef _corbasim_Test::Huge::operation198 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation198(value.a);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Huge::operation199
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Huge::operation199,
	( ::CORBA::Long, a)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Huge::operation199 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Huge::operation199 >
{
	typedef _corbasim_Test::Huge::operation199 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation199(value.a);
    }
};

} // adapted
} // corbasim











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









namespace corbasim
{
namespace adapted
{

template < >
struct interface < SimpleExample::Test >
{
	typedef cs_mpl::list< _corbasim_SimpleExample::Test::operation1, cs_mpl::list< _corbasim_SimpleExample::Test::operation4  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: SimpleExample::Test::operation1
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_SimpleExample::Test::operation1,
	( ::CORBA::Long, a)
	( ::CORBA::Long, b)
	( SimpleExample::St, c)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_SimpleExample::Test::operation1 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_SimpleExample::Test::operation1 >
{
	typedef _corbasim_SimpleExample::Test::operation1 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation1(value.a, value.b, value.c);
    }
};

} // adapted
} // corbasim




// OperationDef: SimpleExample::Test::operation4
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_SimpleExample::Test::operation4,
	( SimpleExample::Test_var, a)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_SimpleExample::Test::operation4 >
{
	typedef _corbasim_SimpleExample::Test::operation4 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation4(value.a);
    }
};

} // adapted
} // corbasim























namespace corbasim
{
namespace adapted
{

template < >
struct interface < StringTest::InterfaceString >
{
	typedef cs_mpl::list< _corbasim_StringTest::InterfaceString::operation1, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation2, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation3, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation4, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation5, cs_mpl::list< _corbasim_StringTest::InterfaceString::operation6  >  >  >  >  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: StringTest::InterfaceString::operation1
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation1,
	( ::corbasim::orbimpl::String_Manager, s)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation1 >
{
	typedef _corbasim_StringTest::InterfaceString::operation1 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation1(value.s);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation2
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation2,
	( ::corbasim::orbimpl::String_Manager, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation2 >
{
	typedef _corbasim_StringTest::InterfaceString::operation2 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation2(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation3
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation3,
	( StringTest::NameSeq, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation3 >
{
	typedef _corbasim_StringTest::InterfaceString::operation3 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation3(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation4
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation4,
	( StringTest::StructWithStrings, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation4 >
{
	typedef _corbasim_StringTest::InterfaceString::operation4 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation4(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation5
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation5,
	( ::corbasim::orbimpl::String_Manager, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation5 >
{
	typedef _corbasim_StringTest::InterfaceString::operation5 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation5(value.n);
    }
};

} // adapted
} // corbasim


// OperationDef: StringTest::InterfaceString::operation6
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_StringTest::InterfaceString::operation6,
	( StringTest::NameIDSeq, n)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_StringTest::InterfaceString::operation6 >
{
	typedef _corbasim_StringTest::InterfaceString::operation6 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation6(value.n);
    }
};

} // adapted
} // corbasim















namespace corbasim
{
namespace adapted
{

template < >
struct interface < MyModule::MyInterface >
{
	typedef cs_mpl::list< _corbasim_MyModule::MyInterface::operation, cs_mpl::list< _corbasim_MyModule::MyInterface::operation1, cs_mpl::list< _corbasim_MyModule::MyInterface::operation2, cs_mpl::list< _corbasim_MyModule::MyInterface::operation3  >  >  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: MyModule::MyInterface::operation
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_MyModule::MyInterface::operation,
	( MyModule::MyUnion, uni)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_MyModule::MyInterface::operation >
{
	typedef _corbasim_MyModule::MyInterface::operation Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation(value.uni);
    }
};

} // adapted
} // corbasim


// OperationDef: MyModule::MyInterface::operation1
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_MyModule::MyInterface::operation1,
	( MyModule::MyUnion2, uni)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_MyModule::MyInterface::operation1 >
{
	typedef _corbasim_MyModule::MyInterface::operation1 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation1(value.uni);
    }
};

} // adapted
} // corbasim


// OperationDef: MyModule::MyInterface::operation2
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_MyModule::MyInterface::operation2,
	( MyModule::MyStruct, uni)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_MyModule::MyInterface::operation2 >
{
	typedef _corbasim_MyModule::MyInterface::operation2 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation2(value.uni);
    }
};

} // adapted
} // corbasim


// OperationDef: MyModule::MyInterface::operation3
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_MyModule::MyInterface::operation3,
	( MyModule::MyUnion3, uni)
     )

namespace corbasim
{
namespace adapted
{     

template< >
struct call< _corbasim_MyModule::MyInterface::operation3 >
{
	typedef _corbasim_MyModule::MyInterface::operation3 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operation3(value.uni);
    }
};

} // adapted
} // corbasim











namespace corbasim
{
namespace adapted
{

template < >
struct interface < Test::Prueba >
{
	typedef cs_mpl::list< _corbasim_Test::Prueba::operacion1, cs_mpl::list< _corbasim_Test::Prueba::operacion2, cs_mpl::list< _corbasim_Test::Prueba::operacion3  >  >  >   _op_list;
	
};

} // adapted
} // corbasim

// OperationDef: Test::Prueba::operacion1
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Prueba::operacion1,
	( Test::St2, a)
	( Test::St, b)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Prueba::operacion1 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Prueba::operacion1 >
{
	typedef _corbasim_Test::Prueba::operacion1 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operacion1(value.a, value.b);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Prueba::operacion2
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Prueba::operacion2,
	( Test::Prueba_var, myref)
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Prueba::operacion2 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Prueba::operacion2 >
{
	typedef _corbasim_Test::Prueba::operacion2 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operacion2(value.myref);
    }
};

} // adapted
} // corbasim


// OperationDef: Test::Prueba::operacion3
BOOST_FUSION_ADAPT_STRUCT(
	_corbasim_Test::Prueba::operacion3,
     )

namespace corbasim
{
namespace adapted
{     
template< >
struct is_oneway< _corbasim_Test::Prueba::operacion3 > : public cs_mpl::true_
{
};

template< >
struct call< _corbasim_Test::Prueba::operacion3 >
{
	typedef _corbasim_Test::Prueba::operacion3 Value;
	
    template < typename Interface >
    static inline void invoke(Interface * ref, Value& value)
    {
 ref->operacion3();
    }
};

} // adapted
} // corbasim




#endif // MAPPING_ADAPTED_HPP



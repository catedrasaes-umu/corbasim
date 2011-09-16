#ifndef SIMPLE_SERVANT_HPP
#define SIMPLE_SERVANT_HPP

#include "simpleS.h"
#include "simple_adapted.hpp"

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct sevant< SimpleExample::Test >
        {
            template< typename F >
            class _type: public virtual POA_SimpleExample::Test
            {
            public:

                _type(F f) :
                    __f( f)
                {
                }

                void operation1(::CORBA::Long a, ::CORBA::Long b,
                        const SimpleExample::St& c)
                {
                    _corbasim_SimpleExample::Test::operation1 _val( a, b, c);

                    __f( _val);

                }

                void operation4(SimpleExample::Test_ptr a)
                {
                    _corbasim_SimpleExample::Test::operation4 _val( a);

                    __f( _val);

                }

            protected:
                F __f;
            };
        };

    } // adapted
} // corbasim


#endif // SIMPLE_SERVANT_HPP


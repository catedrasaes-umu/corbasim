#ifndef HELLO_SERVANT_HPP
#define HELLO_SERVANT_HPP

#include "helloS.h"
#include "hello_adapted.hpp"

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct sevant< HelloApp::Hello >
        {
            template< typename F >
            class _type: public virtual POA_HelloApp::Hello
            {
            public:

                _type(F f) :
                    __f( f)
                {
                }

                char* sayHello()
                {
                    _corbasim_HelloApp::Hello::sayHello _val;

                    __f( _val);

                    return CORBA::string_dup( _val._return);
                }

                char* sayHelloTo(const HelloApp::Names& people)
                {
                    _corbasim_HelloApp::Hello::sayHelloTo _val( people);

                    __f( _val);

                    return CORBA::string_dup( _val._return);
                }

                void shutdown()
                {
                    _corbasim_HelloApp::Hello::shutdown _val;

                    __f( _val);

                }

            protected:
                F __f;
            };
        };

    } // adapted
} // corbasim


#endif // HELLO_SERVANT_HPP


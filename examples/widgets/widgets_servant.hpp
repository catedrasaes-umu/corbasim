#ifndef WIDGETS_SERVANT_HPP
#define WIDGETS_SERVANT_HPP

#include "widgetsS.h"
#include "widgets_adapted.hpp"

namespace corbasim
{
    namespace adapted
    {

        template< >
        struct servant< Test::Prueba >
        {
            template< typename F >
            class _type: public virtual POA_Test::Prueba
            {
            public:

                _type(F f) :
                    __f( f)
                {
                }

                void operacion1(const Test::St2& a, const Test::St& b)
                {
                    _corbasim_Test::Prueba::operacion1 _val( a, b);

                    __f( _val);

                }

                void operacion2(Test::Prueba_ptr myref)
                {
                    _corbasim_Test::Prueba::operacion2 _val( myref);

                    __f( _val);

                }

                void operacion3()
                {
                    _corbasim_Test::Prueba::operacion3 _val;

                    __f( _val);

                }

            protected:
                F __f;
            };
        };

    } // adapted
} // corbasim


#endif // WIDGETS_SERVANT_HPP


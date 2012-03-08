#include <iostream>
#include "unionC.h"
#include "union_adapted.hpp"
#include "union_servant.hpp"
#include <corbasim/core/reflective.hpp>


int main(int argc, const char *argv[])
{
    MyModule::MyUnion union_;
    
    corbasim::core::reflective_base const * r =
        corbasim::core::reflective< MyModule::MyUnion >::get_instance();

    using namespace corbasim::core;

    holder h = r->create_holder();
    

    std::cout << r->get_length(h) << std::endl;

    std::cout << r->get_child_name(r->get_length(h)) << std::endl;

    holder _d = r->get_child_value(h, 0);
    std::cout << _d.to_value< MyModule::MyEnum >() << std::endl;

   
    std::cout << union_._d() << std::endl;

    return 0;
}



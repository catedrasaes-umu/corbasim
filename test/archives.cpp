#include <corbasim/core/archives.hpp>
#include <iostream>

struct prueba
{
    int a;
    int b;

    template < typename Archive >
    void serialize(Archive& ar, const unsigned int /*unused*/)
    {
        ar & a;
        ar & b;
    }
};


int main(int argc, const char *argv[])
{
   prueba p;
   p.a = 10;
   p.b = 13;

   corbasim::core::text_oarchive toa(std::cout);
   toa << p;
}

#include <iostream>
#include <corbasim/mpl/vector.hpp>
#include <corbasim/mpl/for_each.hpp>

struct tmp
{
    template< typename Val >
    void operator()(const Val& v)
    {
        std::cout << v << std::endl;
    }
};

int main(int argc, const char *argv[])
{
    typedef corbasim::cs_mpl::vector< > v0_type;
    std::cout << v0_type::size_type::value << std::endl;

    typedef corbasim::cs_mpl::vector< int > v1_type;
    std::cout << v1_type::size_type::value << std::endl;

    typedef corbasim::cs_mpl::vector< int, int > v2_type;
    std::cout << v2_type::size_type::value << std::endl;

    typedef corbasim::cs_mpl::vector< int, int, int > v3_type;
    std::cout << v3_type::size_type::value << std::endl;

    typedef corbasim::cs_mpl::vector< int, int, int, int, int, int > v6_type;
    std::cout << v6_type::size_type::value << std::endl;

    tmp t;
    corbasim::cs_mpl::for_each< v6_type >(tmp());
    return 0;
}

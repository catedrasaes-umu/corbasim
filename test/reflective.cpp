#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE reflective
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <corbasim/corba_adapted.hpp>
#include <corbasim/core/copy.hpp>
#include <corbasim/core/reflective_fwd.hpp>

using namespace corbasim::core;
using namespace std;
using namespace CORBA;

extern "C" const corbasim::core::interface_reflective_base* corbasim_reflective_Test_Prueba();

BOOST_AUTO_TEST_CASE(interfaceRelective)
{
    const interface_reflective_base* i = corbasim_reflective_Test_Prueba();
    BOOST_REQUIRE(i);

    BOOST_CHECK_EQUAL(i->operation_count(), 3);
    BOOST_CHECK_EQUAL(string("Test::Prueba"), i->get_fqn());

    BOOST_CHECK(i->get_reflective_by_index(0));
    BOOST_CHECK(i->get_reflective_by_index(1));
    BOOST_CHECK(i->get_reflective_by_index(2));
    BOOST_CHECK(i->get_reflective_by_index(3) == NULL);

    BOOST_CHECK(i->get_reflective_by_name("operacion1"));
    BOOST_CHECK(i->get_reflective_by_name("operacion2"));
    BOOST_CHECK(i->get_reflective_by_name("operacion3"));
    BOOST_CHECK(i->get_reflective_by_name("operacion4") == NULL);

    BOOST_CHECK_EQUAL(i->get_reflective_by_name("operacion1"), i->get_reflective_by_index(0));
    BOOST_CHECK_EQUAL(i->get_reflective_by_name("operacion2"), i->get_reflective_by_index(1));
    BOOST_CHECK_EQUAL(i->get_reflective_by_name("operacion3"), i->get_reflective_by_index(2));

    const operation_reflective_base* o = i->get_reflective_by_index(0);
    BOOST_REQUIRE(o);
    BOOST_CHECK_EQUAL(string("operacion1"), o->get_name());
    BOOST_CHECK_EQUAL(o->get_children_count(), 2);
    BOOST_CHECK_EQUAL(string("a"), o->get_child_name(0));
    BOOST_CHECK_EQUAL(string("b"), o->get_child_name(1));

    const reflective_base* r = o->get_child(0);
    BOOST_REQUIRE(r);
    BOOST_CHECK_EQUAL(r->get_type(), TYPE_STRUCT);
    BOOST_CHECK_EQUAL(r->get_children_count(), 4);
}

BOOST_AUTO_TEST_CASE(holderUsage)
{
    const interface_reflective_base* i = corbasim_reflective_Test_Prueba();
    BOOST_REQUIRE(i);
    const operation_reflective_base* o = i->get_reflective_by_index(0);
    BOOST_REQUIRE(o);
    const reflective_base* r = o->get_child(0);
    BOOST_REQUIRE(r);
    const reflective_base* c = r->get_child(3);
    BOOST_REQUIRE(c);
    BOOST_CHECK_EQUAL(c->get_type(), TYPE_LONG);

    holder p = r->create_holder();
    holder h = c->create_holder();
    h.to_value<Long>() = 1234321;
    r->set_child_value(p, 3, h);

    holder v = r->get_child_value(p, 3);
    BOOST_CHECK_EQUAL(v.to_value<Long>(), 1234321);

    // Holder contains a reference for struct's members
    v.to_value<Long>() = 9876543;
    h = r->get_child_value(p, 3);
    BOOST_CHECK_EQUAL(h.to_value<Long>(), 9876543);
}

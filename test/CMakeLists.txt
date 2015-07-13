add_executable(test_reflective reflective.cpp)
target_link_libraries(test_reflective
    corbasim_reflective_Test_Prueba
    corbasim_reflective_MyModule_MyInterface
    corbasim boost_unit_test_framework)

add_custom_target(build_tests)
add_dependencies(build_tests test_reflective)
add_test(reflective test_reflective)

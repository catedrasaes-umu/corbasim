add_executable(reflective reflective.cpp)
target_link_libraries(reflective
    corbasim_reflective_Test_Prueba
    corbasim boost_unit_test_framework)

add_test(reflective_test reflective)

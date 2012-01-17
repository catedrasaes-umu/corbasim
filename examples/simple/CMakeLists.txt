include(simple.cmake)

add_executable(simple_prueba prueba.cpp)
target_link_libraries(simple_prueba corbasim simple_idl TAO
    # TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)

if (Qwt6_FOUND)
    add_executable(prueba_reflective 
        prueba_reflective.cpp)
    target_link_libraries(prueba_reflective
        simple_idl
        corbasim corbasim_qt corbasim_qwt
        # TAO
        TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming 
        TAO_ObjRefTemplate)
endif()


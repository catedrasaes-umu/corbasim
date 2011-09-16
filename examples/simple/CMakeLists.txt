include(simple.cmake)

add_executable(simple_prueba prueba.cpp)
target_link_libraries(simple_prueba corbasim simple_idl TAO
    # TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)


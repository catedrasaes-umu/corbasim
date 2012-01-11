include(simple.cmake)

add_executable(simple_prueba prueba.cpp)
target_link_libraries(simple_prueba corbasim simple_idl TAO
    # TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)


qt4_wrap_cpp(prueba_reflective_MOC_SRCS PlotModel.hpp)
add_executable(prueba_reflective 
    ${prueba_reflective_MOC_SRCS}
    prueba_reflective.cpp PlotModel.cpp)
target_link_libraries(prueba_reflective
    simple_idl
    corbasim corbasim_qt
    # TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)


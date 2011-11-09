include(widgets.cmake)

# Server
add_executable(${CORBASIM_PREFIX}Test_Prueba_server2 Test_Prueba_server2.cpp)
target_link_libraries(${CORBASIM_PREFIX}Test_Prueba_server2 
	${CORBASIM_PREFIX}widgets_idl
	# CORBASIM Libraries
	corbasim corbasim_qt
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate
    # QT
    ${QT_LIBRARIES}
    )


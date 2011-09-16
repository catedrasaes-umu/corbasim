

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(widgets_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/widgetsC.h
	${CMAKE_CURRENT_SOURCE_DIR}/widgetsC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/widgetsC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/widgetsS.h
	${CMAKE_CURRENT_SOURCE_DIR}/widgetsS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/widgetsS.inl)

add_custom_command(
	OUTPUT ${widgets_GENERATED}
	DEPENDS widgets.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} widgets.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}widgets_idl SHARED ${widgets_GENERATED})

	
	
	







# Client
add_executable(${CORBASIM_PREFIX}Test_Prueba_client Test_Prueba_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}Test_Prueba_client 
	${CORBASIM_PREFIX}widgets_idl
	# CORBASIM Libraries
	corbasim corbasim_qt
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate
	# QT 
	${QT_LIBRARIES})
	
# Injector	
add_executable(${CORBASIM_PREFIX}Test_Prueba_injector Test_Prueba_injector.cpp)
target_link_libraries(${CORBASIM_PREFIX}Test_Prueba_injector
	${CORBASIM_PREFIX}widgets_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)
	
# Server
add_executable(${CORBASIM_PREFIX}Test_Prueba_server Test_Prueba_server.cpp)
target_link_libraries(${CORBASIM_PREFIX}Test_Prueba_server 
	${CORBASIM_PREFIX}widgets_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)



	

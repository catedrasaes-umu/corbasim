

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(hello_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/helloC.h
	${CMAKE_CURRENT_SOURCE_DIR}/helloC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/helloC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/helloS.h
	${CMAKE_CURRENT_SOURCE_DIR}/helloS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/helloS.inl)

add_custom_command(
	OUTPUT ${hello_GENERATED}
	DEPENDS hello.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} hello.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}hello_idl SHARED ${hello_GENERATED})

	
	
	



# Client
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_client HelloApp_Hello_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_client 
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim corbasim_qt
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate
	# QT 
	${QT_LIBRARIES})
	
# Injector	
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_injector HelloApp_Hello_injector.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_injector
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)
	
# Server
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_server HelloApp_Hello_server.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_server 
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)
	
# PyStim
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_pystim HelloApp_Hello_pystim.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_pystim 
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim corbasim_python corbasim_qt
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate
	# QT 
	${QT_LIBRARIES})



	

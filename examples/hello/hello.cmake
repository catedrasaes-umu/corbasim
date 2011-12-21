

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

	
	



# Corbasim library	
add_library(corbasim_lib_HelloApp_Hello SHARED HelloApp_Hello_lib.cpp)
target_link_libraries(corbasim_lib_HelloApp_Hello
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim corbasim_qt)

# Client
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_client HelloApp_Hello_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_client 
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim corbasim_qt)
	
# Injector	
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_injector HelloApp_Hello_injector.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_injector
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim)
	
# Server
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_server HelloApp_Hello_server.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_server 
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim
	# Boost
	boost_program_options)
	
# PyStim
add_executable(${CORBASIM_PREFIX}HelloApp_Hello_pystim HelloApp_Hello_pystim.cpp)
target_link_libraries(${CORBASIM_PREFIX}HelloApp_Hello_pystim 
	${CORBASIM_PREFIX}hello_idl
	# CORBASIM Libraries
	corbasim corbasim_python corbasim_qt)
	



	

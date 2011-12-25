

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(simple_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/simpleC.h
	${CMAKE_CURRENT_SOURCE_DIR}/simpleC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/simpleC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/simpleS.h
	${CMAKE_CURRENT_SOURCE_DIR}/simpleS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/simpleS.inl)

add_custom_command(
	OUTPUT ${simple_GENERATED}
	DEPENDS simple.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} simple.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}simple_idl SHARED ${simple_GENERATED} simple_adapted.cpp)

	
	





# Corbasim library	
add_library(corbasim_lib_SimpleExample_Test SHARED SimpleExample_Test_lib.cpp)
target_link_libraries(corbasim_lib_SimpleExample_Test
	${CORBASIM_PREFIX}simple_idl
	# CORBASIM Libraries
	corbasim corbasim_qt)

# Client
add_executable(${CORBASIM_PREFIX}SimpleExample_Test_client SimpleExample_Test_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}SimpleExample_Test_client 
	${CORBASIM_PREFIX}simple_idl
	corbasim_lib_SimpleExample_Test
	# CORBASIM Libraries
	corbasim corbasim_qt)
	
	
	











	

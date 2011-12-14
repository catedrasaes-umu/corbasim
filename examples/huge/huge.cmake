

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(huge_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/hugeC.h
	${CMAKE_CURRENT_SOURCE_DIR}/hugeC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/hugeC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/hugeS.h
	${CMAKE_CURRENT_SOURCE_DIR}/hugeS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/hugeS.inl)

add_custom_command(
	OUTPUT ${huge_GENERATED}
	DEPENDS huge.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} huge.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}huge_idl SHARED ${huge_GENERATED})

	
	

# Corbasim library	
add_library(corbasim_lib_Test_Huge SHARED Test_Huge_lib.cpp)
target_link_libraries(corbasim_lib_Test_Huge
	${CORBASIM_PREFIX}huge_idl
	# CORBASIM Libraries
	corbasim corbasim_qt)

# Client
add_executable(${CORBASIM_PREFIX}Test_Huge_client Test_Huge_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}Test_Huge_client 
	${CORBASIM_PREFIX}huge_idl
	# CORBASIM Libraries
	corbasim corbasim_qt)
	
	
	
	



	

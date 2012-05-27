

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(string_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/stringC.h
	${CMAKE_CURRENT_SOURCE_DIR}/stringC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/stringC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/stringS.h
	${CMAKE_CURRENT_SOURCE_DIR}/stringS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/stringS.inl)

add_custom_command(
	OUTPUT ${string_GENERATED}
	DEPENDS string.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} string.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}string_idl SHARED ${string_GENERATED} string_adapted.cpp)

	
	











	
# Corbasim reflective library	
add_library(corbasim_reflective_StringTest_InterfaceString SHARED StringTest_InterfaceString_reflective.cpp)
target_link_libraries(corbasim_reflective_StringTest_InterfaceString
	${CORBASIM_PREFIX}string_idl
	# CORBASIM Library
	corbasim)

	
	
	



	

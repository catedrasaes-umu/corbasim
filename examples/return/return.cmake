

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(return_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/returnC.h
	${CMAKE_CURRENT_SOURCE_DIR}/returnC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/returnC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/returnS.h
	${CMAKE_CURRENT_SOURCE_DIR}/returnS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/returnS.inl)

add_custom_command(
	OUTPUT ${return_GENERATED}
	DEPENDS return.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} return.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}return_idl SHARED ${return_GENERATED} return_adapted.cpp)

	
	







	
# Corbasim reflective library	
add_library(corbasim_reflective_AAAAAAAAA_IIIIIIIIII SHARED AAAAAAAAA_IIIIIIIIII_reflective.cpp)
target_link_libraries(corbasim_reflective_AAAAAAAAA_IIIIIIIIII
	${CORBASIM_PREFIX}return_idl
	# CORBASIM Library
	corbasim)

	
	
	



	

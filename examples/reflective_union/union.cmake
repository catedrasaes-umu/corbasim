

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(union_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/unionC.h
	${CMAKE_CURRENT_SOURCE_DIR}/unionC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/unionC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/unionS.h
	${CMAKE_CURRENT_SOURCE_DIR}/unionS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/unionS.inl)

add_custom_command(
	OUTPUT ${union_GENERATED}
	DEPENDS union.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} union.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}union_idl SHARED ${union_GENERATED} union_adapted.cpp)

	
	











	
# Corbasim reflective library	
add_library(corbasim_reflective_MyModule_MyInterface SHARED MyModule_MyInterface_reflective.cpp)
target_link_libraries(corbasim_reflective_MyModule_MyInterface
	${CORBASIM_PREFIX}union_idl
	# CORBASIM Library
	corbasim)

	
	
	



	



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

add_library(${CORBASIM_PREFIX}huge_idl SHARED ${huge_GENERATED} huge_adapted.cpp)
install(TARGETS ${CORBASIM_PREFIX}huge_idl DESTINATION lib)

	

# Corbasim reflective library	
add_library(corbasim_reflective_Test_Huge SHARED Test_Huge_reflective.cpp)
target_link_libraries(corbasim_reflective_Test_Huge
	${CORBASIM_PREFIX}huge_idl
	# CORBASIM Library
	corbasim)
install(TARGETS corbasim_reflective_Test_Huge DESTINATION lib)


	

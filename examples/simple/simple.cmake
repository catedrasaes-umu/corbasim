

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
install(TARGETS ${CORBASIM_PREFIX}simple_idl DESTINATION lib)



# Corbasim reflective library	
add_library(corbasim_reflective_SimpleExample_Test SHARED SimpleExample_Test_reflective.cpp)
target_link_libraries(corbasim_reflective_SimpleExample_Test
	${CORBASIM_PREFIX}simple_idl
	# CORBASIM Library
	corbasim)
install(TARGETS corbasim_reflective_SimpleExample_Test DESTINATION lib)

# Client
add_executable(${CORBASIM_PREFIX}SimpleExample_Test_client SimpleExample_Test_client.cpp)
target_link_libraries(${CORBASIM_PREFIX}SimpleExample_Test_client 
	${CORBASIM_PREFIX}simple_idl
	corbasim_reflective_SimpleExample_Test
	# CORBASIM Libraries
	corbasim corbasim_qt corbasim_reflective_gui)
install(TARGETS ${CORBASIM_PREFIX}SimpleExample_Test_client DESTINATION bin)

# Server
add_executable(${CORBASIM_PREFIX}SimpleExample_Test_server SimpleExample_Test_server.cpp)
target_link_libraries(${CORBASIM_PREFIX}SimpleExample_Test_server 
	${CORBASIM_PREFIX}simple_idl
	# CORBASIM Libraries
	corbasim
	# Boost
	boost_program_options)
install(TARGETS ${CORBASIM_PREFIX}SimpleExample_Test_server DESTINATION bin)


	

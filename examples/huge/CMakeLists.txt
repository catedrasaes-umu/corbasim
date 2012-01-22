
add_definitions(-DCORBASIM_MPL_VECTOR_MAX_SIZE=200)
include(huge.cmake)

# Corbasim reflective library	
add_library(corbasim_reflective_Test_Huge SHARED Test_Huge_reflective.cpp)
target_link_libraries(corbasim_reflective_Test_Huge
	${CORBASIM_PREFIX}huge_idl)


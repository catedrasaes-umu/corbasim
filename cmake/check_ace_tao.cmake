include(macro_tao_idl)
include(macro_find_ace)

# keep ACE_ROOT variable
if ("$ENV{ACE_ROOT}" STREQUAL "")
    if (NOT "${ACE_DIR}" STREQUAL "")
        set(ENV{ACE_ROOT} ${ACE_DIR})
    endif()
else()
    set(ACE_DIR $ENV{ACE_ROOT} CACHE STRING "ACE directory")
endif()

# keep TAO_ROOT variable
if ("$ENV{TAO_ROOT}" STREQUAL "")
    if (NOT "${TAO_DIR}" STREQUAL "")
        set(ENV{TAO_ROOT} ${TAO_DIR})
    endif()
else()
    set(TAO_DIR $ENV{TAO_ROOT} CACHE STRING "TAO directory")
endif()

# ACE
FIND_ACE(ACE)
if(ACE_FOUND)
    message(STATUS "Found ACE library: ${ACE_LIBRARY}")
    message(STATUS "Include dir is: ${ACE_INCLUDE_DIR}")
else(ACE_FOUND)
    message(SEND_ERROR "Couldn't find ACE library!")
endif(ACE_FOUND)

# TAO
find_package(TAO)
if(TAO_FOUND)
    message(STATUS "TAO found: ${TAO_INCLUDE_DIR}, ${TAO_LIBRARY_DIR}")
else(TAO_FOUND)
    message(SEND_ERROR "Couldn't find TAO!")
endif(TAO_FOUND)


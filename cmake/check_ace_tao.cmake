set(ACE_TAO_DEFAULT /usr/local/ACE+TAO-5.7.9)

include(FindPkgConfig)
include(macro_find_ace)
include(macro_tao_idl)

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

include_directories(${ACE_INCLUDE_DIR} ${TAO_INCLUDE_DIR} ${TAO_INCLUDE_DIR}/orbsvcs)
link_directories(${TAO_LIBRARY_DIR})


set(ACE_TAO_DEFAULT /opt/ACE+TAO-5.7.9)

include_directories(${ACE_TAO_DEFAULT}/include ${ACE_TAO_DEFAULT}/include/orbsvcs)
link_directories(${ACE_TAO_DEFAULT}/lib)
set(TAO_IDL_COMPILER ${ACE_TAO_DEFAULT}/bin/tao_idl)

include(macro_tao_idl)

# ACE
#FIND_ACE(ACE)
#if(ACE_FOUND)
#        message(STATUS "Found ACE library: ${ACE_LIBRARY}")
#        message(STATUS "Include dir is: ${ACE_INCLUDE_DIR}")
#else(ACE_FOUND)
#        message(SEND_ERROR "Couldn't find ACE library!")
#endif(ACE_FOUND)
#
## TAO
#find_package(TAO)
#if(TAO_FOUND)
#        message(STATUS "TAO found: ${TAO_INCLUDE_DIR}, ${TAO_LIBRARY_DIR}")
#else(TAO_FOUND)
#        message(SEND_ERROR "Couldn't find TAO!")
#endif(TAO_FOUND)
#




set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ".")

set(CORBASIM_INSTALL_PREFIX /tmp/corbasim)

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/usr/include)
link_directories(/usr/lib)

# ACE+TAO
include_directories(
    
    
    /orbsvcs)
link_directories()

set(CORBASIM_ORB_LIBS
    TAO;TAO_PortableServer;TAO_AnyTypeCode;TAO_CosNaming;TAO_ObjRefTemplate)


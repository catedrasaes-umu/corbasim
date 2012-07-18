
set(CORBASIM_INSTALL_PREFIX /tmp/corbasim)

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/usr/include)
link_directories(/usr/lib)

# ORB
set(CORBASIM_ORBIMPL
    TAO)

set(CORBASIM_ORB_LIBS
    TAO;TAO_PortableServer;TAO_AnyTypeCode;TAO_CosNaming;TAO_ObjRefTemplate)

include_directories(/orbsvcs)
link_directories()

set(CORBASIM_ORB_IDL_COMPILER
    tao_idl)

set(CORBASIM_ORB_IDL_COMPILER_OPTIONS
    )

# Libraries for clients
set(CORBASIM_CLIENT_LIBS 
    corbasim corbasim_qt corbasim_reflective_gui)

# Libraries for servers
set(CORBASIM_SERVER_LIBS 
    corbasim)


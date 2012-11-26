
if(NOT DEFINED CORBASIM_INSTALL_PREFIX)
    set(CORBASIM_INSTALL_PREFIX /usr/local)
endif()

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/usr/local/include)
link_directories(/usr/local/lib;/usr/lib)

# ORB
set(CORBASIM_ORBIMPL
    TAO)

set(CORBASIM_ORB_LIBS
    ACE;TAO;TAO_PortableServer;TAO_AnyTypeCode;TAO_CosNaming;TAO_ObjRefTemplate)

include_directories(/usr/local/ACE+TAO-5.7.9/include;/usr/local/ACE+TAO-5.7.9/include;/usr/local/ACE+TAO-5.7.9/include/orbsvcs)
link_directories(/usr/local/ACE+TAO-5.7.9/lib)

set(CORBASIM_ORB_IDL_COMPILER
    tao_idl)

set(CORBASIM_ORB_IDL_COMPILER_OPTIONS
    )

# Libraries for clients
set(CORBASIM_CLIENT_LIBS 
    corbasim corbasim_qt corbasim_gui boost_program_options)

set(CORBASIM_CLIENT_STATIC_LIBS 
    corbasim_gui_s corbasim_qt_s corbasim_s boost_program_options)

# Libraries for servers
set(CORBASIM_SERVER_LIBS 
    corbasim boost_program_options)



set(CORBASIM_INSTALL_PREFIX /tmp/prueba_corbasim)

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/usr/local/include)
link_directories(/usr/local/lib;/usr/lib)

# ORB
set(CORBASIM_ORBIMPL
    TAO)

set(CORBASIM_ORB_LIBS
    /usr/local/ACE+TAO-5.7.9/lib/libACE.so;/usr/local/ACE+TAO-5.7.9/lib/libTAO.so;/usr/local/ACE+TAO-5.7.9/lib/libTAO_PortableServer.so;/usr/local/ACE+TAO-5.7.9/lib/libTAO_AnyTypeCode.so;/usr/local/ACE+TAO-5.7.9/lib/libTAO_CosNaming.so;/usr/local/ACE+TAO-5.7.9/lib/libTAO_ObjRefTemplate.so)

include_directories(/usr/local/ACE+TAO-5.7.9/include;/usr/local/ACE+TAO-5.7.9/include;/usr/local/ACE+TAO-5.7.9/include/orbsvcs)
link_directories(/usr/local/ACE+TAO-5.7.9/lib)

set(CORBASIM_ORB_IDL_COMPILER
    /usr/local/ACE+TAO-5.7.9/bin/tao_idl)

set(CORBASIM_ORB_IDL_COMPILER_OPTIONS
    )

# Libraries for clients
set(CORBASIM_CLIENT_LIBS 
    corbasim;corbasim_qt;corbasim_gui;optimized;/usr/lib/libboost_program_options.so;debug;/usr/lib/libboost_program_options.so)

set(CORBASIM_CLIENT_STATIC_LIBS 
    corbasim_gui_s;corbasim_qt_s;corbasim_s;optimized;/usr/lib/libboost_program_options.so;debug;/usr/lib/libboost_program_options.so)

# Libraries for servers
set(CORBASIM_SERVER_LIBS 
    corbasim;optimized;/usr/lib/libboost_program_options.so;debug;/usr/lib/libboost_program_options.so)


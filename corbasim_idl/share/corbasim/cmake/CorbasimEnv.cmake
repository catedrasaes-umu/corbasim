
set(CORBASIM_INSTALL_PREFIX /usr/local)

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/usr/include)
link_directories(/usr/lib)

# ORB
set(CORBASIM_ORBIMPL
    TAO)

set(CORBASIM_ORB_LIBS
    /home/asenac/local/ACE+TAO-5.7.9/lib/libACE.so;/home/asenac/local/ACE+TAO-5.7.9/lib/libTAO.so;/home/asenac/local/ACE+TAO-5.7.9/lib/libTAO_PortableServer.so;/home/asenac/local/ACE+TAO-5.7.9/lib/libTAO_AnyTypeCode.so;/home/asenac/local/ACE+TAO-5.7.9/lib/libTAO_CosNaming.so;/home/asenac/local/ACE+TAO-5.7.9/lib/libTAO_ObjRefTemplate.so)

include_directories(/home/asenac/local/ACE+TAO-5.7.9/include;/home/asenac/local/ACE+TAO-5.7.9/include;/home/asenac/local/ACE+TAO-5.7.9/include/orbsvcs)
link_directories(/home/asenac/local/ACE+TAO-5.7.9/lib)

set(CORBASIM_ORB_IDL_COMPILER
    /home/asenac/local/ACE+TAO-5.7.9/bin/tao_idl)

set(CORBASIM_ORB_IDL_COMPILER_OPTIONS
    )

# Libraries for clients
set(CORBASIM_CLIENT_LIBS 
    corbasim;corbasim_qt;corbasim_gui;/usr/lib/libboost_program_options.so)

set(CORBASIM_CLIENT_STATIC_LIBS 
    corbasim_gui_s;corbasim_qt_s;corbasim_s;/usr/lib/libboost_program_options.so)

# Libraries for servers
set(CORBASIM_SERVER_LIBS 
    corbasim;/usr/lib/libboost_program_options.so)


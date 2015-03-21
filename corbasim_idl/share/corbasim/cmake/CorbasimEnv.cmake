
set(CORBASIM_INSTALL_PREFIX /usr/local)

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/usr/include)
link_directories(/usr/lib/x86_64-linux-gnu)

# ORB
set(CORBASIM_ORBIMPL
    TAO)

set(CORBASIM_ORB_LIBS
    /home/asenac/local/ACE+TAO-6.3.1/lib/libACE.so;/home/asenac/local/ACE+TAO-6.3.1/lib/libTAO.so;/home/asenac/local/ACE+TAO-6.3.1/lib/libTAO_PortableServer.so;/home/asenac/local/ACE+TAO-6.3.1/lib/libTAO_AnyTypeCode.so;/home/asenac/local/ACE+TAO-6.3.1/lib/libTAO_CosNaming.so;/home/asenac/local/ACE+TAO-6.3.1/lib/libTAO_CosNaming_Skel.so;/home/asenac/local/ACE+TAO-6.3.1/lib/libTAO_ObjRefTemplate.so)

include_directories(/home/asenac/local/ACE+TAO-6.3.1/include;/home/asenac/local/ACE+TAO-6.3.1/include;/home/asenac/local/ACE+TAO-6.3.1/include/orbsvcs)
link_directories(/home/asenac/local/ACE+TAO-6.3.1/lib)

set(CORBASIM_ORB_IDL_COMPILER
    /home/asenac/local/ACE+TAO-6.3.1/bin/tao_idl)

set(CORBASIM_ORB_IDL_COMPILER_OPTIONS
    )

# Libraries for clients
set(CORBASIM_CLIENT_LIBS 
    corbasim;corbasim_qt;corbasim_gui;/usr/lib/x86_64-linux-gnu/libboost_program_options.so)

set(CORBASIM_CLIENT_STATIC_LIBS 
    corbasim_gui_s;corbasim_qt_s;corbasim_s;/usr/lib/x86_64-linux-gnu/libboost_program_options.so)

# Libraries for servers
set(CORBASIM_SERVER_LIBS 
    corbasim;/usr/lib/x86_64-linux-gnu/libboost_program_options.so)


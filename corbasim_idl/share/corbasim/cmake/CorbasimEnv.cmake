
set(CORBASIM_INSTALL_PREFIX /usr/local)

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/usr/include)
link_directories(/usr/lib/x86_64-linux-gnu)

# ORB
set(CORBASIM_ORBIMPL
    OMNIORB4)

set(CORBASIM_ORB_LIBS
    omniCodeSets4;omniConnectionMgmt4;omniDynamic4;omniORB4;omnisslTP4;omnithread)

include_directories()
link_directories()

set(CORBASIM_ORB_IDL_COMPILER
    omniidl)

set(CORBASIM_ORB_IDL_COMPILER_OPTIONS
    -bcxx;-Wba)

# Libraries for clients
set(CORBASIM_CLIENT_LIBS 
    corbasim;corbasim_qt;corbasim_gui;/usr/lib/x86_64-linux-gnu/libboost_program_options.so)

set(CORBASIM_CLIENT_STATIC_LIBS 
    corbasim_gui_s;corbasim_qt_s;corbasim_s;/usr/lib/x86_64-linux-gnu/libboost_program_options.so)

# Libraries for servers
set(CORBASIM_SERVER_LIBS 
    corbasim;/usr/lib/x86_64-linux-gnu/libboost_program_options.so)


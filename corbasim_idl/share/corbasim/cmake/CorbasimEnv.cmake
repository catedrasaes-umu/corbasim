
set(CORBASIM_INSTALL_PREFIX /tmp/corbasim_install)

include_directories(${CORBASIM_INSTALL_PREFIX}/include)
link_directories(${CORBASIM_INSTALL_PREFIX}/lib)

# Boost C++ Libraries
include_directories(/home/asenac/local/boost/1_49_0/include)
link_directories(/home/asenac/local/boost/1_49_0/lib)

# ACE+TAO
include_directories(
    /usr/include
    /usr/include
    /usr/include/orbsvcs)
link_directories(/usr/lib)


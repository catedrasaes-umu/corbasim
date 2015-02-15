add_custom_target(corbasim_idl
    ant -f ${CMAKE_CURRENT_SOURCE_DIR}/../org.csu.corbasim/build.xml
    COMMAND ant -f ${CMAKE_CURRENT_SOURCE_DIR}/export.xml
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(clean-corbasim_idl
    ant -f ${CMAKE_CURRENT_SOURCE_DIR}/../org.csu.corbasim/build.xml clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES bin/corbasim_idl
    DESTINATION bin
    PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE)

install(FILES bin/corbasim_make
    DESTINATION bin
    PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE)

install(FILES share/corbasim/corbasim_idl.jar
    DESTINATION share/corbasim)

install(DIRECTORY share/corbasim/corbasim_idl_lib
    DESTINATION share/corbasim PATTERN ".svn" EXCLUDE)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/share/corbasim/cmake/CorbasimEnv.cmake.in
    ${CMAKE_CURRENT_SOURCE_DIR}/share/corbasim/cmake/CorbasimEnv.cmake
    @ONLY
)

install(FILES share/corbasim/cmake/CorbasimEnv.cmake
    DESTINATION share/corbasim/cmake)


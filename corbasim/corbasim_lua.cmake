include_directories(${LUA_INCLUDE_DIR})

set(corbasim_lua_EXPORTED_HEADERS
    lua/interpreter.hpp
    )

foreach(_header ${corbasim_lua_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header} 
        DESTINATION include/corbasim_lua/${_header_path}) 
endforeach(_header ${corbasim_lua_EXPORTED_HEADERS})

set(corbasim_lua_LIBS
    corbasim
    ${LUA_LIBRARIES})

set(corbasim_lua_SRCS
    lua/interpreter.cpp
    )
add_library(corbasim_lua SHARED ${corbasim_lua_SRCS})
target_link_libraries(corbasim_lua
    ${corbasim_lua_LIBS})

set_target_properties(corbasim_lua PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim_lua DESTINATION lib)


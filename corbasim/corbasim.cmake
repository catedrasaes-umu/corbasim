# Fichero version.hpp
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in" 
    "${CMAKE_CURRENT_SOURCE_DIR}/version.hpp" IMMEDIATE @ONLY)

# Fichero config.hpp
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/core/config.hpp.in" 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/config.hpp" IMMEDIATE @ONLY)

set(corbasim_EXPORTED_HEADERS
    adapted.hpp
    corba_adapted.hpp
    core/callable.hpp
    core/caller.hpp
    core/caller_fwd.hpp
    core/config.hpp
    core/copy.hpp
    core/export.hpp
    core/file_format_helper.hpp
    core/inserter.hpp
    core/ns_register.hpp
    core/range.hpp
    core/reference_repository.hpp
    core/reference_validator.hpp
    core/reflective.hpp
    core/reflective.ipp
    core/reflective_fwd.hpp
    core/reflective_primitive.ipp
    core/servant.hpp
    cosnaming/CosnamingC.h
    cosnaming/Cosnaming_adapted.hpp
    event.hpp
    event_fwd.hpp
    impl.hpp
    json/converter.hpp
    json/detail/json.hpp
    json/detail/json_parse.hpp
    json/detail/json_writer.hpp
    json/helper.hpp
    json/parser.hpp
    json/reflective.hpp
    json/writer.hpp
    mpl.hpp
    mpl/for_each.hpp
    mpl/list.hpp
    mpl/vector.hpp
    mpl/vector100.hpp
    mpl/vector200.hpp
    mpl/vector50.hpp
    omniorb4.hpp
    tao.hpp
    version.hpp
)

foreach(_header ${corbasim_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header} 
        DESTINATION include/corbasim/${_header_path}) 
endforeach(_header ${corbasim_EXPORTED_HEADERS})

set(corbasim_LIBS
    ${CORBASIM_ORB_LIBS}
    pthread
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY})

set(corbasim_SRCS
    core/core.cpp
    core/file_format_helper.cpp
    core/ns_register.cpp
    core/reference_repository.cpp
    core/reference_validator.cpp
    core/reflective.cpp
    event.cpp

    # JSON
    json/reflective.cpp
)
add_library(corbasim SHARED ${corbasim_SRCS})
target_link_libraries(corbasim
    ${corbasim_LIBS})

# static library
add_library(corbasim_s STATIC ${corbasim_SRCS})

set_target_properties(corbasim PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim corbasim_s DESTINATION lib)


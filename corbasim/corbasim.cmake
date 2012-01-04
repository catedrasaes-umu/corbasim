# Fichero version.hpp
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in" 
    "${CMAKE_CURRENT_SOURCE_DIR}/version.hpp" IMMEDIATE @ONLY)

# Fichero config.hpp
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/core/config.hpp.in" 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/config.hpp" IMMEDIATE @ONLY)

set(corbasim_EXPORTED_HEADERS
    adapted.hpp
    corba_adapted.hpp
    corbasim.hpp
    core/archives.hpp
    core/caller_fwd.hpp
    core/caller.hpp
    core/callable.hpp
    core/config.hpp
    core/copy.hpp
    core/factory_fwd.hpp
    core/factory.hpp
    core/injector.hpp
    core/inserter.hpp
    core/range.hpp
    core/reference_validator.hpp
    core/reference_repository.hpp
    core/request_serializer.hpp
    core/servant.hpp
    event_fwd.hpp
    event.hpp
    impl.hpp
    json/parser.hpp
    json/writer.hpp
    json/helper.hpp
    json/detail/modp_b64.h
    json/detail/json_writer.hpp
    json/detail/json.hpp
    json/detail/json_parse.hpp
    json/detail/modp_b64_data.h
    json/detail/base64_blob.hpp
    json/converter.hpp
    cosnaming/Cosnaming_adapted.hpp
    cosnaming/CosnamingC.h
    mpl/for_each.hpp
    mpl.hpp
    mpl/vector100.hpp
    mpl/vector200.hpp
    mpl/vector50.hpp
    mpl/vector.hpp
    mpl/list.hpp
    omniorb4.hpp
    serialization.hpp
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
    ${Boost_SERIALIZATION_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_REGEX_LIBRARY})

set(corbasim_SRCS
    core/archives.cpp
    core/core.cpp
    core/event_notifier.cpp
    core/factory.cpp
    core/reference_repository.cpp
    core/reference_validator.cpp
    core/request_serializer.cpp

    core/reflective.cpp

    scripting/request_processor.cpp
    scripting/interpreter.cpp

    event.cpp

    # JSON
    json/detail/modp_b64.c
    )
add_library(corbasim SHARED ${corbasim_SRCS})
target_link_libraries(corbasim
    ${corbasim_LIBS})

set_target_properties(corbasim PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim DESTINATION lib)


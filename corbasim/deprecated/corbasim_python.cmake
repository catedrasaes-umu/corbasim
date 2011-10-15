set(corbasim_python_EXPORTED_HEADERS
    python/auto_response.hpp
    )

foreach(_header ${corbasim_python_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header} 
        DESTINATION include/corbasim_python/${_header_path}) 
endforeach(_header ${corbasim_python_EXPORTED_HEADERS})

set(corbasim_python_LIBS
    corbasim
    ${PYTHON_LIBRARIES}
    boost_python)

set(corbasim_python_SRCS
    python/auto_response.cpp
    )
add_library(corbasim_python SHARED ${corbasim_python_SRCS})
target_link_libraries(corbasim_python
    ${corbasim_python_LIBS})

set_target_properties(corbasim_python PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim_python DESTINATION lib)


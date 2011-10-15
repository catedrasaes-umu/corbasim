set(corbasim_qt_python_EXPORTED_HEADERS
    qt/python/AutoResponse.hpp
    qt/python/AutoResponseMainWindow.hpp)

foreach(_header ${corbasim_qt_python_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header} 
        DESTINATION include/corbasim/${_header_path}) 
endforeach(_header ${corbasim_qt_python_EXPORTED_HEADERS})

set(corbasim_qt_python_MOC_HDRS
    qt/python/AutoResponse.hpp
    qt/python/AutoResponseMainWindow.hpp)

set(corbasim_qt_python_SRCS
    qt/python/AutoResponse.cpp
    qt/python/AutoResponseMainWindow.cpp)

set(corbasim_qt_python_LIBS
    ${QT_LIBRARIES}
    corbasim_python
    corbasim_qt
)

qt4_wrap_cpp(corbasim_qt_python_MOC_SRCS ${corbasim_qt_python_MOC_HDRS})
add_library(corbasim_qt_python SHARED ${corbasim_qt_python_SRCS} 
    ${corbasim_qt_python_MOC_SRCS})
target_link_libraries(corbasim_qt_python
    ${corbasim_qt_python_LIB})

set_target_properties(corbasim_qt_python PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim_qt_python DESTINATION lib)


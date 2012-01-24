set(corbasim_reflective_gui_EXPORTED_HEADERS
    reflective_gui/OperationSequence.hpp
    reflective_gui/ReflectiveGUI.hpp)

foreach(_header ${corbasim_reflective_gui_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/corbasim/${_header_path})
endforeach(_header ${corbasim_reflective_gui_EXPORTED_HEADERS})

set(corbasim_reflective_gui_MOC_HDRS
    reflective_gui/OperationSequence.hpp
    reflective_gui/ReflectiveGUI.hpp)

set(corbasim_reflective_gui_SRCS
    reflective_gui/OperationSequence.cpp
    reflective_gui/ReflectiveGUI.cpp)

set(corbasim_reflective_gui_LIBS
    ${QT_LIBRARIES}
    corbasim)

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(corbasim_reflective_gui_MOC_SRCS ${corbasim_reflective_gui_MOC_HDRS} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_library(corbasim_reflective_gui SHARED ${corbasim_reflective_gui_SRCS}
    ${corbasim_reflective_gui_MOC_SRCS})
target_link_libraries(corbasim_reflective_gui
    ${corbasim_reflective_gui_LIBS})

set_target_properties(corbasim_reflective_gui PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim_reflective_gui DESTINATION lib)


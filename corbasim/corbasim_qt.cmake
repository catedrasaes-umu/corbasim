set(corbasim_qt_EXPORTED_HEADERS
    qt/CustomLayouts.hpp
    qt/MultiFileSelectionWidget.hpp
    qt/ReferenceFinder.hpp
    qt/SortableGroup.hpp
    qt/Status.hpp
    qt/TabWidget.hpp
    qt/export.hpp
    qt/types.hpp
    qt/StartStopButton.hpp
    qt/FormWidget.hpp
)

foreach(_header ${corbasim_qt_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/corbasim/${_header_path})
endforeach(_header ${corbasim_qt_EXPORTED_HEADERS})

set(corbasim_qt_MOC_HDRS
    # private
    qt/private/MultiScriptEditor.hpp
    qt/private/ScriptEditor.hpp
    qt/private/codeeditor.h

    qt/CustomLayouts.hpp
    qt/MultiFileSelectionWidget.hpp
    qt/ReferenceFinder.hpp
    qt/SortableGroup.hpp
    qt/Status.hpp
    qt/TabWidget.hpp
    qt/StartStopButton.hpp
    qt/FormWidget.hpp
)

set(corbasim_qt_SRCS
    # private
    qt/private/MultiScriptEditor.cpp
    qt/private/ScriptEditor.cpp
    qt/private/codeeditor.cpp
    qt/private/qscriptsyntaxhighlighter.cpp

    qt/CustomLayouts.cpp
    qt/MultiFileSelectionWidget.cpp
    qt/ReferenceFinder.cpp
    qt/SortableGroup.cpp
    qt/Status.cpp
    qt/TabWidget.cpp
    qt/initialize.cpp
    qt/StartStopButton.cpp
    qt/FormWidget.cpp
)

message(STATUS "Qt libraries: ${QT_LIBRARIES}")

set(corbasim_qt_LIBS
    ${QT_LIBRARIES}
    corbasim)

qt4_add_resources(corbasim_qt_RCC qt/corbasim_qt.qrc)

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(corbasim_qt_MOC_SRCS ${corbasim_qt_MOC_HDRS} 
    OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_library(corbasim_qt SHARED ${corbasim_qt_SRCS}
    ${corbasim_qt_MOC_SRCS}
    ${corbasim_qt_RCC})
target_link_libraries(corbasim_qt
    ${corbasim_qt_LIBS})

set_target_properties(corbasim_qt PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

add_library(corbasim_qt_s STATIC ${corbasim_qt_SRCS}
    ${corbasim_qt_MOC_SRCS}
    ${corbasim_qt_RCC})

install(TARGETS corbasim_qt corbasim_qt_s DESTINATION lib)


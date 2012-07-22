set(corbasim_qt_EXPORTED_HEADERS
    qt/export.hpp
    # QObjects
    qt/TabWidget.hpp
    qt/PlotModel.hpp

    qt/FilterModel.hpp
    qt/CustomLayouts.hpp
    qt/SortableGroup.hpp
    qt/types.hpp
    qt/ReferenceModel.hpp
    qt/ReferenceFinder.hpp
    qt/Status.hpp
    qt/RangedWidget.hpp
    qt/MultiFileSelectionWidget.hpp
    qt/TemplatedSpinBox.hpp
    qt/ScriptWindow.hpp
    qt/ObjrefWidget.hpp
)

foreach(_header ${corbasim_qt_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/corbasim/${_header_path})
endforeach(_header ${corbasim_qt_EXPORTED_HEADERS})

set(corbasim_qt_MOC_HDRS
    # private
    qt/private/codeeditor.h
    qt/private/ScriptEditor.hpp
    qt/private/MultiScriptEditor.hpp

    qt/TabWidget.hpp
    qt/PlotModel.hpp
    qt/ReferenceFinder.hpp
    qt/FilterModel.hpp
    qt/CustomLayouts.hpp
    qt/SortableGroup.hpp
    qt/ReferenceModel.hpp
    qt/ScriptWindow.hpp
    qt/ObjrefWidget.hpp
    qt/MultiFileSelectionWidget.hpp
    qt/RangedWidget.hpp
    qt/Status.hpp
)

set(corbasim_qt_SRCS
    # private
    qt/private/codeeditor.cpp
    qt/private/qscriptsyntaxhighlighter.cpp
    qt/private/ScriptEditor.cpp
    qt/private/MultiScriptEditor.cpp

    qt/TabWidget.cpp
    qt/PlotModel.cpp
    qt/FilterModel.cpp
    qt/CustomLayouts.cpp
    qt/SortableGroup.cpp
    qt/ReferenceModel.cpp
    qt/ReferenceFinder.cpp
    qt/initialize.cpp
    qt/ScriptWindow.cpp
    qt/ObjrefWidget.cpp
    qt/MultiFileSelectionWidget.cpp
    qt/Status.cpp
)

message(STATUS "Qt libraries: ${QT_LIBRARIES}")

set(corbasim_qt_LIBS
    ${QT_LIBRARIES}
    corbasim)

qt4_add_resources(corbasim_qt_RCC qt/corbasim_qt.qrc)

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(corbasim_qt_MOC_SRCS ${corbasim_qt_MOC_HDRS} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

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


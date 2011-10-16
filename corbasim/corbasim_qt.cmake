set(corbasim_qt_EXPORTED_HEADERS
    gui/dialogs.hpp
    gui/gui_factory_fwd.hpp
    gui/gui_factory.hpp
    gui/initialize.hpp
    gui/macros.hpp
    gui/macros_impl.hpp
    gui/tree_factory.hpp
    gui/trees/array.hpp
    gui/trees/enum.hpp
    gui/trees_fwd.hpp
    gui/trees.hpp
    gui/trees/primitive.hpp
    gui/trees/sequence.hpp
    gui/trees/string.hpp
    gui/trees/struct.hpp
    gui/widget_factory_fwd.hpp
    gui/widget_factory.hpp
    gui/widgets/array.hpp
    gui/widgets/enum.hpp
    gui/widgets_fwd.hpp
    gui/widgets/generic.hpp
    gui/widgets/grid.hpp
    gui/widgets.hpp
    gui/widgets/objrefvar.hpp
    gui/widgets/primitive.hpp
    gui/widgets/sequence_fwd.hpp
    gui/widgets/sequence.hpp
    gui/widgets/string.hpp
    gui/widgets/struct.hpp

    # QObjects
    qt/Interpreter.hpp
    qt/Status.hpp
    qt/MultiInputWidget.hpp
    qt/RangedWidget.hpp
    qt/LogTreeWidget.hpp
    qt/LogWidget.hpp
    qt/MultiFileSelectionWidget.hpp
    qt/PythonHighlighter.hpp
    qt/TemplatedSpinBox.hpp
    qt/RequestDialog.hpp
    qt/RequestNotifier.hpp
    qt/RequestProcessor.hpp
    qt/SimpleScriptEditor.hpp
    qt/client/SimpleClient.hpp
    qt/ObjrefWidget.hpp
    qt/SequenceWidget.hpp)

foreach(_header ${corbasim_qt_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header} 
        DESTINATION include/corbasim/${_header_path}) 
endforeach(_header ${corbasim_qt_EXPORTED_HEADERS})

set(corbasim_qt_MOC_HDRS
    qt/Interpreter.hpp
    qt/client/SimpleClient.hpp
    qt/SimpleScriptEditor.hpp
    qt/ObjrefWidget.hpp
    qt/MultiFileSelectionWidget.hpp
    qt/MultiInputWidget.hpp
    qt/SequenceWidget.hpp
    qt/RequestDialog.hpp
    qt/RequestNotifier.hpp
    qt/RequestProcessor.hpp
    qt/RangedWidget.hpp
    qt/LogWidget.hpp
    qt/LogTreeWidget.hpp
    qt/Status.hpp)

set(corbasim_qt_SRCS
    gui/tree_factory.cpp
    gui/gui_factory.cpp

    qt/Interpreter.cpp
    qt/initialize.cpp
    qt/client/SimpleClient.cpp
    qt/SimpleScriptEditor.cpp
    qt/ObjrefWidget.cpp
    qt/LogWidget.cpp
    qt/LogTreeWidget.cpp
    qt/MultiFileSelectionWidget.cpp
    qt/MultiInputWidget.cpp
    qt/PythonHighlighter.cpp
    qt/RequestProcessor.cpp
    qt/SequenceWidget.cpp
    qt/RequestDialog.cpp
    qt/Status.cpp)

set(corbasim_qt_LIBS
    ${QT_LIBRARIES}
    corbasim
    boost_serialization
    boost_thread
    boost_system
    boost_regex
)

qt4_wrap_cpp(corbasim_qt_MOC_SRCS ${corbasim_qt_MOC_HDRS})
add_library(corbasim_qt SHARED ${corbasim_qt_SRCS} 
    ${corbasim_qt_MOC_SRCS})
target_link_libraries(corbasim_qt
    ${corbasim_qt_LIB})

set_target_properties(corbasim_qt PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim_qt DESTINATION lib)


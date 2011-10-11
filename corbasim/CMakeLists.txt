#
# CORBASIM BASE
#

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
    core/caller.hpp
    core/config.hpp
    core/copy.hpp
    core/factory.cpp
    core/injector.hpp
    core/inserter.hpp
    core/range.hpp
    core/reference_validator.hpp
    core/request_serializer.hpp
    core/servant.hpp
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
    mpl/for_each.hpp
    mpl.hpp
    mpl/vector100.hpp
    mpl/vector200.hpp
    mpl/vector50.hpp
    mpl/vector.hpp
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
    boost_serialization
    boost_thread
    boost_system
    boost_regex)

set(corbasim_SRCS
    core/archives.cpp
    core/core.cpp
    core/event_notifier.cpp
    core/reference_repository.cpp
    core/reference_validator.cpp
    core/request_serializer.cpp

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

#
# CORBASIM QT
#
if(NOT DEFINED CORBASIM_DISABLE_UI)

    find_package(Qt4 REQUIRED)

    include(${QT_USE_FILE})

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
        qt/Status.hpp
        qt/MultiInputWidget.hpp
        qt/RangedWidget.hpp
        qt/LogTreeWidget.hpp
        qt/MultiFileSelectionWidget.hpp
        qt/TemplatedSpinBox.hpp
        qt/RequestDialog.hpp
        qt/RequestNotifier.hpp
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
        qt/client/SimpleClient.hpp
        qt/SimpleScriptEditor.hpp
        qt/ObjrefWidget.hpp
        qt/MultiFileSelectionWidget.hpp
        qt/MultiInputWidget.hpp
        qt/SequenceWidget.hpp
        qt/RequestDialog.hpp
        qt/RequestNotifier.hpp
        qt/RangedWidget.hpp
        qt/LogTreeWidget.hpp
        qt/Status.hpp)

    set(corbasim_qt_SRCS
        gui/tree_factory.cpp
        gui/gui_factory.cpp

        qt/initialize.cpp
        qt/client/SimpleClient.cpp
        qt/SimpleScriptEditor.cpp
        qt/ObjrefWidget.cpp
        qt/LogTreeWidget.cpp
        qt/MultiFileSelectionWidget.cpp
        qt/MultiInputWidget.cpp
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
endif()

#
# CORBASIM PYTHON
#

find_package(PythonLibs REQUIRED)

# TODO check python found

include_directories(${PYTHON_INCLUDE_PATH})

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

#
# CORBASIM QT PYTHON
#
if(NOT DEFINED CORBASIM_DISABLE_UI)

    find_package(Qt4 REQUIRED)

    include(${QT_USE_FILE})

    set(corbasim_qt_python_EXPORTED_HEADERS
        qt/AutoResponse.hpp)

    foreach(_header ${corbasim_qt_python_EXPORTED_HEADERS})
        get_filename_component(_header_path ${_header} PATH)
        install(FILES ${_header} 
            DESTINATION include/corbasim/${_header_path}) 
    endforeach(_header ${corbasim_qt_python_EXPORTED_HEADERS})

    set(corbasim_qt_python_MOC_HDRS
        qt/python/AutoResponse.hpp)

    set(corbasim_qt_python_SRCS
        qt/python/AutoResponse.cpp)

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
endif()



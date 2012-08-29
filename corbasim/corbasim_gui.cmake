set(corbasim_gui_EXPORTED_HEADERS
    gui/Application.hpp
    gui/Model.hpp
    gui/export.hpp
    gui/json.hpp
    gui/qvariant.hpp
    gui/types.hpp
    gui/utils.hpp

    # item models
    gui/item/FilterModel.hpp
    gui/item/InstanceModel.hpp
    gui/item/InterfaceModel.hpp
    gui/item/LogModel.hpp
    gui/item/ModelNode.hpp
    gui/item/OperationParametersModel.hpp
    gui/item/OperationsView.hpp
    gui/item/ParametersModel.hpp
    gui/item/ScriptModel.hpp
    gui/item/TreeView.hpp

    # script
    gui/script/ReflectiveScriptClass.hpp
    gui/script/ScriptEvaluator.hpp

    # dialogs
    gui/dialog/CreateDialog.hpp
    gui/dialog/SetReferenceDialog.hpp
    gui/dialog/UpdateReferenceDialog.hpp

    # server
    gui/server/Server.hpp

    # client
    gui/client/SimpleClient.hpp

    gui/InputRequestProcessor.hpp
    gui/OperationForm.hpp
    gui/ParametersFromFilesTool.hpp
    gui/ReflectiveGUI.hpp
    gui/RequestDialog.hpp
    gui/Sender.hpp

    # tools
    gui/tools/DumpTool.hpp
    gui/tools/FilteredLogView.hpp
    gui/tools/OperationSequence.hpp
    gui/tools/SenderSequence.hpp
    gui/tools/SimpleScriptEditor.hpp

    # TODO gui/RecorderTool.hpp
    # TODO gui/ServerApp.hpp
)

foreach(_header ${corbasim_gui_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/corbasim/${_header_path})
endforeach(_header ${corbasim_gui_EXPORTED_HEADERS})

set(corbasim_gui_MOC_HDRS
    gui/Model.hpp
    gui/Application.hpp

    # item models
    gui/item/LogModel.hpp
    gui/item/InstanceModel.hpp
    gui/item/InterfaceModel.hpp
    gui/item/FilterModel.hpp
    gui/item/ParametersModel.hpp
    gui/item/OperationsView.hpp
    gui/item/OperationParametersModel.hpp
    gui/item/ScriptModel.hpp
    gui/item/TreeView.hpp

    # script
    gui/script/ScriptEvaluator.hpp

    # dialogs
    gui/dialog/CreateDialog.hpp
    gui/dialog/UpdateReferenceDialog.hpp
    gui/dialog/SetReferenceDialog.hpp

    # server
    gui/server/Server.hpp

    # client
    gui/client/SimpleClient.hpp

    gui/InputRequestProcessor.hpp
    gui/OperationForm.hpp
    gui/ParametersFromFilesTool.hpp
    gui/ReflectiveGUI.hpp
    gui/RequestDialog.hpp
    gui/Sender.hpp

    # tools
    gui/tools/DumpTool.hpp
    gui/tools/FilteredLogView.hpp
    gui/tools/OperationSequence.hpp
    gui/tools/SenderSequence.hpp
    gui/tools/SimpleScriptEditor.hpp

    # TODO gui/RecorderTool.hpp
)

set(corbasim_gui_SRCS
    gui/json.cpp
    gui/utils.hpp
    gui/utils.cpp
    gui/qvariant.cpp
    gui/initialize.cpp
    gui/Model.cpp
    gui/Application.cpp

    # item model
    gui/item/ModelNode.cpp
    gui/item/InstanceModel.cpp
    gui/item/InterfaceModel.cpp
    gui/item/FilterModel.cpp
    gui/item/LogModel.cpp
    gui/item/ParametersModel.cpp
    gui/item/OperationsView.cpp
    gui/item/OperationParametersModel.cpp
    gui/item/ScriptModel.cpp
    gui/item/TreeView.cpp

    # script
    gui/script/ReflectiveScriptClass.cpp
    gui/script/ScriptEvaluator.cpp

    # dialogs
    gui/dialog/CreateDialog.cpp
    gui/dialog/UpdateReferenceDialog.cpp
    gui/dialog/SetReferenceDialog.cpp

    # server
    gui/server/Server.cpp

    # client
    gui/client/SimpleClient.cpp

    gui/Sender.cpp
    gui/InputRequestProcessor.cpp
    gui/OperationForm.cpp
    gui/ParametersFromFilesTool.cpp
    gui/ReflectiveGUI.cpp
    gui/RequestDialog.cpp

    # tools
    gui/tools/DumpTool.cpp
    gui/tools/FilteredLogView.cpp
    gui/tools/OperationSequence.cpp
    gui/tools/SenderSequence.cpp
    gui/tools/SimpleScriptEditor.cpp

    # TODO gui/RecorderTool.cpp
    # TODO gui/ServerApp.cpp
)

set(corbasim_gui_LIBS
    ${QT_LIBRARIES}
    corbasim
    corbasim_qt)

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(corbasim_gui_MOC_SRCS ${corbasim_gui_MOC_HDRS} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_library(corbasim_gui SHARED ${corbasim_gui_SRCS}
    ${corbasim_gui_MOC_SRCS})
target_link_libraries(corbasim_gui
    ${corbasim_gui_LIBS})

set_target_properties(corbasim_gui PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

add_library(corbasim_gui_s STATIC ${corbasim_gui_SRCS}
    ${corbasim_gui_MOC_SRCS})

install(TARGETS corbasim_gui corbasim_gui_s DESTINATION lib)

add_executable(corbasim_script_evaluator_test 
    gui/script/ScriptEvaluatorTest.cpp)
target_link_libraries(corbasim_script_evaluator_test
    corbasim_gui
    boost_program_options)

add_executable(corbasim_client.real
    gui/client/ClientMain.cpp)
target_link_libraries(corbasim_client.real
    corbasim_gui
    boost_program_options)
add_executable(corbasim_client
    gui/launcher.cpp)
target_link_libraries(corbasim_client
    ${QT_LIBRARIES})
install(TARGETS corbasim_client corbasim_client.real DESTINATION bin)


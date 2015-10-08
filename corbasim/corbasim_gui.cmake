set(corbasim_gui_EXPORTED_HEADERS
    gui/Application.hpp
    gui/Model.hpp
    gui/export.hpp
    gui/json.hpp
    gui/qvariant.hpp
    gui/types.hpp
    gui/utils.hpp
    gui/ObjrefWidget.hpp

    # proc
    gui/proc/RequestProcessor.hpp
    gui/proc/DumpProcessor.hpp
    gui/proc/FileLoaderProcessor.hpp
    gui/proc/HolderEmitter.hpp

    # item models
    gui/item/ApplicationLogModel.hpp
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
    gui/script/TriggerEngine.hpp

    # dialogs
    gui/dialog/CreateDialog.hpp
    gui/dialog/SetReferenceDialog.hpp
    gui/dialog/UpdateReferenceDialog.hpp

    # server
    gui/server/Server.hpp
    gui/server/ServerApp.hpp

    # client
    gui/client/ClientApp.hpp
    gui/client/SimpleClient.hpp

    gui/InputRequestProcessor.hpp
    gui/NSManager.hpp
    gui/OperationForm.hpp
    gui/ReflectiveGUI.hpp
    gui/RequestDialog.hpp
    gui/Sender.hpp

    # tools
    gui/tools/AbstractTool.hpp
    gui/tools/AbstractInputTool.hpp
    gui/tools/AbstractSequenceTool.hpp
    gui/tools/DumpTool.hpp
    gui/tools/FilteredLogView.hpp
    gui/tools/OperationSequence.hpp
    gui/tools/ParametersFromFilesTool.hpp
    gui/tools/SenderSequence.hpp
    gui/tools/StatusView.hpp
    gui/tools/SimpleScriptEditor.hpp
    gui/tools/ValueViewerTool.hpp
    gui/tools/RecorderTool.hpp
)

foreach(_header ${corbasim_gui_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/corbasim/${_header_path})
endforeach(_header ${corbasim_gui_EXPORTED_HEADERS})

set(corbasim_gui_MOC_HDRS
    gui/Model.hpp
    gui/Application.hpp
    gui/ObjrefWidget.hpp

    # proc
    gui/proc/DumpProcessor.hpp
    gui/proc/FileLoaderProcessor.hpp
    gui/proc/HolderEmitter.hpp

    # item models
    gui/item/ApplicationLogModel.hpp
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
    gui/script/TriggerEngine.hpp

    # dialogs
    gui/dialog/CreateDialog.hpp
    gui/dialog/UpdateReferenceDialog.hpp
    gui/dialog/SetReferenceDialog.hpp

    # server
    gui/server/Server.hpp

    # client
    gui/client/SimpleClient.hpp

    gui/InputRequestProcessor.hpp
    gui/NSManager.hpp
    gui/OperationForm.hpp
    gui/ReflectiveGUI.hpp
    gui/RequestDialog.hpp
    gui/Sender.hpp

    # tools
    gui/tools/AbstractTool.hpp
    gui/tools/AbstractInputTool.hpp
    gui/tools/AbstractSequenceTool.hpp
    gui/tools/DumpTool.hpp
    gui/tools/FilteredLogView.hpp
    gui/tools/OperationSequence.hpp
    gui/tools/ParametersFromFilesTool.hpp
    gui/tools/SenderSequence.hpp
    gui/tools/SimpleScriptEditor.hpp
    gui/tools/StatusView.hpp
    gui/tools/ValueViewerTool.hpp
    gui/tools/RecorderTool.hpp
)

set(corbasim_gui_SRCS
    gui/Application.cpp
    gui/Model.cpp
    gui/initialize.cpp
    gui/json.cpp
    gui/qvariant.cpp
    gui/utils.cpp
    gui/ObjrefWidget.cpp

    # proc
    gui/proc/RequestProcessor.cpp
    gui/proc/DumpProcessor.cpp
    gui/proc/FileLoaderProcessor.cpp
    gui/proc/HolderEmitter.cpp

    # item model
    gui/item/ApplicationLogModel.cpp
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
    gui/script/TriggerEngine.cpp

    # dialogs
    gui/dialog/CreateDialog.cpp
    gui/dialog/UpdateReferenceDialog.cpp
    gui/dialog/SetReferenceDialog.cpp

    # server
    gui/server/Server.cpp
    gui/server/ServerApp.cpp

    # client
    gui/client/ClientApp.cpp
    gui/client/SimpleClient.cpp

    gui/Sender.cpp
    gui/InputRequestProcessor.cpp
    gui/NSManager.cpp
    gui/OperationForm.cpp
    gui/ReflectiveGUI.cpp
    gui/RequestDialog.cpp

    # tools
    gui/tools/AbstractTool.cpp
    gui/tools/AbstractInputTool.cpp
    gui/tools/AbstractSequenceTool.cpp
    gui/tools/DumpTool.cpp
    gui/tools/FilteredLogView.cpp
    gui/tools/OperationSequence.cpp
    gui/tools/ParametersFromFilesTool.cpp
    gui/tools/SenderSequence.cpp
    gui/tools/SimpleScriptEditor.cpp
    gui/tools/StatusView.cpp
    gui/tools/ValueViewerTool.cpp
    gui/tools/RecorderTool.cpp
)

set(corbasim_gui_LIBS
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
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

install(TARGETS corbasim_gui DESTINATION lib)

add_executable(corbasim_script_evaluator_test 
    gui/script/ScriptEvaluatorTest.cpp)
target_link_libraries(corbasim_script_evaluator_test
    corbasim_gui
    ${Boost_PROGRAM_OPTIONS_LIBRARY})

add_executable(corbasim_client.real
    gui/client/ClientMain.cpp)
target_link_libraries(corbasim_client.real
    corbasim_gui
    ${Boost_PROGRAM_OPTIONS_LIBRARY})
add_executable(corbasim_client
    gui/launcher.cpp)
target_link_libraries(corbasim_client
    ${QT_LIBRARIES})
install(TARGETS corbasim_client corbasim_client.real DESTINATION bin)

if (${CORBASIM_STATIC_LIBS})
    add_library(corbasim_gui_s STATIC ${corbasim_gui_SRCS}
        ${corbasim_gui_MOC_SRCS})

    install(TARGETS corbasim_gui_s DESTINATION lib)
endif()

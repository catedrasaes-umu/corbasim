
set(CORBASIM_PREFIX corbasim_)
include(app.cmake)

set_target_properties(corbasim_app_idl PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

set(corbasim_app_SRCS
    AppModel.cpp
    AppController.cpp
    AppMainWindow.cpp
    
    AppConfiguration.cpp
    AppFileWatcher.cpp

    TriggerEngine.cpp

    view/CreateDialog.cpp
    view/Objref.cpp
    view/Servant.cpp

    model/Objref.cpp
    model/Servant.cpp

    NSWatcher.cpp

    # TODO
    # NSBrowser.cpp
    IDLBuilder.cpp
    )

set(corbasim_app_MOC_HDRS
    AppController.hpp
    AppMainWindow.hpp
    AppFileWatcher.hpp

    TriggerEngine.hpp

    view/CreateDialog.hpp
    view/Objref.hpp
    view/Servant.hpp

    NSWatcher.hpp

    # TODO
    # NSBrowser.hpp
    IDLBuilder.hpp
    )

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(corbasim_app_MOC_SRCS
    ${corbasim_app_MOC_HDRS} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_executable(corbasim_app.real
    main.cpp
    ${corbasim_app_MOC_SRCS}
    ${corbasim_app_SRCS})
target_link_libraries(corbasim_app.real
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    corbasim
    corbasim_qt
    corbasim_gui
    corbasim_app_idl)

install(TARGETS corbasim_app.real DESTINATION bin)
install(TARGETS corbasim_app_idl DESTINATION lib)

add_executable(corbasim_app_test EXCLUDE_FROM_ALL
    test.cpp)
target_link_libraries(corbasim_app_test
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    corbasim
    corbasim_qt
    corbasim_gui
    corbasim_app_idl)

# Launcher
add_executable(corbasim_app
    launcher.cpp
)
target_link_libraries(corbasim_app
    ${QT_LIBRARIES}
)
install(TARGETS corbasim_app DESTINATION bin)


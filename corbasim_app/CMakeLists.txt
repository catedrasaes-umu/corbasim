
set(CORBASIM_PREFIX corbasim_)
include(app.cmake)

set_target_properties(corbasim_app_idl PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

set(corbasim_app_SRCS
    AppModel.cpp
    AppController.cpp
    AppMainWindow.cpp
    main.cpp
    
    AppConfiguration.cpp

    TriggerEngine.cpp

    view/CreateDialog.cpp
    view/Objref.cpp
    view/Servant.cpp

    model/Objref.cpp
    model/Servant.cpp
    model/ReferenceModel.cpp
    )

set(corbasim_app_MOC_HDRS
    AppController.hpp
    AppMainWindow.hpp

    TriggerEngine.hpp

    view/CreateDialog.hpp
    view/Objref.hpp
    view/Servant.hpp
    
    model/ReferenceModel.hpp
    )

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(corbasim_app_MOC_SRCS
    ${corbasim_app_MOC_HDRS} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_executable(corbasim_app
    ${corbasim_app_MOC_SRCS}
    ${corbasim_app_SRCS})
target_link_libraries(corbasim_app
    dl # for dlopen, dlsym
    boost_filesystem
    boost_program_options
    corbasim
    corbasim_qt
    corbasim_app_idl)

install(TARGETS corbasim_app DESTINATION bin)
install(TARGETS corbasim_app_idl DESTINATION lib)

add_executable(corbasim_app_test test.cpp)
target_link_libraries(corbasim_app_test
    dl # for dlopen, dlsym
    corbasim
    corbasim_qt
    corbasim_app_idl)



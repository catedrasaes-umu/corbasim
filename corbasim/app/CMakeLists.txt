
set(CORBASIM_PREFIX corbasim_)
include(app.cmake)

set(corbasim_app_SRCS
    AppModel.cpp
    AppController.cpp
    AppMainWindow.cpp
    main.cpp

    view/CreateDialog.cpp
    view/Objref.cpp
    view/Servant.cpp

    model/Objref.cpp
    model/Servant.cpp
    )

set(corbasim_app_MOC_HDRS
    AppController.hpp
    AppMainWindow.hpp
    
    view/CreateDialog.hpp
    view/Objref.hpp
    view/Servant.hpp
    )

qt4_wrap_cpp(corbasim_app_MOC_SRCS 
    ${corbasim_app_MOC_HDRS})

add_executable(corbasim_app 
    ${corbasim_app_MOC_SRCS}
    ${corbasim_app_SRCS})
target_link_libraries(corbasim_app 
    dl # for dlopen, dlsym
    corbasim 
    corbasim_qt 
    corbasim_app_idl)

install(TARGETS corbasim_app DESTINATION bin)

add_executable(corbasim_app_test test.cpp)
target_link_libraries(corbasim_app_test 
    dl # for dlopen, dlsym
    corbasim 
    corbasim_qt 
    corbasim_app_idl)



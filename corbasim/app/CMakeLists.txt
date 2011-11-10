
set(corbasim_app_SRCS
    AppMainWindow.cpp
    main.cpp
    )

set(corbasim_app_MOC_HDRS
    AppMainWindow.hpp
    )

qt4_wrap_cpp(corbasim_app_MOC_SRCS 
    ${corbasim_app_MOC_HDRS})

add_executable(corbasim_app 
    ${corbasim_app_MOC_SRCS}
    ${corbasim_app_SRCS})
target_link_libraries(corbasim_app corbasim corbasim_qt)


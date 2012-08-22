# CORBASIM (core library)
# Depends on some boost libraries
include(corbasim.cmake)

# CORBASIM QT library
if(QT_FOUND)
    include(corbasim_qt.cmake)
    include(corbasim_gui.cmake)

    if (Qwt6_FOUND)
        #        include(corbasim_qwt.cmake)
    endif()
endif()

add_subdirectory(cosnaming)


find_package(PythonLibs)

include(corbasim.cmake)

if (PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_PATH})
    include(corbasim_python.cmake)
endif()

if(NOT DEFINED CORBASIM_DISABLE_UI)
    find_package(Qt4 REQUIRED)
    include(${QT_USE_FILE})

    include(corbasim_qt.cmake)

    if (PYTHONLIBS_FOUND)
        include(corbasim_qt_python.cmake)
    endif()
endif()


find_package(PythonLibs)
find_package(Lua51)

include(corbasim.cmake)

if(PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_PATH})
    include(corbasim_python.cmake)
endif()

if(LUA51_FOUND)
    include(corbasim_lua.cmake)
endif()

if(NOT DEFINED CORBASIM_DISABLE_UI)
    find_package(Qt4 REQUIRED)
    include(${QT_USE_FILE})

    include(corbasim_qt.cmake)
endif()


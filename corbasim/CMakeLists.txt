find_package(PythonLibs)
find_package(Lua51)

# CORBASIM (core library)
# Depends on some boost libraries
include(corbasim.cmake)

# CORBASIM Python library
# Just depends on core library
if(PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_PATH})
    include(corbasim_python.cmake)
endif()

# CORBASIM Lua library
# Just depends on core library
if(LUA51_FOUND)
    include(corbasim_lua.cmake)
endif()

# CORBASIM QT library
# Just depends on core library
if(NOT DEFINED CORBASIM_DISABLE_UI)
    find_package(Qt4 REQUIRED)
    include(${QT_USE_FILE})

    include(corbasim_qt.cmake)
endif()

# CORBASIM HTTP library
# Will allow to do remote calls over HTTP requests
# Depends on core library and cpp-netlib, proposed for Boost
if(DEFINED CORBASIM_ENABLE_HTTP)
    include(corbasim_http.cmake)
endif()





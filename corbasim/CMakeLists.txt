# CORBASIM (core library)
# Depends on some boost libraries
include(corbasim.cmake)

# CORBASIM Python library
if(PYTHONLIBS_FOUND AND Boost_PYTHON_LIBRARY)
    include_directories(${PYTHON_INCLUDE_PATH})
    include(corbasim_python.cmake)
endif()

# CORBASIM Lua library
if(LUA51_FOUND)
    include(corbasim_lua.cmake)
endif()

# CORBASIM QT library
if(QT_FOUND)
    set(QT_USE_QTSCRIPT 1)
    include(${QT_USE_FILE})

    include(corbasim_qt.cmake)

    add_subdirectory(app)
endif()

# CORBASIM HTTP library
# Will allow to do remote calls over HTTP requests
# Depends on core library and cpp-netlib, proposed for Boost
if(DEFINED CORBASIM_ENABLE_HTTP)
    include(corbasim_http.cmake)
endif()


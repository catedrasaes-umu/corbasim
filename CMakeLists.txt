cmake_minimum_required(VERSION 2.6)
project(corbasim C CXX)

# Numero de version
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_LEVEL 0)
set(${PROJECT_NAME}_VERSION
        "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}")

# Compilación en modo Release por defecto
if(NOT DEFINED CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT DEFINED CORBASIM_ORBIMPL)
    set(CORBASIM_ORBIMPL "TAO")
endif()

if("${CORBASIM_ORBIMPL}" STREQUAL "TAO")
    include(check_ace_tao)
    set(CORBASIM_ORB_LIBS
        TAO 
        TAO_PortableServer 
        TAO_AnyTypeCode 
        TAO_CosNaming 
        TAO_ObjRefTemplate)
elseif("${CORBASIM_ORBIMPL}" STREQUAL "OMNIORB4")
    # TODO check omni
endif()

add_definitions(-Wall)

set(Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.45.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!")
else(NOT Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(NOT Boost_FOUND)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(corbasim)
add_subdirectory(corbasim_idl)
add_subdirectory(examples EXCLUDE_FROM_ALL)
add_subdirectory(test EXCLUDE_FROM_ALL)

# Opciones de empaquetado
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_PATCH_LEVEL})
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)


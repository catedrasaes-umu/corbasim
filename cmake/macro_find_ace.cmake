# This module defines
#  ACE_FOUND -- true if ACE was found
#  ACE_LIBRARY -- the library to link against
#  ACE_INCLUDE_DIR -- path to ace/ACE.h
MACRO(FIND_ACE LIBNAME)

  GET_FILENAME_COMPONENT(parent_dir_ "${PROJECT_SOURCE_DIR}/.." ABSOLUTE)
  FIND_PATH(
    ACE_INCLUDE_DIR ace/ACE.h
    PATHS "${CMAKE_INSTALL_PREFIX}/include" "${parent_dir_}/ACE_wrappers"
    $ENV{ACE_ROOT} $ENV{ACE_ROOT}/include ${ACE_TAO_DEFAULT}/include
    DOC "Path to ace/ACE.h"
    )
  
  # This prevents it being taken from cache.
  SET(ACE_LIBRARY ACE_LIBRARY-NOTFOUND)
  
  FIND_LIBRARY(
    ACE_LIBRARY "${LIBNAME}"
    PATHS "${CMAKE_INSTALL_PREFIX}/lib" "${parent_dir_}/ACE_wrappers/ace"
    $ENV{ACE_ROOT} $ENV{ACE_ROOT}/lib ${ACE_TAO_DEFAULT}/lib
    DOC "Path to ACE library file"
    )
  IF(ACE_INCLUDE_DIR AND ACE_LIBRARY)
    SET(ACE_FOUND TRUE)
  ELSE(ACE_INCLUDE_DIR AND ACE_LIBRARY)
    SET(ACE_FOUND FALSE)
  ENDIF(ACE_INCLUDE_DIR AND ACE_LIBRARY)

ENDMACRO(FIND_ACE)


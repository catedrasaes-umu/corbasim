###############################################################################
# MACRO: TAO_IDL
#
# Entrada:
#         - ficheros IDL
#         - ${TAO_IDL_COMPILER} - Ruta al compilador de IDL
#         - ${TAO_IDL_OPTIONS} - Opciones del compilador
# Salida: Por cada fichero IDL "interfaz"
#         - ${interfaz_STUB} - Ficheros stub
#         - ${interfaz_SKEL} - Ficheros skeleton
#         - ${interfaz_GENERATED} - Todos los ficheros generados
#         - Reglas para construir los ficheros generados a partir del fichero
#         IDL.
#         - ${TAO_IDL_GENERATED} - Todos los ficheros generados a partir de
#         todas la interfaces.
#
# Nota: Los ficheros generados se generan en el directorio
#       ${CMAKE_CURRENT_SOURCE_DIRECTORY}
#       Da igual que se encuentren bajo control de versiones ya. Si el fichero
#       es posterior al generador, este se vuelve a generar. 
#
# Nota: Ejemplo de uso:
#
#  TAO_IDL(mapping.idl test.idl)
#
###############################################################################

include(MacroAddFileDependencies)

macro(TAO_IDL)

  foreach(_in_FILE ${ARGN})

    GET_FILENAME_COMPONENT(_out_FILE ${_in_FILE} NAME_WE)
    GET_FILENAME_COMPONENT(_in_PATH ${_in_FILE} PATH)

    if(_in_PATH STREQUAL "")
	set(_out_BASE ${CMAKE_CURRENT_SOURCE_DIR})
    else()
	set(_out_BASE ${CMAKE_CURRENT_SOURCE_DIR}/${_in_PATH})
    endif()

    SET(TAO_IDL_OPTIONS_IMPL -Sd -Sm -I ${_out_BASE} -o ${_out_BASE} ${TAO_IDL_OPTIONS}) # -as

    SET(out_FILE ${_out_BASE}/${_out_FILE})

    SET(${_out_FILE}_STUB ${out_FILE}C.h ${out_FILE}C.cpp)
    SET(${_out_FILE}_SKEL ${out_FILE}S.h ${out_FILE}S.cpp)
    SET(${_out_FILE}_INL ${out_FILE}S.inl ${out_FILE}C.inl)

    SET(${_out_FILE}_GENERATED
      ${${_out_FILE}_STUB} ${${_out_FILE}_SKEL}
      )

    # foreach(_file ${${_out_FILE}_GENERATED})
    #     message(STATUS "${_file} will be generated from ${_in_FILE}")
    # endforeach()

    SET(TAO_IDL_GENERATED ${TAO_IDL_GENERATED} ${${_out_FILE}_GENERATED})

    # Comando para la generacion de stubs y skels
    ADD_CUSTOM_COMMAND(
      OUTPUT ${${_out_FILE}_GENERATED}
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${_in_FILE}
      COMMAND ${TAO_IDL_COMPILER} ${TAO_IDL_OPTIONS_IMPL} ${CMAKE_CURRENT_SOURCE_DIR}/${_in_FILE}
      )

    SET_SOURCE_FILES_PROPERTIES(
     ${${_out_FILE}_GENERATED}
     PROPERTIES
     GENERATED TRUE
     )


#    SET_DIRECTORY_PROPERTIES(
#     DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#     PROPERTY
#     CLEAN_NO_CUSTOM TRUE
#     )
  endforeach(_in_FILE ${ARGN})
endmacro(TAO_IDL)


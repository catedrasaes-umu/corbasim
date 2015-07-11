


set(mapping_GENERATED
    ${CMAKE_CURRENT_SOURCE_DIR}/mappingC.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mappingC.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mappingS.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mappingS.cpp)

add_custom_command(
    OUTPUT ${mapping_GENERATED}
    DEPENDS mapping.idl
    COMMAND ${CORBASIM_ORB_IDL_COMPILER} ${CORBASIM_ORB_IDL_COMPILER_OPTIONS} mapping.idl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}mapping_idl SHARED ${mapping_GENERATED} mapping_adapted.cpp)
install(TARGETS ${CORBASIM_PREFIX}mapping_idl DESTINATION lib)

add_library(${CORBASIM_PREFIX}mapping_idl_s STATIC ${mapping_GENERATED} mapping_adapted.cpp)
install(TARGETS ${CORBASIM_PREFIX}mapping_idl_s DESTINATION lib)



# Corbasim reflective library
add_library(corbasim_reflective_HelloApp_Hello SHARED HelloApp_Hello_reflective.cpp)
target_link_libraries(corbasim_reflective_HelloApp_Hello
    ${CORBASIM_PREFIX}mapping_idl
    # CORBASIM Library
    corbasim)
install(TARGETS corbasim_reflective_HelloApp_Hello DESTINATION lib)

add_library(corbasim_static_reflective_HelloApp_Hello STATIC HelloApp_Hello_reflective.cpp)
install(TARGETS corbasim_static_reflective_HelloApp_Hello DESTINATION lib)


    

# Corbasim reflective library
add_library(corbasim_reflective_Test_Huge SHARED Test_Huge_reflective.cpp)
target_link_libraries(corbasim_reflective_Test_Huge
    ${CORBASIM_PREFIX}mapping_idl
    # CORBASIM Library
    corbasim)
install(TARGETS corbasim_reflective_Test_Huge DESTINATION lib)

add_library(corbasim_static_reflective_Test_Huge STATIC Test_Huge_reflective.cpp)
install(TARGETS corbasim_static_reflective_Test_Huge DESTINATION lib)




# Corbasim reflective library
add_library(corbasim_reflective_AAAAAAAAA_IIIIIIIIII SHARED AAAAAAAAA_IIIIIIIIII_reflective.cpp)
target_link_libraries(corbasim_reflective_AAAAAAAAA_IIIIIIIIII
    ${CORBASIM_PREFIX}mapping_idl
    # CORBASIM Library
    corbasim)
install(TARGETS corbasim_reflective_AAAAAAAAA_IIIIIIIIII DESTINATION lib)

add_library(corbasim_static_reflective_AAAAAAAAA_IIIIIIIIII STATIC AAAAAAAAA_IIIIIIIIII_reflective.cpp)
install(TARGETS corbasim_static_reflective_AAAAAAAAA_IIIIIIIIII DESTINATION lib)




# Corbasim reflective library
add_library(corbasim_reflective_SimpleExample_Test SHARED SimpleExample_Test_reflective.cpp)
target_link_libraries(corbasim_reflective_SimpleExample_Test
    ${CORBASIM_PREFIX}mapping_idl
    # CORBASIM Library
    corbasim)
install(TARGETS corbasim_reflective_SimpleExample_Test DESTINATION lib)

add_library(corbasim_static_reflective_SimpleExample_Test STATIC SimpleExample_Test_reflective.cpp)
install(TARGETS corbasim_static_reflective_SimpleExample_Test DESTINATION lib)




# Corbasim reflective library
add_library(corbasim_reflective_StringTest_InterfaceString SHARED StringTest_InterfaceString_reflective.cpp)
target_link_libraries(corbasim_reflective_StringTest_InterfaceString
    ${CORBASIM_PREFIX}mapping_idl
    # CORBASIM Library
    corbasim)
install(TARGETS corbasim_reflective_StringTest_InterfaceString DESTINATION lib)

add_library(corbasim_static_reflective_StringTest_InterfaceString STATIC StringTest_InterfaceString_reflective.cpp)
install(TARGETS corbasim_static_reflective_StringTest_InterfaceString DESTINATION lib)




# Corbasim reflective library
add_library(corbasim_reflective_MyModule_MyInterface SHARED MyModule_MyInterface_reflective.cpp)
target_link_libraries(corbasim_reflective_MyModule_MyInterface
    ${CORBASIM_PREFIX}mapping_idl
    # CORBASIM Library
    corbasim)
install(TARGETS corbasim_reflective_MyModule_MyInterface DESTINATION lib)

add_library(corbasim_static_reflective_MyModule_MyInterface STATIC MyModule_MyInterface_reflective.cpp)
install(TARGETS corbasim_static_reflective_MyModule_MyInterface DESTINATION lib)




# Corbasim reflective library
add_library(corbasim_reflective_Test_Prueba SHARED Test_Prueba_reflective.cpp)
target_link_libraries(corbasim_reflective_Test_Prueba
    ${CORBASIM_PREFIX}mapping_idl
    # CORBASIM Library
    corbasim)
install(TARGETS corbasim_reflective_Test_Prueba DESTINATION lib)

add_library(corbasim_static_reflective_Test_Prueba STATIC Test_Prueba_reflective.cpp)
install(TARGETS corbasim_static_reflective_Test_Prueba DESTINATION lib)




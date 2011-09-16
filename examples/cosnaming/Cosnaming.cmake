

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(Cosnaming_GENERATED
	${CMAKE_CURRENT_SOURCE_DIR}/CosnamingC.h
	${CMAKE_CURRENT_SOURCE_DIR}/CosnamingC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/CosnamingC.inl
	${CMAKE_CURRENT_SOURCE_DIR}/CosnamingS.h
	${CMAKE_CURRENT_SOURCE_DIR}/CosnamingS.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/CosnamingS.inl)

add_custom_command(
	OUTPUT ${Cosnaming_GENERATED}
	DEPENDS Cosnaming.idl
	COMMAND tao_idl ${TAO_IDL_OPTIONS} Cosnaming.idl
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CORBASIM_PREFIX}Cosnaming_idl SHARED ${Cosnaming_GENERATED})

	
	
	















# Client
add_executable(${CORBASIM_PREFIX}CosNaming_NamingContext_client CosNaming_NamingContext_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_NamingContext_client 
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim corbasim_qt
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate
	# QT 
	${QT_LIBRARIES})
	
# Injector	
add_executable(${CORBASIM_PREFIX}CosNaming_NamingContext_injector CosNaming_NamingContext_injector.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_NamingContext_injector
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)
	
# Server
add_executable(${CORBASIM_PREFIX}CosNaming_NamingContext_server CosNaming_NamingContext_server.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_NamingContext_server 
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)





# Client
add_executable(${CORBASIM_PREFIX}CosNaming_BindingIterator_client CosNaming_BindingIterator_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_BindingIterator_client 
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim corbasim_qt
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate
	# QT 
	${QT_LIBRARIES})
	
# Injector	
add_executable(${CORBASIM_PREFIX}CosNaming_BindingIterator_injector CosNaming_BindingIterator_injector.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_BindingIterator_injector
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)
	
# Server
add_executable(${CORBASIM_PREFIX}CosNaming_BindingIterator_server CosNaming_BindingIterator_server.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_BindingIterator_server 
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)





# Client
add_executable(${CORBASIM_PREFIX}CosNaming_NamingContextExt_client CosNaming_NamingContextExt_client_main.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_NamingContextExt_client 
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim corbasim_qt
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate
	# QT 
	${QT_LIBRARIES})
	
# Injector	
add_executable(${CORBASIM_PREFIX}CosNaming_NamingContextExt_injector CosNaming_NamingContextExt_injector.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_NamingContextExt_injector
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)
	
# Server
add_executable(${CORBASIM_PREFIX}CosNaming_NamingContextExt_server CosNaming_NamingContextExt_server.cpp)
target_link_libraries(${CORBASIM_PREFIX}CosNaming_NamingContextExt_server 
	${CORBASIM_PREFIX}Cosnaming_idl
	# CORBASIM Libraries
	corbasim
	# TAO
	TAO TAO_PortableServer TAO_AnyTypeCode TAO_CosNaming TAO_ObjRefTemplate)



	

	
# Corbasim reflective library	
add_library(corbasim_reflective_CosNaming_NamingContext SHARED CosNaming_NamingContext_reflective.cpp Cosnaming_adapted.cpp)
target_link_libraries(corbasim_reflective_CosNaming_NamingContext
    ${COSNAMING_LIBS}
	# CORBASIM Library
	corbasim)
	
# Corbasim reflective library	
add_library(corbasim_reflective_CosNaming_BindingIterator SHARED CosNaming_BindingIterator_reflective.cpp Cosnaming_adapted.cpp)
target_link_libraries(corbasim_reflective_CosNaming_BindingIterator
    ${COSNAMING_LIBS}
	# CORBASIM Library
	corbasim)
	
# Corbasim reflective library	
add_library(corbasim_reflective_CosNaming_NamingContextExt SHARED CosNaming_NamingContextExt_reflective.cpp Cosnaming_adapted.cpp)
target_link_libraries(corbasim_reflective_CosNaming_NamingContextExt
    ${COSNAMING_LIBS}
	# CORBASIM Library
	corbasim)



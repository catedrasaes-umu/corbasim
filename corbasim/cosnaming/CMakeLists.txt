set(COSNAMING_LIBS
    ${CORBASIM_COSNAMING_LIBS})

include(Cosnaming_static.cmake)

install(TARGETS corbasim_reflective_CosNaming_NamingContext DESTINATION lib)
install(TARGETS corbasim_reflective_CosNaming_BindingIterator DESTINATION lib)
install(TARGETS corbasim_reflective_CosNaming_NamingContextExt DESTINATION lib)


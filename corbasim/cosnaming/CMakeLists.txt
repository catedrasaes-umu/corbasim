set(COSNAMING_LIBS
    TAO_ImR_Client
    TAO_CosNaming_Serv
    TAO_Svc_Utils
    TAO_Messaging
    TAO_PI
    TAO_CodecFactory
    TAO_Valuetype
    TAO_IORTable
    TAO_CosNaming_Skel
    TAO_PortableServer
    TAO_CosNaming
    TAO_AnyTypeCode
    TAO)

include(Cosnaming_static.cmake)

install(TARGETS corbasim_reflective_CosNaming_NamingContext DESTINATION lib)
install(TARGETS corbasim_reflective_CosNaming_BindingIterator DESTINATION lib)
install(TARGETS corbasim_reflective_CosNaming_NamingContextExt DESTINATION lib)


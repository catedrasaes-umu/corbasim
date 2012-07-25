include_directories(${Qwt6_INCLUDE_DIR})

set(corbasim_qwt_EXPORTED_HEADERS
    qwt/export.hpp
    qwt/SimplePlot.hpp
    qwt/PlotModel.hpp
    qwt/ReflectivePlotTool.hpp
    )

foreach(_header ${corbasim_qwt_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/corbasim/${_header_path})
endforeach(_header ${corbasim_qwt_EXPORTED_HEADERS})

set(corbasim_qwt_MOC_HDRS
    qwt/SimplePlot.hpp
    qwt/PlotModel.hpp
    qwt/ReflectivePlotTool.hpp
    qwt/private/Plot.hpp
    )

set(corbasim_qwt_SRCS
    qwt/SimplePlot.cpp
    qwt/PlotModel.cpp
    qwt/ReflectivePlotTool.cpp
    qwt/private/Plot.cpp
    qwt/private/HistoricData.cpp
    )

set(corbasim_qwt_LIBS
    ${QT_LIBRARIES}
    corbasim
    corbasim_qt
    ${Qwt6_Qt4_LIBRARY})

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(corbasim_qwt_MOC_SRCS ${corbasim_qwt_MOC_HDRS} 
    OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_library(corbasim_qwt SHARED ${corbasim_qwt_SRCS}
    ${corbasim_qwt_MOC_SRCS}
    ${corbasim_qwt_RCC})

target_link_libraries(corbasim_qwt
    ${corbasim_qwt_LIBS})

set_target_properties(corbasim_qwt PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS corbasim_qwt DESTINATION lib)


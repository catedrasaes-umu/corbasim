include_directories(${Qwt6_INCLUDE_DIR})

qt4_wrap_cpp(example_MOC_SRCS producer.hpp 
    OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_executable(qwt_test_plot 
    plot.cpp ${example_MOC_SRCS})

target_link_libraries(qwt_test_plot 
    ${Qwt6_Qt4_LIBRARY} ${QT_LIBRARIES})


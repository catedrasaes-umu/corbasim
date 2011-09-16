
add_executable(test_archives archives.cpp)
target_link_libraries(test_archives
    corbasim boost_serialization)

add_executable(test_mpl_vector mpl_vector.cpp)



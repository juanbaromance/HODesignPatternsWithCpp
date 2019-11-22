
project(Chapter05)
set(artefact benchmark)
set(CMAKE_CXX_FLAGS "-O4 -g -std=c++17")
add_executable(${artefact}.x scoped_ptr1_bm.C)
include_directories( ./ )
set( SOURCES scoped_ptr1.C scoped_ptr1_bm.C memory1.C mutex1.C )
target_link_libraries(${artefact}.x gtest benchmark pthread rt m  )

set(testing tests)
add_executable(${testing}.x scoped_ptr1.C memory1.C mutex1.C)
target_link_libraries(${testing}.x gtest gtest_main pthread rt m  )

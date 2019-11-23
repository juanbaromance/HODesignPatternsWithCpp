
project(Chapter06)
set(artefact smart_ptr)
set(CMAKE_CXX_FLAGS "-O4 -g -std=c++17")
add_executable(${artefact}.x smartptr.C smartptr_extra.C)
include_directories( ./ )
set( SOURCES smartptr.C )
target_link_libraries(${artefact}.x gtest gtest_main benchmark pthread rt m  )

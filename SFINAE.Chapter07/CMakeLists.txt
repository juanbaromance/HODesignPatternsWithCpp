
project(Chapter07)

set(artefact sfinae)
add_executable(${artefact}.x sfinae1a.C sfinae2.C sfinae3.C sfinae4.C )

include_directories( ./ )
set(CMAKE_CXX_FLAGS "-O4 -g -std=c++17")
target_link_libraries(${artefact}.x gtest gtest_main benchmark pthread rt m  )

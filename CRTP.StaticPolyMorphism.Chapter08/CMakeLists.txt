
project(Chapter05)

set(artefact benchmark)
set(CMAKE_CXX_FLAGS "-O4 -g -std=c++17")
add_executable(${artefact}.x function_call.C )
include_directories( ./ )


add_executable(visitor.x visitor.C )
target_link_libraries(${artefact}.x gtest benchmark pthread rt m  )

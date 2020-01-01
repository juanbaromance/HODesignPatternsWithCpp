
project(Chapter05)

set(artefact test)
set(CMAKE_CXX_FLAGS "-O4 -g -std=c++17")

add_executable(${artefact}.x named_args.C named_args_extra.C )
include_directories( ./ )

target_link_libraries(${artefact}.x gtest benchmark pthread rt m  )

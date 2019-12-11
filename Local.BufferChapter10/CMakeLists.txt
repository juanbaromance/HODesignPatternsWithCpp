
project(Chapter05)

set(artefact smartPTRtelb)
set(CMAKE_CXX_FLAGS "-g -std=c++17")

add_executable(${artefact}.x smartptr.C )
add_executable(newusage.x newusage.C )

include_directories( ./ )

target_link_libraries( ${artefact}.x gtest benchmark pthread rt m  )

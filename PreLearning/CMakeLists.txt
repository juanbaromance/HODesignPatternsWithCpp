set(ppc no)

if( ppc )
    set(CMAKE_C_COMPILER   ppc-gcc)
    set(CMAKE_CXX_COMPILER ppc-g++)
    set(tail ppc )
    set(CMAKE_CXX_FLAGS "-O3 -g")
else()
    set(tail local)
    set(CMAKE_CXX_FLAGS "-g -std=c++1z")
endif()

add_executable(testing.${tail}.x templates.cpp)
add_executable(testingTemplatedFunctions.${tail}.x templatedFunctions.cpp)
add_executable(testingVariadics.${tail}.x variadics.cpp)

if( ppc )
    
else()
# target_link_libraries(testing.${tail}.x pthread boost_system boost_regex)
endif()



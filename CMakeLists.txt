cmake_minimum_required(VERSION 3.5)

project(PID)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")


include_directories(include)
include_directories(lib)

###############################################################################
## Build project
###############################################################################

set(sources
    src/main.cpp
    src/helpers.cpp
    src/PID.cpp
    src/Monitor.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

include_directories(/usr/local/include)
include_directories(/usr/local/opt/openssl/include)
link_directories(/usr/local/lib)
link_directories(/usr/local/opt/openssl/lib)
link_directories(/usr/local/Cellar/libuv/1*/lib)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 


add_executable(pid ${sources})

target_link_libraries(pid z ssl uv uWS)

###############################################################################
## Testing with Catch2
###############################################################################

set(test_sources
    test/main_test.cpp
    test/helpers_test.cpp
    src/helpers.cpp
    src/helpers.h )

add_executable(tests ${test_sources})

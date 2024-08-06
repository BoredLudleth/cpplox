cmake_minimum_required(VERSION 3.10)
project(VirtualFileSystem)

set(CMAKE_CXX_STANDARD 17)

set(MY_COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${MY_COMPILE_FLAGS})

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

add_executable(cpplox ${SRC_DIR}/main.cpp
                      ${SRC_DIR}/lox.cpp
                      ${SRC_DIR}/token.cpp
                      ${SRC_DIR}/scanner.cpp)


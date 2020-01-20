cmake_minimum_required(VERSION 3.0)

project(tiny_gp)

set(CMAKE_MACOSX_RPATH 1)
set (CMAKE_OSX_ARCHITECTURES "x86_64")

set(CMAKE_BUILD_TYPE "Debug")

set(SOURCE 
schema.cpp
genetic.cpp
main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

include(CPack)
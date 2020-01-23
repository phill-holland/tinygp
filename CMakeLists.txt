cmake_minimum_required(VERSION 3.9)

project(tiny_gp)

set(CMAKE_MACOSX_RPATH 1)
set (CMAKE_OSX_ARCHITECTURES "x86_64")

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE 
schema.cpp
genetic.cpp
bugger.cpp
main.cpp)

include_directories(/Library/Developer/CommandLineTools/usr/include)

add_executable(${PROJECT_NAME} ${SOURCE})
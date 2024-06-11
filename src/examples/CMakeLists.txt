#########################################################
# CMake example to configure your project to use vk_sdk.
#########################################################
cmake_minimum_required(VERSION 3.16)
project(my_project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the directory to find the necessary libraries.
# Alternatively, you may specify these when you run `cmake` command instead. To do so, run
# `cmake -DCapnProto_DIR="..." -Dvk_sdk_DIR="..." "<source_directory>"` in your build directory.

set(CapnProto_DIR "/installation/path/capnproto/lib/cmake/CapnProto")
set(vk_sdk_DIR "/opt/vilota/lib/cmake/vk_sdk")

find_package(vk_sdk CONFIG REQUIRED)

add_executable(my_project my_main.cpp)

target_link_libraries(my_project PUBLIC CapnProto::capnp PRIVATE vilota::vk_sdk)
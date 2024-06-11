cmake_minimum_required(VERSION 3.21)
project(my_project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Install Capnp (https://capnproto.org/install.html)
set(CapnProto_DIR "/usr/local/lib/cmake/CapnProto/")
set(vk_sdk_DIR "/opt/vilota/lib/cmake/vk_sdk")

find_package(vk_sdk CONFIG REQUIRED)

add_executable(my_project src/main.cpp)

target_link_libraries(my_project PUBLIC CapnProto::capnp PRIVATE vilota::vk_sdk)
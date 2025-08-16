cmake_minimum_required(VERSION 3.16)
project(spaceinvaders_raylib_prototype LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(spaceinvaders_proto src/main.cpp)

target_include_directories(spaceinvaders_proto PRIVATE ${RAYLIB_INCLUDE_DIRS})
target_link_libraries(spaceinvaders_proto PRIVATE ${RAYLIB_LIBRARIES})

cmake_minimum_required(VERSION 3.0)
project(Obj2Points)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR})

message("CMAKE_CURRENT_LIST_DIR is ${CMAKE_CURRENT_LIST_DIR}")

add_executable(Obj2Points main.cpp utils_sampling.cpp vcg_mesh.cpp obj_shape_loader.cpp)


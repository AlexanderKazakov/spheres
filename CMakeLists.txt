cmake_minimum_required(VERSION 2.8)
project(spheres)

set(WARNING_FLAGS "-Wall -Wextra -Wsign-conversion -Wconversion -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${WARNING_FLAGS}")

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

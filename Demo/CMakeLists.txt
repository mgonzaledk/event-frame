cmake_minimum_required(VERSION 3.10)
project(demo CXX)

set(SOURCE_FILES
    Main.cpp)

add_executable(demo ${SOURCE_FILES})
target_link_libraries(demo event-frame)
target_include_directories(demo PRIVATE ../Include)

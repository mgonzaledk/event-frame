cmake_minimum_required(VERSION 3.10)
project(event-frame CXX)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

set(SOURCE_FILES
    Semaphore.cpp)

add_library(event-frame SHARED STATIC ${SOURCE_FILES})
target_include_directories(event-frame PRIVATE ../Include)
target_link_libraries(event-frame m rt Threads::Threads)

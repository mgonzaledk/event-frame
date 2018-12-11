set(SOURCE_FILES
    Main.cpp)

add_executable(demo ${SOURCE_FILES})
target_link_libraries(demo event-frame)

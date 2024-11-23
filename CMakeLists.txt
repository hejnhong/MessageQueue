cmake_minimum_required(VERSION 2.8)

project(MessageQueue)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB SRC_LIST
    "*.cpp"
)

add_executable(main ${SRC_LIST})

add_subdirectory(handler)
add_subdirectory(looper)
add_subdirectory(message)

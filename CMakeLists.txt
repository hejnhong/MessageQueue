cmake_minimum_required (VERSION 2.8)

project (MessageQueue)

aux_source_directory(. SRC_LIST)

add_executable(main ${SRC_LIST})

cmake_minimum_required(VERSION 3.10)

project(cache)

set(SOURCE_EXE main.cpp)

include_directories(src/utils/Log src/services/Database)

add_executable(main ${SOURCE_EXE})

add_subdirectory(src/utils/Log src/services/Database)


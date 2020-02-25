cmake_minimum_required(VERSION 3.10)

project(database)

set(SOURCE_LIB Database.cpp)

add_library(database STATIC ${SOURCE_LIB})

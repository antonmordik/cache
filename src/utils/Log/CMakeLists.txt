cmake_minimum_required(VERSION 3.10)

project(log)

set(SOURCE_LIB Log.cpp)

add_library(log STATIC ${SOURCE_LIB})

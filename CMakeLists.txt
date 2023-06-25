cmake_minimum_required(VERSION 3.20)
project(tmdf)

set(CMAKE_CXX_STANDARD 20)

add_executable(tmdf main.cpp tmdf.cpp tmdf.h tag.h numerical_tag.h bool_tag.h string_tag.h tmdfUtils.h collection_tag.h array_tag.h)

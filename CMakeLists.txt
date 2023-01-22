cmake_minimum_required(VERSION 3.25)
project(Logger
        VERSION 0.1
        LANGUAGES C CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCE)

add_library(Logger ${SOURCE})
target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
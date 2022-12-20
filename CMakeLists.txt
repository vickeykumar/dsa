cmake_minimum_required(VERSION 3.10)
project(cda LANGUAGES C CXX VERSION 0.1.0)

add_library(cda SHARED
        src/search.c
        include/search.h
        )

target_include_directories(cda
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

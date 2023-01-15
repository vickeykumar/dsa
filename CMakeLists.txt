cmake_minimum_required(VERSION 3.10)
project(cda LANGUAGES C CXX VERSION 0.1.0)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c" "src/*.cpp" "src/*.cc")

# will be using c++ to compile the c codes as well, to be used in cling
SET_SOURCE_FILES_PROPERTIES(${SOURCES} PROPERTIES LANGUAGE CXX )
add_library(dsa SHARED
            ${SOURCES}
        )

target_include_directories(dsa
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

cmake_minimum_required(VERSION 3.12)
add_subdirectory(../cmake-tools cmake-tools)
ensure_vcpkg()
project(elf-reader)
add_subdirectory(../bin-util/src bin-util)

set(CMAKE_CXX_STANDARD 11)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(src)
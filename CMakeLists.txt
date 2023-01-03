cmake_minimum_required(VERSION 3.12)

project(elf-reader)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(thirdpart/reader-util)
add_executable(elf-reader src/elf.cpp src/elf.h src/main.cc)
target_link_libraries(elf-reader reader-util)

install(TARGETS elf-reader)
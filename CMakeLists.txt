cmake_minimum_required(VERSION 3.12)

project(elf-reader)

add_subdirectory(thirdpart/reader-util)
add_executable(elf-reader src/elf.cpp src/elf.h src/main.cc)
target_link_libraries(elf-reader reader-util)
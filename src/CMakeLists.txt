file(GLOB_RECURSE elf_reader_SRC *.cpp *.cc *.h *.hpp)

add_executable(elf_reader ${elf_reader_SRC})
file(GLOB_RECURSE elf_reader_SRC *.cpp *.cc *.h *.hpp)

add_executable(elf-reader ${elf_reader_SRC})
set_property(TARGET elf-reader PROPERTY CXX_STANDARD 11)

install(TARGETS elf-reader DESTINATION bin)
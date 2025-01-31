file(GLOB_RECURSE _src "*.cpp" "*.cc" "*.h")
list(FILTER _src EXCLUDE REGEX ".*[/\\]main\\.cc$")
add_library(elf-reader ${_src})
target_link_libraries(elf-reader bin-util)

add_executable(elf-reader-main main.cc)
target_link_libraries(elf-reader-main elf-reader bin-util)
install(TARGETS elf-reader-main)

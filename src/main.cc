//
// Created by huhua on 2022/12/28.
//
#include <reader_util.h>
#include <fstream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " filepath" << std::endl;
    return 0;
  }

  if (!reader_util::isFileExists(argv[1])) {
    std::cout << "file not exist: " << argv[1] << std::endl;
    return 1;
  }

  std::ifstream f;
  f.open(argv[1]);
}

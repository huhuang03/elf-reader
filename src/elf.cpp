#include "elf.h"
#include <iostream>
#include <bin_util/bin_util.h>

std::string Elf::checkMagic() {
  // assume in_stream_ is ok
  char magic[4];
  this->in_stream_->read(magic, 4);
  char rightMagic[] = {0x7F, 'E', 'L', 'F'};
  for (int i = 0; i < 4; i++) {
    if (magic[i] != rightMagic[i]) {
      return "magic at pos " + std::to_string(i) + " want " + std::to_string(rightMagic[i]) + " but was: "
          + std::to_string(magic[i]);
    }
  }
  return "";
}

Elf::Elf(const std::string &filepath) {
  if (!bu::isFileExists(filepath)) {
    std::cout << filepath << " not exit!" << std::endl;
    // good at here??
    exit(0);
  }

  // good!!
  this->in_stream_ = new std::ifstream(filepath.c_str());
  auto errMsg = checkMagic();
  if (!errMsg.empty()) {
    std::cout << filepath << " is not a elf file(" << errMsg << ")" << std::endl;
  }
}

Elf::~Elf() {
  if (in_stream_ != nullptr && !in_stream_->is_open()) {
    in_stream_->close();
    in_stream_ = nullptr;
  }
}
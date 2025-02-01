//
// Created by huhua on 2025/1/31.
//

#ifndef SECTION_H
#define SECTION_H
#include "./sys_elf.h"
#include <fstream>

namespace elf_reader {
class SectionHeader {
  Elf64_Shdr _shdr{};
public:
  void read(std::ifstream &f);
  Elf64_Shdr* getShdr();
  friend std::ostream& operator<<(std::ostream& stream, const SectionHeader& sectionHeader);
};
} // namespace elf_reader
#endif // SECTION_H

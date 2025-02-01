#ifndef ELF_H
#define ELF_H

#include <fstream>
#include <string>
#include <vector>

#include "./section_header.h"
#include "./sys_elf.h"

namespace elf_reader {
class Elf {
  std::vector<SectionHeader> sectionHeaders;
  Elf64_Ehdr ehdr{};
  std::ifstream *in_stream_ = nullptr;
  // return error msg.
  std::string checkMagic() const;
  // where define kMagic??
  const static char kMagic[];

public:
  explicit Elf(const std::string &filepath);
  ~Elf();
  SectionHeader* symHeader();
  SectionHeader* dynHeader();
  void printSections() const;
};
}

#endif
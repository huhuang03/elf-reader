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
  std::ifstream* getStream() const;
  /**
   * @return the str section header which contains the section names
   */
  SectionHeader* getShstrHeader();
  SectionHeader* getSymSh();
  SectionHeader* getDynHeader();
  SectionHeader* getSymNameSh();
  std::string getName(SectionHeader* nameSectionHeader, int offset) const;
  std::string getSectionName(SectionHeader*);
  void printSections() const;
  bool is64() const;
  int getShstrndx() const;
};
}

#endif
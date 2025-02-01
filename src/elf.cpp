#include "elf.h"
#include <iostream>
#include <bin_util/bin_util.h>

elf_reader::Elf::Elf(const std::string &filepath) {
  if (!bu::isFileExists(filepath)) {
    std::cout << filepath << " not exit!" << std::endl;
    // good at here??
    exit(0);
  }

  this->in_stream_ = new std::ifstream(filepath.c_str());
  // read ehdr
  Elf64_Ehdr ehdr;
  this->in_stream_->read(reinterpret_cast<char *>(&ehdr), sizeof ehdr);

  const auto errMsg = checkMagic();
  if (!errMsg.empty()) {
    std::cout << filepath << " is not a elf file(" << errMsg << ")" << std::endl;
  }

  // read sections.
  this->in_stream_->seekg(static_cast<long long>(ehdr.e_shoff));
  this->sectionHeaders = std::vector<SectionHeader>(ehdr.e_shnum);
  std::cout << "shnum: " << ehdr.e_shnum << std::endl;
  for (auto & sectionHeader : this->sectionHeaders) {
    sectionHeader.read(*this->in_stream_);
  }
}

elf_reader::Elf::~Elf() {
  if (in_stream_ != nullptr && !in_stream_->is_open()) {
    in_stream_->close();
    in_stream_ = nullptr;
  }
}

elf_reader::SectionHeader *elf_reader::Elf::symHeader() {
  for (auto &section: sectionHeaders) {
    if (section.getShdr()->sh_type == SHT_SYMTAB) {
      return &section;
    }
  }
  return nullptr;
}

elf_reader::SectionHeader *elf_reader::Elf::dynHeader() {
  for (auto &section : sectionHeaders) {
    if (section.getShdr()->sh_type == SHT_DYNSYM) {
      return &section;
    }
  }
  return nullptr;
}

void elf_reader::Elf::printSections() const {
  std::cout << "Sections: " << std::endl;
  for (int i = 0; i < sectionHeaders.size(); i++) {
    auto item = sectionHeaders[i];
    std::cout << "\ttype: " << item.getShdr()->sh_type << "(" << sectionTypeName(item.getShdr()->sh_type) << ")";
    if (i != sectionHeaders.size() - 1) {
      std::cout << std::endl;
    }
  }
  // for (const auto & sectionHeader : sectionHeaders) {
  // }
}

std::string elf_reader::Elf::checkMagic() const {
  constexpr char rightMagic[] = {0x7F, 'E', 'L', 'F'};
  const auto magic = this->ehdr.e_ident;
  for (int i = 0; i < 4; i++) {
    if (magic[i] != rightMagic[i]) {
      return "magic at pos " + std::to_string(i) + " want " + std::to_string(rightMagic[i]) + " but was: "
          + std::to_string(magic[i]);
    }
  }
  return "";
}


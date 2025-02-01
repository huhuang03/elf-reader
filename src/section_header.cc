//
// Created by huhua on 2025/1/31.
//

#include "section_header.h"
void elf_reader::SectionHeader::read(std::ifstream &f) {
  f.read(reinterpret_cast<char *>(&this->_shdr), sizeof(this->_shdr));
}

elf_reader::Elf64_Shdr *elf_reader::SectionHeader::getShdr() { return &this->_shdr; }

std::ostream &elf_reader::operator<<(std::ostream &stream, const SectionHeader &sectionHeader) {
  stream << "SectionHeader: sh_size: " << sectionHeader._shdr.sh_size << ", entsize: " << sectionHeader._shdr.sh_entsize;
  return stream;
}

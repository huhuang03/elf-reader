//
// Created by huhua on 2025/1/31.
//

#include "section_header.h"
void elf_reader::SectionHeader::read(std::ifstream &f) {
  f.read(reinterpret_cast<char *>(&this->_shdr), sizeof(this->_shdr));
}

elf_reader::Elf64_Shdr *elf_reader::SectionHeader::getShdr() {
  return &this->_shdr;
}

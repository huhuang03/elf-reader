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

std::ifstream* elf_reader::Elf::getStream() const {
  return this->in_stream_;
}

elf_reader::SectionHeader *elf_reader::Elf::getShstrHeader() {
  return &this->sectionHeaders[this->getShstrndx()];
}

elf_reader::SectionHeader *elf_reader::Elf::getSymSh() {
  for (auto &section: sectionHeaders) {
    if (section.getShdr()->sh_type == SHT_SYMTAB) {
      return &section;
    }
  }
  return nullptr;
}

elf_reader::SectionHeader *elf_reader::Elf::getDynHeader() {
  for (auto &section : sectionHeaders) {
    if (section.getShdr()->sh_type == SHT_DYNSYM) {
      return &section;
    }
  }
  return nullptr;
}

elf_reader::SectionHeader *elf_reader::Elf::getSymNameSh() {
  auto symSh = this->getSymSh();
  if (!symSh) {
    std::cerr << "not find sym sh" << std::endl;
    return nullptr;
  }
  return &sectionHeaders[symSh->getShdr()->sh_link];
}

std::string elf_reader::Elf::getName(SectionHeader *nameSectionHeader, int offset) const {
  std::vector<char> rst(nameSectionHeader->getShdr()->sh_size);
  this->in_stream_->seekg(nameSectionHeader->getShdr()->sh_offset);
  this->in_stream_->read(rst.data(), nameSectionHeader->getShdr()->sh_size);
  return std::string(&rst[offset]);
}

std::string elf_reader::Elf::getSectionName(SectionHeader *sectionHeader) {
  return getName(this->getShstrHeader(), sectionHeader->getShdr()->sh_name);
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

bool elf_reader::Elf::is64() const { return this->ehdr.e_ident[0x04] == 2; }

int elf_reader::Elf::getShstrndx() const {
  return this->ehdr.e_shstrndx;
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


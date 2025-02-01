//
// Created by huhua on 2022/12/28.
//
#include <bin_util/bin_util.h>
#include <fstream>
#include <string>
#include "./sys_elf.h"
#include "./elf.h"

static std::vector<char> readStrTab(std::ifstream &stream, elf_reader::Elf64_Shdr strShdr) {
  stream.seekg(strShdr.sh_offset);
  std::vector<char> rst(strShdr.sh_size);
  stream.read(rst.data(), strShdr.sh_size);
  return rst;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " filepath" << std::endl;
    return 0;
  }

  if (!bu::isFileExists(argv[1])) {
    std::cout << "file not exist: " << argv[1] << std::endl;
    return 1;
  }
  const auto elf = new elf_reader::Elf(argv[1]);
  auto symHeader = elf->getSymSh();
  auto stream = elf->getStream();
  auto size = symHeader->getShdr()->sh_size / sizeof(elf_reader::Elf64_Sym);
  std::vector<elf_reader::Elf64_Sym> symbols(size);
  stream->seekg(symHeader->getShdr()->sh_offset);
  stream->read(reinterpret_cast<char*>(symbols.data()), symHeader->getShdr()->sh_size);
  auto symNameSh = elf->getSymNameSh();
  std::cout << "symNameSh: " << symNameSh << std::endl;
  for (auto symbol : symbols) {
    std::cout << elf->getName(symNameSh, symbol.st_name) << "\n";
  }
  // but how to get str tab??
  // std::cout << elf->getSectionName(symHeader) << std::endl;
  // std::cout << *symHeader << std::endl;
  // std::cout << elf->getShstrndx() << std::endl;
  // std::cout << "is64: " << elf->is64() << std::endl;
  // // elf->printSections();
  // auto symHeader = elf->symHeader();
  // std::cout << "symHeader: " << *symHeader << std::endl;
  // // sizeof(elf_reader::Elf64_Shdr)
  // std::cout << "Elf64_Shdr: " << sizeof(elf_reader::Elf64_Sym) << std::endl;
  // how to do this?
  // std::ifstream f;
  // f.open(argv[1], std::ios::binary);
  //
  // elf_reader::Elf64_Ehdr ehdr;
  // f.read(reinterpret_cast<char *>(&ehdr), sizeof ehdr);
  //
  // std::cout << "Header:" << std::endl;
  // // how to do this?
  // std::cout << "\te_entry: " << bu::toStrAsLEHex(&ehdr.e_entry, sizeof ehdr.e_entry) << std::endl;
  // std::cout << "\te_shnum: " << ehdr.e_shnum << std::endl;
  // std::cout << "\te_shstrndx: " << ehdr.e_shstrndx << std::endl;
  // std::cout << "\tshoff: " << ehdr.e_shoff << std::endl;
  //
  // std::cout << "Sections:" << std::endl;
  // f.seekg(static_cast<long long>(ehdr.e_shoff));
  // std::vector<elf_reader::Elf64_Shdr> sectionHeader(ehdr.e_shnum);
  // f.read(reinterpret_cast<char*>(sectionHeader.data()), ehdr.e_shnum * sizeof(elf_reader::Elf64_Shdr));
  // elf_reader::Elf64_Shdr* symtab = nullptr;
  // elf_reader::Elf64_Shdr* dynsym = nullptr;
  // elf_reader::Elf64_Shdr* strtab = nullptr;
  // elf_reader::Elf64_Shdr* dynStrtab = nullptr;
  //
  // for (const auto& sh : sectionHeader) {
  //   if (sh.sh_type == SHT_SYMTAB) {
  //     symtab = const_cast<elf_reader::Elf64_Shdr*>(&sh);
  //   }
  //   if (sh.sh_type == SHT_DYNSYM) {
  //     std::cout << "found dynsym" << std::endl;
  //     dynsym = const_cast<elf_reader::Elf64_Shdr*>(&sh);
  //   }
  //   if (sh.sh_type == SHT_STRTAB && symtab && sectionHeader[symtab->sh_link].sh_offset == sh.sh_offset) {
  //     strtab = const_cast<elf_reader::Elf64_Shdr*>(&sh);
  //   }
  //   if (sh.sh_type == SHT_STRTAB && dynsym && sectionHeader[dynsym->sh_link].sh_offset == sh.sh_offset) {
  //     dynStrtab = const_cast<elf_reader::Elf64_Shdr*>(&sh);
  //   }
  // }
  // if (!strtab) {
  //   std::cerr << "Symbol table or string table not found" << std::endl;
  //   return 1;
  // }
  // std::cout << "dynStrtab: " << dynStrtab << std::endl;;
  // // 读取符号表
  // std::vector<elf_reader::Elf64_Sym> symbols(symtab->sh_size / sizeof(elf_reader::Elf64_Sym));
  // f.seekg(symtab->sh_offset);
  // f.read(reinterpret_cast<char*>(symbols.data()), symtab->sh_size);
  // std::cout << "Functions:" << std::endl;
  // auto parsedString = readStrTab(f, *strtab);
  // for (const auto & sym : symbols) {
  //   if (ELF64_ST_TYPE(sym.st_info) == STT_FUNC) {
  //     std::cout << &parsedString[sym.st_name] << std::endl;
  //   }
  // }
}
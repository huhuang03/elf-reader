//
// Created by huhua on 2022/12/28.
//
#include <bin_util/bin_util.h>
#include <fstream>
#include <string>

namespace elf_reader {
#define EI_NIDENT 16
typedef uint16_t Elf32_Half;
typedef int16_t Elf32_SHalf;
typedef uint32_t Elf32_Word;
typedef int32_t Elf32_Sword;
typedef uint64_t Elf32_Xword;
typedef int64_t Elf32_Sxword;

typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Section;

typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off e_phoff;
  Elf32_Off e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
} Elf32_Ehdr;

typedef uint64_t	Elf64_Addr;
typedef uint16_t	Elf64_Half;
typedef uint64_t	Elf64_Off;
typedef int32_t		Elf64_Sword;
typedef int64_t		Elf64_Sxword;
typedef uint32_t	Elf64_Word;
typedef uint64_t	Elf64_Lword;
typedef uint64_t	Elf64_Xword;

typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf64_Half e_type;
  Elf64_Half e_machine;
  Elf64_Word e_version;
  Elf64_Addr e_entry;
  Elf64_Off e_phoff;
  Elf64_Off e_shoff;
  Elf64_Word e_flags;
  Elf64_Half e_ehsize;
  Elf64_Half e_phentsize;
  Elf64_Half e_phnum;
  Elf64_Half e_shentsize;
  Elf64_Half e_shnum;
  Elf64_Half e_shstrndx;
} Elf64_Ehdr;

typedef struct {
	Elf32_Word	sh_name;
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	Elf32_Addr	sh_addr;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_addralign;
	Elf32_Word	sh_entsize;
} Elf32_Shdr;

typedef struct {
	Elf64_Word	sh_name;
	Elf64_Word	sh_type;
	Elf64_Xword	sh_flags;
	Elf64_Addr	sh_addr;
	Elf64_Off	sh_offset;
	Elf64_Xword	sh_size;
	Elf64_Word	sh_link;
	Elf64_Word	sh_info;
	Elf64_Xword	sh_addralign;
	Elf64_Xword	sh_entsize;
} Elf64_Shdr;
}

static void readString(std::ifstream &stream, std::string& str);

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " filepath" << std::endl;
    return 0;
  }

  if (!bu::isFileExists(argv[1])) {
    std::cout << "file not exist: " << argv[1] << std::endl;
    return 1;
  }

  // how to do this?

  std::ifstream f;
  f.open(argv[1], std::ios::binary);

  elf_reader::Elf64_Ehdr ehdr;
  f.read(reinterpret_cast<char *>(&ehdr), sizeof ehdr);

  std::cout << "Header:" << std::endl;
  // how to do this?
  std::cout << "\te_entry: " << bu::toStrAsLEHex(&ehdr.e_entry, sizeof ehdr.e_entry) << std::endl;
  std::cout << "\te_shnum: " << ehdr.e_shnum << std::endl;
  std::cout << "\te_shstrndx: " << ehdr.e_shstrndx << std::endl;
  std::cout << "\tshoff: " << ehdr.e_shoff << std::endl;

  int curOffset = ehdr.e_shoff;
  f.seekg((ehdr.e_shstrndx) * sizeof(elf_reader::Elf64_Ehdr) + ehdr.e_shoff, std::ios::beg);
  elf_reader::Elf64_Shdr nameShdr;
  f.read(reinterpret_cast<char *>(&nameShdr), sizeof(elf_reader::Elf64_Ehdr));

//  std::cout << "name\t\t\toffset" << std::endl;
  for (int i = 0; i < ehdr.e_shnum; i++) {
    f.seekg(curOffset, std::ios::beg);
    elf_reader::Elf64_Shdr shdr;
    f.read(reinterpret_cast<char *>(&shdr), sizeof shdr);
    // 这里其实有问题，第一个偏移和后面的偏移计算不同
    int offset = nameShdr.sh_offset + shdr.sh_name;
//    if (shdr.sh_name == 0) {
//      offset += 1;
//    }
    f.seekg(offset, std::ios::beg);
    std::string name;
    readString(f, name);
    std::cout << name << ", sh_offset: " << shdr.sh_offset << ", sh_size: " << shdr.sh_size << ", sh_entsize: " << shdr.sh_entsize << std::endl;
    curOffset += sizeof shdr;
  }

  std::cout << "\nProgram Headers(" << ehdr.e_phnum << ")" << std::endl;
  f.seekg(ehdr.e_phoff, std::ios::beg);
  for (int i = 0; i < ehdr.e_phnum; i++) {
    f.read()
    std::cout << "p_vaddr" <<  << std::endl;
  }
}

static void readString(std::ifstream &stream, std::string& str) {
  int s = stream.peek();
  while (s != 0) {
    str.push_back((char)s);
    stream.get();
    s = stream.peek();
  }
}

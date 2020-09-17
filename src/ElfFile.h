//
// Created by th on 2020/9/16.
//

#ifndef ELF_READER_ELFFILE_H
#define ELF_READER_ELFFILE_H

#include <string>
#include <vector>
#include "elf.h"

using namespace std;

class ElfFile {
private:
    vector<uint8_t> data;
    Elf32_Ehdr *elf32Ehdr;
    Elf64_Ehdr *elf64Ehdr;
    bool _is32;

public:
    ElfFile();
    ElfFile(vector<uint8_t> &data);
    bool is32();
    bool is64();

    static bool initialFromFilePath(ElfFile &elfFile, const string &path);
};


#endif //ELF_READER_ELFFILE_H

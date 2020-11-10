//
// Created by th on 2020/9/16.
//

#ifndef ELF_READER_ELFFILE_H
#define ELF_READER_ELFFILE_H

#include <string>
#include <vector>
#include "elf.h"
#include "os_elf.h"

using namespace std;

class Elf {
private:
    vector<uint8_t> data;
    Elf32_Ehdr *elf32Ehdr;
    Elf64_Ehdr *elf64Ehdr;
    bool _is32;
    void initialWithData(vector<uint8_t> data);
    int get_e_type();
    int get_class();

public:
    Elf();
    Elf(vector<uint8_t> &data);
    bool is32();
    bool is64();

    static bool initialFromFilePath(Elf &elf, const string &path);
    void pp(bool isPHeader=true);
};


#endif //ELF_READER_ELFFILE_H

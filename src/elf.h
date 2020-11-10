//
// Created by th on 2020/9/16.
//

#ifndef ELF_READER_ELF_H
#define ELF_READER_ELF_H

#include <string>
#include <vector>
#include "os_elf.h"
#include "str_section.h"

using namespace std;

class Elf {
private:
    vector<uint8_t> data;
    Elf32_Ehdr *elf32Ehdr;
    Elf64_Ehdr *elf64Ehdr;
    bool _is32;
    void initStringTable();
    void initialWithData(vector<uint8_t> data);
    StrSection *strSection;

    int get_e_type();
    int get_class();
    int get_e_shentsize();
    int get_e_shnum();
    int get_e_shstrndx();
    int get_e_shoff();
    int get_e_machine();

    /**
     * This is for section header.
     * @return The section start offset
     */
    uint8_t *getSectionOffsetByIndex(int index);

    Elf32_Ehdr* as32Ehdr();
    Elf64_Ehdr* as64Ehdr();

public:
    Elf();
    Elf(vector<uint8_t> &data);
    bool is32();
    bool is64();

    static bool initialFromFilePath(Elf &elf, const string &path);
    void pp(bool isPHeader=true, bool isPSection=true);
};


#endif //ELF_READER_ELF_H

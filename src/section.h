//
// Created by th on 2020/11/10.
//

#ifndef ELF_READER_SECTION_H
#define ELF_READER_SECTION_H
#include <stdint.h>
#include <vector>
#include "os_elf.h"

class Section {
protected:
    uint8_t* data;
    bool is32;
    Elf32_Shdr *as32();
    Elf64_Shdr *as64();

public:
    Section(uint8_t* data, bool is32): data(data), is32(is32) {};
    uint32_t get_sh_name();
    int get_sh_offset();
    int get_sh_size();
};

#endif //ELF_READER_SECTION_H

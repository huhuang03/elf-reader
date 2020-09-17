//
// Created by huhua on 2020/9/17.
//

#ifndef ELF_READER_ELF32_H
#define ELF_READER_ELF32_H

#include "ElfBase.h"
#include "elf.h"


class Elf32: ElfBase {
private:
    vector<Elf32_Shdr> shdrs;
};


#endif //ELF_READER_ELF32_H

//
// Created by th on 2020/11/10.
//

#include "section.h"
#include <iostream>
#include "util.h"
using namespace std;

Elf32_Shdr *Section::as32() {
    return (Elf32_Shdr*)this->data;
}

Elf64_Shdr *Section::as64() {
    return (Elf64_Shdr*)this->data;
}

#define GET_VALUE_OF(name) \
if (is32) {\
    return as32()->name;\
} else {\
    return as64()->name;\
}

uint32_t Section::get_sh_name() {
    if (is32) {
        return as32()->sh_name;
    } else {
        return as64()->sh_name;
    }
}

int Section::get_sh_offset() {
    GET_VALUE_OF(sh_offset)
}

int Section::get_sh_size() {
    GET_VALUE_OF(sh_size)
}


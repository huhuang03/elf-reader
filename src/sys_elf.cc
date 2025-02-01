//
// Created by huhua on 2025/2/1.
//

#include "./sys_elf.h"

std::string elf_reader::sectionTypeName(int st) {
    static const std::unordered_map<int, std::string> sectionTypeMap = {
        {SHT_NULL, "SHT_NULL"},
        {SHT_PROGBITS, "SHT_PROGBITS"},
        {SHT_SYMTAB, "SHT_SYMTAB"},
        {SHT_STRTAB, "SHT_STRTAB"},
        {SHT_RELA, "SHT_RELA"},
        {SHT_HASH, "SHT_HASH"},
        {SHT_DYNAMIC, "SHT_DYNAMIC"},
        {SHT_NOTE, "SHT_NOTE"},
        {SHT_NOBITS, "SHT_NOBITS"},
        {SHT_REL, "SHT_REL"},
        {SHT_SHLIB, "SHT_SHLIB"},
        {SHT_DYNSYM, "SHT_DYNSYM"},
        {SHT_NUM, "SHT_NUM"},
        {SHT_LOPROC, "SHT_LOPROC"},
        {SHT_HIPROC, "SHT_HIPROC"},
        {SHT_LOUSER, "SHT_LOUSER"},
        {SHT_HIUSER, "SHT_HIUSER"}
    };

    auto it = sectionTypeMap.find(st);
    return (it != sectionTypeMap.end()) ? it->second : "UNKNOWN";
}

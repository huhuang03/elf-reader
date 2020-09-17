//
// Created by th on 2020/9/16.
//

#include "ElfFile.h"
#include <fstream>
#include <cassert>

bool ElfFile::initialFromFilePath(ElfFile &elfFile, const string &path) {
    // read file to content
    ifstream is(path);
    assert(is.good());
    std::istream_iterator<uint8_t> start(is), end;
    elfFile.data = vector<uint8_t>(start, end);
    return true;
}

ElfFile::ElfFile(vector<uint8_t> &data) {
    this->data = data;
    auto *ehdr = (Elf32_Ehdr*)this->data.data();
    assert(ehdr->e_type == 1 || ehdr->e_type == 2);
    this->_is32 = ehdr->e_type == 1;
}

bool ElfFile::is32() {
    return this->_is32;
}

bool ElfFile::is64() {
    return !this->is32();
}

ElfFile::ElfFile() = default;

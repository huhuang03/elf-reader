//
// Created by huhua on 2020/9/17.
//

#ifndef ELF_READER_ELFBASE_H
#define ELF_READER_ELFBASE_H

#include <utility>
#include <vector>
#include <stdint.h>

using namespace std;

class ElfBase {
private:
    vector<uint8_t> data;
    
public:
    ElfBase(vector<uint8_t> data): data(std::move(data)) {};

    virtual bool is32() = 0;
    virtual int get_e_shentsize() = 0;
    virtual int get_e_shnum() = 0;
    virtual int get_e_shstrndx() = 0;
};

#endif //ELF_READER_ELFBASE_H

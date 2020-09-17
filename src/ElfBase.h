//
// Created by huhua on 2020/9/17.
//

#ifndef ELF_READER_ELFBASE_H
#define ELF_READER_ELFBASE_H

#include <vector>

using namespace std;

class ElfBase {
private:
    vector<uint8_t> data;
    
public:
    virtual bool is32() = 0;
};

#endif //ELF_READER_ELFBASE_H

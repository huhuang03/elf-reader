//
// Created by th on 2020/9/16.
//

#ifndef ELF_READER_ELFFILE_H
#define ELF_READER_ELFFILE_H

#include <string>

using namespace std;

class ElfFile {
public:
    static bool initialFromFilePath(const string &path);
};


#endif //ELF_READER_ELFFILE_H

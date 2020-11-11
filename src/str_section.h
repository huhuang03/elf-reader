//
// Created by th on 2020/11/10.
//

#ifndef ELF_READER_STR_SECTION_H
#define ELF_READER_STR_SECTION_H

#include "section.h"
#include <string>

using namespace std;

class StrSection: public Section {
public:
    StrSection(uint8_t* data, bool is32);

    string getNameByIndex(const vector<uint8_t> &data, int index);
};

#endif //ELF_READER_STR_SECTION_H

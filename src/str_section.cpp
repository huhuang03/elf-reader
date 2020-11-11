//
// Created by th on 2020/11/10.
//

#include "str_section.h"

StrSection::StrSection(uint8_t *data, bool is32) : Section(data, is32) {
}

string StrSection::getNameByIndex(const vector<uint8_t> &data, int index) {
    assert(index < this->get_sh_size());
    return std::string((char*)(data.data() + this->get_sh_offset() + index));
}

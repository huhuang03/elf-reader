//
// Created by th on 2020/11/10.
//

#ifndef ELF_READER_UTIL_H
#define ELF_READER_UTIL_H
#include <string>

using namespace std;

string to_hex(uint32_t value, bool with0x=true, int width=-1);
string to_hex(int value, bool with0x, int width);
string to_hex(const uint8_t *data, int len);

#endif //ELF_READER_UTIL_H
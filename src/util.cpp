//
// Created by th on 2020/11/10.
//

#include "util.h"
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

string to_hex(uint32_t value, bool with0x, int width) {
    std::stringstream stream;
    if (with0x) {
        stream << "0x" << endl;
    }
    stream << std::hex << value;
    std::string result( stream.str() );
    return std::string();
}

string to_hex(int value, bool with0x, int width) {
    return to_hex((uint32_t)value, with0x, width);
}

string to_hex(const uint8_t *data, int len) {
    cout << "111" << endl;
    std::stringstream stream;
    cout << "222" << endl;
    stream << hex;
    cout << "333" << endl;
    stream << std::setfill('0') << std::setw(2);
    cout << "444" << endl;

    for (int i = 0; i < len; i++) {
        cout << "555" << endl;
        printf("%p\n", data);
        uint8_t d = data[i];
        cout << "666" << endl;
        stream << d;
        stream << " ";
    }
    return std::string();
}

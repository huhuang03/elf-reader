//
// Created by th on 2020/9/16.
//

#include "elf.h"
#include <fstream>
#include <cassert>
#include <iostream>

using namespace std;

bool Elf::initialFromFilePath(Elf &elfFile, const string &path) {
    // read file to content
    ifstream is(path);
    assert(is.good());
    std::istream_iterator<uint8_t> start(is), end;
    elfFile.initialWithData(vector<uint8_t>(start, end));
    return true;
}

#define ET_EXEC 0x2
#define ET_DYN 0x3


void Elf::pp(bool isPHeader) 
{
    if (isPHeader) {
        cout << "Header: \n";
        if (this->get_e_type() == ET_EXEC) {
            cout << "  Type: EXEC"  << endl;
        } else if (this->get_e_type()== ET_DYN) {
            cout << "  Type: DYN"  << endl;
        }
        cout << "  64 Or 32: " << (is32()? "32": "64") << endl;
    }
}

Elf::Elf(vector<uint8_t> &data) {
    this->initialWithData(data);
}

bool Elf::is32() {
    auto clazz = get_class();
    assert(clazz == 1 || clazz == 2);
    return clazz == 1;
}

bool Elf::is64() {
    return !this->is32();
}

Elf::Elf() = default;

void Elf::initialWithData(vector<uint8_t> data) 
{
    this->data = data;
    auto *ehdr = (Elf32_Ehdr*)this->data.data();
    assert(ehdr->e_type == 1 || ehdr->e_type == 2);
    this->_is32 = ehdr->e_type == 1;
}

int Elf::get_e_type() 
{
    if (this->is32()) {
        return ((Elf32_Ehdr*)this->data.data())->e_type;
    } else {
        return ((Elf64_Ehdr*)this->data.data())->e_type;
    }
}

int Elf::get_class() 
{
    return ((Elf32_Ehdr*)this->data.data())->e_ident[0x4];
}

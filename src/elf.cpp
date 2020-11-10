//
// Created by th on 2020/9/16.
//

#include "elf.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <utility>
#include "section.h"
#include "util.h"

using namespace std;

bool Elf::initialFromFilePath(Elf &elfFile, const string &path) {
    // read file to content
    std::ifstream testFile(path, std::ios::binary);
    std::vector<char> fileContents((std::istreambuf_iterator<char>(testFile)),
                                   std::istreambuf_iterator<char>());
    std::vector<unsigned char> data(fileContents.begin(), fileContents.end());

    elfFile.initialWithData(data);
    return true;
}

#define ET_EXEC 0x2
#define ET_DYN 0x3

void Elf::pp(bool isPHeader, bool isPSection) 
{
    if (isPHeader) {
        cout << "Header: \n";
        cout << "  64 Or 32: " << (is32()? "32": "64") << endl;
        if (this->get_e_type() == ET_EXEC) {
            cout << "  Type: EXEC"  << endl;
        } else if (this->get_e_type()== ET_DYN) {
            cout << "  Type: DYN"  << endl;
        }
        cout << "  Machine: " << to_hex(this->get_e_machine()) << endl;
    }

    cout << "shstrndx: " << this->get_e_shstrndx() << endl;
    if (isPSection) {
        cout << "Sections: \n";
        if (this->get_e_shnum() > 0) {
            for (int i = 0; i < this->get_e_shnum(); i++) {
                auto start = this->get_e_shoff() + (i * this->get_e_shentsize());
                auto section = Section(this->data.data() + start, is32());
                section.get_sh_name();
                cout << "  Section " << section.get_sh_name() << endl;
                cout << "    Name: " << this->strSection->getNameByIndex(this->data, section.get_sh_name()) << endl;
            }
        } else {
            cout << "  No Sections" << endl;
        }
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
    // what is move
    // why you can move??
    // what function called in vector??
    this->data = data;
    this->strSection = new StrSection(this->getSectionOffsetByIndex(this->get_e_shstrndx()), is32());
}


int Elf::get_class() 
{
    return ((Elf32_Ehdr*)this->data.data())->e_ident[0x4];
}

void Elf::initStringTable() 
{
}

Elf32_Ehdr *Elf::as32Ehdr() {
    return (Elf32_Ehdr*)this->data.data();
}

Elf64_Ehdr *Elf::as64Ehdr() {
    return (Elf64_Ehdr*)this->data.data();
}

#define header_value_of(name) \
if (this->is32()) {           \
    return as32Ehdr()->name;\
} else {                      \
    return as64Ehdr()->name;\
}

int Elf::get_e_shentsize() {
    header_value_of(e_shentsize)
}

int Elf::get_e_type()
{
    header_value_of(e_type)
}

int Elf::get_e_shnum() {
    if (this->is32()) {
        return as32Ehdr()->e_shnum;
    } else {
        return as64Ehdr()->e_shnum;
    }
}

int Elf::get_e_shstrndx() {
    header_value_of(e_shstrndx)
}

int Elf::get_e_shoff() {
    header_value_of(e_shoff)
}

int Elf::get_e_machine() {
    header_value_of(e_machine)
}

uint8_t* Elf::getSectionOffsetByIndex(int index) {
    return this->data.data() + this->get_e_shoff() + this->get_e_shstrndx() * this->get_e_shentsize();
}

//Elf32_Shdr *Elf::as32Shdr(int start) {
//    return (Elf32_Shdr*)this->data.data() + start;
//}
//
//Elf64_Shdr *Elf::as64Shdr(int start) {
//    return (Elf64_Shdr*)this->data.data() + start;
//}

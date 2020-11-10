#include <iostream>
#include "elf.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " elf_file" << endl;
        return 0;
    }

    char* path = argv[1];
    Elf elf;
    Elf::initialFromFilePath(elf, path);
    elf.pp();
}
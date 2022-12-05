#include "elf.h"
#include <iostream>

static bool file_exits(std::string path) {
    std::ifstream f(path.c_str());
    return f.good();
}

std::string Elf::checkMagic() {
    // assume in_stream_ is ok
    char magic[4];
    this->in_stream_->read(magic, 4);
    char rightMagic[] = {0x7F, 'E', 'L', 'F'};
    for (int i = 0; i < 4; i++) {
        if (magic[i] != rightMagic[i]) {
            return "magic at pos " + std::to_string(i) + " want " + std::to_string(rightMagic[i]) + " but was: "
            + std::to_string(magic[i]);
        }
    }
    return "";
}

Elf::Elf(const std::string& filepath) {
    if (!file_exits(filepath)) {
        std::cout << filepath << " not exit!" << std::endl;
        // good at here??
        exit(0);
    }

    // good!!
    this->in_stream_ = new std::ifstream(filepath.c_str());
    auto errMsg = checkMagic();
    if (!errMsg.empty()) {
        std::cout << filepath << " is not a elf file(" << errMsg << ")" << std::endl;
    }
}

Elf::~Elf() {
    if (in_stream_ != nullptr && !in_stream_->is_open()) {
        in_stream_->close();
        in_stream_ = nullptr;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " filepath" << std::endl;
        return 0;
    }
    Elf elf(argv[1]);
}
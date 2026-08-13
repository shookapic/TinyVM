#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "cpu.hpp"

class Assembly {
    public:
        Assembly(std::string file_path);
        ~Assembly() = default;
        int validate_path(std::string filepath);
        void parse();
        std::vector<std::uint8_t> get_bytecode();
        void set_bytecode(std::vector<std::uint8_t>);
    private:
        const std::string filepath;
        std::vector<std::uint8_t> bytecode;
        std::ifstream asmfile;
};

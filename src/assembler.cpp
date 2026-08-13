#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "cpu.hpp"

std::vector<std::uint8_t> assemble(const std::string& source) {
    std::ifstream myfile = std::ifstream(source);
    if (!myfile) {
        std::cerr << "Unable to open file." << std::endl;
        exit(1);
    }
    std::vector<std::uint8_t> bytecode;
    std::string line;
    while (std::getline(myfile, line)) {
        std::istringstream iss(line);

        std::string instruction;
        iss >> instruction;

        if (instruction == "HALT") {
            bytecode.push_back(static_cast<std::uint8_t>(OP_CODE::HALT));
        }else if (instruction == "MOV") {
            std::string reg;
            std::string value;

            iss >> reg >> value;

            if (reg.size() != 2 ||
                reg[0] != 'R' ||
                reg[1] < '0' ||
                reg[1] > '7')
            {
                std::cerr << "Invalid register: " << reg << '\n';
                continue;
            }

            std::uint8_t register_index = reg[1] - '0';
            std::uint64_t number = std::stoull(value);

            bytecode.push_back(static_cast<std::uint8_t>(OP_CODE::MOV));
            bytecode.push_back(register_index);

            for (int i = 0; i < 8; i++) {
                std::uint8_t byte =
                static_cast<std::uint8_t>((number >> (i * 8)) & 0xFF);

                bytecode.push_back(byte);
                }
        } else if (instruction == "ADD") {
            std::string destination;
            std::string source;

            iss >> destination >> source;

            // encoder ADD
        }
    }
}

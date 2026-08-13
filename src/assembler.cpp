#include "cpu.hpp"
#include "assembler.hpp"

Assembly::Assembly(std::string file_path) : filepath(file_path)
{
    this->validate_path(file_path);
    this->parse();
}

int Assembly::validate_path(std::string file_path) {
    std::ifstream asmfile(this->filepath);
    if (!asmfile) {
        std::cerr << "Unable to open file." << std::endl;
        exit(1);
    }
    return 0;
}

void Assembly::parse() {
    std::ifstream myfile = std::ifstream(this->filepath);
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
            
            if (destination.size() == 2 &&
                destination[0] == 'R' &&
                destination[1] >= '0' &&
                destination[1] <= '7' &&
                source.size() == 2 &&
                source[0] == 'R' &&
                source[1] >= '0' &&
                source[1] <= '7') {
                std::uint8_t dest_index = destination[1] - '0';
                std::uint8_t src_index = source[1] - '0';
                bytecode.push_back(static_cast<std::uint8_t>(OP_CODE::ADD));
                bytecode.push_back(dest_index);
                bytecode.push_back(src_index);
                }
            
        } else if (instruction == "CMP") {
            std::string destination;
            std::string source;

            iss >> destination >> source;
            if (destination.size() == 2 &&
                destination[0] == 'R' &&
                destination[1] >= '0' &&
                destination[1] <= '7' &&
                source.size() == 2 &&
                source[0] == 'R' &&
                source[1] >= '0' &&
                source[1] <= '7') {
                std::uint8_t dest_index = destination[1] - '0';
                std::uint8_t src_index = source[1] - '0';
                bytecode.push_back(static_cast<std::uint8_t>(OP_CODE::CMP));
                bytecode.push_back(dest_index);
                bytecode.push_back(src_index);
                }

        } else if (instruction == "JMP") {
            std::string value;

            if (!(iss >> value)) {
                std::cerr << "JMP requires an address.\n";
                continue;
            }

            if (value.find_first_not_of("0123456789") != std::string::npos) {
                std::cerr << "JMP address must be a non-negative number.\n";
                continue;
            }
            bytecode.push_back(static_cast<std::uint8_t>(OP_CODE::JMP));
            
            std::uint64_t address = std::stoull(value);
            for (int i = 0; i < 8; i++) {
                std::uint8_t byte =
                static_cast<std::uint8_t>((address >> (i * 8)) & 0xFF);
                bytecode.push_back(byte);
            }
        }
    }
    this->bytecode = bytecode;
}

std::vector<std::uint8_t> Assembly::get_bytecode()
{
    return this->bytecode;
}

void Assembly::set_bytecode(std::vector<std::uint8_t> bytecode)
{
    this->bytecode = bytecode;
}
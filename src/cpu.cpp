#include "cpu.hpp"

CPU::CPU() {
    _registers.fill(0);
    _pc = 0;
}

void CPU::load_program(const std::vector<std::uint8_t>& program_data) {
    this->_program = program_data;
    this->_pc = 0;
}

void CPU::run() {
    this->_isRunning = true;
    while (this->_isRunning) {
        this->execute_instruction();
    }
}

void CPU::execute_instruction() {
    if (this->_pc >= this->_program.size()) {
        this->_isRunning = false;
        return;
    }

    std::uint8_t opcode = _program[_pc];
    _pc++;

    //decode opcode

    OP_CODE decoded_opcode = static_cast<OP_CODE>(opcode);

    //execute opcode

    switch (decoded_opcode) {
        case OP_CODE::HALT:
            this->_isRunning = false;
            break;

        case OP_CODE::MOV:
            if (this->_pc < this->_program.size()) {
                std::uint8_t register_index = this->_program[this->_pc];
                this->_pc++;
                if (register_index < this->_registers.size()) {
                    if (_pc + 8 <= _program.size()) {
                        std::uint64_t value = 0;
                        for (int i = 0; i < 8; i++) {
                            value |= static_cast<std::uint64_t>(
                                        this->_program[this->_pc + i]
                                        ) << (i * 8);
                        }
                        this->_pc += 8;
                        this->_registers[register_index] = value;
                    }
                }
            }
            break;

        case OP_CODE::ADD:
            if (this->_pc + 2 <= this->_program.size()) {
                std::uint8_t destination;
                std::uint8_t source;
                destination = _program[_pc];
                source = _program[_pc + 1];
                _pc+=2;
                if (destination < _registers.size() && source < _registers.size()) {
                    _registers[destination] += _registers[source];
                }
            }
            break;
        default:
            std::cerr << "OP_CODE: " << static_cast<int>(decoded_opcode) << " not recognized." << std::endl;
        return;
    }
}

void CPU::dump_registers() const {
    for (std::size_t i = 0; i < this->_registers.size(); i++) {
        std::cout << "R" << i << " = " << this->_registers[i] << '\n';
    }

    std::cout << "PC = " << this->_pc << '\n';
}
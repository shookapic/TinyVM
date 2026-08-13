#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <stdbool.h>
#include <iostream>

enum class OP_CODE : std::uint8_t {
    HALT = 0x00,
    MOV  = 0x01,
    ADD  = 0x02,
};

class CPU {
public:
    CPU();
    ~CPU() = default;

    void load_program(const std::vector<std::uint8_t>& program_data);
    void dump_registers() const;
    void run();

private:
    void execute_instruction();

    std::vector<std::uint8_t> _program;
    std::array<std::uint64_t, 8> _registers;
    std::size_t _pc; // Program Counter
    bool _isRunning = false;
};

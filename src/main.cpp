#include "cpu.hpp"

int main(int ac, char** av) {
    CPU cpu;
    std::vector<std::uint8_t> program = {
    0x01, 0x03,
    0x2A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00
    };
    cpu.load_program(program);
    cpu.run();
    cpu.dump_registers();
    return 0;
}

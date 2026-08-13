#include "cpu.hpp"
#include "assembler.hpp"

int main(int ac, char** av) {
    if (ac < 2) {
        std::cerr << "Usage: " << av[0] << " <file.asm>" << std::endl;
        return 1;
    }
    CPU cpu;
    Assembly assembly(av[1]);
    cpu.load_program(assembly.get_bytecode());
    cpu.run();
    cpu.dump_registers();
    return 0;
}

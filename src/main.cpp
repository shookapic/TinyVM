#include "cpu.hpp"
#include "assembler.hpp"

int main(int ac, char** av) {
    CPU cpu;
    

    cpu.load_program(assemble(av[1]));
    cpu.run();
    cpu.dump_registers();
    return 0;
}

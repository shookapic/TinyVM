# TinyVM

TinyVM is a lightweight 64-bit virtual machine built from scratch in C++.

The goal of this project is to explore low-level concepts such as virtual CPU design, instruction encoding, bytecode execution, registers, memory, stack operations, and assembly language design by implementing them from the ground up.

> TinyVM is currently under active development.

## Overview

TinyVM implements a custom virtual CPU with its own instruction set architecture (ISA) and bytecode format.

Programs can be written using TinyVM assembly:

```asm
MOV R0 5
MOV R1 10
ADD R0 R1
HALT
```

The assembler converts the source code into TinyVM bytecode:

```text
Assembly source
      ↓
   Assembler
      ↓
   Bytecode
      ↓
 Virtual CPU
      ↓
Fetch → Decode → Execute
```

For example:

```asm
ADD R0 R1
```

is encoded as:

```text
02 00 01
│  │  │
│  │  └── Source register (R1)
│  └───── Destination register (R0)
└──────── ADD opcode
```

## Architecture

The current virtual CPU contains:

- 8 general-purpose 64-bit registers (`R0` - `R7`)
- A program counter (`PC`)
- A custom 8-bit opcode instruction set
- A fetch/decode/execute execution loop
- Little-endian 64-bit immediate values
- A basic assembler
- Register state dumping for debugging

## Instruction Set

| Opcode | Instruction | Encoding | Description |
|---|---|---|---|
| `0x00` | `HALT` | `HALT` | Stops execution |
| `0x01` | `MOV` | `MOV Rx imm64` | Loads a 64-bit immediate into a register |
| `0x02` | `ADD` | `ADD Rx Ry` | Adds the source register to the destination register |

Example:

```asm
MOV R0 5
MOV R1 10
ADD R0 R1
HALT
```

Expected state after execution:

```text
R0 = 15
R1 = 10
R2 = 0
R3 = 0
R4 = 0
R5 = 0
R6 = 0
R7 = 0
```

## Project Structure

```text
TinyVM/
├── include/
│   └── cpu.hpp
├── src/
│   ├── assembler.cpp
│   ├── cpu.cpp
│   └── main.cpp
├── tests/
└── CMakeLists.txt
```

## Roadmap

TinyVM is being developed incrementally.

- [x] Virtual CPU
- [x] 64-bit registers
- [x] Program counter
- [x] Fetch / Decode / Execute loop
- [x] `HALT`
- [x] `MOV`
- [x] `ADD`
- [ ] Assembler improvements and error handling
- [ ] `SUB`, `MUL`, `DIV`
- [ ] CPU flags
- [ ] `CMP`
- [ ] Conditional and unconditional jumps
- [ ] Virtual memory
- [ ] Stack
- [ ] `PUSH` / `POP`
- [ ] `CALL` / `RET`
- [ ] Labels
- [ ] Binary executable format
- [ ] Disassembler
- [ ] Interactive debugger

## Why TinyVM?

TinyVM is primarily an educational systems programming project.

Instead of relying on an existing VM framework, the project implements the core components manually to better understand how instructions are encoded, decoded and executed by a CPU-like architecture.

The long-term goal is to evolve TinyVM from a minimal bytecode interpreter into a small but complete virtual computer with its own assembler, memory model, stack and debugging tools.

## Build

Requirements:

- C++17 or newer
- CMake
- A C++ compiler supporting C++17

```bash
cmake -S . -B build
cmake --build build
```

## License

MIT

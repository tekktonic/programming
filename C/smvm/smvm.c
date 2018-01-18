#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// memory[2047]is the status register
// memory[2048] is packed kdr, ksr, ddr, dsr
int32_t memory[2046];
int32_t status;
char kdr, ksr, ddr, dsr;

int32_t registers[16];
uint16_t pc;

uint16_t retreg;


enum registers
{
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    RA,
    RB,
    RC,
    RD,
    RE,
    RF
};

const char * const ops_strings[] = {
    "ADD",
    "AND",
    "OR",
    "NOT",
    "BR",
    "LD",
    "LDI",
    "ST",
    "STI",
    "JMP",
    "TRP",
    "JSR"
};

enum ops
{

// | O | O | O | 1 | DR | DR | DR | DR | 0 | SR1 | SR1 | SR1 | SR1 | SR1 | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
// | O | O | O | 1 | DR | DR | DR | DR | 1 | SR1 | SR1 | SR1 | SR1 | SR1 | SR2 | SR2 | SR2 | SR2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    ADD,
    
// | O | O | 1 | O | DR | DR | DR | DR | 0 | SR1 | SR1 | SR1 | SR1 | SR1 | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
// | O | O | 1 | O | DR | DR | DR | DR | 1 | SR1 | SR1 | SR1 | SR1 | SR1 | SR2 | SR2 | SR2 | SR2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    AND,
    
// | O | O | 1 | 1 | DR | DR | DR | DR | 0 | SR1 | SR1 | SR1 | SR1 | SR1 | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
// | O | O | 1 | 1 | DR | DR | DR | DR | 1 | SR1 | SR1 | SR1 | SR1 | SR1 | SR2 | SR2 | SR2 | SR2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    OR,

// | O | 1 | 0 | 1 | DR | DR | DR | DR | 0 | SR1 | SR1 | SR1 | SR1 | SR1 | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
// | O | 1 | 0 | 1 | DR | DR | DR | DR | 1 | SR1 | SR1 | SR1 | SR1 | SR1 | SR2 | SR2 | SR2 | SR2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    NOT,
    

    
// | O | 1 | O | O | 0  | N  | Z  | P  | # | #   | #   | #   | #   | #   | #   | #   | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | 
    BR,

// | O | 1 | 1 | 1 | DR | DR | DR | DR | # | #   | #   | #   | #   | #   | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
    LD,
    
// | 1 | 0 | 0 | 0 | DR | DR | DR | DR | # | #   | #   | #   | #   | #   | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
    LDI,

// | 1 | 0 | 0 | 1 | DR | DR | DR | DR | # | #   | #   | #   | #   | #   | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
    ST,
// | 1 | 0 | 1 | 0 | DR | DR | DR | DR | # | #   | #   | #   | #   | #   | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | # | # | # |
    STI,
    
// | 1 | 0 | 1 | 1 | 0  | 0  | 0  | 0  | 0 |SR1  | SR1 | SR1 | SR1 | 0   | 0   | 0   | 0   | 0   | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    JMP,
    
// | 1 | 1 | 0 | 0 | DR | DR | DR | DR | 0 |SR1  | SR1 | SR1 | SR1 | 0   | 0   | 0   | 0   | 0   | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
    TRP,


// | O | 1 | 1 | O | #  | #  | #  | #  | # | #   | #   | #   | #   | #   | #   | #   | #   | #   | #   | #   | # | # | # | # | # | # | # | # | # | # | # | # | 
    JSR


};

union operands
{
    int32_t lit_28bit;
    struct {
        uint8_t dr;
        int32_t lit_24bit;
    } dr;
    
    struct {
        uint8_t dr;
        uint8_t sr1;
        int32_t lit_19bit;
    } drsr;

    struct {
        uint8_t dr;
        uint8_t sr1;
        uint8_t sr2;
    } drsr2;
};

struct opcode
{
    enum ops opcode;
    bool variant;
    union operands operands;
};

enum ops get_op(int32_t instruction)
{
    return instruction >> 28;
}

bool get_variant(int32_t instruction)
{
    return (instruction >> 24) & 0x1;
}

int32_t get_dr(int32_t instruction)
{
    return (instruction << 4) >> 24;
}

int32_t get_sr1(int32_t instruction)
{
    return (instruction << 9) >> 19;
}

int32_t get_sr2(int32_t instruction)
{
    return (instruction << 13) >> 15;
}

enum ops get_operands(int32_t instruction)
{
    switch (get_op(instruction))
    {
    // break into our classes of instruction
    case ADD:
    case AND:
    case OR:
    case NOT:
        if (get_variant(instruction))
            return (enum operands){.drsr2.dr = get_dr(instruction), .drsr2.sr1 = get_sr1(instruction), .drsr2.sr2 = get_sr2(instruction)};
        else
            return (enum operands){.drsr.dr = get_dr(instruction), .drsr.sr1 = get_sr1(instruction), .drsr.lit19bit = instruction & 0x7FFFF};
        break;

    case BR:
    case LD:
    case LDI:
    case ST:
    case STI:
        return (enum operands){.dr.dr = get_dr(instruction), .lit_24bit = instruction & 0xFFFFFF};
        break;
        
    case JMP:
    case TRP:
        return (enum operands){.drsr.dr = get_dr(instruction), .drsr.sr1 = get_sr1(instruction), .lit_19bit = 0};
        
    case JSR:
        return (enum operands){.lit_28bit = instruction & 0xFFFFFF};
    }
}

struct opcode parse_opcode(int32_t instruction)
{
    return {.opcode = get_op(instruction), .variant = get_variant(instruction), .operands = get_operands(instruction)};
}

void print_opcode(int32_t instruction)
{
    printf("%s\n", ops_strings[get_op(instruction)]);
}


int main(void)
{
    while (!feof(stdin))
    {
        int instruction;
        scanf("%X", &instruction);
        print_opcode(instruction);
    }

    return 0;
}

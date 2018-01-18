#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t memory[255];

void dump_memory(void) {
    for (int i = 0; i < 256; i++) {
        printf(" %c ", memory[i]);
        if (i % 8 == 7)
            printf("\n");
    }
}

int main(int argc, char **argv) {
    uint8_t pc=0, load = 0, store = 0;

    memset(memory, 0, 256);

    FILE *binary = fopen(argv[1], "r");
    fread(memory, sizeof(uint8_t), 256, binary);
    fclose(binary);

    store = memory[pc+1];
    load = memory[pc];
    pc = memory[pc+2];
    if (!(pc | store | load)) {
        exit(0);
    }
    while (((pc != memory[pc+2]) | store | load)) {
        dump_memory();
        printf("\n\n");
        memory[store] = memory[load];
        store = memory[pc+1];
        load = memory[pc];
        pc = memory[pc+2];
    
    } 
}

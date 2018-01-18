#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fenv.h>

typedef enum
{
    NOP,//0
    LOD,//1
    STO,//2
    ADD,//3
    SUB,//4
    DIV,//5
    MUL,//6
    MOD,//7
    CMP,//8
    JMP,//9
    JGE,//A
    JLE,//B
    JG,//C
    JL,//D
    JE,//E
    DPY,// F
    HLT,//10
    DMP//11
}opcodes;

typedef enum
{
    OK,
    DIVZERO,
    NOIMG,
}errors;


unsigned char pc = 0;
int flags = 0x00;
unsigned char *memory;
unsigned char debugMode;

void eval(void);

int main(int argc,const char **argv)
{
    FILE *image;
    int imgsize;
    if (argc == 1)
    {
	printf("No binary image specified\n");
	return NOIMG;
    }
    if (strcmp(argv[1], "-d") == 0)
    {
	debugMode = 1;
	image = fopen(argv[2], "rb");
    }
    else
	image = fopen(argv[1], "rb");

    fseek(image, 0, SEEK_END);
    imgsize = ftell(image);
    fseek(image, 0, SEEK_SET);
    printf("%d", ftell(image));
    memory = calloc(1, 512);
    fread(memory + 3, 1, imgsize, image);
    while (flags != 0xDEAD)
    {
	eval();
    }
    printf("\n");
    return 0;
}

void eval(void)
{
    switch (memory[pc])
    {
    case NOP: break;
    case LOD: memory[0] = /*memory[*/memory[++pc]/*]*/; printf("LDA %d\n", memory[memory[pc]]);break;
    case STO: assert(memory[++pc] == 0 || memory[pc] == 1 || memory[pc] == 2);memory[memory[++pc]] = memory[--pc]; printf("STA %d\n", memory[memory[pc]]);pc += 2;break;

    case ADD: memory[2] = memory[0] + memory[1];break;
    case SUB: memory[2] = memory[0] - memory[1];break;
    case MUL: memory[2] = memory[0] * memory[1];break;
    case DIV: memory[2] = memory[0] / memory[1];break;
    case MOD: memory[2] = memory[0] % memory[1]; break;


    case CMP: flags = (memory[0] < memory[1] ? 0 : memory[0] > memory[1] ? 2 : 1);break;
    case JMP: pc = memory[++pc] - 1;break;
    case JGE: (flags == 0x0001 || flags == 0x0002) ? pc = memory[++pc] : 0; break;
    case JLE: (flags == 0x0000 || flags == 0x0001) ? pc = memory[++pc] : 0; break;
    case JG: (flags == 0x0002) ? pc = memory[++pc] : 0;break;
    case JL: (flags == 0x0000) ? pc = memory[++pc] : 0;break;
    case JE: (flags == 0x0001) ? pc = memory[++pc] : 0;break;
    case DPY: printf("%c", memory[++pc]);break;
    case HLT: flags = 0xDEAD;break;
    case DMP:
	printf("BEGIN DUMP:\na: %x\nb: %x\nc: %x\nflags: %d\npc: %x\n", memory[0], memory[1], memory[2], flags, pc);
	register int i = 0;
	for (; i < 64; ++i)
	{
	    printf("%x ", memory[i]);
	}
	printf("\nEND DUMP\n");
	break;
    }
    ++pc;
}

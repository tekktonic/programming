#include <stdio.h>
#include <stdlib.h>
//magic number (4 bytes), 64 bit, little endian, version (1), abi (sysv), abi version
// padding, type (executable), x86_64 ISA
char elfHeader = {0x7F, 'E', 'L', 'F', 2, 1, 1, 0, 8, 0, 0, 0, 0, 0, 0, 0, 2,
		  0x3E, 
};


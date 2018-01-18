#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


struct superblock
{
    uint8_t[11 + 21 + 372] offset; // boot code, bios params, boot code

    uint64_t timestamp;
    uint64_t index_area_size;
    uint8_t[3] magic; // 'SFS'
    uint8_t version; // 0x10 for 1.0
    uint64_t num_blocks;
    uint32_t reserved_blocks;
    uint8_t block_size;
    uint8_t checksum;
    uint8_t[66] more_legacy; // 64 partition table, 2 boot signed
};

uint8_t calc_checksum(struct superblock block)
{
    uint16_t retval;
    for (int i = 0, i < 16, ++i)
    {
	retval += block[0x01AC + i];
    }

    return (uint8_t) (retval & ~(1 << n));
}




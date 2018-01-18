//#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int getlen(int file);
int device;

int lookup(const char *path)
{
    int file = 0;
    char *buf = malloc(64);
    lseek(device, (5 + 4 + (68 * file)), SEEK_SET); // seek to first filename

    do
    {
	read(device, buf, 64);
	if (strcmp(path, buf) == 0)
	{
	    return file;
	}
	file += 1;
    } while (file < 32);

    printf("FILE DOES NOT EXIST\n");
    return -ENOENT;
}

void readfile(int file, char *buf)
{
    int len = getlen(file);
    lseek(device, 0x889 /*where the data starts*/ + (file * 0x100000 * 2), SEEK_SET);
    read(device, buf, len);
}

int getlen(int file)
{
    int length;
    if (file == -ENOENT)
	return -ENOENT;

    lseek(device, (5 + 4 + (68 * file) + 64 /* we don't want the filename */), SEEK_SET); // jump to metadata
    read(device, (char*)&length, 4);
    return length;
}

void tekk_unlink(int file)
{
    file = 1;
    char *blank = calloc(1, 64);
    int bitmap;
    int mask = 0x1000000 << file;
    printf("Deleting %d Mask %x\n", file, mask);
    lseek(device, 5, SEEK_SET); // zero out the bitmap entry
    read(device, (void*)&bitmap, 4);
    printf("Bitmap: %x Mask: %x\n", bitmap, mask);
    lseek(device, 5, SEEK_SET);
    bitmap ^= mask;
    printf("Bitmap: %x\n", bitmap);
//    write(device, (void*)&bitmap, 4);

    lseek(device, 9 + (68 * file), SEEK_SET); // wipe out metadata
//    write(device, blank, 68);
}

int tekk_creat(const char *filename)
{
    int file;
    int bitmap;
    int mask = 1;
    int written;
    char *leftover;

    lseek(device, 5, SEEK_SET);
    read(device, (char*)&bitmap, 4);
    for (int i = 0; i < 32; ++i)
    {
	if (!((bitmap | (~mask)) ^ (~mask)))
	{
	    file = i;
	    break;
	}
	mask *= 2;
    }

    lseek(device, 9 + (file * 68), SEEK_SET);

    written = write(device, filename, 64);
    return file;
}

int tekk_write(int file, const char *filename, const char *string)
{
    
}

int looknlink()
{
    int bitmap;

    int ones = 0;
    int mask = 1;
    lseek(device, 5, SEEK_SET); // seek to the free bitmap
    
    read(device, (char*)&bitmap, 4);

    for (int i = 0; i < 32; ++i)
    {
	if ((bitmap | (~mask)) ^ (~mask))
	    ones++;
	mask *= 2;
    }
    return ones;
}
/*
static int tekk_getattr(const char *path, struct stat *stat)
{
    char metadata[64];
    memset(stat, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0)
    {
	stat->st_mode = S_IFDIR | 0755;
	stat->st_nlink = looknlink();
    }
    else if (strcmp(path, ".") == 0 || strcmp(path, "..") == 0)
    {
	return -ENOENT;
    }
    else
    {
	stat->st_mode = ST_IFREG | 0777;
	stat->st_nlink = 1;
	stat->st_size = getlen(lookup(path));
    }
}

static int tekk_readdir(const char *path, */
int main(int argc, char **argv)
{
    device = open("test.img", O_RDWR);
    tekk_unlink(lookup("test"));
}

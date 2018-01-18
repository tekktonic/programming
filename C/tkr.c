#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>

#include "dtype.h"

typedef int fd_t;

enum EntryType
{
    file,
    directory
};

struct Entry;

struct File // This is not a replacement for tar, there is no user/group or permission management. everything is created with usual permissions if it's created at all.
{
    uint64_t offset;
    uint64_t length;
    char name[256];
};

struct Directory
{
    char name[256];
    uint64_t numEntries;
    struct Entry *entries;
};

union contents
{
    struct File file;
    struct Directory directory;
};

struct Entry
{
    enum EntryType type;
    union contents content;
};

struct Archive
{
    char magic[3]; // TKR
    uint64_t numFiles; // there is always at least 1 directory, ".". If no directory is specified then all files go in there.
    struct Files *files;
    char *data;
};

/*void extract_archive(int argc, char **args)
{

}*/

/*struct Directory make_entry(char *filename)
{
    struct Directory ret;
    struct stat st;

    stat(filename, &st);

    if (S_ISDIR(st.st_mode))
    {
	ret.type = directory;
	strncpy(ret.content.directory.name, filename, 256);
	ret.content.directory.name[255] = 0;
    }
    else
    {

      ret.type = file;
      ret.content.file.length = st.st_size;
	strncpy(ret.content.file.name, filename, 256);
	ret.content.file.name[255] = 0;
    }

    return ret;
    }
*/


void add_file_entry(List filelist, char *filename)
{
    struct File *ret = malloc(sizeof(struct File));
    struct stat st;

    stat(filename, &st);

    ret->length = st.st_size;
    strncpy(ret->name, filename, sizeof(ret->name));
    ret->name[255] = 0;

    List_enqueue(filelist, ret);
}

void write_files(List filelist, fd_t archive)
{
    List last = NULL;

    for(List cur = filelist; cur; cur = cur->cdr)
    {
	struct File *entry = (struct File*)cur->car;
	fd_t file = open(cur->car, O_RDONLY);
	char buf[256];

	entry->offset = lseek(archive, SEEK_CUR, 0);

	while(read(file, buf, 256)
	{
	    int bytes = write(archive, buf, 256);
	    printf("%d\n", bytes);
	}
    }
}

void create_archive(int argc, char **files)
{
    List files;
    fd_t archive = open(args[0], O_WRONLY | O_CREAT);
    if (archive == -1)
    {
	perror(strerror(errno));
    }

    files = new_List(NULL);
    for(int i = 1; i < argc; i++) // archive name is args[0]
    {
	add_file_entry(files, args[i]);
    }
    write_files(files, archive);
}

int main(int argc, char **argv)
{
    assert(argc > 3);

    if (argv[1][0] == 'c')
	create_archive(argc - 2, argv + 2);
    if (argv[1][0] == 'x')
	extract_archive(argc - 2, argv + 2);
}

#ifndef DLIB_H
#define DLIB_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define die(m) {fprintf(stderr, "Dead at __FILE__:__LINE__: %s", m);exit(1);}

#define nulldie(v, m) {if (!v) {die(m)}};

off_t fsize(FILE *fp)
{
    off_t ret;
    off_t prev;
    prev = ftell(fp);
    fseek(fp, 0, SEEK_END);
    ret = ftell(fp);
    fseek(fp, prev, SEEK_SET);
    return ret;
}

char *slurp(char *file)
{
    char *buf;

    FILE *fp = fopen(file, "r");
    nulldie(fp, "Unable to open file");

    off_t fileSize = fsize(fp);
    buf = malloc(fileSize);
        nulldie(buf, "Unable to allocate buffer\n");
    fread(buf, sizeof(char), fileSize, fp);

    return buf;
}

#endif

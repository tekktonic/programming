#ifndef PERSON_H
#define PERSON_H

#include "dumpable.h"

struct person {
    struct dumpable dumper;
    // first, middle, last
    char *name[3];
    // Can't be worth more than a few billion, sorry.
    int wealth;

    // see preferences.h
    float preferences[4];
};

struct person new_person();

#endif

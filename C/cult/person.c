#include <stdio.h>
#include <stdlib.h>

#include "person.h"
#include "preferences.h"
#include "names.h"

void print_person(struct dumpable *dump_self)
{
    struct person *self = (struct person*)dump_self;

    printf("{\n\tname: %s %s %s\n", self->name[0], self->name[1], self->name[2]);
    for (int i = 0; i < sizeof(preference_strings)/sizeof(*preference_strings); i++)
    {
        printf("\t%s: %f\n", preference_strings[i], self->preferences[i]);
    }

    printf("\twealth: %d\n}", self->wealth);
}

float random_float() { return ((((double)rand()) / RAND_MAX) * 2) - 1;}

struct person new_person()
{
    struct person ret;
    ret.dumper.dump = print_person;
    ret.name[0] = firstnames[rand() % (sizeof(firstnames)/sizeof(*firstnames))];
    ret.name[1] = firstnames[rand() % (sizeof(firstnames)/sizeof(*firstnames))];
    ret.name[2] = lastnames[rand() % (sizeof(lastnames)/sizeof(*lastnames))];

    for (int i = 0; i < sizeof(preference_strings)/sizeof(*preference_strings); i++)
    {
        ret.preferences[i] = random_float();
    }

    ret.wealth = random();

    return ret;
}

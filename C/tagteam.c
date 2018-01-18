#include <stdio.h>
#include <stdlib.h>

#define error(s) fprintf(stderr, s);exit(1);
typedef struct 
{
    char *first;
    char *last;
}name;

typedef struct
{
    name name;
    int value;
    char used;
} fighter;

typedef struct
{
    fighter first;
    fighter second;
}pair;

typedef struct
{
    void *elm;
    int length;
} ArrayList;

ArrayList MakeTeams(ArrayList fighters);

int main(void)
{
    ArrayList fighters, pairs;
    int i;
    FILE *list = fopen("FighterList.txt", "r");
    if (!list)
    {
	perror(NULL);
    }

    fighters.elm = calloc(128, sizeof(fighter));
    fighters.length = 128;
    i = 0;
    while (!feof(list))
    {
	fighter f = ((fighter*)fighters.elm)[i];
	int result = fscanf(list, "%ms %ms %d", &f.name.first, &f.name.last, &f.value);
	printf("%s %s %d\n", f.name.first, f.name.last, f.value);
	if (result != 3)
	{
	    fprintf(stderr, "There was a problem with your file near line %d\n", i + 1);
	    exit(1);
	}
	f.used = 0;
	++i;
    }

    pairs = MakeTeams(fighters);
    return 0;
}

char AcceptablePair(fighter f1, fighter f2)
{
    return ((f1.value + f2.value <= 7) && !(f1.used || f2.used) && (&f1 != &f2));
}

ArrayList MakeTeams(ArrayList fighters)
{
    int pairings = fighters.length / 2;
    int f1, f2, i, reti;
    ArrayList ret;
    fighter* fs;
    ret.elm = calloc(sizeof(fighter), pairings);
    ret.length = pairings;

    if (fighters.length % 2 != 0)
	error("Odd number of fighters");

    f1 = 0;
    fs = ((fighter*)fighters.elm);

    while ((reti < ret.length) && (fs[f1] != 0))
    {
    start:
	f2 = rand() % fighters.length;

	if (AcceptablePair(fs[f1], fs[f2]))
	{
	    fs[f1].used = fs[f2].used = 1;
	    ((pair*)ret.elm)[reti].first = fs[f1];
	    ((pair*)ret.elm)[reti].second = fs[f2];

	    reti++;
	    f1++;
	}
    }

    return ret;
}

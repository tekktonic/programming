#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

enum directions
{
    D_NORTH,
    D_SOUTH,
    D_EAST,
    D_WEST,
    D_UP,
    D_DOWN
};

struct room
{
    struct room **exits; // north south east west up down
    char *description;
    char *distDescription; // description when looking from another room
    Mix_Chunk *sound; // each room has one ambient sound
    
    bool used;
};

typedef verb (void*)(struct room *room, char **nouns);

struct command
{
    verb verb;
    char **nouns;
}
int main(void)
{
    return 0;
}

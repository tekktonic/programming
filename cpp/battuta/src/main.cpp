#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "room.hpp"
//#include "globals.hpp"

SDL_Renderer *renderer;
int main(void)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);
    SDL_Window *win = SDL_CreateWindow("Battuta", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    renderer = SDL_CreateRenderer(win, -1, 0);
    
    Room r("room1.json");
    return 0;
}

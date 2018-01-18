#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"
#include "util.h"

SDL_Texture *spritesheets[4];

void draw_sprite(SDL_Renderer *r, Spritesheets sheet, int row, int column,
    SDL_Rect *where) {
    SDL_Rect dest = *where;
    if (!dest.w)
        dest.w = 32;
    if (!dest.h)
        dest.h = 32;
    dest.x -= 16;
    dest.y -= 16;
    SDL_Rect srcrect = {column*16, row*16, 16, 16};
    SDL_RenderCopy(r, spritesheets[sheet], &srcrect, &dest);
}

void init_spritesheets(SDL_Renderer *r) {
    const char *spritefiles[] = {
        "basictiles.png",
        "characters.png",
        "dead.png",
        "things.png",
        NULL
    };

    for (int i = 0; spritefiles[i]; i++) {
        spritesheets[i] = IMG_LoadTexture(r, spritefiles[i]);
        ORDIE(spritesheets[i] != NULL, IMG_GetError());
    }
}

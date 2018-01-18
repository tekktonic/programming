#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"
#include "entity.h"
#include "player.h"
#include "component.h"

const unsigned char *keyboard;

void render_base_room(SDL_Renderer *r) {
    static SDL_Texture *room = NULL;

    SDL_Rect dstrect= {0, 0, 0, 0} ;
    if (!room) {
        room = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
        SDL_SetRenderTarget(r, room);
        for (int i = 16; i < (768); i += 32){
            for (int ii = 16; ii < 1024; ii += 32) {
                dstrect.y = i;
                dstrect.x = ii;
                if (i == 16 || i == 768-16
                    || ii == 16 || ii == 1024-16) {
                    draw_sprite(r, SS_BASIC, 0, 0, &dstrect);
                }
                else {
                    draw_sprite(r, SS_BASIC, 0, 1, &dstrect);   
                }
            }
        }

        SDL_SetRenderTarget(r, NULL);
    }
    else {
//        dstrect = (SDL_Rect){0, 0, 1024, 768};
        SDL_RenderCopy(r, room, NULL, NULL);
    }
    
}

void update_components(Component *c, void *data) {
    c->update(c, (Entity*)data, 1000.0/60);
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    srand(time(NULL));

    SDL_Window *w = SDL_CreateWindow("Topdown", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);

    SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

    init_spritesheets(r);
    bool done = false;
    for (int i = 0; i < 256; i++)
    {
        entities[i] = NULL;
    }
    delete_clear();
    add_entity(new_player(r, 512, 384));


    while (!done) {
        uint32_t start_time = SDL_GetTicks();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {done = true;}
        }

        keyboard = SDL_GetKeyboardState(NULL);
 
        SDL_RenderClear(r);
    
        render_base_room(r);

        for (int i = 0; i < 256 && entities[i]; i++) {
            ch_iter(entities[i]->components, update_components, entities[i]);
            entities[i]->render->update(entities[i]->render, entities[i], 1000.0/60);
        }
//        printf("Done frame\n");
        delete_commit();
        SDL_RenderPresent(r);

        uint32_t sleeptime = 1000/60.0 - (start_time - SDL_GetTicks());
//        printf("%d\n", sleeptime);
        SDL_Delay(1000./60);
//        SDL_Delay(sleeptime);
//        SDL_Delay(2000);
    }
    IMG_Quit();
    SDL_Quit();
}

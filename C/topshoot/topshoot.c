#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <jansson.h>

#include "hashtbl.h"
#include "hint.h"
#include "jsonutils.h"
#include "obj.h"
#include "tonic.h"

#include "extras.h"
#include "globals.h"
#include "player.h"
#include "room.h"

#if INPUT == CONTROLLER
SDL_GameController *controller;
#endif




// UPDATE THIS
void die(struct obj *self, struct obj *other) // assume other takes care of itself
{
    printf("killing %p  %p\n", (void*)self, (void*)other);
    struct obj_vect *layer = hashtbl_find(&object_layers, self->layer);
    obj_vector_delete(layer, self);
    obj_vector_delete(self->object_vect, self);
    *self = (struct obj){.tex = NULL}; // null everything out
    struct obj *tof = self;
    self = NULL;
    free(tof);
}

static struct hashtbl images;
SDL_Texture *load_texture(SDL_Renderer *r, const char *filename)
{
    SDL_Texture *tex;
    tex = (SDL_Texture*)hashtbl_find(&images, filename);
    if (!tex) {
	printf("Loading a texture: %s\n", filename);
	tex = IMG_LoadTexture(r, filename);
	hashtbl_insert(&images, filename, tex);
    }
    return tex;
}

void release_textures(void)
{
    struct hashtbl *current = &images;

    while(current)
    {
	for(int i = 0; i < HASHTBL_SIZE; i++)
	    if (current->values[i])
		SDL_DestroyTexture(current->values[i]);
	current = current->next;
    }
}


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow("DECL TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
    SDL_Renderer *r = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


	
    SDL_Event e;
    bool running = true;
    struct room *room = NULL;
#if INPUT == CONTROLLER
    controller = SDL_GameControllerOpen(0);
    SDL_EventState(SDL_CONTROLLERAXISMOTION, SDL_IGNORE); // we handle these ourselves and they clog the input queue
    SDL_EventState(SDL_CONTROLLERBUTTONUP, SDL_IGNORE);
    SDL_EventState(SDL_CONTROLLERBUTTONDOWN, SDL_IGNORE);
#endif

    room = instantiate_room("level.json", r);
    printf("%p\n", (void*)room);
    // while (room)
    while(running)
    {
	room_update(room);
	while (SDL_PollEvent(&e))
	    if(e.type == SDL_QUIT)
		running = 0;

	SDL_RenderPresent(r);
    cpSpaceStep(room->space, 1.0/60.0);

	SDL_Delay(1000/60);
    }
    printf("CLOSING THE GAME\n");
    release_textures();
#if INPUT == CONTROLLER
    SDL_GameControllerClose(controller);
#endif
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
}

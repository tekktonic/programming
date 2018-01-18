#include "positionc.h"

#include <SDL2/SDL.h>

#include "../entity.h"
#include "../event.h"

static void update(Component *self, Entity *e, int dt) {
    SDL_Rect s = *(SDL_Rect*)self->data;
    if (s.x + s.w < 0 || s.x > 1024 || s.y + s.h < 0 || s.y > 768) {
        if (e->id == 2)
        {
            printf("ID is 2\n");
        }
        printf("Deleting %d\n", e->id);
        delete_entity(e->id);
    }
}

static void cleanup(Component *self) {
    free(self->data);
}

static void move(Component *self, EventData d) {
    SDL_Rect *r = (SDL_Rect*)d.data;
        SDL_Rect *s = (SDL_Rect*)self->data;
    s->x = r->x;
    s->y = r->y;
}

static void move_rel(Component *self, EventData d) {
    SDL_Rect *r = (SDL_Rect*)d.data;

    SDL_Rect *s = (SDL_Rect*)self->data;
    s->x += r->x;
    s->y += r->y;
    s->w += r->w;
    s->h += r->h;
}

static void *inspect(Component *self, int type) {
    SDL_Rect *ret;
    SDL_Rect *data = (SDL_Rect*)self->data;
    switch(type) {
    case POSITIONC_RECT:
        return self->data;
    case POSITIONC_CENTER:
        ret = malloc(sizeof(SDL_Rect));
        *ret = (SDL_Rect){.x = data->x + (data->w / 2),
                          .y = data->y + (data->h / 2)};
        return ret;
    default:
        return NULL;
    }
}

static void receive(Component *self, Event e) {
    receivecb callbacks[] = {move, move_rel};

    callbacks[e.t](self, e.d);
}


Component new_positionc(int x, int y, int w, int h) {
    Component ret = {.update = update, .cleanup = cleanup, .receive = receive,
    .inspect = inspect};
    ret.data = malloc(sizeof(SDL_Rect));

    *(SDL_Rect*)ret.data = (SDL_Rect){.x = x, .y = y, .w = w, .h = h};
    return ret;
}

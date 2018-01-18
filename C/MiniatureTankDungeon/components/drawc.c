#include "drawc.h"

#include "../entity.h"

typedef struct {
    int row;
    int column;
    SDL_Renderer *r;
    Spritesheets sheet;
}Draw;

static void cleanup(Component *self) {free(self->data);}

static void update(Component *self, Entity *e, int dt) {
    Draw *d = (Draw*)self->data;
    SDL_Rect *rect = (SDL_Rect*)ch_get(e->components, "position")->data;

    draw_sprite(d->r, d->sheet, d->row, d->column, rect);
}

static void row(Component *self, EventData d) {
    Draw *dr = (Draw*)self->data;

    dr->row = (int)d.i;
}

static void column(Component *self, EventData d) {
    Draw *dr = (Draw*)self->data;

    dr->column = (int)d.i;
}

static void sheet(Component *self, EventData d) {
    Draw *dr = (Draw*)self->data;

    dr->sheet = (Spritesheets)d.i;
}

static void receive(Component *self, Event e) {
    receivecb callbacks[] = {row, column, sheet};

    callbacks[e.t](self, e.d);
}

Component new_drawc(SDL_Renderer *r, Spritesheets sheet, int row, int col) {
    Component ret = {.cleanup = cleanup, .update = update, .receive = receive};
    ret.data = malloc(sizeof(Draw));
    Draw *d = (Draw*)ret.data;
    d->r = r;
    d->sheet = sheet;
    d->row = row;
    d->column = col;

    return ret;
}

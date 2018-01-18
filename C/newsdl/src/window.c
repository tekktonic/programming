#include "window.h"
#include "tonic.h"
struct Window_s
{
    SDL_Window *sdlwin;
    const char *title;
    SDL_Renderer *renderer;
    int ow, oh;
    double wScale, hScale;
};

Window new_Window(const char *title, int w, int h, Uint32 flags)
{
    Window ret = malloc(sizeof(struct Window_s));
    
    ret->sdlwin = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
    ret->ow = w;
    ret->oh = h;
    ret->wScale = ret->hScale = 1.0;
    ret->renderer = SDL_CreateRenderer(ret->sdlwin, -1, SDL_RENDERER_ACCELERATED);
    ret->title = title;

    return ret;
}

void Window_blit(Window self, Sprite image)
{
    Rect orig = image->rect;
    SDL_Rect drawRect = {orig.pos.x * self->wScale, orig.pos.y * self->hScale, orig.w * self->wScale, orig.h * self->hScale};

    SDL_Rect draw = {0, 0, 640, 480};
    SDL_RenderCopy(self->renderer, image->tex, NULL, &drawRect);
}

void Window_draw(Window self)
{
    SDL_RenderPresent(self->renderer);
}

void Window_resizedCB(Window self)
{
    int nw, nh;
    SDL_GetWindowSize(self->sdlwin, &nw, &nh);
    self->wScale = (double)nw / (double)self->ow;
    self->hScale = (double)nh / (double)self->oh;
    printf("%f %f\n", self->wScale, self->hScale);
}

SDL_Window *Window_getWindow(Window self)
{
    return self->sdlwin;
}

SDL_Renderer *Window_getRenderer(Window self)
{
    return self->renderer;
}

void H_Window_kill(Window *self)
{
    Window s = *self;
//    SDL_DestroyRenderer(s->renderer);
    s->renderer = NULL;
    printf("%p\n", (s)->renderer);
//    SDL_DestroyWindow(s->sdlwin);
    s->sdlwin = NULL;


    free(s);
}

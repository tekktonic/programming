#include "sprite.h"

void Sprite_kill(Sprite self)
{
    SDL_DestroyTexture(self->tex);
    free(self);
}

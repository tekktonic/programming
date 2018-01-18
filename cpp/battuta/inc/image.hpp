#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

#include "texturewrap.hpp"

class Image
{
public:
    Image(SDL_Rect *position, std::shared_ptr<TextureWrap> tex);
    std::shared_ptr<TextureWrap> tex;
    SDL_Rect position;
};
#endif

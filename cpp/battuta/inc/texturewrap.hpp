#ifndef TEXTUREWRAP_H
#define TEXTUREWRAP_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include "serializable.hpp"

class TextureWrap// : public Serializable
{
    std::string source;
    SDL_Texture *texture;
public:
    std::string serialize();
    SDL_Texture *ref_texture();
    TextureWrap(std::string source);
    ~TextureWrap();
};
#endif

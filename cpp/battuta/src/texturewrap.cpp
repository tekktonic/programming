#include "texturewrap.hpp"

#include "globals.hpp"

TextureWrap::TextureWrap(std::string source)
{
    std::string sourceFile = "resources/images/" + source;

    this->texture = IMG_LoadTexture(renderer, sourceFile.c_str());
    this->source = source;
}

std::string TextureWrap::serialize()
{
    return this->source;
}

SDL_Texture *TextureWrap::ref_texture()
{
    return this->texture;
}

TextureWrap::~TextureWrap()
{
    SDL_DestroyTexture(this->texture);
}

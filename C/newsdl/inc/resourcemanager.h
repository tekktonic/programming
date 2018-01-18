#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <jansson.h>
#include "window.h"
#include "dtype.h"
#include "tonic.h"

typedef Hash *ResourceManager;
ResourceManager new_ResourceManager(void);
void ResourceManager_kill(ResourceManager rm);
SDL_Texture *ResourceManager_loadImage(ResourceManager rm, Window win, const char *image);
json_t *ResourceManager_loadMap(ResourceManager rm, const char *map);
#endif

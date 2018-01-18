#include "resourcemanager.h"
#include "window.h"

enum ResourceType
{
    IMAGE,
    MAP,
    SOUND,
};

ResourceManager new_ResourceManager(void)
{
    ResourceManager ret = malloc(3 * sizeof(Hash));
    for (int i = 0; i <= 3; i++)
    {
	ret[i] = new_Hash();
    }
    return ret;
}

SDL_Texture *ResourceManager_loadImage(ResourceManager rm, Window win, const char *image)
{
    char prefix[] = "resources/images/";
    size_t path_size = strlen(image) + strlen(prefix) + 1;
    char *path = malloc(path_size);
    strncpy(path, prefix, path_size);
    strncat(path, image, path_size);

    if (!Hash_get(rm[IMAGE], image))
    {
	SDL_Texture *tex = IMG_LoadTexture(Window_getRenderer(win), path);
	if (!tex)
	{
	    printf("%s\n", IMG_GetError());
	}
	Hash_insert(rm[IMAGE], image, 
		    (void*)tex);
    }

    return (SDL_Texture*)Hash_get(rm[IMAGE], image);
}

json_t *ResourceManager_loadMap(ResourceManager rm, const char *map)
{
    char prefix[] = "resources/maps/";
    size_t path_size = strlen(map) + strlen(prefix) + 1;
    char *path = malloc(path_size);
    strncpy(path, prefix, path_size);
    strncat(path, map, path_size);

    if (!Hash_get(rm[MAP], map))
    {
	json_error_t error;
	json_t *mapobj = json_load_file(map, 0, &error);
	json_check(mapobj, error);
	assert(json_is_object(mapobj));
	
	Hash_insert(rm[MAP], map, 
		    (void*)mapobj);
    }

    return (json_t*)Hash_get(rm[MAP], map);
}

void mapkill(ResourceManager rm)
{

}
void ResourceManager_kill(ResourceManager rm)
{
    
}

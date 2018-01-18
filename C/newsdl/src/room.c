#include "room.h"
#include "stdio.h"
#define json_value(type, obj, key) json_##type##_value(json_object_get(obj, key));

struct Room_s
{
    List entities;
    Window window;
    Sprite bg;
    int offsetX, offsetY;
    int width, height;
    struct Room_s *lastRoom;
    Entity cameraFocus;
};

int Room_getEntityIdx(Room self, Entity entity) // This is -1 if the entity isn't in.
{
    int idx = 0;
    for (List cur = self->entities->car; cur; cur = cur->car)
    {
	if (entity == (Entity)cur->car)
	    return idx;
	idx++;
    }
    return -1;
}

Room new_Room( ResourceManager rm, Window win, const char *bg, const char *map)
{
    Room ret = malloc(sizeof(*ret));
    ret->bg = malloc(sizeof(Sprite_s));
    ret->window = win;
    

    ret->bg->tex = ResourceManager_loadImage(rm, win, bg);
    ret->bg->rect.pos.x = ret->bg->rect.pos.y = 0;
    ret->bg->rect.w = 640;
    ret->bg->rect.h = 480;
    ret->offsetX = ret->offsetY = 0;
    ret->cameraFocus = NULL;
    ret->entities = new_List(0);

    if (map)
    {
	json_t *maproot, *entities;
	json_error_t jsonError;

	maproot = ResourceManager_loadMap(rm, map);
	ret->width = json_value(integer, maproot, "width");
	ret->width = json_value(integer, maproot, "height");

	entities = json_object_get(maproot, "entities");
	for(unsigned int i = 0; i < json_array_size(entities); i++)
	{
	    json_t *elm, *args;
	    char *type;
	    elm = json_array_get(entities, i);
	    assert(json_is_object(elm));
	    type = (char*)json_value(string, elm, "type");

	    Entity (*constructor)(json_t*);
	    if (constructor = FHash_get(constructors, type))
		constructor(elm);
	}
    }
    return ret;
}

void Room_draw(Room self)
{
    Window_blit(self->window, self->bg);
    for (List cur = self->entities; cur; cur = cur->cdr)
    {
	if ((Entity)cur->car && ((Entity)cur->car)->draw)
	    ((Entity)cur->car)->draw((Entity)cur->car);
    }
    Window_draw(self->window);
}
void Room_update(Room self)
{
    for (List cur = self->entities; cur; cur = cur->cdr)
    {
	if ((Entity)cur->car && ((Entity)cur->car)->update)
	    ((Entity)cur->car)->update((Entity)cur->car);
    }
}
void Room_react(Room self)
{
    for (List cur = self->entities; cur; cur = cur->cdr)
    {
	if ((Entity)cur->car && ((Entity)cur->car)->react)
	    ((Entity)cur->car)->react((Entity)cur->car);
    }
}

void Room_killEntity(Room self, Entity entity)
{
    List_delete(self->entities, Room_getEntityIdx(self, entity), entity->kill);
}

void Room_SpawnEntity(Room self, const char *name, json_t* args)
{
    Entity (*constructor)(json_t*) = FHash_get(constructors, name);
    Entity *val = constructor(args);
    List_enqueue(self->entities, val);
}

void Room_kill(Room *self, enum KillType kt)
{
    Room ptr = *self;
    for (List cur = ptr->entities; cur; cur = cur->cdr)
    {
	if (cur && cur->car)
	    Room_killEntity(ptr, (Entity)cur->car);
    }
    
    Sprite_kill(ptr->bg);
    // everything else is either autocollected or outlives us, so...
    free(*self);
}

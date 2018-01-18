#ifndef ROOM_H
#define ROOM_H
#include <stdbool.h>
#include "entity.h"
#include "resourcemanager.h"
#include "game.h"
#include <jansson.h>
#define MAP_PREFIX "resources/maps/"

struct Room_s;
typedef struct Room_s *Room;

Room new_Room(ResourceManager rm, Window window, const char *bg, const char *map);
void Room_update(Room self);
void Room_react(Room self);
void Room_draw(Room self);
void Room_kill(Room *self, enum KillType kt);
void Room_killEntity(Room self, Entity entity);
void Room_spawnEntity(Room self, const char *name, json_t* args);

#endif

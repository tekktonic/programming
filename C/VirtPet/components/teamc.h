#ifndef TEAMC_H
#define TEAMC_H
#include "../component.h"

typedef enum {
    TEAM_CHANGE
}TeamCEvents;

typedef enum {
    TEAM_NEUTRAL,
    TEAM_PACIFIST,
    TEAM_PLAYER,
    TEAM_ENEMY
}Teams;

Component new_teamc(Teams team);

#endif

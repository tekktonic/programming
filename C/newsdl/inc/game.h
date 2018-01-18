#ifndef GAME_H
#define GAME_H

struct Room_s;
typedef struct Room_s *Room;

enum KillType
{
    NORMAL,
    GAME_KILLED
};

Room currentRoom;
#endif
